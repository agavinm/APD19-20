/******************************************************************************
 * @file    ConjuntoProductos.hpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío
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
 * compradosJuntos almacena los booleanos correspondientes a si dos productos (i,j) han sido almacenados juntos alguna
 * vez, como (i,i) es Verdad y (i,j) = (j,i) solo se almacenan los valores no repetidos, es decir, el triángulo superior
 * de la matriz sin incluir la diagonal.
 *
 * tam(compradosJuntos) = (n * n - n) / 2
 *
 * Ejemplo de matriz compradosJuntos:
 *  V A B C
 *  A V D E
 *  B D V F
 *  C E F V
 * compradosJuntos = [A, B, C, D, E, F]
 *
 */
class ConjuntoProductos {
    std::vector<Producto> productos;
    std::vector<bool> compradosJuntos;

public:
    /**
     * Genera un conjunto de numProductos productos aleatorios.
     * @param numProductos
     */
    explicit ConjuntoProductos(int numProductos);

    /**
     * Genera un conjunto de productos a partir de los ficheros fin1 y fin2.
     * @param fin1
     * @param fin2
     */
    ConjuntoProductos(const std::string &fin1, const std::string &fin2);

    const std::vector<Producto> &getProductos() const;

    void save(const std::string &fout1, const std::string &fout2) const;
};


#endif //PRACTICA1_CONJUNTOPRODUCTOS_HPP
