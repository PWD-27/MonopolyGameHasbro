#ifndef CASILLA_H
#define CASILLA_H

#include <string>
using namespace std;

class Casilla {
private:
    int posicion;       // Posición de la casilla en el tablero (0–39)
    string nombre;      // Nombre visible de la casilla
    string tipo;        // Tipo de casilla: "propiedad", "salida", "carcel", etc.

public:

    // ------------------------------------------------------------
    // Constructor
    // PRE: pos >= 0; n y t pueden ser cadenas vacías.
    // POST: Crea una casilla con la posición, nombre y tipo indicados.
    // ------------------------------------------------------------
    Casilla(int pos = 0, const string& n = "", const string& t = "");

    // ------------------------------------------------------------
    // getNombre()
    // PRE: Ninguna.
    // POST: Devuelve el nombre de la casilla.
    // ------------------------------------------------------------
    string getNombre() const;

    // ------------------------------------------------------------
    // getTipo()
    // PRE: Ninguna.
    // POST: Devuelve el tipo de la casilla.
    // ------------------------------------------------------------
    string getTipo() const;

    // ------------------------------------------------------------
    // mostrar()
    // PRE: Ninguna.
    // POST: Imprime por consola la información de la casilla.
    // ------------------------------------------------------------
    void mostrar() const;
};

#endif