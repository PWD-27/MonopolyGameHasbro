#include "Jugador.h"

Jugador::Jugador(int id_, string nombre_, long long dineroInicial) {
    id = id_;
    nombre = nombre_;
    dinero = dineroInicial;
    posicion = 0;
    enCarcel = false;
    bancarrota = false;
}

bool Jugador::pagar(long long monto) {
    if (monto <= 0) return false;
    if (dinero >= monto) {
        dinero -= monto;
        return true;
    } else {
        bancarrota = true;
        cout << " !SALDO INSUFICIENTE! " << nombre << " no tiene suficiente dinero y ha caído en bancarrota!" << endl;
        return false;
    }
}

void Jugador::recibir(long long monto) {
    if (monto > 0) dinero += monto;
}

void Jugador::moverA(int nuevaPos) {
    posicion = nuevaPos;
}

void Jugador::agregarPropiedad(int idPropiedad) {
    propiedades.push_back(idPropiedad);
}

void Jugador::mostrarEstado() const {
    cout << "Jugador: " << nombre
         << " | Dinero: $" << dinero
         << " | Posicion: " << posicion
         << " | Propiedades: " << propiedades.size()
         << (enCarcel ? " | En carcel" : "")
         << (bancarrota ? " | Bancarrota" : "")
         << endl;
}

int Jugador::getPosicion() const { return posicion; }
long long Jugador::getDinero() const { return dinero; }
string Jugador::getNombre() const { return nombre; }
bool Jugador::estaEnCarcel() const { return enCarcel; }
void Jugador::setEnCarcel(bool estado) { enCarcel = estado; }
