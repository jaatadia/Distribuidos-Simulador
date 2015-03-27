/* 
 * File:   Puerta.cpp
 * Author: knoppix
 *
 * Created on March 26, 2015, 2:00 PM
 */

#include <cstdlib>
#include <iostream>
#include "Logger.h"
#include "Simulador.h"
#include "semaforo.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/types.h>

using namespace std;


#define PUERTA_ID "PUERTA"

//en arv[1] el numero de puerta
int main(int argc, char** argv) {
    if ((argc == 1) || (atoi(argv[1]) < 0) || (atoi(argv[1])>=CANT_PUERTAS)){
        Logger::startLog(LOGGER_DEFAULT_PATH,PUERTA_ID);
        Logger::loggError("No se paso el numero de puerta correcto como parametro");
        exit(1);
    }
    
    int numero = atoi(argv[1]);
    Logger::startLog(LOGGER_DEFAULT_PATH,(string(PUERTA_ID)+argv[1]).c_str());
    
    Logger::logg("Obteniendo el mutex");
    int mutex;
    if ( (mutex = getsem(MUTEX)) == -1){
        Logger::loggError("No se pudo encontrar el mutex");
        exit(1);
    };
    
    Logger::logg("Obteniendo el museo");
    int shmid;
    if( (shmid = shmget(ftok(DIRECTORIO_IPC,MUSEO), sizeof(Museo),PERMISOS)) == -1 ){
        Logger::loggError("Error al encontrar la memoria compartida");
        exit(1);   
    }
    
    Logger::logg("Uniendose al museo");
    Museo* myMuseum;
    if ( (myMuseum = (Museo*) shmat(shmid,NULL,0)) == (Museo*) -1 ){
        Logger::loggError("Error al atachearse a la memoria compartida");
        exit(1);   
    }
    
    //busco las colas
    Logger::logg("Buscando la cola de entrada");
    int colaEntrada,colaRespuesta;
    if( (colaEntrada = msgget(ftok(DIRECTORIO_IPC,PUERTA_FILA[numero]),IPC_CREAT|IPC_EXCL|PERMISOS)) == -1){
        Logger::loggError("Error al encontrar la cola de entrada");
        exit(1);   
    }

    Logger::logg("Buscando la cola de respuesta");
    if( (colaRespuesta = msgget(ftok(DIRECTORIO_IPC,PUERTA_RESP[numero]),IPC_CREAT|IPC_EXCL|PERMISOS)) == -1){
        Logger::loggError("Error al encontrar la cola de respuesta");
        exit(1);   
    }
    
    
}