#ifndef TARJETA_H
#define TARJETA_H

#include <string>
#include <queue>
using namespace std;

class Tarjeta {
private:
    string tipo;      // "Casualidad" o "Arca Comunal"
    string descripcion;  // Texto que se muestra al jugador
    string accion;    // Tipo de acción: mover, pagar, cobrar, carcel_libre, no_pasa_por_salida
    int efecto;       // Valor numérico asociado (puede ser 0)

public:
    // Constructor
    Tarjeta(const string& t = "", const string& d = "", const string& a = "", int e = 0);

    // Getters
    string getTipo() const;
    string getDescripcion() const;
    string getAccion() const;
    int getEfecto() const;

    // Cargar tarjetas desde archivo txt
    static void cargarDesdeArchivo(const string& nombreArchivo, queue<Tarjeta>& cola, const string& tipoFiltro);

    // Mostrar tarjeta
    void mostrar() const;
};

#endif