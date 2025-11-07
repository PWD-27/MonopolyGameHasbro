#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <string>
#include "Casilla.h"
using namespace std;

class Tablero {
private:
    vector<Casilla> casillas;
    int posicionCarcel;

public:
    Tablero();

    bool cargarDesdeArchivo(const string& archivo);
    Casilla getCasilla(int pos) const;
    int getCarcel() const;
    void mostrar() const;
    int tamaño() const;
};

#endif