#include "Casilla.h"
#include <iostream>
using namespace std;

Casilla::Casilla(int pos, const string& n, const string& t)
    : posicion(pos), nombre(n), tipo(t) {}

string Casilla::getNombre() const { return nombre; }
string Casilla::getTipo() const { return tipo; }

void Casilla::mostrar() const {
    cout << posicion << ": " << nombre << " (" << tipo << ")" << endl;
}