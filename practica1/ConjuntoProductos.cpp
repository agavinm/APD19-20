/******************************************************************************
 * @file    ConjuntoProductos.hpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Diciembre 2019
 * @coms    Algoritmia para Problemas Difíciles - Práctica 1
 ******************************************************************************/

#include <random>
#include <iostream>
#include <fstream>
#include "ConjuntoProductos.hpp"

// Valores máximos para generar aleatorios
#define MAX_NOMBRE 20
#define MAX_UNIDADES 1000000
#define MAX_PRECIO 100000
#define MAX_SPACES 5

using namespace std;

void ConjuntoProductos::generarConjuntoProductos(uint32_t numProductos, float probV) {
    this->productos.reserve(numProductos);
    uint32_t compradosJuntosTam = (numProductos * numProductos - numProductos) / 2;
    this->compradosJuntos.reserve(compradosJuntosTam);

    random_device rd;
    mt19937 mt(rd());

    // Generar la información de los productos
    uniform_int_distribution<char> distLetra('A', 'Z');
    uniform_int_distribution<uint32_t> distNombre(1, MAX_NOMBRE);
    uniform_int_distribution<uint32_t> distUnidades(1, MAX_UNIDADES);
    uniform_real_distribution<float> distPrecio(1, MAX_PRECIO);

    for (uint32_t i = 0; i < numProductos; i++) {
        string nombre;
        uint32_t maxNombre = distNombre(mt);
        for (uint32_t j = 0; j < maxNombre; j++)
            nombre.push_back(distLetra(mt));

        Producto producto(nombre, distUnidades(mt), distPrecio(mt));
        this->productos.push_back(producto);
    }

    // Generar la matriz de compradosJuntos
    uniform_real_distribution<float> distProb(0, 1);
    for (uint32_t i = 0; i < compradosJuntosTam; i++)
        this->compradosJuntos.push_back(probV >= distProb(mt));
}

ConjuntoProductos::ConjuntoProductos(uint32_t numProductos, float probV) {
    generarConjuntoProductos(numProductos, probV);
}

ConjuntoProductos::ConjuntoProductos(uint32_t numProductos) {
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<float> distProbV(0.3f, 0.7f);

    generarConjuntoProductos(numProductos, distProbV(mt));
}

uint32_t posCompradosJuntosAux(uint32_t i, uint32_t j, uint32_t numProductos) {
    // Posición si se almacenara toda la matriz: n * i + j
    // Número de elementos en el triángulo inferior de la matriz incluyendo la diagonal hasta (i,j): Suma de progresión
    // aritmética siendo a1 = 1, an = i + 1, y n = i + 1.
    return numProductos * i + j - ((i + 2) * (i + 1) / 2);
}

uint32_t ConjuntoProductos::posCompradosJuntos(uint32_t i, uint32_t j) const {
    // Posición si se almacenara toda la matriz: n * i + j
    // Número de elementos en el triángulo inferior de la matriz incluyendo la diagonal hasta (i,j): Suma de progresión
    // aritmética siendo a1 = 1, an = i + 1, y n = i + 1.
    return posCompradosJuntosAux(i, j, (uint32_t) this->productos.size());
}

ConjuntoProductos::ConjuntoProductos(const std::string &fin1, const std::string &fin2) {
    // Abrir segundo fichero de entrada
    ifstream f2(fin2);
    if (!f2.is_open()) {
        cerr << "Error al abrir el fichero " << fin2 << endl;
        exit(1);
    }
    uint32_t numProductos;
    f2 >> numProductos;
    uint32_t compradosJuntosTam = (numProductos * numProductos - numProductos) / 2;
    this->compradosJuntos.reserve(compradosJuntosTam);
    uint32_t val;
    for (uint32_t i = 0; i < numProductos; i++)
        for (uint32_t j = 0; j < numProductos; j++) {
            f2 >> val;
            if (i == j && val != 1) {
                cerr << "Error en el formato del fichero " << fin2 << ", en la posición i=" << i << ", j=" << j << endl;
                exit(1);
            }
            else if (i < j)
                this->compradosJuntos.push_back(val);
            else if (j < i && val != this->compradosJuntos[posCompradosJuntosAux(j, i, numProductos)]) {
                cerr << "Error en el formato del fichero " << fin2 << ", en la posición i=" << i << ", j=" << j << endl;
                exit(1);
            }
        }

    // Abrir primer fichero de entrada
    ifstream f1(fin1);
    if (!f1.is_open()) {
        cerr << "Error al abrir el fichero " << fin1 << endl;
        exit(1);
    }
    this->productos.reserve(numProductos);
    string nombre;
    uint32_t unidades;
    float precio;
    f1 >> nombre >> unidades >> precio;
    while (!f1.eof()) {
        Producto p(nombre, unidades, precio);
        this->productos.push_back(p);
        f1 >> nombre >> unidades >> precio;
    }
}

const std::vector<Producto> &ConjuntoProductos::getProductos() const {
    return productos;
}

void ConjuntoProductos::save(const string &fout1, const string &fout2, bool randomSpaces) const {
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
    for (uint32_t i = 0; i < (uint32_t) this->productos.size(); i++) {
        for (uint32_t j = 0; j < (uint32_t) this->productos.size(); j++) {
            if (!randomSpaces && j != 0)
                f2 << " ";

            if (i == j)
                f2 << true;
            else if (i < j)
                f2 << this->compradosJuntos[this->posCompradosJuntos(i, j)];
            else
                f2 << this->compradosJuntos[this->posCompradosJuntos(j, i)];

            if (randomSpaces) {
                random_device rd;
                mt19937 mt(rd());
                uniform_int_distribution<uint32_t> distSpaces(1, MAX_SPACES);
                uniform_real_distribution<float> distProb(0, 1);
                uint32_t numSpaces = distSpaces(mt);
                float prob = distProb(mt);

                for (uint32_t s = 0; s < numSpaces; s++) {
                    if (prob < 0.333f)
                        f2 << ' ';
                    else if (prob < 0.666f)
                        f2 << '\t';
                    else
                        f2 << endl;
                }
            }
        }
        if (!randomSpaces && i != (uint32_t) this->productos.size() - 1)
            f2 << endl;
    }
}

void ConjuntoProductos::save(const string &fout1, const string &fout2) const {
    this->save(fout1, fout2, false);
}

bool ConjuntoProductos::operator==(const ConjuntoProductos &rhs) const {
    return productos == rhs.productos &&
           compradosJuntos == rhs.compradosJuntos;
}

bool ConjuntoProductos::operator!=(const ConjuntoProductos &rhs) const {
    return !(rhs == *this);
}
