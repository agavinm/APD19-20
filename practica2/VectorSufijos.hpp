/******************************************************************************
 * @file    VectorSufijos.hpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Enero 2020
 * @coms    Algoritmia para Problemas Difíciles - Práctica 2
 ******************************************************************************/

#ifndef PRACTICA2_VECTORSUFIJOS_HPP
#define PRACTICA2_VECTORSUFIJOS_HPP


#include <cstdint>
#include <vector>

/**
 * Dada una cadena (vector de bytes) de longitud máxima 65536, devuelve el vector de sufijos correspondiente.
 *
 * Para generar el vector de sufijos se ha seguido el algoritmo de Skew, disponible en el material de clase,
 * String Matching (pags. 68-81).
 *
 * Explicación de la longitud máxima establecida:
 * Una cadena está formada por un máximo de 65536 Bytes (64 KiB).
 * Con 2 Bytes se pueden direccionar 2^16 posiciones (bytes), es decir, 65536 posiciones. Con 4 Bytes la cadena
 * podría tener un máximo de 2^32 = 4 GiB, por eso se han optado por cadenas de hasta 64 KiB y direccionarlas con
 * enteros de 2 Bytes.
 * El tamaño máximo del vector será de 65536, por lo que en memoria ocupará un máximo de 2 Bytes * 65536 = 128 KiB.
 *
 * @param cadena
 * @return vector de sufijos
 */
std::vector<uint16_t> vectorSufijos(const std::vector<uint8_t> &cadena);


#endif //PRACTICA2_VECTORSUFIJOS_HPP
