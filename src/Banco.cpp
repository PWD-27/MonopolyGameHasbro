#include "../include/Banco.h"
#include <iostream>
using namespace std;

// Constructor
Banco::Banco(int dineroInicial, int casas, int hoteles)
    : dinero(dineroInicial), casasDisponibles(casas), hotelesDisponibles(hoteles) {}

// Getters
int Banco::getDinero() const { return dinero; }
int Banco::getCasasDisponibles() const { return casasDisponibles; }
int Banco::getHotelesDisponibles() const { return hotelesDisponibles; }

// Operaciones
void Banco::cobrar(int cantidad) {
    dinero += cantidad;
}

bool Banco::pagar(int cantidad) {
    if (cantidad > dinero) return false; // No hay suficiente dinero
    dinero -= cantidad;
    return true;
}

// Retirar dinero al jugador
void Banco::retirar(int cantidad) {
    if (cantidad > dinero) cantidad = dinero; // No puede ser más de lo que tiene
    dinero -= cantidad;
}

// Depositar dinero del jugador
void Banco::depositar(int cantidad) {
    dinero += cantidad;
}

// Casas y hoteles
bool Banco::comprarCasa() {
    if (casasDisponibles <= 0) return false;
    casasDisponibles--;
    return true;
}

bool Banco::venderCasa() {
    casasDisponibles++;
    return true;
}

bool Banco::comprarHotel() {
    if (hotelesDisponibles <= 0) return false;
    hotelesDisponibles--;
    return true;
}

bool Banco::venderHotel() {
    hotelesDisponibles++;
    return true;
}

// Mostrar estado
void Banco::mostrar() const {
    cout << "Banco: Dinero: $" << dinero
         << " | Casas disponibles: " << casasDisponibles
         << " | Hoteles disponibles: " << hotelesDisponibles << endl;
}