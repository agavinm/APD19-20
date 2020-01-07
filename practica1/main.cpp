/******************************************************************************
 * @file    main.cpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Enero 2020
 * @coms    Algoritmia para Problemas Difíciles - Práctica 1
 ******************************************************************************/

#include <iostream>
#include <array>
#include <map>
#include <limits>
#include <cmath>
#include <random>
#include <chrono>
#include <iomanip>
#include "ConjuntoProductos.hpp"

using namespace std;

/**
 * Genera los ficheros de prueba entregados en la parte 1 de la práctica
 * @param f
 * @param maxJuntos
 */
void generarDatosPrueba(const string &f, const uint32_t maxJuntos) {
    int numProd = 1000;
    // probabilidades de que dos productos se hayan comprado juntos
    const array<float, 11> p = {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f};

    int r = 0;
    for (float i : p) {
        string f1 = f + "f1_" + to_string(numProd) + "_" + to_string(i).substr(0, 3) + ".txt";
        string f2 = f + "f2_" + to_string(numProd) + "_" + to_string(i).substr(0, 3) + ".txt";

        ConjuntoProductos *cp;
        if (r % 2 != 0)
            cp = new ConjuntoProductos(numProd, maxJuntos);
        else
            cp = new ConjuntoProductos(numProd, i, maxJuntos);

        cp->save(f1, f2, r % 2 != 0);
        ConjuntoProductos aux(f1, f2);
        if (*cp == aux)
            cout << i << ": Correcto" << endl;
        else
            cout << i << ": Distintos" << endl;

        delete(cp);
        r++;
    }
}

/**
 * Algoritmo de corte mínimo basado en iterar el algoritmo de Karger T veces con coste O(T * n²)
 * https://en.wikipedia.org/wiki/Karger%27s_algorithm
 * @param cp
 * @param T
 * @return
 */
tuple<map<uint32_t, uint32_t>, map<uint32_t, uint32_t>, uint32_t> corteMinimo(const ConjuntoProductos &cp, const uint32_t T) {
    const vector<uint32_t> &compradosJuntos = cp.getCompradosJuntos(); // Matriz de adyacencia del grafo
    const uint32_t numProductos = cp.getProductos().size(); // n

    tuple<map<uint32_t, uint32_t>, map<uint32_t, uint32_t>, uint32_t> corte; // <conjunto1, conjunto2, aristas>
    uint32_t aristasCorte = numeric_limits<uint32_t>::max(); // Se inicializa a "infinito"

    vector<map<uint32_t, uint32_t>> nodos; // Vector de nodos del grafo. Cada nodo es un mapa de los nodos originales,
    // ya que, en el algoritmo de Karger en cada iteración se fusionan dos nodos en uno.
    nodos.reserve(numProductos);
    for (uint32_t i = 0; i < numProductos; i++) { // Coste O(n)
        map<uint32_t, uint32_t> m;
        m.emplace(i, i);
        nodos.push_back(m);
    }

    random_device rd;
    mt19937 mt(rd());

    // Repetir T veces, coste O(T * n²)
    for (uint32_t i = 0; i < T; i++) {
        vector<map<uint32_t, uint32_t>> nodosAux = nodos; // O(n)

        // Algoritmo de Karger, coste O(n²)
        while (nodosAux.size() > 2) { // O(n)
            uniform_int_distribution<uint32_t> randDist(0, nodosAux.size() - 1);
            uint32_t nodoA = randDist(mt), nodoB = randDist(mt); // Se eligen dos nodos aleatorios para fusionar
            while (nodoA == nodoB) { // Los nodos deben de ser diferentes
                nodoB = randDist(mt);
            }

            // Coste O(n)
            nodosAux[nodoA].insert(nodosAux[nodoB].begin(), nodosAux[nodoB].end()); // El nodo resultate contiene los
            // nodos originales de los dos nodos fusionados
            nodosAux.erase(nodosAux.begin() + nodoB); // Se elimina el nodoB que se ha fusionado en el nodoA
        }

        uint32_t aristasCorteAux = 0; // Aristas que separan los dos conjuntos, coste O(n²)
        for (pair <uint32_t, uint32_t> nodoA : nodosAux[0]) { // Nodos del conjunto 1
            for (pair <uint32_t, uint32_t> nodoB : nodosAux[1]) { // Nodos del conjunto 2
                // Las aristas que separan los conjuntos son la suma de todas las aristas que unen cada nodo del
                // conjunto 1 con los nodos del conjunto 2
                aristasCorteAux += compradosJuntos[posCompradosJuntosAux(nodoA.first, nodoB.first, numProductos)];
            }
        }

        if (aristasCorteAux < aristasCorte) { // Guarda el corte con menor número de aristas que separan los conjuntos
            aristasCorte = aristasCorteAux;
            corte = {nodosAux[0], nodosAux[1], aristasCorte};
        }
    }

    return corte;
}

