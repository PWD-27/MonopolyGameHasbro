#include "Jugadores.h"
#include <iostream>
using namespace std;

// Constructor
Jugador::Jugador(const string& n, int dineroInicial)
    : nombre(n), dinero(dineroInicial), posicion(0), enCarcel(false), tarjetaLibertad(false) {}

// Getters
string Jugador::getNombre() const { return nombre; }
int Jugador::getDinero() const { return dinero; }
int Jugador::getPosicion() const { return posicion; }
bool Jugador::estaEnCarcel() const { return enCarcel; }
bool Jugador::tieneTarjetaLibertad() const { return tarjetaLibertad; }
vector<Prop*> Jugador::getPropiedades() const { return propiedades; }

// Setters
void Jugador::setPosicion(int p) { posicion = p; }
void Jugador::setDinero(int d) { dinero = d; }
void Jugador::setEnCarcel(bool estado) { enCarcel = estado; }
void Jugador::setTarjetaLibertad(bool estado) { tarjetaLibertad = estado; }
void Jugador::usarTarjetaLibertad() { tarjetaLibertad = false; enCarcel = false; }

// Operaciones
void Jugador::mover(int casillas, int tamañoTablero) { posicion = (posicion + casillas) % tamañoTablero; }
void Jugador::cobrar(int cantidad) { dinero += cantidad; }
bool Jugador::pagar(int cantidad) {
    if (cantidad > dinero) return false;
    dinero -= cantidad;
    return true;
}
void Jugador::comprarPropiedad(Prop* propiedad) {
    if (propiedad != nullptr && propiedad->disponible && dinero >= propiedad->precio) {
        pagar(propiedad->precio);
        propiedad->disponible = false;
        propiedades.push_back(propiedad);
        cout << nombre << " compró " << propiedad->nombre << endl;
    }
}
bool Jugador::tieneMonopolio(const string& color, const ManejadorPropiedades& todasPropiedades) const {
    int totalColor = 0, jugadorColor = 0;
    for (auto p : propiedades) if (p->color == color) jugadorColor++;
    for (auto p : todasPropiedades.getLista()) if (p.color == color) totalColor++;
    return totalColor > 0 && jugadorColor == totalColor;
}

// Mostrar estado
void Jugador::mostrar() const {
    cout << "Jugador: " << nombre << " | Dinero: $" << dinero
         << " | Posición: " << posicion
         << " | En cárcel: " << (enCarcel ? "Sí" : "No") << endl;
    cout << "Propiedades: ";
    if (propiedades.empty()) cout << "Ninguna";
    else for (auto p : propiedades) cout << p->nombre << ", ";
    cout << endl;
}