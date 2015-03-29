/* 
 * File:   Puerta.cpp
 * Author: knoppix
 *
 * Created on March 26, 2015, 2:00 PM
 */

#include <stdlib.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>

#include "Logger.h"
#include "Simulador.h"
#include "semaforo.h"

using namespace std;


#define PUERTA_ID "PUERTA"

//en argv[1] el numero de puerta, argv[2] la cantidad de personas
int main(int argc, char** argv) {
    if (argc != 3 ){
        Logger::startLog(LOGGER_DEFAULT_PATH,PUERTA_ID);
        Logger::loggError("No se pasaron los parametros correctos 1: numero de puerta 2: cantidad de personas");
        exit(1);
    }
    
    int numero = atoi(argv[1]);
    int personas = atoi(argv[2]);
    string puertaid=string(PUERTA_ID)+argv[1];
    Logger::startLog(LOGGER_DEFAULT_PATH,puertaid.c_str());
    
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
   /*
    //busco las colas
    Logger::logg("Buscando la cola de entrada");
    int colaEntrada,colaRespuesta;
    if( (colaEntrada = msgget(ftok(DIRECTORIO_IPC,PUERTA_FILA + 2 * numero),PERMISOS)) == -1){
        Logger::loggError("Error al encontrar la cola de entrada");
        exit(1);   
    }

    Logger::logg("Buscando la cola de respuesta");
    if( (colaRespuesta = msgget(ftok(DIRECTORIO_IPC,PUERTA_RESP + 2 * numero),PERMISOS)) == -1){
        Logger::loggError("Error al encontrar la cola de respuesta");
        exit(1);   
    }
    */
    srand(time(NULL));
    for (int i=0;i<100;i++){rand();};
    
    
    for(int i=0;i<personas;i++){ 
        
        usleep(rand()%100000);
        
        Logger::logg("Esperando el control de la puerta");
        if(p(mutex)==-1){
            Logger::loggError("Error al pedir el mutex");
            exit(1);   
        }
        Logger::logg("Consegui el control de la puerta");
        
        if (!myMuseum->estaAbierto){
            while (myMuseum->personasAdentro > 0){
                myMuseum->personasAdentro--;
                std::stringstream ss;
                ss<<myMuseum->personasAdentro;
                Logger::logg("Salio una persona. Personas adentro: "+ss.str());
            }
        }else{
            std::string mensaje;
            std::stringstream ss;
            if(rand()%2==0){//entrar
                if(myMuseum->personasAdentro<MUSEO_MAX){
                    myMuseum->personasAdentro++;
                    mensaje="Entro una persona.";
                }else{
                    mensaje="No pudo entrar la persona, el museo esta lleno.";
                }
       
            }else{//salir
                if(myMuseum->personasAdentro>0){
                    myMuseum->personasAdentro--;
                    mensaje="Salio una persona.";
                }else{
                    mensaje="No pudo salir la persona, el museo esta vacio.";
                }
            }
            ss<<myMuseum->personasAdentro;
            Logger::logg(mensaje+" Personas adentro: "+ss.str());
            
            if(v(mutex)==-1){
                Logger::loggError("Error al liberar el mutex");
                exit(1);   
            }    
        }
    }

}
