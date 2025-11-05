#include "Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Constructor
Juego::Juego() : turnoActual(0) {
    srand(time(nullptr)); // Semilla para dados aleatorios
}

// Agregar jugador
void Juego::agregarJugador(const string& nombre) {
    jugadores.push_back(Jugador(nombre));
}

// Cargar tablero
void Juego::cargarTablero(const string& archivoTablero) {
    tablero.cargarDesdeArchivo(archivoTablero);
}

// Cargar propiedades
void Juego::cargarPropiedades(const string& archivoPropiedades) {
    propiedades.cargarDesdeArchivo(archivoPropiedades);
}

// Cargar tarjetas
void Juego::cargarTarjetas(const string& archivoTarjetas) {
    Tarjeta::cargarDesdeArchivo(archivoTarjetas, arcaComunal, "Arca Comunal");
    Tarjeta::cargarDesdeArchivo(archivoTarjetas, casualidad, "Casualidad");
}

// Siguiente turno
void Juego::siguienteTurno() {
    turnoActual = (turnoActual + 1) % jugadores.size();
}

// Pagar alquiler según casas o hotel
void Juego::pagarAlquiler(Jugador& inquilino, Prop* propiedad) {
    if (!propiedad->disponible) {
        for (auto& jugador : jugadores) {
            for (auto p : jugador.getPropiedades()) {
                if (p == propiedad) {
                    int indiceAlquiler = propiedad->tieneHotel ? 5 : propiedad->numCasas;
                    int alquiler = propiedad->alquiler[indiceAlquiler];
                    cout << inquilino.getNombre() << " debe pagar $" << alquiler
                         << " a " << jugador.getNombre() << " por " << propiedad->nombre
                         << (propiedad->tieneHotel ? " (Hotel)" : "") << endl;

                    if (inquilino.pagar(alquiler)) {
                        jugador.cobrar(alquiler);
                    } else {
                        cout << inquilino.getNombre() << " no tiene suficiente dinero para pagar!" << endl;
                    }
                    return;
                }
            }
        }
    }
}

// Mover jugador con cobro por pasar salida
void Juego::moverJugador(Jugador& jugador, int casillas) {
    int nuevaPos = (jugador.getPosicion() + casillas) % tablero.tamaño();
    if (jugador.getPosicion() + casillas >= tablero.tamaño()) {
        cout << jugador.getNombre() << " pasa por la salida y cobra $200" << endl;
        jugador.cobrar(200);
    }
    jugador.setPosicion(nuevaPos);
}

// Buscar posición de casilla por nombre
int Juego::buscarPosicionCasilla(const string& nombreCasilla) {
    for (int i = 0; i < tablero.tamaño(); i++) {
        if (tablero.getCasilla(i).getNombre() == nombreCasilla)
            return i;
    }
    return 0; // fallback a salida
}

// Aplicar tarjeta
void Juego::aplicarTarjeta(Jugador& jugador, const Tarjeta& tarjeta) {
    cout << "Tarjeta: " << tarjeta.getDescripcion()
         << " (Acción: " << tarjeta.getAccion()
         << ", Efecto: " << tarjeta.getEfecto() << ")" << endl;

    string accion = tarjeta.getAccion();
    int efecto = tarjeta.getEfecto();

    if (accion == "mover") {
        string desc = tarjeta.getDescripcion();
        if (desc.find("Avanza hasta") != string::npos) {
            size_t pos = desc.find("Avanza hasta ");
            string nombreDestino = desc.substr(pos + 13);
            size_t extra = nombreDestino.find(" si pasas");
            if (extra != string::npos) nombreDestino = nombreDestino.substr(0, extra);

            int posDestino = buscarPosicionCasilla(nombreDestino);
            int actuales = jugador.getPosicion();
            int mov = (posDestino - actuales + tablero.tamaño()) % tablero.tamaño();

            if (actuales + mov >= tablero.tamaño()) {
                cout << jugador.getNombre() << " pasa por la salida y recibe $200" << endl;
                jugador.cobrar(200);
            }

            moverJugador(jugador, mov);
            cout << jugador.getNombre() << " avanza hasta " << nombreDestino << endl;
        } else {
            moverJugador(jugador, efecto);
        }
    }
    else if (accion == "cobrar") {
        jugador.cobrar(efecto);
        cout << jugador.getNombre() << " recibe $" << efecto << endl;
    }
    else if (accion == "pagar") {
        if (!jugador.pagar(efecto)) {
            cout << jugador.getNombre() << " no tiene suficiente dinero para pagar $" << efecto << endl;
        } else {
            cout << jugador.getNombre() << " paga $" << efecto << endl;
        }
    }
    else if (accion == "carcel_libre") {
        jugador.setTarjetaLibertad(true);
        cout << jugador.getNombre() << " obtiene una tarjeta de salida de la cárcel" << endl;
    }
    else if (accion == "ir_carcel" || accion == "no_pasa_por_salida") {
        jugador.setPosicion(tablero.getCarcel());
        jugador.setEnCarcel(true);
        cout << jugador.getNombre() << " va directamente a la cárcel" << endl;
    }
    else if (accion == "cobrar_por_jugador") {
        int total = 0;
        for (auto& j : jugadores) {
            if (&j != &jugador) {
                if (j.pagar(efecto)) total += efecto;
                else cout << j.getNombre() << " no puede pagar $" << efecto << endl;
            }
        }
        jugador.cobrar(total);
        cout << jugador.getNombre() << " recibe $" << total << " de los demás jugadores" << endl;
    }
    else if (accion == "pagar_por_jugador") {
        if (!jugador.pagar(efecto * (jugadores.size() - 1))) {
            cout << jugador.getNombre() << " no tiene suficiente dinero para pagar a todos!" << endl;
        } else {
            for (auto& j : jugadores) {
                if (&j != &jugador) j.cobrar(efecto);
            }
            cout << jugador.getNombre() << " paga $" << efecto << " a cada jugador" << endl;
        }
    }
    else {
        cout << "Acción de tarjeta desconocida: " << accion << endl;
    }
}

