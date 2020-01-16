/**********************************************************************
 * File:   BurrowsWheeler.hpp
 * Author: Andrés Gavín Murillo
 * Date:   16/1/20
 * Coms:   
 **********************************************************************/

#ifndef PRACTICA2_BURROWSWHEELER_HPP
#define PRACTICA2_BURROWSWHEELER_HPP

#include "VectorSufijos.hpp"

std::pair<std::vector<uint8_t>, uint16_t> transformar(const std::vector<uint16_t> &vectorSufijos,
                                                      const std::vector<uint8_t> &cadena);

std::vector<uint8_t> revertir(const std::vector<uint8_t> &transformada, uint16_t posicionI);


#endif //PRACTICA2_BURROWSWHEELER_HPP
