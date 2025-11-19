#include "../include/Tarjeta.h"
#include "../include/Jugadores.h"  // Necesario para aplicar efectos al jugador
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
using namespace std;

// Constructor
Tarjeta::Tarjeta(const string& t, const string& d, const string& a, int e)
    : tipo(t), descripcion(d), accion(a), efecto(e) {}

// Getters
string Tarjeta::getTipo() const { return tipo; }
string Tarjeta::getDescripcion() const { return descripcion; }
string Tarjeta::getAccion() const { return accion; }
int Tarjeta::getEfecto() const { return efecto; }

// Mostrar tarjeta
void Tarjeta::mostrar() const {
    cout << "[" << tipo << "] " << descripcion 
         << " (Accion: " << accion << ", Efecto: " << efecto << ")" << endl;
}

// Cargar tarjetas desde archivo, filtrando por tipo
void Tarjeta::cargarDesdeArchivo(const string& nombreArchivo, queue<Tarjeta>& cola, const string& tipoFiltro) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string t, desc, acc, efStr;

        if (!getline(ss, t, ',')) continue;
        if (!getline(ss, desc, ',')) continue;
        if (!getline(ss, acc, ',')) continue;
        if (!getline(ss, efStr, ',')) continue;

        int ef = stoi(efStr);

        if (t == tipoFiltro) {
            cola.push(Tarjeta(t, desc, acc, ef));
        }
    }
    archivo.close();
}

// Aplicar el efecto de la tarjeta a un jugador
void aplicarTarjeta(Tarjeta& tarjeta, Jugador& jugador, int tamañoTablero = 40) {
    string accion = tarjeta.getAccion();
    int valor = tarjeta.getEfecto();

    if (accion == "cobrar") {
        jugador.cobrar(valor);
        cout << jugador.getNombre() << " recibe $" << valor << endl;
    }
    else if (accion == "pagar") {
        if (!jugador.pagar(valor))
            cout << jugador.getNombre() << " no tiene suficiente dinero para pagar $" << valor << endl;
        else
            cout << jugador.getNombre() << " paga $" << valor << endl;
    }
    else if (accion == "mover") {
        jugador.mover(valor, tamañoTablero);
        cout << jugador.getNombre() << " se mueve " << valor << " casillas" << endl;
    }
    else if (accion == "carcel_libre") {
        jugador.setTarjetaLibertad(true);
        cout << jugador.getNombre() << " obtiene una tarjeta de libertad" << endl;
    }
    else if (accion == "no_pasa_por_salida") {
        cout << jugador.getNombre() << " no cobra al pasar por salida" << endl;
    }
}