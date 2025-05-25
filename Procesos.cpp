#include "Header.h"
vector<Proceso> listaProcesos;

// void crearProceso() {
//     pid_t pid = fork();

//     if (pid < 0) {
//         cout << "Error al crear el proceso.\n";
//         return;
//     }

//     if (pid == 0) {
//         // Este es el proceso hijo
//         cout << "Proceso hijo creado. PID: " << getpid() << endl;
//         execl("/bin/ls", "ls", "-l", NULL);  // reemplaza el proceso con 'ls -l'
//         cout << "Si ves esto, exec falló.\n";
//         exit(1);
//     } else {
//         // Este es el proceso padre
//         cout << "Proceso padre. Esperando al hijo (PID: " << pid << ")...\n";
//         wait(NULL);
//         cout << "Proceso hijo finalizado.\n";
//     }
// }

// void suspenderProceso(pid_t pid) {
//     if (kill(pid, SIGSTOP) == 0) {
//         cout << "Proceso " << pid << " suspendido.\n";
//     } else {
//         cout << "No se pudo suspender el proceso.\n";
//     }
// }

// void reanudarProceso(pid_t pid) {
//     if (kill(pid, SIGCONT) == 0) {
//         cout << "Proceso " << pid << " reanudado.\n";
//     } else {
//         cout << "No se pudo reanudar el proceso.\n";
//     }
// }

void crearProcesoSimulado(string nombre, int tiempo) {
    static int contadorPID = 1000;

    Proceso nuevo;
    nuevo.pid = contadorPID++;
    nuevo.nombre = nombre;
    nuevo.estado = NUEVO;
    nuevo.tiempoEjecucion = tiempo;
    nuevo.tiempoRestante = tiempo;

    listaProcesos.push_back(nuevo);
    cout << "Proceso \"" << nombre << "\" creado con PID " << nuevo.pid << " y tiempo de ejecución " << tiempo << ".\n";
    registrarLog("Se creo el proceso '" + nuevo.nombre + "' con PID '" + to_string(nuevo.pid) + "'");
}

void mostrarProcesos() {
    cout << "\n--- Lista de procesos ---\n";
    for (int i = 0; i < listaProcesos.size(); i++) {
        cout << "PID: " << listaProcesos[i].pid
             << " | Nombre: " << listaProcesos[i].nombre
             << " | Estado: " << listaProcesos[i].estado
             << " | Tiempo restante: " << listaProcesos[i].tiempoRestante << endl;
    }
}

void ejecutarFIFO() {
    cout << "\n--- Ejecución FIFO ---\n";
    for (int i = 0; i < listaProcesos.size(); i++) {
        cout << "\nEjecutando proceso " << listaProcesos[i].nombre << " (PID " << listaProcesos[i].pid << ")..." << endl;
        for(int j = 0; j < listaProcesos[i].tiempoEjecucion; j++) {
            sleep(1);
            cout << j+1 << "s\n";
        }
        listaProcesos[i].estado = TERMINADO;
        listaProcesos[i].tiempoRestante = 0;
        cout << "Proceso " << listaProcesos[i].pid << " terminado.\n";
    }
}

void ejecutarRoundRobin(int quantum) {
    cout << "\n--- Ejecución Round Robin (Quantum = " << quantum << ") ---\n";
    int cantidadCiclos = 0;
    bool procesosPendientes = true;
    while (procesosPendientes) {
        procesosPendientes = false;

        for (int i = 0; i < listaProcesos.size(); i++) {
            if (listaProcesos[i].estado == TERMINADO) continue;

            procesosPendientes = true;
            listaProcesos[i].estado = EJECUTANDO;

            int ejecucion = min(quantum, listaProcesos[i].tiempoRestante);
            cout << "\nProceso " << listaProcesos[i].nombre << " (PID " << listaProcesos[i].pid << ") ejecutando " << ejecucion << " segundos..." << endl;
            for(int j = 0; j < ejecucion; j++) {
                sleep(1);
                cout << j+1 << "s\n";
            }
            listaProcesos[i].tiempoRestante -= ejecucion;

            if (listaProcesos[i].tiempoRestante <= 0) {
                listaProcesos[i].estado = TERMINADO;
                cout << "Proceso " << listaProcesos[i].pid << " terminado.\n";
            } else {
                listaProcesos[i].estado = PAUSADO;
                cout << "Proceso " << listaProcesos[i].pid << " pausado. Tiempo restante: " << listaProcesos[i].tiempoRestante << endl;
            }
        }
        if(procesosPendientes){
            cantidadCiclos++;
            cout << "\nCiclo " << cantidadCiclos << " terminado\n- - - - - - -\n\n";
        }
    }
}