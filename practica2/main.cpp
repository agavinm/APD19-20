/******************************************************************************
 * @file    main.cpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Enero 2020
 * @coms    Algoritmia para Problemas Difíciles - Práctica 2
 ******************************************************************************/

#include <iostream>
#include "BurrowsWheeler.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    vector<uint8_t> cadena = {'a', 'b', 'r', 'a', 'c', 'a'};
    vector<uint16_t> vectorSufijos = {5, 0, 3, 1, 4, 2};

    pair<std::vector<uint8_t>, uint16_t> transformada = transformar(vectorSufijos, cadena);
    cout << "I: " << transformada.second << endl;
    cout << "Transformada: ";
    for (uint8_t c : transformada.first)
        cout << (char) c;
    cout << endl;

    return 0;
}
