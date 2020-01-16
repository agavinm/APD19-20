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
#include <algorithm>

using namespace std;

/**
 * Funcion para comparar sufijos
 * @param
 * @param b
 * @return
 */
int cmp(Suffix a, Suffix b){
    if(a.rank[0] == b.rank[0]){
        if(a.rank[1]<b.rank[1]){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(a.rank[0] < b.rank[0]){
        return 1;
    }
    else{
        return 0;
    }
}


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

/**
 * Devuelve el vector de sufijos de la cadena utilizando el siguiente algoritmo:
 * https://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/
 * @param cadena,metodo de ordenacion(1->std::sort,2->radix_sort)
 * @return
 */
std::vector<uint16_t> create_suffixes(const std::vector<uint8_t> &cadena,int sorting_method){
    int length=cadena.size();
    Suffix suffixes[length];
    for (int i = 0; i < length; ++i){
        suffixes[i].i=i;
        suffixes[i].rank[0]=cadena[i]-'a';
        if (i+1<length){
            suffixes[i].rank[1]=cadena[i+1]-'a';
        }
        else{
            suffixes[i].rank[1]=-1;
        }
    }
    int indexes[length];
    sort(suffixes, suffixes+length, cmp);
    for (int k = 4; k < 2*length; k=k*2){
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        //suffixes ya esta ordenado.[0] es el primero
        suffixes[0].rank[0] = rank;
        indexes[suffixes[0].i] = 0;
        for (int i = 1; i < length; i++){
            //Si coinciden los rankings 0 y 1 con el ranking del anterior
            //se le da el mismo ranking que el sufijo anterior
            if (suffixes[i].rank[0] == prev_rank &&
                suffixes[i].rank[1] == suffixes[i-1].rank[1]){
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else{
                //Se incrementa el ranking y se asigna
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            indexes[suffixes[i].i] = i;
        }

        // Assign next rank to every suffix
        for (int i = 0; i < length; i++)
        {
            int nextindex = suffixes[i].i + k/2;
            suffixes[i].rank[1] = (nextindex < length)?
                                  suffixes[indexes[nextindex]].rank[0]: -1;
        }

        // Sort the suffixes according to first k characters
        sort(suffixes, suffixes+length, cmp);
    }
    vector<uint16_t> final_suffixes;
    for (int i = 0; i < length; i++){
        final_suffixes.push_back(suffixes[i].i);
    }
    return final_suffixes;
}