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

vector<uint8_t> transformar(const vector<uint16_t> &vectorSufijos, const vector<uint8_t> &cadena) {
    vector<uint8_t> transformada(cadena.size() + 2); // Los dos primeros bytes están reservados para I
    uint16_t posicionI = 0;

    for (uint32_t i = 0; i < vectorSufijos.size(); i++) {
        if (vectorSufijos[i] == 0) {
            posicionI = i;
            transformada[i + 2] = cadena[cadena.size() - 1];
        }
        else {
            transformada[i + 2] = cadena[vectorSufijos[i] - 1];
        }
    }

    transformada[0] = posicionI & 0xFFu;
    transformada[1] = posicionI >> 8u;

    return transformada;
}

vector<uint8_t> revertir(const vector<uint8_t> &transformada) {
    vector<uint8_t> cadena(transformada.size() - 2);
    vector<uint32_t> P(cadena.size()), C(1 + numeric_limits<uint8_t>::max(), 0);

    for (uint32_t i = 0; i < cadena.size(); i++) {
        P[i] = C[transformada[i + 2]];
        C[transformada[i + 2]] += 1;
    }

    uint32_t sum = 0;
    for (uint32_t &ch : C) {
        sum += ch;
        ch = sum - ch;
    }

    uint16_t i = ((uint16_t) ((uint16_t)transformada[1] << 8u)) | transformada[0]; // Posición I
    bool end = false;
    for (uint32_t j = cadena.size() - 1; !end; j--) {
        cadena[j] = transformada[i + 2];
        i = P[i] + C[transformada[i + 2]];
        if (j == 0)
            end = true;
    }

    return cadena;
}
