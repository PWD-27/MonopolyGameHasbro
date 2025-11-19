#ifndef TARJETA_H
#define TARJETA_H

#include <string>
#include <queue>
using namespace std;

class Tarjeta {
private:
    string tipo;        // "Casualidad" o "Arca Comunal"
    string descripcion; // Texto que se muestra al jugador
    string accion;      // Tipo de acción: mover, pagar, cobrar, carcel_libre, no_pasa_por_salida
    int efecto;         // Valor numérico asociado (puede ser 0)

public:
    // Constructor
    /*
        PRE:
            - Ninguna; todos los parámetros son opcionales.
        POST:
            - Inicializa una tarjeta con el tipo, descripción, acción y efecto indicados.
            - Si no se pasan parámetros, la tarjeta queda vacía con valores por defecto.
    */
    Tarjeta(const string& t = "", const string& d = "", const string& a = "", int e = 0);

    // Getters

    /*
        PRE: Ninguna.
        POST: Retorna el tipo de la tarjeta ("Casualidad" o "Arca Comunal").
    */
    string getTipo() const;

    /*
        PRE: Ninguna.
        POST: Retorna el texto descriptivo de la tarjeta.
    */
    string getDescripcion() const;

    /*
        PRE: Ninguna.
        POST: Retorna el tipo de acción que ejecuta la tarjeta.
    */
    string getAccion() const;

    /*
        PRE: Ninguna.
        POST: Retorna el valor numérico asociado a la tarjeta (efecto).
    */
    int getEfecto() const;

    // Cargar tarjetas desde archivo txt
    /*
        PRE:
            - 'nombreArchivo' debe ser el nombre de un archivo existente y accesible.
            - El archivo debe contener tarjetas con el formato correcto (tipo;descripcion;accion;efecto).
            - 'cola' debe ser una cola válida donde se insertarán las tarjetas cargadas.
            - 'tipoFiltro' debe ser "Casualidad" o "Arca Comunal".
        POST:
            - Lee todas las tarjetas del archivo.
            - Inserta en 'cola' únicamente las tarjetas cuyo tipo coincide con 'tipoFiltro'.
            - No retorna valor porque modifica directamente la cola recibida por referencia.
    */
    static void cargarDesdeArchivo(const string& nombreArchivo, queue<Tarjeta>& cola, const string& tipoFiltro);

    // Mostrar tarjeta
    /*
        PRE: Ninguna.
        POST:
            - Imprime en consola la información de la tarjeta (tipo, descripción y acción).
    */
    void mostrar() const;
};

#endif