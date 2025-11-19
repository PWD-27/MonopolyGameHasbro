#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include <queue>
#include <stack>
#include <string>
#include "../include/Jugadores.h"
#include "../include/Tablero.h"
#include "../include/Propiedades.h"
#include "../include/Banco.h"
#include "../include/Tarjeta.h"

// ------------------------------------------------------------
// Estructura que almacena el estado del juego para permitir undo
// ------------------------------------------------------------
struct Estado {
    std::vector<int> posiciones;   // Posición de cada jugador en el tablero
    std::vector<int> dinero;       // Dinero de cada jugador
    // Se pueden agregar más datos si es necesario (propiedades, casas, hoteles, etc.)
};

class Juego {
private:
    std::vector<Jugador> jugadores;     // Lista de jugadores
    Tablero tablero;                    // Tablero con sus casillas
    ManejadorPropiedades propiedades;   // Propiedades del juego
    Banco banco;                         // Banco del Monopoly
    std::queue<Tarjeta> arcaComunal;    // Mazo de Arca Comunal
    std::queue<Tarjeta> casualidad;     // Mazo de Casualidad
    int turnoActual;                    // Índice del jugador que juega
    std::stack<Estado> historial;       // Historial para deshacer

public:
    // ------------------------------------------------------------
    // Constructor
    // PRE: Ninguna.
    // POST: Inicializa el juego con sus estructuras vacías y turnoActual = 0.
    // ------------------------------------------------------------
    Juego();

    // ------------------------------------------------------------
    // agregarJugador(nombre)
    // PRE: nombre no debe estar vacío.
    // POST: Agrega un nuevo jugador al vector jugadores.
    // ------------------------------------------------------------
    void agregarJugador(const std::string& nombre);

    // ------------------------------------------------------------
    // Carga de archivos
    // PRE: Los archivos deben existir y tener formato válido.
    // POST: Cargan datos del tablero, propiedades o tarjetas al juego.
    // ------------------------------------------------------------
    void cargarTablero(const std::string& archivoTablero);
    void cargarPropiedades(const std::string& archivoPropiedades);
    void cargarTarjetas(const std::string& archivoTarjetas);

    // ------------------------------------------------------------
    // siguienteTurno()
    // PRE: Debe haber al menos 1 jugador.
    // POST: Cambia turnoActual al siguiente jugador en orden circular.
    // ------------------------------------------------------------
    void siguienteTurno();

    // ------------------------------------------------------------
    // jugarTurno()
    // PRE: Debe haber jugadores cargados.
    // POST: Ejecuta todas las acciones del turno del jugador actual.
    // ------------------------------------------------------------
    void jugarTurno();

    // ------------------------------------------------------------
    // deshacerTurno()
    // PRE: Debe haber al menos un estado guardado en historial.
    // POST: Restaura el estado previo del juego.
    // ------------------------------------------------------------
    void deshacerTurno();

    // ------------------------------------------------------------
    // mostrarEstado()
    // PRE: Ninguna.
    // POST: Muestra dinero, posición y estado general de los jugadores y el banco.
    // ------------------------------------------------------------
    void mostrarEstado() const;

    // ------------------------------------------------------------
    // moverJugador(jugador, casillas)
    // PRE: casillas puede ser positivo o negativo.
    // POST: Actualiza la posición del jugador y gestiona si pasa por salida.
    // ------------------------------------------------------------
    void moverJugador(Jugador& jugador, int casillas);

    // ------------------------------------------------------------
    // aplicarTarjeta(jugador, tarjeta)
    // PRE: tarjeta válida del mazo correspondiente.
    // POST: Aplica la acción indicada por la tarjeta al jugador.
    // ------------------------------------------------------------
    void aplicarTarjeta(Jugador& jugador, const Tarjeta& tarjeta);

    // ------------------------------------------------------------
    // pagarAlquiler(inquilino, propiedad)
    // PRE: propiedad debe ser válida y tener dueño.
    // POST: Transfiere dinero del inquilino al dueño según el alquilerActual().
    // ------------------------------------------------------------
    void pagarAlquiler(Jugador& inquilino, Prop* propiedad);

    // ------------------------------------------------------------
    // guardarEstado()
    // PRE: Ninguna.
    // POST: Guarda posiciones y dinero de todos los jugadores en el historial.
    // ------------------------------------------------------------
    void guardarEstado();

    // ------------------------------------------------------------
    // buscarPosicionCasilla(nombreCasilla)
    // PRE: nombreCasilla no debe estar vacío.
    // POST: Devuelve la posición de la casilla cuyo nombre coincide.
    //       Retorna -1 si no existe.
    // ------------------------------------------------------------
    int buscarPosicionCasilla(const std::string& nombreCasilla);
};

#endif