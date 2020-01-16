/**********************************************************************
 * File:   BurrowsWheeler.cpp
 * Author: Andrés Gavín Murillo
 * Date:   16/1/20
 * Coms:   
 **********************************************************************/

#include "BurrowsWheeler.hpp"

using namespace std;

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

std::vector<uint8_t> revertir(const std::vector<uint8_t> &transformada, uint16_t posicionI) {
    vector<uint8_t> cadena(transformada.size());



    return cadena;
}
