#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
    TAD: Jugador
    Responsabilidad: Representa a un jugador del juego Monopoly.
*/
class Jugador {
private:
    int id;
    string nombre;
    long long dinero;
    int posicion;
    bool enCarcel;
    bool bancarrota;
    vector<int> propiedades; // IDs de propiedades del tablero

public:
    // Pre: nombre no vacio, dineroInicial >= 0
    // Post: Se crea un jugador con dinero inicial y estado normal
    Jugador(int id_, string nombre_, long long dineroInicial);

    // Pre: monto >= 0
    // Post: Reduce el dinero del jugador en 'monto' si tiene suficiente
    bool pagar(long long monto);

    // Pre: monto >= 0
    // Post: Aumenta el dinero del jugador en 'monto'
    void recibir(long long monto);

    // Pre: pos >= 0
    // Post: Actualiza la posición del jugador en el tablero
    void moverA(int nuevaPos);

    // Pre: propiedad valida
    // Post: Agrega el ID de propiedad a la lista de propiedades
    void agregarPropiedad(int idPropiedad);

    // Pre: ninguno
    // Post: Imprime información del jugador
    void mostrarEstado() const;

    // Getters
    int getPosicion() const;
    long long getDinero() const;
    string getNombre() const;
    bool estaEnCarcel() const;

    // Pre: ninguno
    // Post: Cambia el estado de encarcelado
    void setEnCarcel(bool estado);
};