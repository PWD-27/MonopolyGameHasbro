#ifndef PROPIEDADES_H
#define PROPIEDADES_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>  // Para la tabla hash de acceso directo
#include "Banco.h"        // Para interactuar con el banco al construir casas y hoteles
using namespace std;

struct Prop {
    string nombre;
    string color;
    int precio;
    int alquiler[6];   // Alquiler según casas (0..4) y hotel (5)
    int numCasas;      // Casas construidas
    bool tieneHotel;   
    bool hipotecada;   // Indica si está hipotecada
    bool disponible;   // Indica si se puede comprar
    bool esFerrocarril;
    bool esServicios;

    Prop()
        : nombre(""), color(""), precio(0), numCasas(0), tieneHotel(false), 
          hipotecada(false), disponible(true), esFerrocarril(false), esServicios(false) {
        for (int i = 0; i < 6; i++) alquiler[i] = 0;
    }

    // Construir casa o hotel en la propiedad
    bool construirCasa(Banco& banco) {
        if (esFerrocarril || esServicios) {
            cout << "No se pueden construir casas ni hoteles en " << nombre 
                 << " (Ferrocarril o Servicio)." << endl;
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

    // Obtener alquiler actual según casas/hotel
    int alquilerActual() const {
        if (hipotecada) return 0;  
        return tieneHotel ? alquiler[5] : alquiler[numCasas];
    }

    // Hipotecar la propiedad
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

    // Cancelar hipoteca pagando 10% de interés
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

// Clase manejadora de propiedades
class ManejadorPropiedades {
private:
    vector<Prop> lista;                        // Para iteraciones ordenadas
    unordered_map<string, Prop*> tabla;        // Para acceso directo por nombre

public:
    bool cargarDesdeArchivo(const string& archivo);
    Prop* buscarPorNombre(const string& nombre) {
        auto it = tabla.find(nombre);
        return (it != tabla.end()) ? it->second : nullptr;
    }

    void imprimirTodas() const;

    int contarPorColor(const string& color) const {
        int total = 0;
        for (const auto& p : lista)
            if (p.color == color) total++;
        return total;
    }

    vector<Prop>& getLista() { return lista; }
    const vector<Prop>& getLista() const { return lista; }

    // Actualizar tabla hash después de cargar propiedades
    void actualizarTabla() {
        tabla.clear();
        for (auto& p : lista)
            tabla[p.nombre] = &p;
    }
};

#endif