#include <iostream>
#include <vector>
//#include <cstdlib>

using namespace std;

const int FILAS = 10;
const int COLUMNAS = 10;

enum Direcciones
{
    ARRIBA,
    ABAJO,
    IZQUIERDA,
    DERECHA
};

class Jugador
{
protected:
    int fila;
    int columna;

public:
    Jugador(int fila, int columna) : fila(fila), columna(columna) {}

    int getFila() const { return fila; }
    int getColumna() const { return columna; }

    void setFila(int nuevaFila) { fila = nuevaFila; }
    void setColumna(int nuevaColumna) { columna = nuevaColumna; }

    bool moverse(Direcciones direccion, vector<vector<char>> &laberinto)
    {
        int nuevaFila = fila;
        int nuevaColumna = columna;

        switch (direccion)
        {
        case ARRIBA:
            nuevaFila--;
            break;
        case ABAJO:
            nuevaFila++;
            break;
        case IZQUIERDA:
            nuevaColumna--;
            break;
        case DERECHA:
            nuevaColumna++;
            break;
        }

        if (nuevaFila >= 0 && nuevaFila < FILAS && nuevaColumna >= 0 && nuevaColumna < COLUMNAS &&
            laberinto[nuevaFila][nuevaColumna] != '#')
        {
            laberinto[fila][columna] = ' ';
            fila = nuevaFila;
            columna = nuevaColumna;
            laberinto[fila][columna] = 'P';
            return true;
        }
        return false;
    }
};

class Momia : public Jugador
{
public:
    Momia(int fila, int columna) : Jugador(fila, columna) {}

    void perseguirJugador(const Jugador &jugador, vector<vector<char>> &laberinto)
    {
        Direcciones direccion;

        // Calcular la dirección para perseguir al jugador
        if (jugador.getFila() < getFila())
            direccion = ARRIBA;
        else if (jugador.getFila() > getFila())
            direccion = ABAJO;
        else if (jugador.getColumna() < getColumna())
            direccion = IZQUIERDA;
        else
            direccion = DERECHA;

        // Intentar moverse en la dirección calculada
        moverse(direccion, laberinto);
    }

    // Sobrescribir la función moverse para la momia
    bool moverse(Direcciones direccion, vector<vector<char>> &laberinto)
    {
        int nuevaFila = getFila();
        int nuevaColumna = getColumna();

        switch (direccion)
        {
        case ARRIBA:
            nuevaFila--;
            break;
        case ABAJO:
            nuevaFila++;
            break;
        case IZQUIERDA:
            nuevaColumna--;
            break;
        case DERECHA:
            nuevaColumna++;
            break;
        }

        if (nuevaFila >= 0 && nuevaFila < FILAS && nuevaColumna >= 0 && nuevaColumna < COLUMNAS &&
            laberinto[nuevaFila][nuevaColumna] != '#')
        {
            laberinto[getFila()][getColumna()] = ' ';
            setFila(nuevaFila);
            setColumna(nuevaColumna);
            laberinto[getFila()][getColumna()] = 'M';
            return true;
        }
        return false;
    }
};

class Tesoro : public Jugador
{
public:
    Tesoro(int fila, int columna) : Jugador(fila, columna) {}

    bool moverse(Direcciones direccion, vector<vector<char>> &laberinto)
    {
        // El tesoro no se mueve, por lo que este método no hace nada
        return true;
    }
};

class Nivel
{
public:
    int vidas;
    string mensaje;
    pair<int, int> jugadorInicial;
    pair<int, int> momiaInicial;
    pair<int, int> tesoroInicial;
    vector<vector<char>> mapa;

    Nivel(const vector<vector<char>> &tablero,
          int vidas,
          const string &mensaje,
          const pair<int, int> &posicionInicialJugador,
          const pair<int, int> &posicionInicialMomia,
          const pair<int, int> &posicionInicialTesoro)
        : mapa(tablero),
          vidas(vidas),
          mensaje(mensaje),
          jugadorInicial(posicionInicialJugador),
          momiaInicial(posicionInicialMomia),
          tesoroInicial(posicionInicialTesoro) {}
};

