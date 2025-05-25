#include "Header.h"
#include "Usuarios.cpp"
#include "Menu.cpp"
#include "Procesos.cpp"
#include "Archivos.cpp"

vector <Usuario> usuarios;

int main() {

    setlocale(LC_ALL, "");
    
    Usuario usuarioRoot = CrearUsuarioRoot();
    usuarios.push_back(usuarioRoot);
    char login, opcion, tipoProceso;
    bool usuarioEncontrado = false;
    Usuario usuarioActual;
    string entrada_nombre, entrada_clave;
    string nombreProceso;
    int tiempoProceso;

    do {
        cout << "\n---- PANTALLA DE INICIO ----\n";
        cout << "1. Iniciar Sesion\n";
        cout << "2. Crear nuevo usuario\n";
        cout << "0. Salir\n-> ";
        cin >> login;
        cin.ignore();

        switch (login)
        {
        case '1':
            cout << "\n---- LOG IN ----\n";
            cout << "Ingrese el nombre de usuario: ";
            getline(cin, entrada_nombre);
            cout << "Ingrese la contraseña: ";
            getline(cin, entrada_clave);

            usuarioEncontrado = false;
            for (int i = 0; i < usuarios.size(); i++) {
                if (entrada_nombre == usuarios[i].nombre && entrada_clave == usuarios[i].clave)
                {
                    usuarioEncontrado = true;
                    usuarioActual = usuarios[i];
                }
            }
            break;

        case '2':
            usuarios.push_back(CrearUsuario());
            break;

        case '0':
            cout << "\nSaliendo del sistema...\n";
            break;

        default:
            cout << "Opción inválida\n";
            break;
        }

        if (usuarioEncontrado) {
            do {
                mostrarMenu();
                cout << "Seleccione una opción: ";
                cin >> opcion;
                cin.ignore();

                switch (opcion) {
                case '1':
                    //crearProceso();
                    break;

                case '2':
                    cout << "\nIngrese el nombre del proceso: ";
                    getline(cin, nombreProceso);
                    cout << "Ingrese el tiempo de duracion del proceso en segundos: ";
                    cin >> tiempoProceso;
                    cin.ignore();
                    crearProcesoSimulado(nombreProceso, tiempoProceso);
                    break;

                case '3':
                    mostrarProcesos();
                    break;

                case '4':
                    cout << "Elegir algoritmo (f: FIFO, r: Round Robin): ";
                    cin >> tipoProceso;

                    if (tipoProceso == 'f') {
                        ejecutarFIFO();
                    } 
                    else if (tipoProceso == 'r') {
                        int quantum;
                        cout << "Ingresa quantum: ";
                        cin >> quantum;
                        ejecutarRoundRobin(quantum);
                    }
                    break;

                case '5':
                    crearArchivo(usuarioActual);
                    break;

                case '6':
                    escribirArchivo(usuarioActual);
                    break;

                case '7':
                    leerArchivo(usuarioActual);
                    break;

                case '8':
                    listarArchivos();
                    break;

                case '0':
                    usuarioEncontrado = false;
                    cout << "\nCerrando Sesion...\n";
                    break;

                default:
                    cout << "\nOpción inválida\n";
                }

            } while (opcion != '0');
        }
        else if (!usuarioEncontrado && login == '1')
        {
            cout << "!!! ERROR: Nombre de usuario o contraseña invalida !!!\n";
        }
    } while (login != '0');
    return 0;
}