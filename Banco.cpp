#include "Banco.h"
#include "Jugador.h"

Banco::Banco(long long montoInicial) {
    this->dineroTotal = montoInicial;
}

bool Banco::pagarAJugador(Jugador &jug, long long monto) {
    if (monto <= 0 || dineroTotal < monto) return false;
    jug.recibir(monto);
    dineroTotal -= monto;
    return true;
}

bool Banco::cobrarDeJugador(Jugador &jug, long long monto) {
    if (monto <= 0) return false;
    if (jug.pagar(monto)) {
        dineroTotal += monto;
        return true;
    }
    return false;
}

void Banco::mostrarEstado() const {
    cout << "Dinero total en el banco: $" << dineroTotal << endl;
}

long long Banco::getDineroTotal() const {
    return dineroTotal;
}