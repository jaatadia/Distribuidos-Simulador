/* 
 * File:   Abrir.cpp
 * Author: knoppix
 *
 * Created on March 28, 2015, 8:50 PM
 */

#include <stdlib.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#include "Logger.h"
#include "Simulador.h"
#include "semaforo.h"

using namespace std;

#define CERRAR_ID "Cerrar"

int main(int argc, char** argv) {
    Logger::startLog(LOGGER_DEFAULT_PATH,CERRAR_ID);
    
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
    
    

    Logger::logg("Esperando el control sobre las puertas");
    if(p(mutex)==-1){
        Logger::loggError("Error al tomar el mutex");
        exit(1);   
    }
    Logger::logg("Cerrando el museo");
    myMuseum->estaAbierto=false;    
    Logger::logg("Liberando las puertas");
    if(v(mutex)==-1){
        Logger::loggError("Error al liberar el mutex");
    }    

    if ( shmdt(myMuseum) == -1 ){
        Logger::loggError("Error al desatachearse a la memoria compartida");
    }
    
    Logger::closeLogger();
    
    return 0;
}

