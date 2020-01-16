/******************************************************************************
 * @file    BurrowsWheeler.cpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Enero 2020
 * @coms    Algoritmia para Problemas Difíciles - Práctica 2
 ******************************************************************************/

#include <limits>
#include "BurrowsWheeler.hpp"

using namespace std;

/*
 * Las implementaciones han sido desarrolladas siguiendo el documento publicado por Burrows y Wheeler en May 10, 1994:
 * https://www.hpl.hp.com/techreports/Compaq-DEC/SRC-RR-124.pdf
 */

pair<vector<uint8_t>, uint16_t> transformar(const vector<uint16_t> &vectorSufijos, const vector<uint8_t> &cadena) {
    vector<uint8_t> transformada(cadena.size());
    uint16_t posicionI;

    for (uint32_t i = 0; i < vectorSufijos.size(); i++) {
        if (vectorSufijos[i] == 0) {
            posicionI = i;
            transformada[i] = cadena[cadena.size() - 1];
        }
        else {
            transformada[i] = cadena[vectorSufijos[i] - 1];
        }
    }

    return make_pair(transformada, posicionI);
}

vector<uint8_t> revertir(const vector<uint8_t> &transformada, const uint16_t posicionI) {
    vector<uint8_t> cadena(transformada.size());
    vector<uint32_t> P(transformada.size()), C(numeric_limits<uint8_t>::max() + 1, 0);

    for (uint32_t i = 0; i < transformada.size(); i++) {
        P[i] = C[transformada[i]];
        C[transformada[i]] += 1;
    }

    uint32_t sum = 0;
    for (uint32_t &ch : C) {
        sum += ch;
        ch = sum - ch;
    }

    uint16_t i = posicionI;
    bool end = false;
    for (uint32_t j = transformada.size() - 1; !end; j--) {
        cadena[j] = transformada[i];
        i = P[i] + C[transformada[i]];
        if (j == 0)
            end = true;
    }

    return cadena;
}