class Juego
{
private:
    Jugador jugador;
    Momia momia;
    Tesoro tesoro;
    vector<Nivel> niveles;
    int nivelActual;
    int vidas;
    Direcciones direccion;

public:
    Juego() : jugador(1, 1), momia(5, 5), nivelActual(0), vidas(3), tesoro(7, 7), direccion(ARRIBA)
    {
        bienvenida();
        inicializarNiveles();
    }

    void bienvenida()
    {
        cout << "====================================================\n";
        cout << "=                 BIENVENIDO A                    =\n";
        cout << "=                  MUMMY MAZE                     =\n";
        cout << "=               CONSOLE EDITION                   =\n";
        cout << "====================================================\n\n";
    }

    void inicializarNiveles()
    {
        // Nivel 1
        Nivel nivel1({
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                        {'#', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', '#'},
                        {'#', ' ', '#', '#', ' ', ' ', '#', '#', ' ', '#'},
                        {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                        {'#', ' ', '#', ' ', '#', ' ', ' ', '#', '#', '#'},
                        {'#', ' ', '#', ' ', '#', '#', ' ', ' ', ' ', '#'},
                        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
                        {'#', '#', '#', ' ', ' ', ' ', '#', ' ', '#', '#'},
                        {'#', '#', '#', '#', '#', ' ', '#', ' ', ' ', '#'},
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                     },
                     3, "¡Bienvenido al Nivel 1!", {1, 1}, {5, 5}, {8, 8});

        // Nivel 2
        Nivel nivel2({
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', '#'},
                        {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#'},
                        {'#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#'},
                        {'#', ' ', '#', '#', '#', ' ', '#', '#', ' ', '#'},
                        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
                        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#'},
                        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', '#'},
                        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                     },
                     3, "¡Bienvenido al Nivel 2!", {1, 1}, {5, 5}, {8, 8});

        // Nivel 3
        Nivel nivel3({
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'},
                        {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#'},
                        {'#', '#', '#', ' ', '#', ' ', ' ', ' ', '#', '#'},
                        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', '#'},
                        {'#', ' ', '#', ' ', '#', '#', '#', ' ', ' ', '#'},
                        {'#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#'},
                        {'#', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', '#'},
                        {'#', '#', ' ', '#', '#', ' ', '#', ' ', ' ', '#'},
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                     },
                     3, "¡Bienvenido al Nivel 3!", {1, 1}, {5, 5}, {8, 8});

        // Nivel 4
        Nivel nivel4({
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                        {'#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
                        {'#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#'},
                        {'#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
                        {'#', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', '#'},
                        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
                        {'#', ' ', '#', '#', '#', ' ', ' ', '#', ' ', '#'},
                        {'#', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', '#'},
                        {'#', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', '#'},
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                     },
                     3, "¡Bienvenido al Nivel 4!", {1, 1}, {5, 5}, {8, 8});

        // Nivel 5
        Nivel nivel5({
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                        {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#'},
                        {'#', '#', '#', ' ', ' ', '#', '#', '#', '#', '#'},
                        {'#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#'},
                        {'#', ' ', '#', ' ', ' ', '#', '#', ' ', '#', '#'},
                        {'#', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '#'},
                        {'#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#'},
                        {'#', ' ', '#', '#', ' ', ' ', ' ', '#', ' ', '#'},
                        {'#', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#'},
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                     },
                     3, "¡Bienvenido al Nivel 5!", {1, 1}, {5, 5}, {8, 8});

        // Nivel 6
        Nivel nivel6({
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
                        {'#', ' ', '#', ' ', '#', '#', ' ', '#', '#', '#'},
                        {'#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                        {'#', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', '#'},
                        {'#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#'},
                        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
                        {'#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
                        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                     },
                     3, "¡Bienvenido al Nivel 6!", {1, 1}, {5, 5}, {8, 8});

        // Nivel 7
        Nivel nivel7({
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                        {'#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
                        {'#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#'},
                        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                        {'#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#'},
                        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
                        {'#', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', '#'},
                        {'#', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', '#'},
                        {'#', ' ', '#', '#', ' ', ' ', '#', ' ', ' ', '#'},
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                     },
                     3, "¡Bienvenido al Nivel 7!", {1, 1}, {5, 5}, {8, 8});

        // Nivel 8
        Nivel nivel8({
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                        {'#', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', '#'},
                        {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#'},
                        {'#', '#', '#', '#', '#', '#', ' ', ' ', '#', '#'},
                        {'#', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#'},
                        {'#', ' ', '#', '#', ' ', '#', ' ', ' ', ' ', '#'},
                        {'#', ' ', '#', ' ', ' ', ' ', ' ', '#', '#', '#'},
                        {'#', ' ', ' ', ' ', '#', '#', ' ', '#', ' ', '#'},
                        {'#', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                     },
                     3, "¡Bienvenido al Nivel 8!", {1, 1}, {5, 5}, {8, 8});

        // Nivel 9
        Nivel nivel9({
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                        {'#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#'},
                        {'#', ' ', '#', '#', '#', ' ', '#', '#', ' ', '#'},
                        {'#', ' ', '#', '#', ' ', ' ', '#', '#', ' ', '#'},
                        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
                        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                        {'#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#'},
                        {'#', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', '#'},
                        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                     },
                     3, "¡Bienvenido al Nivel 9!", {1, 1}, {5, 5}, {8, 8});

        // Nivel 10
        Nivel nivel10({
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
                        {'#', ' ', ' ', '#', '#', '#', ' ', '#', ' ', '#'},
                        {'#', ' ', '#', '#', '#', ' ', ' ', '#', '#', '#'},
                        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                        {'#', '#', ' ', '#', ' ', '#', '#', ' ', '#', '#'},
                        {'#', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', '#'},
                        {'#', ' ', ' ', '#', ' ', '#', '#', ' ', '#', '#'},
                        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                      },
                      3, "¡Bienvenido al Nivel 10!", {1, 1}, {5, 5}, {8, 8});

        // Agregar niveles al vector
        niveles.push_back(nivel1);
        niveles.push_back(nivel2);
        niveles.push_back(nivel3);
        niveles.push_back(nivel4);
        niveles.push_back(nivel5);
        niveles.push_back(nivel6);
        niveles.push_back(nivel7);
        niveles.push_back(nivel8);
        niveles.push_back(nivel9);
        niveles.push_back(nivel10);
        // ... puedes seguir agregando más niveles de la misma manera
    }

    void resetearNivelActual()
    {
        // Restablecer la posición del jugador al inicial del nivel actual
        jugador.setFila(niveles[nivelActual].jugadorInicial.first);
        jugador.setColumna(niveles[nivelActual].jugadorInicial.second);

        // Restablecer la posición de la momia al inicial del nivel actual
        momia.setFila(niveles[nivelActual].momiaInicial.first);
        momia.setColumna(niveles[nivelActual].momiaInicial.second);

        // Restablecer la posición del tesoro al inicial del nivel actual
        tesoro.setFila(niveles[nivelActual].tesoroInicial.first);
        tesoro.setColumna(niveles[nivelActual].tesoroInicial.second);

        // Restablecer el número de vidas al inicial del nivel actual
        vidas = niveles[nivelActual].vidas;
    }

    void mostrarMapa()
    {
        //cout << "DEBUG: Mostrando el mapa del nivel actual:" << endl;
        bienvenida();
        mostrarMensaje();

        for (int i = 0; i < FILAS; ++i)
        {
            for (int j = 0; j < COLUMNAS; ++j)
            {
                char c = niveles[nivelActual].mapa[i][j];

                // Agregar condiciones para mostrar el jugador y el tesoro
                if (i == jugador.getFila() && j == jugador.getColumna())
                    c = 'P';
                else if (i == tesoro.getFila() && j == tesoro.getColumna())
                    c = 'T';

                cout << c;
            }
            cout << endl;
        }

        //cout << "DEBUG: Fin del mapa" << endl;
    }

    void mostrarMensaje()
    {
        // Mostrar el mensaje del nivel actual y la cantidad de vidas
        cout << niveles[nivelActual].mensaje << '\n' << " Vidas restantes: " << vidas << '\n' << '\n';
    }

    bool moverJugador(Direcciones direccion);
    bool moverMomia(Direcciones direccion);
    bool moverTesoro(Direcciones direccion);

    bool verificarColisiones()
    {
        int jugadorFila = jugador.getFila();
        int jugadorColumna = jugador.getColumna();

        int momiaFila = momia.getFila();
        int momiaColumna = momia.getColumna();

        int tesoroFila = tesoro.getFila();
        int tesoroColumna = tesoro.getColumna();

        // Realizar copias de las posiciones actuales antes de intentar moverse
        int jugadorAntiguaFila = jugadorFila;
        int jugadorAntiguaColumna = jugadorColumna;

        int momiaAntiguaFila = momiaFila;
        int momiaAntiguaColumna = momiaColumna;

        int tesoroAntiguaFila = tesoroFila;
        int tesoroAntiguaColumna = tesoroColumna;

        // Obtener la dirección del movimiento del jugador desde la entrada del usuario
        switch (direccion)
        {
        case ARRIBA:
            jugadorFila--;
            break;
        case ABAJO:
            jugadorFila++;
            break;
        case IZQUIERDA:
            jugadorColumna--;
            break;
        case DERECHA:
            jugadorColumna++;
            break;
        }

        // Verificar si el movimiento del jugador es válido
        if (jugadorFila >= 0 && jugadorFila < FILAS && jugadorColumna >= 0 && jugadorColumna < COLUMNAS &&
            niveles[nivelActual].mapa[jugadorFila][jugadorColumna] != '#')
        {
            // El movimiento del jugador es válido
            jugador.setFila(jugadorFila);
            jugador.setColumna(jugadorColumna);

            momia.perseguirJugador(jugador, niveles[nivelActual].mapa);

            // Intentar mover a la momia
            if (!momia.moverse(direccion, niveles[nivelActual].mapa))
            {
                // El movimiento de la momia no fue válido
                // Restaurar la posición original de la momia
                momia.setFila(momiaAntiguaFila);
                momia.setColumna(momiaAntiguaColumna);
            }

            // Intentar mover al tesoro
            if (!tesoro.moverse(direccion, niveles[nivelActual].mapa))
            {
                // El movimiento del tesoro no fue válido
                // Restaurar la posición original del tesoro
                tesoro.setFila(tesoroAntiguaFila);
                tesoro.setColumna(tesoroAntiguaColumna);
            }

            // Verificar colisión con la momia
            if (jugadorFila == momiaFila && jugadorColumna == momiaColumna)
            {
                vidas--;
                if (vidas > 0)
                {
                    // Restaurar la posición del jugador y de la momia al inicial del nivel actual
                    resetearNivelActual();

                    cout << "¡Te atrapó la momia! Pierdes una vida. Vidas restantes: " << vidas << endl;

                    // Puedes agregar un mensaje adicional si deseas
                    cout << "¡Ten cuidado! Intenta de nuevo." << endl;
                }
                else
                {
                    cout << "¡La momia te atrapó! Fin del juego." << endl;

                    // Preguntar al usuario si quiere continuar jugando
                    char respuesta;
                    cout << "¿Quieres continuar jugando? (S/N): ";
                    cin >> respuesta;

                    if (respuesta == 'S' || respuesta == 's')
                    {
                        // Reiniciar el juego
                        nivelActual = 0;
                        vidas = 3;
                        resetearNivelActual();
                    }
                    else
                    {
                        return false; // Juego terminado
                    }
                }
            }

            // Verificar colisión con el tesoro
            if (jugadorFila == tesoroFila && jugadorColumna == tesoroColumna)
            {
                cout << "¡Encontraste el tesoro! ";

                if (nivelActual == niveles.size() - 1)
                {
                    cout << "¡Has completado el juego! Felicidades." << endl;
                    return false; // Juego terminado
                }
                else
                {
                    // Pasar al siguiente nivel
                    nivelActual++;
                    resetearNivelActual();
                    cout << "Nivel completado. ¡Bien hecho!" << endl;
                }
            }

            return true; // El juego continúa
        }

        // Restaurar la posición original del jugador si el movimiento no es válido
        jugador.setFila(jugadorAntiguaFila);
        jugador.setColumna(jugadorAntiguaColumna);

        return true; // El juego continúa
    }

    void ejecutarJuego()
    {
        //cout << "DEBUG: Iniciando el bucle del juego" << endl;

        bienvenida();

        while (true)
        {
// Limpiar la pantalla
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif

            

            // Agregar saltos de línea adicionales
            cout << endl;

            mostrarMapa();

            // Agregar saltos de línea adicionales
            cout << endl;

            char movimiento;
            cout << "Ingresa tu movimiento (W/A/S/D): ";
            cin >> movimiento;

            switch (movimiento)
            {
            case 'w':
            case 'W':
                direccion = ARRIBA;
                break;
            case 'a':
            case 'A':
                direccion = IZQUIERDA;
                break;
            case 's':
            case 'S':
                direccion = ABAJO;
                break;
            case 'd':
            case 'D':
                direccion = DERECHA;
                break;
            default:
                cout << "Movimiento no válido. Intenta de nuevo." << endl;
                continue; // Volver a solicitar movimiento
            }

            if (!verificarColisiones())
            {
                break; // El juego ha terminado
            }
        }

        //cout << "DEBUG: Fin del bucle del juego" << endl;
    }
};
bool Juego::moverJugador(Direcciones direccion)
{
    // Realizar copias de las posiciones actuales antes de intentar moverse
    int jugadorAntiguaFila = jugador.getFila();
    int jugadorAntiguaColumna = jugador.getColumna();

    // Intentar mover al jugador
    if (!jugador.moverse(direccion, niveles[nivelActual].mapa))
    {
        // El movimiento del jugador no fue válido
        return false;
    }

    // Verificar colisión con la momia
    if (jugador.getFila() == momia.getFila() && jugador.getColumna() == momia.getColumna())
    {
        vidas--;
        if (vidas > 0)
        {
            // Restaurar la posición original del jugador y de la momia
            jugador.setFila(jugadorAntiguaFila);
            jugador.setColumna(jugadorAntiguaColumna);
            momia.setFila(niveles[nivelActual].momiaInicial.first);
            momia.setColumna(niveles[nivelActual].momiaInicial.second);

            cout << "¡Te atrapó la momia! Pierdes una vida. Vidas restantes: " << vidas << endl;
        }
        else
        {
            cout << "¡La momia te atrapó! Fin del juego." << endl;
            return false; // Juego terminado
        }
    }

    // Mover a la momia después de que el jugador se haya movido
    momia.perseguirJugador(jugador, niveles[nivelActual].mapa);

    // Verificar colisión con el tesoro
    if (jugador.getFila() == tesoro.getFila() && jugador.getColumna() == tesoro.getColumna())
    {
        cout << "¡Encontraste el tesoro! Avanzas al siguiente nivel." << endl;
        nivelActual++;

        // Verificar si se completaron todos los niveles
        if (nivelActual == niveles.size())
        {
            cout << "¡Felicidades! Has completado todos los niveles." << endl;
            return false; // Juego terminado
        }

        resetearNivelActual();
    }

    return true; // El juego continúa
}

bool Juego::moverMomia(Direcciones direccion)
{
    return momia.moverse(direccion, niveles[nivelActual].mapa);
}

bool Juego::moverTesoro(Direcciones direccion)
{
    // El tesoro no se mueve, por lo que este método no hace nada
    return true;
}

int main()
{
    Juego juego;
    juego.ejecutarJuego();

    return 0;
}
