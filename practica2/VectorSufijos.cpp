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
#include <cmath>
#include "VectorSufijos.hpp"

using namespace std;

/**
 *  Representacion de un sufijo mediante su indice,
 *  su primer ranking y su ranking siguiente
 */
struct Suffix {
    int index;   //indice del sufijo
    int first_rank;       // ranking primera mitad del sufijo
    int next_rank;      // ranking segunda mitad del sufijo
};

/**
 * Funcion para comparar sufijos
 * @param
 * @param b
 * @return
 */
//Comparar sufijos para std::sort
int cmp(Suffix s1, Suffix s2) {
    if(s1.first_rank == s2.first_rank){
        return s1.next_rank<s2.next_rank;
    }
    else{
        return s1.first_rank < s2.first_rank;
    }
}


/**
 * Devuelve el vector de sufijos de la cadena.
 * @param cadena
 * @return vectorSufijos
 */
vector<uint16_t> vectorSufijos(const vector<uint8_t> &cadena) {
    assert(cadena.size() <= 1 + numeric_limits<uint16_t>::max()); // Max cadena: 64 KiB = 65536 Bytes

    return vectorSufijos(cadena, 1);
}

/**
 * Devuelve el vector de sufijos de la cadena utilizando el siguiente algoritmo:
 * https://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/
 * @param cadena
 * @param sorting_method metodo de ordenacion(1->std::sort,2->radix_sort)
 * @return vectorSufijos
 */
std::vector<uint16_t> vectorSufijos(const std::vector<uint8_t> &cadena, int sorting_method) {
    assert(cadena.size() <= 1 + numeric_limits<uint16_t>::max()); // Max cadena: 64 KiB = 65536 Bytes

    int N = cadena.size();
    int suffix_rank[N];
    Suffix L[N];
    for (int i = 0; i <N ; ++i) {
        suffix_rank[i]=cadena[i]-'a';
    }
    int total_iterations=ceil(log2(N));
    for (int times = 0; times<total_iterations; ++times) {
        for (int i = 0; i <N ; ++i) {
            L[i].index=i;
            L[i].first_rank=suffix_rank[i];
            if(i+pow(2,times)<N){
                int offset=pow(2,times);
                L[i].next_rank=suffix_rank[i+offset];
            }
            else{
                L[i].next_rank=-1;
            }
        }
        //ordenar una vez tomadas todas
        //las medidas de ranking
        sort(L,L+N,cmp);
        //colocar el mejor de los sufijos a 0
        // y volver a calcular los rankings
        int updated_rank=0;
        suffix_rank[L[0].index]=updated_rank;
        for (int i = 0; i <N-1 ; ++i){
            if(L[i+1].first_rank!=L[i].first_rank || L[i+1].next_rank!=L[i].next_rank){
                updated_rank++;
            }
            suffix_rank[L[i+1].index]=updated_rank;
        }
    }
    //devolver el orden final de suffixes
    vector<uint16_t> final_suffixes;
    for (int i = 0; i < N; i++){
        final_suffixes.push_back(L[i].index);
    }
    return final_suffixes;
}