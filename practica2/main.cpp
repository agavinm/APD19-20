/******************************************************************************
 * @file    main.cpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Enero 2020
 * @coms    Algoritmia para Problemas Difíciles - Práctica 2
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <limits>
#include "BurrowsWheeler.hpp"

using namespace std;

/**
 * Devuelve el fichero comprimido fout.
 *
 * Comprime el fichero fin por trozos de n bytes en el fichero fout. El fichero fout está compuesto por cadenas de bytes
 * formadas por un entero (4 bytes) que indica el número de bytes que ocupa el siguiente trozo comprimido y, a
 * continuación, los bytes correspondientes al trozo comprimido.
 *
 * @param fin
 * @param fout
 * @param n
 */
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
            if (cadena != revertir(transformar(vectorSufijos(cadena), cadena))) {// TODO: Error aquí, cuando funcione borrar
                auto v = vectorSufijos(cadena);
                auto t = transformar(vectorSufijos(cadena), cadena);
                auto r = revertir(transformar(vectorSufijos(cadena), cadena));
                cerr << "ERROR" << endl;
                exit(1);
            }// TODO: Borrar hasta aquí

            // Procesar cadena
            cadena = transformar(vectorSufijos(cadena), cadena); // Transformada

            // Comprimir transformada
            // cadena = algoritmosDeCompresion(cadena) TODO

            // Escribir en el fichero de salida el número de bytes que tiene la cadena de salida (4 bytes)
            uint32_t numBytes = cadena.size();
            fout.write(reinterpret_cast<char *>(&numBytes), sizeof(numBytes));

            // Escribir en fichero de salida la cadena comprimida
            for (uint8_t b : cadena)
                fout.write(reinterpret_cast<char *>(&b), sizeof(b));

            cadena.clear();
        }
    }
}

/**
 * Devuelve el fichero descomprimido fout.
 *
 * Descomprime el fichero fin por trozos en el fichero fout. El fichero fin debe seguir la especificación descrita en
 * void comprimir(ifstream &fin, ofstream &fout, uint32_t n).
 *
 * @param fin
 * @param fout
 */
void descomprimir(ifstream &fin, ofstream &fout) {
    vector<uint8_t> cadena;
    uint8_t byte;
    uint32_t numBytes;

    while (fin.read(reinterpret_cast<char *>(&numBytes), sizeof(numBytes))) {
        cadena.reserve(numBytes);

        // Copiar fichero comprimido a memoria en trozos de numBytes bytes
        for (uint32_t i = 0; i < numBytes; i++) {
            if (fin.read(reinterpret_cast<char *>(&byte), sizeof(byte)))
                cadena.push_back(byte);
            else {
                cerr << "Fichero de entrada no válido" << endl;
                exit(1);
            }
        }

        // Descomprimir entrada
        // cadena = algoritmosDeDesompresion(cadena) TODO

        // Revertir transformada
        cadena = revertir(cadena);

        // Escribir en fichero de salida la cadena descomprimida
        for (uint8_t b : cadena)
            fout.write(reinterpret_cast<char *>(&b), sizeof(b));

        cadena.clear();
    }
}

void help(char *argv[]) {
    cout << "Uso: " << argv[0] << " [-c | -d] <file>" << endl;
    cout << '\t' << "-c Crea el archivo comprimido <file>.bwh usando BWT, Move-To-Front y Huffman." << endl;
    cout << '\t' << "-d Crea el archivo descomprimido <file> usando BWT, Move-To-Front y Huffman." << endl;
    cout << '\t' << "   El archivo a descomprimir debe tener extensión .bwh" << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        help(argv);
        return 0;
    }

    string action(argv[1]);
    if (action != "-c" && action != "-d") {
        help(argv);
        return 0;
    }

    string file(argv[2]);
    if (action == "-d" && (file.size() <= 4 || file.substr(file.length() - 4) != ".bwh")) {
        cerr << "El archivo a descomprimir debe tener extensión .bwh" << endl;
        return 1;
    }

    ifstream fin(file, ios::binary);
    if (!fin.is_open()) {
        cerr << "El archivo " << file << " no se puede leer." << endl;
        return 1;
    }

    ofstream fout;
    if (action == "-d")
        fout.open(file.substr(0, file.length() - 4), ios::binary);
    else
        fout.open(file + ".bwh", ios::binary);
    if (!fin.is_open()) {
        cerr << "El archivo " << argv[2] << " no se puede crear." << endl;
        return 1;
    }

    if (action == "-d")
        descomprimir(fin, fout);
    else
        comprimir(fin, fout, 1 + numeric_limits<uint16_t>::max());

    fin.close();
    fout.close();
    return 0;
}
