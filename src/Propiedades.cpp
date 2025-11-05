#include "Propiedades.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// =========================================
// Cargar propiedades desde archivo txt
// =========================================
bool ManejadorPropiedades::cargarDesdeArchivo(const string& archivo) {
    ifstream fin(archivo);
    if (!fin) {
        cerr << "Error: no se pudo abrir el archivo " << archivo << endl;
        return false;
    }

    lista.clear();   // Limpiar lista antes de cargar
    string linea;
    while (getline(fin, linea)) {
        stringstream ss(linea);
        string token;

        Prop p;

        // Nombre
        if (!getline(ss, token, ',')) continue;
        p.nombre = token;

        // Color
        if (!getline(ss, token, ',')) continue;
        p.color = token;

        // Precio
        if (!getline(ss, token, ',')) continue;
        p.precio = stoi(token);

        // Alquiler[0..5]
        for (int i = 0; i < 6; i++) {
            if (!getline(ss, token, ',')) break;
            p.alquiler[i] = stoi(token);
        }

        // Inicialización
        p.numCasas = 0;
        p.tieneHotel = false;
        p.hipotecada = false;
        p.disponible = true;

        // esFerrocarril
        if (!getline(ss, token, ',')) p.esFerrocarril = false;
        else p.esFerrocarril = (token == "1");

        // esServicios
        if (!getline(ss, token, ',')) p.esServicios = false;
        else p.esServicios = (token == "1");

        lista.push_back(p);
    }

    fin.close();

    // Actualizar tabla hash para acceso directo
    actualizarTabla();

    return true;
}

// =========================================
// Imprimir todas las propiedades
// =========================================
void ManejadorPropiedades::imprimirTodas() const {
    for (const auto& p : lista) {
        cout << p.nombre << " | Color: " << p.color
             << " | Precio: " << p.precio
             << " | Alquiler: ";
        for (int i = 0; i < 6; i++) cout << p.alquiler[i] << " ";
        cout << "| Casas: " << p.numCasas
             << " | Hotel: " << (p.tieneHotel ? "Sí" : "No")
             << " | Hipotecada: " << (p.hipotecada ? "Sí" : "No")
             << " | Disponible: " << (p.disponible ? "Sí" : "No")
             << " | Ferrocarril: " << (p.esFerrocarril ? "Sí" : "No")
             << " | Servicio: " << (p.esServicios ? "Sí" : "No")
             << endl;
    }
}

// =========================================
// Construir casa o hotel en propiedad
// =========================================
bool construirCasa(Prop* propiedad, Banco& banco) {
    if (!propiedad) return false;
    return propiedad->construirCasa(banco);
}

// =========================================
// Hipotecar propiedad
// =========================================
bool hipotecarPropiedad(Prop* propiedad, Banco& banco) {
    if (!propiedad || propiedad->hipotecada) return false;
    return propiedad->hipotecar(banco);
}

// =========================================
// Deshipotecar propiedad (requiere dinero del jugador)
// =========================================
bool deshipotecarPropiedad(Prop* propiedad, Banco& banco, int& dineroJugador) {
    if (!propiedad || !propiedad->hipotecada) return false;
    return propiedad->deshipotecar(banco, dineroJugador);
}