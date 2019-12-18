/******************************************************************************
 * @file    main.cpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Darío
 * @date    Diciembre 2019
 * @coms    Algoritmia para Problemas Difíciles - Práctica 1
 ******************************************************************************/

#include <iostream>
#include <array>
#include "ConjuntoProductos.hpp"

using namespace std;

int main() {
    const string f = "../ficheros/";
    const array<int, 3> s = {10, 100, 1000}; // número de productos
    const array<float, 3> p = {0.1f, 0.5f, 0.9f}; // probabilidades de que dos productos se hayan comprado juntos

    for (int r = 0; r <= 1; r++)
        for (unsigned long i = 0; i < s.size(); i++) {
            string f1 = f + "f1_";
            string f2 = f + "f2_";

            ConjuntoProductos *cp;
            if (r == 1) {
                cp = new ConjuntoProductos(s[i]);

                f1 += "random_";
                f2 += "random_";
            }
            else
                cp = new ConjuntoProductos(s[i], p[i]);

            f1 += to_string(s[i]) + ".txt";
            f2 += to_string(s[i]) + ".txt";

            cp->save(f1, f2, r == 1);
            ConjuntoProductos aux(f1, f2);
            if (*cp == aux)
                cout << s[i] << ": Correcto" << endl;
            else
                cout << s[i] << ": Distintos" << endl;

            delete(cp);
        }
    return 0;
}