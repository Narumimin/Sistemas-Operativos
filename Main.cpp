#include "Header.h"
#include "Usuarios.cpp"
#include "Menu.cpp"
#include "Procesos.cpp"

int main() {

    setlocale(LC_ALL, "");

    vector <Usuario> usuarios;
    Usuario usuarioRoot = CrearUsuarioRoot();
    usuarios.push_back(usuarioRoot);
    char login;
    char opcion;
    bool usuarioEncontrado = false;
    Usuario usuarioActual;
    string entrada_nombre, entrada_clave;
    string nombreProceso;
    int tiempoProceso;

    do {
        cout << "\n----\tPANTALLA DE INICIO\t----\n";
        cout << "1. Iniciar Sesion\n";
        cout << "2. Crear nuevo usuario\n";
        cout << "0. Salir\n->";
        cin >> login;
        cin.ignore();

        switch (login)
        {
        case '1':
            cout << "\n----\tLOG IN\t----\n";
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
                    crearProceso();
                    break;

                case '2':
                    cout << "Ingrese el nombre del proceso: ";
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
                    //leerArchivo(usuario_actual);
                    break;

                case '5':
                    //escribirArchivo(usuario_actual);
                    break;

                case '6':
                    //listarArchivos();
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
        else if (!usuarioEncontrado && login != '0')
        {
            cout << "!!! ERROR: Nombre de usuario o contraseña invalida !!!\n";
        }
    } while (login != '0');
    return 0;
}