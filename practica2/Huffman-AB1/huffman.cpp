//*****************************************************************
// File:   huffman.cpp
// Author: Andrés Gavín Murillo 716358
// Author: Andrew Mackay 737069
// Date:   Mayo 2019
// Coms:   Algoritmia básica - Práctica 1
//*****************************************************************

#include <queue>
#include "huffman.hpp"
#include "arbol.hpp"
#include "heap.hpp"

using namespace std;

/* Dado un fichero file y N el número de carácteres posibles, devuelve una cola de árboles hoja, donde cada hoja
 * contiene su símbolo y su frecuencia */
void calcularFrecuencias(const vector<uint8_t> &cadena, queue<Arbol*> &caracteres, const uint16_t N) {
    uint16_t frecuencias[N];
    for (uint16_t &frecuencia : frecuencias) {
        frecuencia = 0;
    }

    // Calcular frecuencias
    for (uint8_t caracter : cadena) {
        frecuencias[caracter]++;
    }

    uint8_t caracter = 0;
    for (uint16_t &frecuencia : frecuencias) {
        if (frecuencia > 0) {
            caracteres.push(new Arbol(frecuencia, caracter));
        }
        caracter++;
    }
}

/* Dada una cola de árboles hoja c, donde cada hoja contiene su símbolo y su frecuencia, devuelve el árbol
 * lexicográfico de un código libre de prefijos óptimo resultante de aplicar el algoritmo de Huffman. */
Arbol* huffman(queue<Arbol*> &c) {
    /* Paso 1: Crear heap de los árboles hoja de v.
     * Paso 2: Aplicar algoritmo de Huffman.
     * Paso 3: Devolver el único árbol que contiene el heap. */
    Heap q;
    Arbol *z, *x, *y;
    int tam = c.size();

    // Paso 1
    while (!c.empty()) {
        x = c.front();
        c.pop();
        q.insertar(*x);
    }

    // Paso 2
    for (int i=1; i<tam; i++) {
        x = q.primero();
        y = q.primero();
        z = new Arbol(*x, *y);
        q.insertar(*z);
    }

    // Paso 3
    z = q.primero();
    return z;
}

/* Dado un árbol lexicográfico a de un código libre de prefijos y un vector vacío acumulados, devuelve la tabla de
 * codificación tabla. */
void tablaCodificacion(const Arbol *const a, vector<vector<bool>*> &tabla, vector<bool> &acumulados) {
    if (a != nullptr) {
        if (a->esHoja()) {
            tabla[a->obtenerByte()] = new vector<bool> (acumulados);
        }
        else {
            acumulados.push_back(false); // false = 0
            tablaCodificacion(a->izdo(), tabla, acumulados);
            acumulados.pop_back();

            acumulados.push_back(true); // true = 1
            tablaCodificacion(a->dcho(), tabla, acumulados);
            acumulados.pop_back();
        }
    }
}

vector<uint8_t> comprimir(const vector<uint8_t> &cadena) {
    vector<uint8_t> resultado;

    // Obtener frecuencias
    const uint16_t N = 256; // Número de caracteres posibles
    queue<Arbol*> q;
    calcularFrecuencias(cadena, q, N);

    // Obtener arbol de huffman
    Arbol *a = huffman(q);

    // Obtener tabla de codificación
    vector<vector<bool>*> tabla(N, nullptr);
    vector<bool> acumulados;
    tablaCodificacion(a, tabla, acumulados);

    // Guardar arbol de huffman
    a->guardar(resultado);

    // Comprimir fichero
    queue<bool> byte;
    vector<bool> *codigo;
    uint8_t numBit;
    for (uint8_t caracter : cadena) {
        codigo = tabla[caracter];

        for (bool b : *codigo) {
            byte.push(b);
            if (byte.size() == 8) { // 1 byte (char) = 8 bits
                caracter = 0;
                numBit = 0;
                while (!byte.empty()) {
                    if (byte.front()) { // true = 1
                        caracter |= 1u << numBit;
                    }
                    byte.pop();
                    numBit++;
                }
                resultado.push_back(caracter);
            }
        }
    }

    // Indicar los bits que se han quedado sueltos (no llegan a 1 byte)
    uint8_t caracter = 0, sueltos = byte.size();
    if (sueltos > 0) {
        while (!byte.empty()) {
            caracter = 0;
            numBit = 8-sueltos;
            while (!byte.empty()) {
                if (byte.front()) { // true = 1
                    caracter |= 1u << numBit;
                }
                byte.pop();
                numBit++;
            }
        }
    }
    resultado.push_back(caracter); // Escribir los últimos bits
    resultado.push_back(sueltos); // Escribir el número de bits sueltos

    return resultado;
}

vector<uint8_t> descomprimir(const vector<uint8_t> &cadena) {
    vector<uint8_t> resultado;

    // Obtener arbol de huffman
    uint16_t i = 0;
    Arbol *a = new Arbol(cadena, i);

    // Descomprimir fichero
    uint8_t caracter, caracterSiguiente, caracterSiguienteSiguiente, caracterAux, numBit;
    Arbol *aux = a;

    if (cadena.size() - i > 1) {
        caracter = cadena[i];
        i++;
        caracterSiguiente = cadena[i];
        i++;

        for (uint32_t j = i; j < cadena.size(); j++) {
            caracterSiguienteSiguiente = cadena[j];

            numBit = 0;
            while (numBit<8) {
                if (((uint8_t)(caracter >> numBit) & 1u) == 1u) {
                    aux = aux->dcho();
                }
                else {
                    aux = aux->izdo();
                }

                if (aux->esHoja()) {
                    caracterAux = aux->obtenerByte();
                    resultado.push_back(caracterAux);
                    aux = a;
                }

                numBit++;
            }

            caracter = caracterSiguiente;
            caracterSiguiente = caracterSiguienteSiguiente;
        }
        numBit = 8-caracterSiguiente;
        while (numBit<8) {
            if (((uint8_t)(caracter >> numBit) & 1u) == 1u) {
                aux = aux->dcho();
            }
            else {
                aux = aux->izdo();
            }

            if (aux->esHoja()) {
                caracterAux = aux->obtenerByte();
                resultado.push_back(caracterAux);
                aux = a;
            }

            numBit++;
        }
    }

    return resultado;
}