/******************************************************************************
 * @file    BurrowsWheeler.cpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Enero 2020
 * @coms    Algoritmia para Problemas Difíciles - Práctica 2
 ******************************************************************************/

#include <limits>
#include <cassert>
#include <list>
#include "VectorSufijos.hpp"
#include "BurrowsWheeler.hpp"

using namespace std;

/*
 * Las implementaciones han sido desarrolladas siguiendo el documento publicado por Burrows y Wheeler en May 10, 1994:
 * https://www.hpl.hp.com/techreports/Compaq-DEC/SRC-RR-124.pdf
 */

/*
 * Idea de duplicar la cadena:
 * https://stackoverflow.com/questions/34639854/using-suffix-array-algorithm-for-burrows-wheeler-transform
 */
vector<uint8_t> transformar(const vector<uint8_t> &cadena) {
    assert(cadena.size() < numeric_limits<uint16_t >::max() - 1); // Max cadena: 64 KiB = 65533 Bytes

    vector<uint8_t> bloque;
    bloque.reserve(2 * cadena.size());
    bloque.insert(bloque.begin(), cadena.begin(), cadena.end());
    bloque.insert(bloque.end(), cadena.begin(), cadena.end());

    const vector<uint32_t> vectorSufijos = crearVectorSufijos(bloque);

    vector<uint8_t> transformada(cadena.size() + 2); // Los dos primeros bytes están reservados para I
    uint16_t posicionI = 0;

    uint16_t count = 0;
    for (unsigned int index : vectorSufijos) {
        if (index < cadena.size()) {
            if (index == 0) {
                posicionI = count;
                index = cadena.size();
            }

            transformada[count] = bloque[index - 1];
            count++;
        }
    }

    transformada[cadena.size()] = posicionI & 0xFFu;
    transformada[cadena.size() + 1] = posicionI >> 8u;

    return transformada;
}

vector<uint8_t> revertir(const vector<uint8_t> &transformada) {
    assert(transformada.size() < numeric_limits<uint16_t >::max() + 1); // Max cadena: 64 KiB = 65533 Bytes + 2 bytes I

    vector<uint8_t> cadena(transformada.size() - 2);
    vector<uint16_t> P(cadena.size()), C(1 + numeric_limits<uint8_t>::max(), 0);

    for (uint32_t i = 0; i < cadena.size(); i++) {
        P[i] = C[transformada[i]];
        C[transformada[i]] += 1;
    }

    uint32_t sum = 0;
    for (uint16_t &ch : C) {
        sum += ch;
        ch = sum - ch;
    }

    uint16_t i = ((uint16_t) ((uint16_t)transformada[cadena.size() + 1] << 8u)) | transformada[cadena.size()]; // Posición I
    bool end = false;
    for (uint32_t j = cadena.size() - 1; !end; j--) {
        cadena[j] = transformada[i];
        i = P[i] + C[transformada[i]];
        if (j == 0)
            end = true;
    }

    return cadena;
}


/*
 * https://en.wikipedia.org/wiki/Move-to-front_transform
 */

vector<uint8_t> moveToFront(const vector<uint8_t> &cadena) {
    vector<uint8_t> resultado;
    resultado.reserve(cadena.size());
    list<uint8_t> diccionario;

    // Inicializar diccionario
    for (uint32_t i = 0; i < 256; i++) {
        diccionario.push_back(i);
    }

    list<uint8_t>::iterator it;
    uint8_t rango;
    for (uint8_t c : cadena) {
        bool encontrada = false;
        it = diccionario.begin();
        rango = 0;
        while (!encontrada) {
            if (*it == c) {
                encontrada = true;
            }
            else {
                it++;
                rango++;
            }
        }

        resultado.push_back(rango);

        diccionario.erase(it);
        diccionario.insert(diccionario.begin(), c);
    }

    return resultado;
}

vector<uint8_t> moveToFrontRevertir(const vector<uint8_t> &cadena) {
    vector<uint8_t> resultado;
    resultado.reserve(cadena.size());
    list<uint8_t> diccionario;

    // Inicializar diccionario
    for (uint32_t i = 0; i < 256; i++) {
        diccionario.push_back(i);
    }

    list<uint8_t>::iterator it;
    uint8_t e;
    for (uint8_t rango : cadena) {
        it = diccionario.begin();
        for (uint8_t i = 0; i < rango; i++)
            it++;

        e = *it;
        resultado.push_back(e);

        diccionario.erase(it);
        diccionario.insert(diccionario.begin(), e);
    }

    return resultado;
}
