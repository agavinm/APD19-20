//*****************************************************************
// File:   heap.cpp
// Author: Andrés Gavín Murillo 716358
// Author: Andrew Mackay 737069
// Date:   Mayo 2019
// Coms:   Algoritmia básica - Práctica 1
//*****************************************************************


#include "arbol.hpp"
#include <vector>
#include "heap.hpp"

/* Inserta el elemento ar al Heap */
void Heap::insertar(Arbol &ar) {
    this->v.push_back(&ar); // Nuevo nodo hoja más a la derecha
    uint16_t pos = this->v.size() - 1, posPadre = (pos+1) / 2 - 1;
    bool continuar = pos != 0;

    while (continuar) { // Intercambiar mientras el hijo sea menor que el padre
        if (this->v[pos]->frecuencia() < this->v[posPadre]->frecuencia()) {
            this->v[pos] = this->v[posPadre];
            this->v[posPadre] = &ar;
            pos = posPadre;
            posPadre = (pos+1) / 2 - 1;
            continuar = pos != 0;
        }
        else {
            continuar = false;
        }
    }
}

/* Elimina del Heap el elemento en la cima y lo devuelve */
Arbol* Heap::primero() {
    if (!this->v.empty()) {
        Arbol *cima = this->v[0]; // Elemento a devolver

        // Nodo hoja más a la derecha en la cima y eliminar ese nodo hoja
        this->v[0] = this->v.back();
        this->v.pop_back();

        // Hundir cima
        uint16_t pos = 0, posHijo = (pos+1) * 2 - 1;
        bool continuar = posHijo < this->v.size();
        Arbol *aux;

        while (continuar) {
            if (posHijo+1 != this->v.size() && this->v[posHijo]->frecuencia() > this->v[posHijo+1]->frecuencia()) {
                posHijo++; // Hijo derecho
            }

            if (this->v[pos]->frecuencia() > this->v[posHijo]->frecuencia()) { // Intercambiar mientras el hijo sea mayor que el padre
                aux = this->v[posHijo];
                this->v[posHijo] = this->v[pos];
                this->v[pos] = aux;
                pos = posHijo;
                posHijo = (pos+1) * 2 - 1;
                continuar = posHijo < this->v.size();
            }
            else {
                continuar = false;
            }
        }

        return cima;
    }
    else {
        return nullptr;
    }
}
