#include "Banco.h"
#include "Jugador.h"

int main() {
    Banco banco(50000);
    Jugador j1(1, "Alex", 1500);

    banco.mostrarEstado();
    j1.mostrarEstado();

    banco.pagarAJugador(j1, 200);
    banco.cobrarDeJugador(j1, 50);

    j1.moverA(5);
    j1.mostrarEstado();
    banco.mostrarEstado();

    return 0;
}
