/******************************************************************************
 * @file    ConjuntoProductos.hpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío
 * @date    Diciembre 2019
 * @coms    Algoritmia para Problemas Difíciles - Práctica 1
 ******************************************************************************/

#include <random>
#include <iostream>
#include <fstream>
#include "ConjuntoProductos.hpp"

#define MAX_NOMBRE 20
#define MAX_UNIDADES 1000000
#define MAX_PRECIO 100000

using namespace std;

ConjuntoProductos::ConjuntoProductos(int numProductos) {
    this->productos.reserve(numProductos);
    int compradosJuntosTam = (numProductos * numProductos - numProductos) / 2;
    this->compradosJuntos.reserve(compradosJuntosTam);

    random_device rd;
    mt19937 mt(rd());

    // Generar la información de los productos
    uniform_int_distribution<char> distLetra('A', 'Z');
    uniform_int_distribution<int> distNombre(1, MAX_NOMBRE);
    uniform_int_distribution<int> distUnidades(1, MAX_UNIDADES);
    uniform_real_distribution<float> distPrecio(1, MAX_PRECIO);

    for (int i = 0; i < numProductos; i++) {
        string nombre;
        int maxNombre = distNombre(mt);
        for (int j = 0; j < maxNombre; j++)
            nombre.push_back(distLetra(mt));

        Producto producto(nombre, distUnidades(mt), distPrecio(mt));
        this->productos.push_back(producto);
    }

    // Generar la matriz de compradosJuntos
    uniform_real_distribution<float> distProbV(0.3f, 0.7f);
    float probV = distProbV(mt);

    uniform_real_distribution<float> distProb(0, 1);
    for (int i = 0; i < compradosJuntosTam; i++)
        this->compradosJuntos.push_back(probV < distProb(mt));
}

const std::vector<Producto> &ConjuntoProductos::getProductos() const {
    return productos;
}

void ConjuntoProductos::save(const string &fout1, const string &fout2) const {
    // Abrir primer fichero de salida
    ofstream f1(fout1);
    if (!f1.is_open()) {
        cerr << "Error al abrir el fichero " << fout1 << endl;
        exit(1);
    }
    for (const Producto &p : this->productos)
        f1 << p << endl;

    // Abrir segundo fichero de salida
    ofstream f2(fout2);
    if (!f2.is_open()) {
        cerr << "Error al abrir el fichero " << fout2 << endl;
        exit(1);
    }
    f2 << this->productos.size() << endl;
    for (int i = 0; i < this->productos.size(); i++)
        for (int j = 0; j < this->productos.size(); j++) {
            if (i == j)
                f2 << true;
            else if (i < j)
                // TODO here
        }
}
