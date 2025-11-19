#ifndef PROPIEDADES_H
#define PROPIEDADES_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map> // Para la tabla hash de acceso directo
#include "Banco.h"       // Para interactuar con el banco al construir casas y hoteles
using namespace std;

struct Prop {
    string nombre;          // Nombre de la propiedad
    string color;           // Color del monopolio al que pertenece
    int precio;             // Precio de compra
    int alquiler[6];        // Alquiler según casas (0-4) o hotel (5)
    int numCasas;           // Cantidad de casas construidas
    bool tieneHotel;        // Indica si la propiedad tiene hotel
    bool hipotecada;        // Indica si la propiedad está hipotecada
    bool disponible;        // Disponible para compra
    bool esFerrocarril;     // Indica si es ferrocarril (no se construyen casas)
    bool esServicios;       // Indica si es empresa de servicios

    // ------------------------------------------------------------
    // Constructor por defecto
    // PRE: Ninguna.
    // POST: Inicializa todos los valores en vacío/0. Propiedad disponible
    //       sin casas, sin hotel, no hipotecada y alquiler inicializado en 0.
    // ------------------------------------------------------------
    Prop()
        : nombre(""), color(""), precio(0), numCasas(0),
          tieneHotel(false), hipotecada(false), disponible(true),
          esFerrocarril(false), esServicios(false)
    {
        for (int i = 0; i < 6; i++) alquiler[i] = 0;
    }

    // ------------------------------------------------------------
    // construirCasa(banco)
    // PRE:
    //  - La propiedad NO debe ser ferrocarril ni servicio.
    //  - banco debe estar correctamente inicializado.
    // POST:
    //  - Si tiene <4 casas, se añade una casa y el banco reduce una casa disponible.
    //  - Si ya tiene 4 casas, se reemplazan por 1 hotel si el banco tiene hoteles.
    //  - Si la construcción es exitosa, retorna true; de lo contrario, false.
    // ------------------------------------------------------------
    bool construirCasa(Banco& banco) {
        if (esFerrocarril || esServicios) {
            cout << "No se pueden construir casas ni hoteles en " << nombre << " (Ferrocarril o Servicio)." << endl;
            return false;
        }
        if (tieneHotel) {
            cout << nombre << " ya tiene un hotel." << endl;
            return false;
        }

        if (numCasas < 4) {
            if (banco.comprarCasa()) {
                numCasas++;
                cout << "Se construyó una casa en " << nombre << endl;
                return true;
            } else {
                cout << "No hay casas disponibles en el banco para " << nombre << endl;
                return false;
            }
        } else {
            if (banco.comprarHotel()) {
                numCasas = 0;
                tieneHotel = true;
                cout << "Se construyó un hotel en " << nombre << endl;
                return true;
            } else {
                cout << "No hay hoteles disponibles en el banco para " << nombre << endl;
                return false;
            }
        }
    }

    // ------------------------------------------------------------
    // alquilerActual()
    // PRE: Ninguna.
    // POST:
    //  - Si hipotecada = true, retorna 0.
    //  - Si no, retorna el valor de alquiler según número de casas u hotel.
    // ------------------------------------------------------------
    int alquilerActual() const {
        if (hipotecada) return 0;
        return tieneHotel ? alquiler[5] : alquiler[numCasas];
    }

    // ------------------------------------------------------------
    // hipotecar(banco)
    // PRE:
    //  - La propiedad no debe estar hipotecada.
    // POST:
    //  - Marca la propiedad como hipotecada.
    //  - El banco entrega al jugador la mitad del precio de la propiedad.
    //  - Devuelve true si se hipotecó, false si ya lo estaba.
    // ------------------------------------------------------------
    bool hipotecar(Banco& banco) {
        if (hipotecada) {
            cout << nombre << " ya estaba hipotecada." << endl;
            return false;
        }
        hipotecada = true;
        banco.depositar(precio / 2);
        cout << nombre << " ha sido hipotecada por $" << precio / 2 << endl;
        return true;
    }

    // ------------------------------------------------------------
    // deshipotecar(banco, dineroJugador)
    // PRE:
    //  - La propiedad debe estar hipotecada.
    //  - dineroJugador >= costo de deshipotecar.
    // POST:
    //  - La propiedad deja de estar hipotecada.
    //  - El jugador paga al banco el costo (50% del precio + 10% interés).
    //  - Retorna true si se pudo deshipotecar, false en caso contrario.
    // ------------------------------------------------------------
    bool deshipotecar(Banco& banco, int& dineroJugador) {
        if (!hipotecada) {
            cout << nombre << " no está hipotecada." << endl;
            return false;
        }
        int costo = static_cast<int>(precio / 2 * 1.1);
        if (dineroJugador < costo) {
            cout << "No hay suficiente dinero para deshipotecar " << nombre << endl;
            return false;
        }
        dineroJugador -= costo;
        banco.depositar(costo);
        hipotecada = false;
        cout << nombre << " ha sido deshipotecada pagando $" << costo << endl;
        return true;
    }
};


// ============================================================
// Clase manejadora de propiedades
// ============================================================
class ManejadorPropiedades {
private:
    vector<Prop> lista;                 // Lista ordenada de propiedades
    unordered_map<string, Prop*> tabla; // Acceso directo mediante nombre

public:
    // ------------------------------------------------------------
    // cargarDesdeArchivo(archivo)
    // PRE: archivo debe existir y tener formato válido.
    // POST:
    //  - Carga todas las propiedades en lista.
    //  - Llama a actualizarTabla() para poblar la tabla hash.
    // ------------------------------------------------------------
    bool cargarDesdeArchivo(const string& archivo);

    // ------------------------------------------------------------
    // buscarPorNombre(nombre)
    // PRE: nombre no vacío.
    // POST: Retorna un puntero a la propiedad si existe; nullptr si no.
    // ------------------------------------------------------------
    Prop* buscarPorNombre(const string& nombre) {
        auto it = tabla.find(nombre);
        return (it != tabla.end()) ? it->second : nullptr;
    }

    // ------------------------------------------------------------
    // imprimirTodas()
    // PRE: Ninguna.
    // POST: Muestra toda la lista de propiedades por consola.
    // ------------------------------------------------------------
    void imprimirTodas() const;

    // ------------------------------------------------------------
    // contarPorColor(color)
    // PRE: color no vacío.
    // POST: Retorna cuántas propiedades del color dado existen en lista.
    // ------------------------------------------------------------
    int contarPorColor(const string& color) const {
        int total = 0;
        for (const auto& p : lista)
            if (p.color == color) total++;
        return total;
    }

    // Getters de lista
    // PRE: Ninguna.
    // POST: Devuelven referencia o const referencia a la lista de propiedades.
    vector<Prop>& getLista() { return lista; }
    const vector<Prop>& getLista() const { return lista; }

    // ------------------------------------------------------------
    // actualizarTabla()
    // PRE: lista debe contener propiedades válidas.
    // POST:
    //  - Vacía la tabla hash.
    //  - Inserta cada propiedad de lista en la tabla con acceso directo.
    // ------------------------------------------------------------
    void actualizarTabla() {
        tabla.clear();
        for (auto& p : lista)
            tabla[p.nombre] = &p;
    }
};

#endif