/**********************************************************************
 * File:   VectorSufijos.cpp
 * Author: Andrés Gavín Murillo
 * Date:   16/1/20
 * Coms:   
 **********************************************************************/

#include <cassert>
#include <limits>
#include <tuple>
#include "VectorSufijos.hpp"

using namespace std;

/**
 * Devuelve el vector de sufijos de la cadena utilizando el algoritmo Skew.
 * @param cadena
 * @return
 */
vector<uint16_t> vectorSufijos(const vector<uint8_t> &cadena) {
    // Una cadena está formada por un máximo de 65536 Bytes (64 KiB).
    // Con 2 Bytes se pueden direccionar 2^16 posiciones (bytes), es decir, 65536 posiciones. Con 4 Bytes la cadena
    // podría tener un máximo de 2^32 = 4 GiB, por eso se han optado por cadenas de hasta 64 KiB y direccionarlas con
    // enteros de 2 Bytes.
    // El tamaño máximo del vector será de 65536, por lo que en memoria ocupará un máximo de 2 Bytes * 65536 = 128 KiB.
    assert(cadena.size() <= 1 + numeric_limits<uint16_t>::max()); // Max cadena: 64 KiB = 65536 Bytes

    // 1. Inicialización
    vector<uint8_t> s = cadena;
    s.push_back(0);
    s.push_back(0);
    s.push_back(0);
    vector<uint16_t> A(cadena.size()); // Hay tantos sufijos como elementos tenga la cadena

    // 2. Construir el vector de sufijos A¹² para el conjunto S¹² de todos los sufijos cadena(i) donde i mod 3 != 0.
    vector<tuple<uint8_t, uint8_t, uint8_t>> t(1 + (2 * cadena.size()) / 3);
    for (uint32_t i = 0; i < cadena.size() + 1; i++) {
        if (i % 3 != 0)
            t[i] = make_tuple(s[i], s[i+1], s[i+2]);
    }

    // TODO
    return A;
}
