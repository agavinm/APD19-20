//*****************************************************************
// File:   arbol.cpp
// Author: Andrés Gavín Murillo 716358
// Author: Andrew Mackay 737069
// Date:   Mayo 2019
// Coms:   Algoritmia básica - Práctica 1
//*****************************************************************

#include "arbol.hpp"

using namespace std;

/* Devuelve la frecuencia. */
uint32_t Arbol::frecuencia() const {
    return this->frec;
}

/* Devuelve el byte. */
uint8_t Arbol::obtenerByte() const {
    return this->byte;
}

/* Devuelve cierto si es hoja, falso en caso contrario. */
bool Arbol::esHoja() const {
    return this->hoja;
}

/* Devuelve el hijo izquierdo. */
Arbol* Arbol::izdo() const {
    return this->hijoI;
}

/* Devuelve el hijo derecho. */
Arbol* Arbol::dcho() const {
    return this->hijoD;
}

/* Dado un fichero file, guarda las frecuencias del árbol en dicho fichero y devuelve carácteres que contiene los
 * nodos hoja ordenados según se han guardado en el fichero. Además avanza el iterador hasta donde se ha leido. */
void Arbol::guardarFrecuencias(vector<uint8_t> &salida, queue<uint8_t> &caracteres) const {
    salida.push_back(this->frec >> 24u);
    salida.push_back(this->frec >> 16u);
    salida.push_back(this->frec >> 8u);
    salida.push_back(this->frec);

    if (this->esHoja()) {
        caracteres.push(this->byte);
    }

    if (this->hijoI != nullptr) {
        this->hijoI->guardarFrecuencias(salida, caracteres);
    }
    else {
        uint32_t nulo = 0;
        salida.push_back(nulo >> 24u);
        salida.push_back(nulo >> 16u);
        salida.push_back(nulo >> 8u);
        salida.push_back(nulo);
    }

    if (this->hijoD != nullptr) {
        this->hijoD->guardarFrecuencias(salida, caracteres);
    }
}

/* Dado un fichero file, guarda el árbol en dicho fichero. */
void Arbol::guardar(vector<uint8_t> &salida) const {
    queue<uint8_t> caracteres;
    guardarFrecuencias(salida, caracteres);

    uint32_t nulo = 0;
    salida.push_back(nulo >> 24u);
    salida.push_back(nulo >> 16u);
    salida.push_back(nulo >> 8u);
    salida.push_back(nulo);

    uint8_t c;
    while (!caracteres.empty()) {
        c = caracteres.front();
        caracteres.pop();
        salida.push_back(c);
    }
}

/* Si b es cierto, convierte el árbol en hoja. */
void Arbol::setHoja(uint8_t b) {
    this->hoja = true;
    this->byte = b;
}

/* Dado un fichero file, donde se ha almacenado un árbol mediante la función guardar() y ya se han leído la
 * frecuencias y están en la cola frecuencias, devuelve el árbol p que estaba almacenado en el fichero. */
Arbol* Arbol::leerFrecuencias(const std::vector<uint8_t> &entrada, uint32_t &i, std::queue<uint32_t> &frecuencias, Arbol *const p) {
    Arbol *a = nullptr;

    if (!frecuencias.empty()) {
        uint32_t frecuencia = frecuencias.front();
        frecuencias.pop();

        if (frecuencia != 0) {
            a = new Arbol(frecuencia);
            if (p != nullptr) {
                if (p->hijoI == nullptr) {
                    p->hijoI = a;
                } else {
                    p->hijoD = a;
                }
            }

            if (frecuencias.front() == 0) { // Es una hoja
                frecuencias.pop();
                uint8_t caracter = entrada[i];
                i++;
                a->setHoja(caracter);
            }
            else {
                leerFrecuencias(entrada, i, frecuencias, a); // Hijo izquierdo
                leerFrecuencias(entrada, i, frecuencias, a); // Hijo derecho
            }
        }
    }

    return a;
}

Arbol::Arbol(const std::vector<uint8_t> &entrada, uint32_t &i) {
    queue<uint32_t> frecuencias;
    uint32_t frecuencia;
    bool nulo = false, fin = false;

    // Leer frecuencias
    while (!nulo || !fin) {
        frecuencia = uint32_t((uint8_t)(entrada[i]) << 24u |
                    (uint8_t)(entrada[i + 1]) << 16u |
                    (uint8_t)(entrada[i + 2]) << 8u |
                    (uint8_t)(entrada[i + 3]));
        i += 4;

        frecuencias.push(frecuencia);

        if (frecuencia == 0) {
            if (nulo)
                fin = true;
            else
                nulo = true;
        }
        else {
            nulo = false;
        }
    }

    Arbol *a = nullptr;
    a = leerFrecuencias(entrada, i, frecuencias, a);

    if (a != nullptr) {
        this->frec = a->frec;
        this->byte = a->byte;
        this->hoja = a->hoja;
        this->hijoI = a->hijoI;
        this->hijoD = a->hijoD;
    }
    else {
        this->frec = -1;
        this->byte = 0;
        this->hoja = false;
        this->hijoI = nullptr;
        this->hijoD = nullptr;
    }
}
