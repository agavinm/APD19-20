//*****************************************************************
// File:   huffman.hpp
// Author: Andrés Gavín Murillo 716358
// Author: Andrew Mackay 737069
// Date:   Mayo 2019
// Coms:   Algoritmia básica - Práctica 1
//*****************************************************************

#ifndef PRACTICA1_HUFFMAN_HPP
#define PRACTICA1_HUFFMAN_HPP

#include <cstdint>
#include <vector>

/* Dada una cadena, devuelve la cadena comprimida mediante el algoritmo de Huffman.
 * El fichero tiene el siguiente formato:
 *      1º: Árbol lexicográfico de código libre.
 *      2º: Símbolos codificados.
 *      3º: Número de símbolos descolocados en el anterior byte. */
std::vector<uint8_t> comprimir(const std::vector<uint8_t> &cadena);

/* Dada una cadena comprimida mediante el algoritmo de Huffman, devuelve la cadena original. */
std::vector<uint8_t> descomprimir(const std::vector<uint8_t> &cadena);


#endif //PRACTICA1_HUFFMAN_HPP
