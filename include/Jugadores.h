#ifndef JUGADORES_H
#define JUGADORES_H

#include <string>
#include <vector>
#include "../include/Propiedades.h"
using namespace std;

class Jugador {
private:
    string nombre;                // Nombre del jugador
    int dinero;                   // Cantidad de dinero disponible
    int posicion;                 // Posición actual en el tablero
    bool enCarcel;                // Indica si el jugador está en la cárcel
    bool tarjetaLibertad;         // Indica si posee una tarjeta de "Salir de la cárcel"
    vector<Prop*> propiedades;    // Lista de propiedades del jugador

public:
    // ------------------------------------------------------------
    // Constructor
    // PRE: Ninguna.
    // POST: Crea un jugador con nombre n y dinero inicial dineroInicial.
    //       Posición = 0, enCarcel = false, tarjetaLibertad = false.
    // ------------------------------------------------------------
    Jugador(const string& n = "", int dineroInicial = 1500);

    // ------------------------------------------------------------
    // Getters
    // PRE: Ninguna.
    // POST: Devuelve el dato solicitado del jugador.
    // ------------------------------------------------------------
    string getNombre() const;
    int getDinero() const;
    int getPosicion() const;
    bool estaEnCarcel() const;
    bool tieneTarjetaLibertad() const;
    vector<Prop*> getPropiedades() const;

    // ------------------------------------------------------------
    // Setters
    // PRE: Los valores deben ser válidos (posición >= 0, dinero >= 0).
    // POST: Actualizan el atributo del jugador.
    // ------------------------------------------------------------
    void setPosicion(int p);
    void setDinero(int d);
    void setEnCarcel(bool estado);
    void setTarjetaLibertad(bool estado);

    // ------------------------------------------------------------
    // usarTarjetaLibertad()
    // PRE: El jugador debe tener tarjetaLibertad = true.
    // POST: Consume la tarjeta (tarjetaLibertad = false).
    // ------------------------------------------------------------
    void usarTarjetaLibertad();

    // ------------------------------------------------------------
    // mover(casillas, tamañoTablero)
    // PRE: tamañoTablero > 0.
    // POST: Modifica la posición del jugador avanzando casillas.
    //       Si supera tamañoTablero, se reinicia módulo el tablero.
    // ------------------------------------------------------------
    void mover(int casillas, int tamañoTablero);

    // ------------------------------------------------------------
    // cobrar(cantidad)
    // PRE: cantidad > 0.
    // POST: Aumenta el dinero del jugador en cantidad.
    // ------------------------------------------------------------
    void cobrar(int cantidad);

    // ------------------------------------------------------------
    // pagar(cantidad)
    // PRE: cantidad > 0.
    // POST: Si el jugador tiene suficiente dinero, lo descuenta y
    //       devuelve true; si no, devuelve false sin modificar dinero.
    // ------------------------------------------------------------
    bool pagar(int cantidad);

    // ------------------------------------------------------------
    // comprarPropiedad(propiedad)
    // PRE: propiedad ≠ nullptr y propiedad->disponible == true.
    // POST: Añade la propiedad a la lista del jugador y la marca como no disponible.
    // ------------------------------------------------------------
    void comprarPropiedad(Prop* propiedad);

    // ------------------------------------------------------------
    // tieneMonopolio(color, todasPropiedades)
    // PRE: color no vacío.
    // POST: Retorna true si el jugador posee todas las propiedades
    //       de ese color dentro del manejador de propiedades.
    // ------------------------------------------------------------
    bool tieneMonopolio(const string& color, const ManejadorPropiedades& todasPropiedades) const;

    // ------------------------------------------------------------
    // mostrar()
    // PRE: Ninguna.
    // POST: Imprime por consola el estado del jugador (dinero, posición, propiedades).
    // ------------------------------------------------------------
    void mostrar() const;
};

#endif