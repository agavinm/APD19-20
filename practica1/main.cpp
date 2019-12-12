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
    const array<int, 3> s = {10, 100, 1000};

    for (int r = 0; r <= 1; r++)
        for (int i : s) {
            string f1 = f + "f1_";
            string f2 = f + "f2_";
            if (r == 1) {
                f1 += "random_";
                f2 += "random_";
            }
            f1 += to_string(i) + ".txt";
            f2 += to_string(i) + ".txt";

            ConjuntoProductos cp(i);
            cp.save(f1, f2, r == 1);
            ConjuntoProductos aux(f1, f2);
            if (cp == aux)
                cout << i << ": Correcto" << endl;
            else
                cout << i << ": Distintos" << endl;
        }
    return 0;
}