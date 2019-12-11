/******************************************************************************
 * @file    main.cpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío
 * @date    Diciembre 2019
 * @coms    Algoritmia para Problemas Difíciles - Práctica 1
 ******************************************************************************/

#include <iostream>
#include "ConjuntoProductos.hpp"

using namespace std;

int main() {
    ConjuntoProductos cp(200);
    for (const auto & i : cp.getProductos()) {
        cout << i << endl;
    }
    return 0;
}