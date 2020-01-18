//*****************************************************************
// File:   arbol.hpp
// Author: Andrés Gavín Murillo 716358
// Author: Andrew Mackay 737069
// Date:   Mayo 2019
// Coms:   Algoritmia básica - Práctica 1
//*****************************************************************

#ifndef PRACTICA1_ARBOL_HPP
#define PRACTICA1_ARBOL_HPP

#include <queue>
#include <cstdint>
#include <vector>


class Arbol {
private:
    uint16_t frec; // clave: frecuencia
    bool hoja; // true si es árbol hoja; false en caso contrario
    uint8_t byte; // valor: byte al que corresponde (sólo si es nodo hoja)
    Arbol *hijoI, *hijoD;

    /* Dado un vector de salida, guarda las frecuencias del árbol y devuelve carácteres que contiene los
     * nodos hoja ordenados según se han guardado. */
    void guardarFrecuencias(std::vector<uint8_t> &salida, std::queue<uint8_t> &caracteres) const;

    /* Si b es cierto, convierte el árbol en hoja. */
    void setHoja(uint8_t b);

    /* Dado un vector de entrada, donde se ha almacenado un árbol mediante la función guardar() y ya se han leído la
     * frecuencias y están en la cola frecuencias, devuelve el árbol p que estaba almacenado. */
    Arbol* leerFrecuencias(const std::vector<uint8_t> &entrada, uint16_t &i, std::queue<uint16_t> &frecuencias, Arbol *const p);

    explicit Arbol(uint16_t frecuencia) : // Constructor intermedio, el árbol no es válido
            frec(frecuencia), hoja(false), byte(0), hijoI(nullptr), hijoD(nullptr) {}

public:
    Arbol(Arbol &hijoIzquierdo, Arbol &hijoDerecho) : // Constructor del árbol con hijos
            frec(hijoIzquierdo.frecuencia() + hijoDerecho.frecuencia()), hoja(false), byte(0), hijoI(&hijoIzquierdo),
            hijoD(&hijoDerecho) {}

    Arbol(const uint16_t frecuencia, const uint8_t byte) : // Constructor del árbol hoja
            frec(frecuencia), hoja(true), byte(byte), hijoI(nullptr), hijoD(nullptr) {}

    explicit Arbol(const std::vector<uint8_t> &entrada, uint16_t &i); // Constructor del árbol desde el vector generado por la función guardar

    /* Devuelve el hijo izquierdo. */
    Arbol* izdo() const;

    /* Devuelve el hijo derecho. */
    Arbol* dcho() const;

    /* Devuelve la frecuencia. */
    uint16_t frecuencia() const;

    /* Devuelve el byte. */
    uint8_t obtenerByte() const;

    /* Devuelve cierto si es hoja, falso en caso contrario. */
    bool esHoja() const;

    /* Dado un fichero file, guarda el árbol en dicho fichero. */
    void guardar(std::vector<uint8_t> &salida) const;
};


#endif //PRACTICA1_ARBOL_HPP
