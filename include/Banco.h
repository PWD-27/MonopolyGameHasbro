#ifndef BANCO_H
#define BANCO_H

#include <iostream>
using namespace std;

class Banco {
private:
    int dinero;               // Dinero total que tiene el banco
    int casasDisponibles;     // Casas que quedan en el banco (máx. 32)
    int hotelesDisponibles;   // Hoteles que quedan en el banco (máx. 12)

public:
    // ------------------------------------------------------------
    // Constructor
    // PRE: dineroInicial, casas y hoteles deben ser valores >= 0.
    // POST: Inicializa el banco con el dinero, casas y hoteles indicados.
    // ------------------------------------------------------------
    Banco(int dineroInicial = 20580, int casas = 32, int hoteles = 12);

    // ------------------------------------------------------------
    // Getters
    // PRE: Ninguna.
    // POST: Devuelven el estado actual del banco.
    // ------------------------------------------------------------
    int getDinero() const;
    int getCasasDisponibles() const;
    int getHotelesDisponibles() const;

    // ------------------------------------------------------------
    // Operaciones
    // cobrar(int cantidad)
    // PRE: cantidad > 0.
    // POST: El banco incrementa su dinero en “cantidad”.
    // ------------------------------------------------------------
    void cobrar(int cantidad);        // El banco recibe dinero

    // pagar(int cantidad)
    // PRE: cantidad > 0.
    // POST: Si el banco tiene suficiente dinero, lo descuenta y retorna true;
    //       si no tiene suficiente, no modifica nada y retorna false.
    // ------------------------------------------------------------
    bool pagar(int cantidad);         // El banco paga dinero

    // retirar(int cantidad)
    // PRE: cantidad > 0 y el banco debe tener suficiente dinero.
    // POST: Reduce el dinero del banco en “cantidad”.
    // ------------------------------------------------------------
    void retirar(int cantidad);       // Dinero que el banco entrega al jugador

    // depositar(int cantidad)
    // PRE: cantidad > 0.
    // POST: Aumenta el dinero del banco en “cantidad”.
    // ------------------------------------------------------------
    void depositar(int cantidad);     // Dinero que el banco recibe de jugador

    // comprarCasa()
    // PRE: Debe haber al menos 1 casa disponible.
    // POST: Si había casas, reduce en 1 y retorna true;
    //       si no había, retorna false sin modificar nada.
    // ------------------------------------------------------------
    bool comprarCasa();               // Reducir casas disponibles si hay

    // venderCasa()
    // PRE: Ninguna.
    // POST: Incrementa en 1 las casas disponibles en el banco.
    // ------------------------------------------------------------
    bool venderCasa();                // Aumentar casas disponibles

    // comprarHotel()
    // PRE: Debe haber al menos 1 hotel disponible.
    // POST: Si había hoteles, reduce en 1 y retorna true;
    //       si no había, retorna false sin modificar nada.
    // ------------------------------------------------------------
    bool comprarHotel();              // Reducir hoteles disponibles si hay

    // venderHotel()
    // PRE: Ninguna.
    // POST: Incrementa en 1 los hoteles disponibles en el banco.
    // ------------------------------------------------------------
    bool venderHotel();               // Aumentar hoteles disponibles

    // ------------------------------------------------------------
    // mostrar()
    // PRE: Ninguna.
    // POST: Imprime por consola el estado actual del banco.
    // ------------------------------------------------------------
    void mostrar() const;
};

#endif