/******************************************************************************
 * @file    ConjuntoProductos.hpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Diciembre 2019
 * @coms    Algoritmia para Problemas Difíciles - Práctica 1
 ******************************************************************************/

#ifndef PRACTICA1_CONJUNTOPRODUCTOS_HPP
#define PRACTICA1_CONJUNTOPRODUCTOS_HPP


#include <vector>
#include "Producto.hpp"

/**
 * n productos
 *
 * productos = [p0, p1, ..., pn-1]
 *
 * compradosJuntos almacena los valores correspondientes a si dos productos (i,j) han sido almacenados juntos alguna
 * vez, como (i,i) es 1 y (i,j) = (j,i) solo se almacenan los valores no repetidos, es decir, el triángulo superior
 * de la matriz sin incluir la diagonal.
 *
 * tam(compradosJuntos) = (n * n - n) / 2
 *
 * Ejemplo de matriz compradosJuntos:
 *  1 A B C
 *  A 1 D E
 *  B D 1 F
 *  C E F 1
 * compradosJuntos = [A, B, C, D, E, F]
 *
 */
class ConjuntoProductos {
    std::vector<Producto> productos;
    std::vector<uint32_t> compradosJuntos;

    /**
     * Genera un conjunto de numProductos productos aleatorios con probabilidad probV de que dos productos se hayan
     * comprado juntos un numero aleatorio de veces entre 1 y maxJuntos.
     * @param numProductos
     * @param probV
     * @param maxJuntos
     */
    void generarConjuntoProductos(uint32_t numProductos, float probV, uint32_t maxJuntos);

public:
    /**
     * Genera un conjunto de numProductos productos aleatorios con probabilidad probV de que dos productos se hayan
     * comprado juntos un numero aleatorio de veces entre 1 y maxJuntos.
     * @param numProductos
     * @param probV
     * @param maxJuntos
     */
    explicit ConjuntoProductos(uint32_t numProductos, float probV, uint32_t maxJuntos);

    /**
     * Genera un conjunto de numProductos productos aleatorios con probabilidad aleatoria perteneciente a [0.3, 0.7] de
     * que dos productos se hayan comprado juntos un numero aleatorio de veces entre 1 y maxJuntos.
     * @param numProductos
     * @param maxJuntos
     */
    explicit ConjuntoProductos(uint32_t numProductos, uint32_t maxJuntos);

    /**
     * Genera un conjunto de productos a partir de los ficheros fin1 y fin2.
     * @param fin1
     * @param fin2
     */
    ConjuntoProductos(const std::string &fin1, const std::string &fin2);

    /**
     * Devuelve la posición que ocupa en el vector compradosJuntos la posición de la matriz (i,j)
     * @param i
     * @param j
     * @return
     */
    uint32_t posCompradosJuntos(uint32_t i, uint32_t j) const;

    const std::vector<Producto> &getProductos() const;

    const std::vector<uint32_t> &getCompradosJuntos() const;

    void save(const std::string &fout1, const std::string &fout2, bool randomSpaces) const;

    void save(const std::string &fout1, const std::string &fout2) const;

    bool operator==(const ConjuntoProductos &rhs) const;

    bool operator!=(const ConjuntoProductos &rhs) const;
};

/**
 * Devuelve la posición que ocupa en el vector compradosJuntos la posición de la matriz (i,j)
 * @param i
 * @param j
 * @param numProductos
 * @return
 */
uint32_t posCompradosJuntosAux(uint32_t i, uint32_t j, uint32_t numProductos);


#endif //PRACTICA1_CONJUNTOPRODUCTOS_HPP
