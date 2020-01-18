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
 * Dada una cadena, devuelve el vector de sufijos correspondiente.
 *
 * @param cadena
 * @return vector de sufijos
 */
std::vector<uint32_t> crearVectorSufijos(const std::vector<uint8_t> &cadena);

#endif //PRACTICA2_VECTORSUFIJOS_HPP
