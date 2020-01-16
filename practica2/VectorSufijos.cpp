/******************************************************************************
 * @file    VectorSufijos.cpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Enero 2020
 * @coms    Algoritmia para Problemas Difíciles - Práctica 2
 ******************************************************************************/

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

    // TODO ESTÁ SIN ACABAR, HAY QUE HACERLO


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
    return A;
}
