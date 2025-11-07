#include "Tablero.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Tablero::Tablero() : posicionCarcel(10) {}

bool Tablero::cargarDesdeArchivo(const string& archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo " << archivo << endl;
        return false;
    }

    casillas.clear();
    string linea;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string posStr, nombre, tipo;
        getline(ss, posStr, ',');
        getline(ss, nombre, ',');
        getline(ss, tipo, ',');

        int pos = stoi(posStr);
        if (tipo == "Carcel") posicionCarcel = pos;
        casillas.push_back(Casilla(pos, nombre, tipo));
    }

    file.close();
    return true;
}

Casilla Tablero::getCasilla(int pos) const {
    if (pos < 0 || pos >= casillas.size()) {
        cerr << "Posición inválida: " << pos << endl;
        return Casilla();
    }
    return casillas[pos];
}

int Tablero::getCarcel() const { return posicionCarcel; }

void Tablero::mostrar() const {
    cout << "=== Tablero ===" << endl;
    for (const Casilla& c : casillas) c.mostrar();
}

int Tablero::tamaño() const { return casillas.size(); }