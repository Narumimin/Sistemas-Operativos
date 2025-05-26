#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <csignal>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

// Funciones en Menu
void mostrarMenu();

// Clase Usuario y funciones
class Usuario {
public:
    Usuario(string nombre, string clave, bool root);
    Usuario();
    string nombre;
    string clave;
    bool esRoot;
};

extern vector <Usuario> usuarios;
Usuario CrearUsuarioRoot();
Usuario CrearUsuario();

// Funciones para procesos

void crearProceso();
void suspenderProceso(pid_t pid);
void reanudarProceso(pid_t pid);

enum EstadoProceso { NUEVO, PAUSADO, EJECUTANDO, TERMINADO};
struct Proceso {
    int pid;                  // ID del proceso (simulado o real)
    string nombre;            // Nombre o descripción del proceso
    EstadoProceso estado;     // Estado del proceso
    int tiempoEjecucion;      // Tiempo que requiere (para Round Robin)
    int tiempoRestante;       // Tiempo restante (solo útil en Round Robin)
};
extern vector<Proceso> listaProcesos;

void crearProcesoSimulado(string nombre, int tiempo);
void mostrarProcesos();
void ejecutarFIFO();
void ejecutarRoundRobin(int quantum);

// Funciones para Archivos

struct Archivo {
    string nombre;
    string contenido;
    string propietario;
    bool permisoLectura;
    bool permisoEscritura;
    string fechaCreacion;
};
extern vector<Archivo> archivos;

void crearArchivo(const Usuario& usuario);
void leerArchivo(const Usuario& usuario);
void escribirArchivo(const Usuario& usuario);
void listarArchivos();
void editarPermisos(const Usuario& usuario);
string obtenerFechaActual();

//Funcion para logs
void registrarLog(const string& mensaje);


#endif