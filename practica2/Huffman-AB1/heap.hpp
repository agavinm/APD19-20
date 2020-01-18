//*****************************************************************
// File:   heap.hpp
// Author: Andrés Gavín Murillo 716358
// Author: Andrew Mackay 737069
// Date:   Mayo 2019
// Coms:   Algoritmia básica - Práctica 1
//*****************************************************************

#ifndef PRACTICA1_HEAP_HPP
#define PRACTICA1_HEAP_HPP


class Heap { // Heap de mínimos
private:
    std::vector<Arbol*> v; // vector dinámico que almacena los datos del montículo

public:
    Heap() {
        v.clear();
    }

    ~Heap() {
        v.clear();
    }

    /* Inserta el elemento ar al Heap */
    void insertar(Arbol &ar);

    /* Elimina del Heap el elemento en la cima y lo devuelve */
    Arbol* primero();
};


#endif //PRACTICA1_HEAP_HPP
