/******************************************************************************
 * @file    main.cpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Enero 2020
 * @coms    Algoritmia para Problemas Difíciles - Práctica 2
 ******************************************************************************/

#include <iostream>
#include "BurrowsWheeler.hpp"
#include "VectorSufijos.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    vector<uint8_t> cadena = {'a', 'b', 'r', 'a', 'c', 'a', 'z'};
    vector<uint16_t> vs = vectorSufijos(cadena);

    pair<std::vector<uint8_t>, uint16_t> transformada = transformar(vs, cadena);
    cout << "I: " << transformada.second << endl;
    cout << "Transformada: ";
    for (uint8_t c : transformada.first)
        cout << (char) c;
    cout << endl;

    vector<uint8_t> transformadaRevertida = revertir(transformada.first, transformada.second);
    cout << "Revertida: ";
    for (uint8_t c : transformadaRevertida)
        cout << (char) c;
    cout << endl;

    if (cadena == transformadaRevertida)
        cout << "CORRECTO" << endl;
    else
        cerr << "ERROR" << endl;

    return 0;
}
