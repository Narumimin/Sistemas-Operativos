#include "Header.h"
vector<Proceso> listaProcesos;


void crearProceso() {
    pid_t pid = fork();

    if (pid < 0) {
        cout << "Error al crear el proceso.\n";
        return;
    }

    if (pid == 0) {
        // Este es el proceso hijo
        cout << "Proceso hijo creado. PID: " << getpid() << endl;
        execl("/bin/ls", "ls", "-l", NULL);  // reemplaza el proceso con 'ls -l'
        cout << "Si ves esto, exec falló.\n";
        exit(1);
    } else {
        // Este es el proceso padre
        cout << "Proceso padre. Esperando al hijo (PID: " << pid << ")...\n";
        wait(NULL);
        cout << "Proceso hijo finalizado.\n";
    }
}

void suspenderProceso(pid_t pid) {
    if (kill(pid, SIGSTOP) == 0) {
        cout << "Proceso " << pid << " suspendido.\n";
    } else {
        cout << "No se pudo suspender el proceso.\n";
    }
}

void reanudarProceso(pid_t pid) {
    if (kill(pid, SIGCONT) == 0) {
        cout << "Proceso " << pid << " reanudado.\n";
    } else {
        cout << "No se pudo reanudar el proceso.\n";
    }
}

void crearProcesoSimulado(string nombre, int tiempo) {
    int contadorPID = 1000;

    Proceso nuevo;
    nuevo.pid = contadorPID++;
    nuevo.nombre = nombre;
    nuevo.estado = NUEVO;
    nuevo.tiempoEjecucion = tiempo;
    nuevo.tiempoRestante = tiempo;

    listaProcesos.push_back(nuevo);
    cout << "Proceso \"" << nombre << "\" creado con PID " << nuevo.pid << " y tiempo de ejecución " << tiempo << ".\n";
}

void mostrarProcesos() {
    cout << "\n--- Lista de procesos ---\n";
    for (const auto& p : listaProcesos) {
        cout << "PID: " << p.pid
             << " | Nombre: " << p.nombre
             << " | Estado: " << p.estado
             << " | Tiempo restante: " << p.tiempoRestante << endl;
    }
}