// Jugar turno
void Juego::jugarTurno() {
    Jugador& jugador = jugadores[turnoActual];
    cout << "\n=== Turno de " << jugador.getNombre() << " ===" << endl;

    guardarEstado();

    // Construcción de casas y hoteles
    if (!jugador.getPropiedades().empty()) {
        for (auto p : jugador.getPropiedades()) {
            if (jugador.tieneMonopolio(p->color, propiedades) && !p->esFerrocarril && !p->esServicios) {
                char opcion;
                cout << "Construir en " << p->nombre << " (actual: "
                     << p->numCasas << " casas"
                     << (p->tieneHotel ? ", Hotel" : "") << ")? (s/n): ";
                cin >> opcion;
                if (opcion == 's' || opcion == 'S') {
                    p->construirCasa(banco);
                }
            }
        }
    }

    // Tirar dados
    int dado1 = rand() % 6 + 1;
    int dado2 = rand() % 6 + 1;
    int movimiento = dado1 + dado2;
    cout << "Sacó " << dado1 << " y " << dado2 << " = " << movimiento << " casillas." << endl;
    moverJugador(jugador, movimiento);

    // Revisar casilla
    Casilla casilla = tablero.getCasilla(jugador.getPosicion());
    cout << "Cayó en: " << casilla.getNombre() << " (" << casilla.getTipo() << ")" << endl;

    // Verificar cárcel
    if (casilla.getNombre() == "Ir a la cárcel") {
        jugador.setPosicion(tablero.getCarcel());
        jugador.setEnCarcel(true);
        cout << jugador.getNombre() << " va directamente a la cárcel" << endl;
        return; // termina el turno
    }

    // Procesar según tipo de casilla
    if (casilla.getTipo() == "Propiedad") {
        Prop* prop = propiedades.buscarPorNombre(casilla.getNombre());
        if (prop != nullptr) {
            if (prop->disponible) {
                cout << "¿Desea comprar esta propiedad por $" << prop->precio << "? (s/n): ";
                char opcion;
                cin >> opcion;
                if (opcion == 's' || opcion == 'S') {
                    jugador.comprarPropiedad(prop);
                    banco.retirar(prop->precio);
                    char opcionCasa;
                    if (jugador.tieneMonopolio(prop->color, propiedades) && !prop->esFerrocarril && !prop->esServicios) {
                        cout << "¿Desea construir casa/hotel en esta propiedad? (s/n): ";
                        cin >> opcionCasa;
                        if(opcionCasa == 's' || opcionCasa == 'S') {
                            prop->construirCasa(banco);
                        }
                    }
                }
            } else {
                pagarAlquiler(jugador, prop);
            }
        }
    } else if (casilla.getTipo() == "Tarjeta") {
        Tarjeta tarjeta = (casilla.getNombre().find("Casualidad") != string::npos) ? casualidad.front() : arcaComunal.front();
        aplicarTarjeta(jugador, tarjeta);

        if (casilla.getNombre().find("Casualidad") != string::npos) {
            casualidad.pop();
            casualidad.push(tarjeta);
        } else {
            arcaComunal.pop();
            arcaComunal.push(tarjeta);
        }
    } else {
        cout << "Casilla especial, nada que hacer por ahora." << endl;
    }
}

// Guardar estado
void Juego::guardarEstado() {
    Estado est;
    for (const auto& j : jugadores) {
        est.posiciones.push_back(j.getPosicion());
        est.dinero.push_back(j.getDinero());
    }
    historial.push(est);
}

// Deshacer turno
void Juego::deshacerTurno() {
    if (historial.empty()) {
        cout << "No hay turnos para deshacer." << endl;
        return;
    }

    Estado est = historial.top();
    historial.pop();
    for (size_t i = 0; i < jugadores.size(); i++) {
        jugadores[i].setPosicion(est.posiciones[i]);
        jugadores[i].setDinero(est.dinero[i]);
    }
    cout << "Turno deshecho." << endl;
}

// Mostrar estado
void Juego::mostrarEstado() const {
    cout << "\n=== Estado actual del juego ===" << endl;
    for (const auto& j : jugadores) j.mostrar();
    banco.mostrar();
}