/******************************************************************************
 * @file    VectorSufijos.cpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Enero 2020
 * @coms    Algoritmia para Problemas Difíciles - Práctica 2
 ******************************************************************************/

#include <cassert>
#include <limits>
#include <algorithm>
#include "VectorSufijos.hpp"

using namespace std;

/**
 *  Representacion de un sufijo mediante su indice
 *  y un ranking
 */
class Suffix {
public:
    uint32_t i;
    int rank[2];
};

/**
 * Funcion para comparar sufijos
 * @param
 * @param b
 * @return
 */
int cmp(const Suffix &a, const Suffix &b) {
    if (a.rank[0] == b.rank[0]) {
        if (a.rank[1] < b.rank[1]) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if (a.rank[0] < b.rank[0]) {
        return 1;
    }
    else {
        return 0;
    }
}


/**
 * Devuelve el vector de sufijos de la cadena.
 * @param cadena
 * @return vectorSufijos
 */
vector<uint32_t> crearVectorSufijos(const vector<uint8_t> &cadena) {
    //assert(cadena.size() <= 1 + numeric_limits<uint32_t>::max()); // Max cadena: 64 KiB = 65536 Bytes

    return crearVectorSufijos(cadena, 1);
}

/**
 * Devuelve el vector de sufijos de la cadena utilizando el siguiente algoritmo:
 * https://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/
 * @param cadena
 * @param sorting_method metodo de ordenacion(1->std::sort,2->radix_sort)
 * @return vectorSufijos
 */
std::vector<uint32_t> crearVectorSufijos(const std::vector<uint8_t> &cadena, int sorting_method) {
    //assert(cadena.size() <= 1 + numeric_limits<uint32_t>::max()); // Max cadena: 64 KiB = 65536 Bytes

    const uint32_t length = cadena.size();
    Suffix suffixes[length];
    for (uint32_t i = 0; i < length; ++i) {
        suffixes[i].i = i;
        suffixes[i].rank[0] = cadena[i];
        if (i+1 < length) {
            suffixes[i].rank[1] = cadena[i+1];
        }
        else {
            suffixes[i].rank[1] = -1;
        }
    }

    uint32_t indexes[length];
    sort(suffixes, suffixes + length, cmp);

    for (int k = 4; k < 2*length; k = k*2) {
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        //suffixes ya esta ordenado.[0] es el primero
        suffixes[0].rank[0] = rank;
        indexes[suffixes[0].i] = 0;
        for (uint32_t i = 1; i < length; i++) {
            //Si coinciden los rankings 0 y 1 con el ranking del anterior
            //se le da el mismo ranking que el sufijo anterior
            if (suffixes[i].rank[0] == prev_rank &&
            suffixes[i].rank[1] == suffixes[i-1].rank[1]) {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else {
                //Se incrementa el ranking y se asigna
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            indexes[suffixes[i].i] = i;
        }

        // Assign next rank to every suffix
        for (uint32_t i = 0; i < length; i++) {
            uint32_t nextindex = suffixes[i].i + k/2;
            suffixes[i].rank[1] = (nextindex < length)?
                                  suffixes[indexes[nextindex]].rank[0]: -1;
        }

        // Sort the suffixes according to first k characters
        sort(suffixes, suffixes + length, cmp);
    }

    vector<uint32_t> final_suffixes(length);
    for (uint32_t i = 0; i < length; i++){
        final_suffixes[i] = suffixes[i].i;
    }
    return final_suffixes;
}