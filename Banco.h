#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
    TAD: Banco
    Responsabilidad: Gestiona el dinero del sistema y las transacciones entre jugadores y el banco.
*/
class Jugador; // Declaración adelantada para poder usar la clase Jugador

class Banco {
private:
    long long dineroTotal;

public:
    // Pre: montoInicial >= 0
    // Post: Se crea un banco con montoInicial de dinero disponible
    Banco(long long montoInicial);

    // Pre: monto >= 0 y jugador valido
    // Post: Se transfiere 'monto' del banco al jugador (si hay fondos suficientes)
    bool pagarAJugador(Jugador &jug, long long monto);

    // Pre: monto >= 0 y jugador valido
    // Post: El banco recibe 'monto' del jugador (si este tiene suficiente dinero)
    bool cobrarDeJugador(Jugador &jug, long long monto);

    // Pre: ninguno
    // Post: Muestra en pantalla el dinero actual del banco
    void mostrarEstado() const;

    // Pre: ninguno
    // Post: Devuelve el dinero total actual del banco
    long long getDineroTotal() const;
};