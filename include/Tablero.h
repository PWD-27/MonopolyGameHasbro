#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <string>
#include "Casilla.h"
using namespace std;

class Tablero {
private:
    vector<Casilla> casillas;   // Lista de casillas del tablero
    int posicionCarcel;         // Índice de la casilla de la cárcel

public:
    Tablero();
    /*
        PRE: Ninguna.
        POST: Crea un tablero vacío con posición de cárcel inicializada
              (generalmente -1 o valor por defecto definido en el .cpp).
    */

    bool cargarDesdeArchivo(const string& archivo);
    /*
        PRE:
            - 'archivo' debe ser el nombre de un archivo existente y accesible.
            - El archivo debe contener los datos de las casillas con el formato esperado.
        POST:
            - Carga todas las casillas dentro del vector 'casillas'.
            - Identifica y guarda la posición de la cárcel.
            - Retorna true si la carga fue exitosa, false si ocurrió algún error.
    */

    Casilla getCasilla(int pos) const;
    /*
        PRE:
            - pos debe estar en el rango: 0 <= pos < casillas.size().
        POST:
            - Devuelve la casilla ubicada en la posición 'pos' del tablero.
    */

    int getCarcel() const;
    /*
        PRE: Ninguna.
        POST:
            - Retorna la posición (índice) de la casilla de la cárcel.
    */

    void mostrar() const;
    /*
        PRE: Ninguna.
        POST:
            - Imprime en consola todas las casillas del tablero, en orden.
    */

    int tamaño() const;
    /*
        PRE: Ninguna.
        POST:
            - Retorna la cantidad total de casillas del tablero.
    */
};

#endif