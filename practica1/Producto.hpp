/******************************************************************************
 * @file    Producto.hpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Diciembre 2019
 * @coms    Algoritmia para Problemas Difíciles - Práctica 1
 ******************************************************************************/

#ifndef PRACTICA1_PRODUCTO_HPP
#define PRACTICA1_PRODUCTO_HPP


#include <string>
#include <ostream>

class Producto {
    std::string nombre;
    uint32_t unidades;
    float precio;
public:
    Producto(const std::string &nombre, uint32_t unidades, float precio);

    const std::string &getNombre() const;

    uint32_t getUnidades() const;

    float getPrecio() const;

    friend std::ostream &operator<<(std::ostream &os, const Producto &producto);

    bool operator==(const Producto &rhs) const;

    bool operator!=(const Producto &rhs) const;
};


#endif //PRACTICA1_PRODUCTO_HPP
