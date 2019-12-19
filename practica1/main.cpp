/******************************************************************************
 * @file    main.cpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío Ferrer Chueca, 721132
 * @date    Diciembre 2019
 * @coms    Algoritmia para Problemas Difíciles - Práctica 1
 ******************************************************************************/

#include <iostream>
#include <array>
#include "ConjuntoProductos.hpp"

using namespace std;

int main() {
    const string f = "../ficheros/";
    int numProd = 1000;
    const array<float, 11> p = {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f}; // probabilidades de que dos productos se hayan comprado juntos

    int r = 0;
    for (float i : p) {
        string f1 = f + "f1_" + to_string(numProd) + "_" + to_string(i).substr(0, 3) + ".txt";
        string f2 = f + "f2_" + to_string(numProd) + "_" + to_string(i).substr(0, 3) + ".txt";

        ConjuntoProductos *cp;
        if (r % 2 != 0)
            cp = new ConjuntoProductos(numProd);
        else
            cp = new ConjuntoProductos(numProd, i);

        cp->save(f1, f2, r % 2 != 0);
        ConjuntoProductos aux(f1, f2);
        if (*cp == aux)
            cout << i << ": Correcto" << endl;
        else
            cout << i << ": Distintos" << endl;

        delete(cp);
        r++;
    }
    return 0;
}