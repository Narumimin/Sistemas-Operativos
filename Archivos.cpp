#include "Header.h"
vector<Archivo> archivos;

void crearArchivo(const Usuario& usuario) {
    Archivo nuevo;
    cout << "Nombre del archivo: ";
    getline(cin, nuevo.nombre);
    nuevo.propietario = usuario.nombre;
    nuevo.permisoLectura = true;
    nuevo.permisoEscritura = true;
    nuevo.contenido = "";
    nuevo.fechaCreacion = obtenerFechaActual();

    archivos.push_back(nuevo);
    cout << "Archivo creado exitosamente.\n";
    registrarLog("El usuario '" + usuario.nombre + "' creó el archivo '" + nuevo.nombre + "'");
}

void escribirArchivo(const Usuario& usuario) {
    string nombre;
    cout << "Nombre del archivo a escribir: ";
    getline(cin, nombre);

    for (int i = 0; i < archivos.size(); i++) {
        if (archivos[i].nombre == nombre) {
            if (archivos[i].permisoEscritura || archivos[i].propietario == usuario.nombre || usuario.esRoot) {
                cout << "Nuevo contenido: ";
                string nuevoContenido;
                getline(cin, nuevoContenido);
                archivos[i].contenido = nuevoContenido;
                cout << "Escritura exitosa.\n";
                registrarLog("El usuario '" + usuario.nombre + "' cambio el contenido del archivo '" + archivos[i].nombre + "'");
                return;
            } else {
                cout << "Permiso denegado.\n";
                registrarLog("Acceso denegado: '" + usuario.nombre + "' intentó escribir en el archivo '" + archivos[i].nombre + "'");
                return;
            }
        }
    }
    cout << "Archivo no encontrado.\n";
}

void leerArchivo(const Usuario& usuario) {
    string nombre;
    cout << "Nombre del archivo a leer: ";
    getline(cin, nombre);

    for (int i = 0; i < archivos.size(); i++) {
        if (archivos[i].nombre == nombre) {
            if (archivos[i].permisoLectura || archivos[i].propietario == usuario.nombre || usuario.esRoot) {
                cout << "Contenido: " << archivos[i].contenido << endl;
                registrarLog("El usuario '" + usuario.nombre + "' leyo el contenido del archivo '" + archivos[i].nombre + "'");
                return;
            } else {
                cout << "Permiso denegado.\n";
                registrarLog("Acceso denegado: '" + usuario.nombre + "' intentó leer el archivo '" + archivos[i].nombre + "'");
                return;
            }
        }
    }
    cout << "Archivo no encontrado.\n";
}

void listarArchivos() {
    cout << "\nArchivos disponibles:\n";
    for (int i = 0; i < archivos.size(); i++) {
        cout << "- " << archivos[i].nombre 
        << " (Propietario: " << archivos[i].propietario    
        << " | Lectura: " << (archivos[i].permisoLectura ? "Sí" : "No")
        << " | Escritura: " << (archivos[i].permisoEscritura ? "Sí" : "No")
        << " | Creado: " << archivos[i].fechaCreacion
        << ")" << endl;
    }
}

void editarPermisos(const Usuario &usuario)
{
    listarArchivos();

    string nombre;
    cout << "Nombre del archivo a editar: ";
    getline(cin, nombre);

    for (int i = 0; i < archivos.size(); i++) {
        if (archivos[i].nombre == nombre) {
            if(archivos[i].propietario == usuario.nombre || usuario.esRoot){
                char nuevaLectura, nuevaEscritura;
                cout << "¿Permitir lectura? (s/n): ";
                cin >> nuevaLectura;
                cout << "¿Permitir escritura? (s/n): ";
                cin >> nuevaEscritura;
                cin.ignore();

                if(nuevaEscritura == 's' || nuevaEscritura == 'S'){
                    archivos[i].permisoEscritura = true;
                }
                else{
                    archivos[i].permisoEscritura = false;
                }   

                if(nuevaLectura == 's' || nuevaLectura == 'S'){
                    archivos[i].permisoLectura = true;
                }
                else{
                    archivos[i].permisoLectura = false;
                }
                cout << "Permisos actualizados correctamente.\n";
                registrarLog("El usuario '" + usuario.nombre + "' cambio los permisos del archivo'" + archivos[i].nombre + "'");
                return;
            }
            else{
                cout << "No tienes permiso para modificar este archivo.\n";
                registrarLog("Acceso denegado: '" + usuario.nombre + "' intentó cambiar los permisos del archivo '" + archivos[i].nombre + "'");
                return;
            }
        }
    }
    cout << "Archivo no encontrado.\n";
}


string obtenerFechaActual() {
    time_t ahora = time(0);
    tm* tiempoLocal = localtime(&ahora);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", tiempoLocal);
    return string(buffer);
}

void registrarLog(const string& mensaje) {
    ofstream logFile("log.txt", ios::app);
    if (logFile.is_open()) {
        logFile << "[" << obtenerFechaActual() << "] " << mensaje << endl;
        logFile.close();
    }
}