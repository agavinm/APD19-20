/******************************************************************************
 * @file    main.cpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Diciembre 2019
 * @coms    Algoritmia para Problemas Difíciles - Práctica 1
 ******************************************************************************/

#include <iostream>
#include <array>
#include <map>
#include <limits>
#include <cmath>
#include <random>
//#include <iomanip>
#include "ConjuntoProductos.hpp"

using namespace std;

void generarDatosPrueba(const string &f) {
    int numProd = 1000;
    const array<float, 11> p = {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f}; // probabilidades de que dos productos se hayan comprado juntos

    int r = 0;
    for (float i : p) {
        string f1 = f + "f1_" + to_string(numProd) + "_" + to_string(i).substr(0, 3) + ".txt";
        string f2 = f + "f2_" + to_string(numProd) + "_" + to_string(i).substr(0, 3) + ".txt";

        ConjuntoProductos *cp;
        if (r % 2 != 0)
            cp = new ConjuntoProductos(numProd);
        else
            cp = new ConjuntoProductos(numProd, i);

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
 * https://en.wikipedia.org/wiki/Karger%27s_algorithm
 * @param cp
 * @return
 */
pair<map<uint32_t, uint32_t>, map<uint32_t, uint32_t>> corteMinimo(const ConjuntoProductos &cp) {
    const vector<uint32_t> &compradosJuntos = cp.getCompradosJuntos();
    const uint32_t numProductos = cp.getProductos().size(); // n

    pair<map<uint32_t, uint32_t>, map<uint32_t, uint32_t>> corte;
    uint32_t aristasCorte = numeric_limits<uint32_t>::max(); // Se inicializa a "infinito"
    const uint32_t T = log(numProductos) * ((double) (numProductos * (numProductos - 1)) / 2);

    vector<map<uint32_t, uint32_t>> nodos;
    nodos.reserve(numProductos);
    for (uint32_t i = 0; i < numProductos; i++) {
        map<uint32_t, uint32_t> m;
        m.emplace(i, i);
        nodos.push_back(m);
    }

    random_device rd;
    mt19937 mt(rd());

    // Repetir T veces
    for (uint32_t i = 0; i < T; i++) {
        vector<map<uint32_t, uint32_t>> nodosAux = nodos; // O(n)

        // Algoritmo de Karger O(n²)
        while (nodosAux.size() > 2) { // O(n)
            uniform_int_distribution<uint32_t> randDist(0, nodosAux.size() - 1);
            uint32_t nodoA = randDist(mt), nodoB = randDist(mt);
            while (nodoA == nodoB) {
                nodoB = randDist(mt);
            }

            // O(n)
            nodosAux[nodoA].insert(nodosAux[nodoB].begin(), nodosAux[nodoB].end());
            nodosAux.erase(nodosAux.begin() + nodoB);
        }

        uint32_t aristasCorteAux = 0;
        for (pair <uint32_t, uint32_t> nodoA : nodosAux[0]) {
            for (pair <uint32_t, uint32_t> nodoB : nodosAux[1]) {
                aristasCorteAux += compradosJuntos[posCompradosJuntosAux(nodoA.first, nodoB.first, numProductos)];
            }
        }

        if (aristasCorteAux < aristasCorte) {
            aristasCorte = aristasCorteAux;
            corte = {nodosAux[0], nodosAux[1]};
        }

        //cout <<'\r' << setprecision(2) << setw(6) << (float) i / T << "%" << flush;
    }

    return corte;
}

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        cout << "Uso:" << endl;
        cout << '\t' << "Generar datos de prueba: " << argv[0] << " <directorioDondeGenerar>" << endl;
        cout << '\t' << "Resolver productos: " << argv[0] << " <ficheroProductos> <ficheroCompradosJuntos>" << endl;
        return 0;
    }

    if (argc == 2) {
        string f(argv[1]);
        if (f[f.length() - 1] != '/')
            f += '/';
        generarDatosPrueba(f);
        return 0;
    }

    ConjuntoProductos cp(argv[1], argv[2]);
    if (cp.getProductos().size() < 2) {
        cerr << "Se necesita al menos un conjunto de 2 productos." << endl;
        return 1;
    }
    pair<map<uint32_t, uint32_t>, map<uint32_t, uint32_t>> corte = corteMinimo(cp);
    cout << corte.first.size() << endl << corte.second.size() << endl;

    return 0;
}