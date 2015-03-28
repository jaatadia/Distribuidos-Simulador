/* 
 * File:   main.cpp
 * Author: knoppix
 *
 * Created on March 24, 2015, 1:51 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sstream>

#include "Simulador.h"
#include "Logger.h"
#include "semaforo.h"

using namespace std;

void crearCarpeta(){
       
    //string commandoLimpiar=string("sudo rm -fr ")+DIRECTORIO_IPC;
    //Logger::logg(string("Borrando carpeta de IPCs")+DIRECTORIO_IPC);
    //system(commandoLimpiar.c_str());    
    
    string commandoCrear=string("sudo mkdir --mode=0777 -p ")+DIRECTORIO_IPC;
    Logger::logg(string("Creando carpeta de IPCs: ")+DIRECTORIO_IPC);
    system(commandoCrear.c_str());    

}

void crearMuseo(){
    
    Logger::logg("Creando la memoria compartida");
    int shmid;
    if( (shmid = shmget(ftok(DIRECTORIO_IPC,MUSEO), sizeof(Museo),IPC_CREAT|IPC_EXCL|PERMISOS)) == -1 ){
        Logger::loggError("Error al crear la memoria compartida");
        exit(1);   
    }
    
    Logger::logg("Uniendose a la memoria compartida");
    Museo* myMuseum;
    if ( (myMuseum = (Museo*) shmat(shmid,NULL,0)) == (Museo*) -1 ){
        Logger::loggError("Error al atachearse a la memoria compartida");
        exit(1);   
    }
    
    
    //TODO cargar configuracion de memoria un archivo
    Logger::logg("Inicializando la memoria compartida");
    myMuseum->estaAbierto=false;
    myMuseum->personasAdentro=0;
    
    Logger::logg("Desuniendose de la memoria compartida");
    if(shmdt(myMuseum)==-1){
        Logger::loggError("Error al desatachearse de la memoria compartida");
        exit(1);   
    }
    
    Logger::logg("Creando semaforo de exclusion mutua");
    int semid;
    if ((semid = creasem(MUTEX))== -1){
        Logger::loggError("Error al crear el semaforo de mutex");
        exit(1);   
    };
    
    Logger::logg("Inicializando el semaforo de exclusion mutua");
    if (inisem(semid,0)==-1){
        Logger::loggError("Error al inicializar semaforo de mutex");
        exit(1);   
    }
    
}


void crearPuertas(){
    //todo cargar cantidad de puertas desde archivo
    int childpid;
    for (int i=0;i<CANT_PUERTAS;i++){
        
        Logger::logg(string("Creando la puerta nro ")+PARAM_PUERTA[i]);
        
        //creo las colas para la puerta
        Logger::logg("Creando la cola de entrada");
        int cola;
        if( (cola = msgget(ftok(DIRECTORIO_IPC,PUERTA_FILA[i]),IPC_CREAT|IPC_EXCL|PERMISOS)) == -1){
            Logger::loggError("Error al crear la cola de entrada");
            exit(1);   
        }
        
        Logger::logg("Creando la cola de respuesta");
        if( (cola = msgget(ftok(DIRECTORIO_IPC,PUERTA_RESP[i]),IPC_CREAT|IPC_EXCL|PERMISOS)) == -1){
            Logger::loggError("Error al crear la cola de respuesta");
            exit(1);   
        }
        
        
        //TODO Preguntar sobre el pasaje del parametro
        Logger::logg("Creando el proceso puerta");
        //preparo los parametros para la puerta
        if ((childpid=fork())<0){
            Logger::loggError(string("Error al crear la puerta nro ") + PARAM_PUERTA[i]);
            exit(1);   
        }else if (childpid == 0){
            execlp(PATH_PUERTA_EXEC,"Puerta",PARAM_PUERTA[i],(char*)NULL);
            Logger::loggError(string("Error al cargar la imagen de ejecutable en la puerta nro ") + PARAM_PUERTA[i]);
            exit(1);
        }
    }
}

void crearClientes(){
    
}


#define INITIALIZER_ID "Initializer"
int main(int argc, char** argv) {
    
    Logger::startLog(LOGGER_DEFAULT_PATH,INITIALIZER_ID);
    crearCarpeta();
    crearMuseo();
    crearPuertas();
    crearClientes();
    Logger::closeLogger();
    
    return 0;
}

