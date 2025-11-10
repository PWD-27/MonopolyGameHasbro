#ifndef BANCO_H
#define BANCO_H

#include <iostream>
using namespace std;

class Banco {
private:
    int dinero;
    int casasDisponibles;
    int hotelesDisponibles;

public:
    // Constructor
    Banco(int dineroInicial = 20580, int casas = 32, int hoteles = 12);

    // Getters
    int getDinero() const;
    int getCasasDisponibles() const;
    int getHotelesDisponibles() const;

    // Operaciones
    void cobrar(int cantidad);        // El banco recibe dinero
    bool pagar(int cantidad);         // El banco paga dinero
    void retirar(int cantidad);       // Dinero que el banco entrega al jugador
    void depositar(int cantidad);     // Dinero que el banco recibe de jugador
    bool comprarCasa();               // Reducir casas disponibles si hay
    bool venderCasa();                // Aumentar casas disponibles
    bool comprarHotel();              // Reducir hoteles disponibles si hay
    bool venderHotel();               // Aumentar hoteles disponibles

    // Mostrar estado
    void mostrar() const;
};

#endif