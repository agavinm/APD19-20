/******************************************************************************
 * @file    Producto.hpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío
 * @date    Diciembre 2019
 * @coms    Algoritmia para Problemas Difíciles - Práctica 1
 ******************************************************************************/

#ifndef PRACTICA1_PRODUCTO_HPP
#define PRACTICA1_PRODUCTO_HPP


#include <string>
#include <ostream>

class Producto {
    std::string nombre;
    int unidades;
    float precio;
public:
    Producto(const std::string &nombre, int unidades, float precio);

    const std::string &getNombre() const;

    int getUnidades() const;

    float getPrecio() const;

    friend std::ostream &operator<<(std::ostream &os, const Producto &producto);
};


#endif //PRACTICA1_PRODUCTO_HPP
