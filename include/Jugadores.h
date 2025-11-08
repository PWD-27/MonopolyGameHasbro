#ifndef JUGADORES_H
#define JUGADORES_H

#include <string>
#include <vector>
#include "Propiedades.h"
using namespace std;

class Jugador {
private:
    string nombre;
    int dinero;
    int posicion;
    bool enCarcel;
    bool tarjetaLibertad;
    vector<Prop*> propiedades;

public:
    // Constructor
    Jugador(const string& n = "", int dineroInicial = 1500);

    // Getters
    string getNombre() const;
    int getDinero() const;
    int getPosicion() const;
    bool estaEnCarcel() const;
    bool tieneTarjetaLibertad() const;
    vector<Prop*> getPropiedades() const;

    // Setters
    void setPosicion(int p);
    void setDinero(int d);
    void setEnCarcel(bool estado);
    void setTarjetaLibertad(bool estado);
    void usarTarjetaLibertad();

    // Operaciones
    void mover(int casillas, int tamañoTablero);
    void cobrar(int cantidad);
    bool pagar(int cantidad);
    void comprarPropiedad(Prop* propiedad);
    bool tieneMonopolio(const string& color, const ManejadorPropiedades& todasPropiedades) const;

    // Mostrar estado
    void mostrar() const;
};

#endif