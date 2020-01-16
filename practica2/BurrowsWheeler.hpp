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
 * @param vectorSufijos
 * @param cadena
 * @return {cadena transformada, posición I}
 */
std::pair<std::vector<uint8_t>, uint16_t> transformar(const std::vector<uint16_t> &vectorSufijos,
                                                      const std::vector<uint8_t> &cadena);

/**
 * Dados la cadena transformada de Burrows-Wheeler y la posición I, devuelve la cadena original.
 * @param transformada
 * @param posicionI
 * @return cadena original
 */
std::vector<uint8_t> revertir(const std::vector<uint8_t> &transformada, uint16_t posicionI);


#endif //PRACTICA2_BURROWSWHEELER_HPP
