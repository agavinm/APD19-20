/******************************************************************************
 * @file    Producto.cpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío
 * @date    Diciembre 2019
 * @coms    Algoritmia para Problemas Difíciles - Práctica 1
 ******************************************************************************/

#include "Producto.hpp"

Producto::Producto(const std::string &nombre, int unidades, float precio) : nombre(nombre), unidades(unidades),
                                                                            precio(precio) {}

const std::string &Producto::getNombre() const {
    return nombre;
}

int Producto::getUnidades() const {
    return unidades;
}

float Producto::getPrecio() const {
    return precio;
}

std::ostream &operator<<(std::ostream &os, const Producto &producto) {
    os << producto.nombre << '\t' << producto.unidades << '\t' << producto.precio;
    return os;
}
