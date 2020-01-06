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

void generarDatosPrueba(const string &f) {
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
}

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        cout << "Uso:" << endl;
        cout << '\t' << "Generar datos de prueba: " << argv[0] << " <directorioDondeGenerar>" << endl;
        cout << '\t' << "Resolver productos: " << argv[0] << " <ficheroProductos> <ficheroCompradosJuntos>" << endl;
        return 0;
    }

    if (argc == 2) {
        string f(argv[1]);
        if (f[f.length() - 1] != '/')
            f += '/';
        generarDatosPrueba(f);
        return 0;
    }

    ConjuntoProductos cp(argv[1], argv[2]);

    return 0;
}