/**
 * Programa que genera conjuntos de productos de prueba y resuelve el corte mínimo dado un conjunto de productos.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
    if (argc != 3 && argc != 4) {
        cout << "Uso:" << endl;
        cout << '\t' << "Generar datos de prueba: " << argv[0] << " <directorioDondeGenerar> <maxJuntos>" << endl;
        cout << '\t' << '\t' << "<maxJuntos> = <natural> => Número máximo de veces que dos productos se han podido comprar juntos." << endl;
        cout << '\t' << "Resolver productos: " << argv[0] << " <ficheroProductos> <ficheroCompradosJuntos> <T>" << endl;
        cout << '\t' << '\t' << "<T> = max => Iteraciones para alcanzar óptimo con alta probabilidad." << endl;
        cout << '\t' << '\t' << "<T> = <natural> => Iteraciones introducidas por el usuario." << endl;
        return 0;
    }

    if (argc == 3) { // Genera los conjuntos de productos de prueba
        string f(argv[1]);
        if (f[f.length() - 1] != '/')
            f += '/';
        generarDatosPrueba(f, stoul(argv[2]));
        return 0;
    }

    // Resuelve el corte mínimo dado un conjunto de productos.
    ConjuntoProductos cp(argv[1], argv[2]); // Lee el conjunto de productos de los ficheros de entrada
    if (cp.getProductos().size() < 2) {
        cerr << "Se necesita al menos un conjunto de 2 productos." << endl;
        return 1;
    }
    cout << "Número de productos: " << cp.getProductos().size() << endl;

    chrono::high_resolution_clock::time_point startTime = chrono::high_resolution_clock::now();

    tuple<map<uint32_t, uint32_t>, map<uint32_t, uint32_t>, uint32_t> corte;
    string sT(argv[3]);
    uint32_t T;
    if (sT == "max") {
        T = log(cp.getProductos().size()) *
                     ((double) (cp.getProductos().size() * (cp.getProductos().size() - 1)) / 2);
        cout << "Iterando el algoritmo de Karger " << T << " veces para alcanzar óptimo con alta probabilidad." << endl;
    }
    else {
        T = stoul(sT);
        cout << "Iterando el algoritmo de Karger " << T << " veces indicadas por el usuario." << endl;
    }
    corte = corteMinimo(cp, T); // Resuelve el corte mínimo del conjunto de productos

    // Funciones para mostrar información del tiempo
    auto dur = chrono::high_resolution_clock::now() - startTime;
    auto h = chrono::duration_cast<chrono::hours>(dur);
    auto m = chrono::duration_cast<chrono::minutes>(dur -= h);
    auto s = chrono::duration_cast<chrono::seconds>(dur -= m);
    auto ms = chrono::duration_cast<chrono::milliseconds>(dur -= s);

    cout << "Corte realizado en ";
    if (h.count() != 0) {
        cout << h.count() << "d ";
    }
    if (m.count() != 0) {
        cout << m.count() << "m ";
    }
    cout << s.count() << "," << setfill('0') << setw(3) << ms.count() << "s." << endl;

    cout << '\t' << "Conjunto 1 con " << get<0>(corte).size() << " nodos:" << endl;
    cout << '\t' << '\t';
    for (pair<uint32_t, uint32_t> p : get<0>(corte)) {
        cout << p.first << " ";
    }
    cout << endl;

    cout << '\t' << "Conjunto 2 con " << get<1>(corte).size() << " nodos:" << endl;
    cout << '\t' << '\t';
    for (pair<uint32_t, uint32_t> p : get<1>(corte)) {
        cout << p.first << " ";
    }
    cout << endl;

    cout << '\t' << "Número de aristas que separan los dos conjuntos: " << get<2>(corte) << endl;

    return 0;
}