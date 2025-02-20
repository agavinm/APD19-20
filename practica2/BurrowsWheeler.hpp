/******************************************************************************
 * @file    BurrowsWheeler.hpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Enero 2020
 * @coms    Algoritmia para Problemas Difíciles - Práctica 2
 ******************************************************************************/

#ifndef PRACTICA2_BURROWSWHEELER_HPP
#define PRACTICA2_BURROWSWHEELER_HPP

#include <cstdint>
#include <vector>

/**
 * Dada una cadena (vector de bytes) de longitud máxima 65533, devuelve la cadena transformada de Burrows-Wheeler.
 *
 * Explicación de la longitud máxima establecida:
 * La cadena transformada está formada por un máximo de 65535 Bytes (64 KiB).
 * Con 2 Bytes se pueden direccionar 2^16 posiciones (bytes), es decir, 65536 posiciones. Con 4 Bytes la cadena
 * podría tener un máximo de 2^32 = 4 GiB, por eso se han optado por cadenas de hasta 64 KiB y direccionarlas con
 * enteros de 2 Bytes.
 * El tamaño máximo del vector será de 65535, por lo que en memoria ocupará un máximo de 2 Bytes * 65535 = 128 KiB.
 *
 * Los dos últimos bytes de transformada corresponden al valor de la posición I.
 *
 * @param vectorSufijos
 * @param cadena
 * @return cadena transformada
 */
std::vector<uint8_t> transformar(const std::vector<uint8_t> &cadena);

/**
 * Dados la cadena transformada de Burrows-Wheeler y la posición I, devuelve la cadena original.
 *
 * Los dos últimos bytes de transformada corresponden al valor de la posición I.
 *
 * @param transformada
 * @return cadena original
 */
std::vector<uint8_t> revertir(const std::vector<uint8_t> &transformada);

/**
 * Devuelve la cadena resultante de aplicar el algoritmo move to front.
 * @param cadena
 * @return cadena aplicando move to front
 */
std::vector<uint8_t> moveToFront(const std::vector<uint8_t> &cadena);

/**
 * Devuelve la cadena original obtenida al aplicar el algoritmo move to front.
 * @param cadena
 * @return
 */
std::vector<uint8_t> moveToFrontRevertir(const std::vector<uint8_t> &cadena);


#endif //PRACTICA2_BURROWSWHEELER_HPP
