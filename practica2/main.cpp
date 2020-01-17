/******************************************************************************
 * @file    main.cpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Enero 2020
 * @coms    Algoritmia para Problemas Difíciles - Práctica 2
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include "BurrowsWheeler.hpp"

using namespace std;

void comprimir(ifstream &fin, ofstream &fout, uint32_t n) {
    vector<uint8_t> cadena;
    uint8_t byte;

    bool end = false;
    while (!end) {
        cadena.reserve(n);

        // Copiar fichero a memoria en trozos de n bytes
        while (cadena.size() < n && fin.read(reinterpret_cast<char *>(&byte), sizeof(byte)))
            cadena.push_back(byte);

        end = cadena.size() < n; // Comprobar si se ha llegado al final del fichero

        if (!cadena.empty()) {
            // Procesar cadena
            vector<uint8_t> transformada = transformar(vectorSufijos(cadena), cadena);

            // Comprimir transformada
            // TODO

            cadena.clear();
        }
    }
}

int main(int argc, char *argv[]) {
    vector<uint8_t> cadena = {'a', 'b', 'r', 'a', 'c', 'a'};
    vector<uint16_t> vs = vectorSufijos(cadena);

    vector<uint8_t> transformada = transformar(vs, cadena);
    cout << "I: " << (((uint16_t) ((uint16_t)transformada[1] << 8u)) | transformada[0]) << endl;
    cout << "Transformada: ";
    for (uint32_t i = 2; i < transformada.size(); i++)
        cout << (char) transformada[i];
    cout << endl;

    vector<uint8_t> transformadaRevertida = revertir(transformada);
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
