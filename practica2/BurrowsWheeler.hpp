/******************************************************************************
 * @file    BurrowsWheeler.hpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Enero 2020
 * @coms    Algoritmia para Problemas Difíciles - Práctica 2
 ******************************************************************************/

#ifndef PRACTICA2_BURROWSWHEELER_HPP
#define PRACTICA2_BURROWSWHEELER_HPP

#include "VectorSufijos.hpp"

// El vector de sufijos sigue la definición de VectorSufijos.hpp

/**
 * Dados una cadena y su correspondiente vector de sufijos, devuelve la cadena transformada de Burrows-Wheeler.
 *
 * Los dos primeros bytes de transformada corresponden al valor de la posición I.
 *
 * @param vectorSufijos
 * @param cadena
 * @return cadena transformada
 */
std::vector<uint8_t> transformar(const std::vector<uint16_t> &vectorSufijos, const std::vector<uint8_t> &cadena);

/**
 * Dados la cadena transformada de Burrows-Wheeler y la posición I, devuelve la cadena original.
 *
 * Los dos primeros bytes de transformada corresponden al valor de la posición I.
 *
 * @param transformada
 * @return cadena original
 */
std::vector<uint8_t> revertir(const std::vector<uint8_t> &transformada);


#endif //PRACTICA2_BURROWSWHEELER_HPP
