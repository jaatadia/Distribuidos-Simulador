/* 
 * File:   Simulador.h
 * Author: knoppix
 *
 * Created on March 26, 2015, 1:53 PM
 */

#ifndef SIMULADOR_H
#define	SIMULADOR_H

#define MUSEO_CONF "./museo.cfg"
#define MUSEO_OPEN "MUSEO_OPEN"
#define MUSEO_CANT_GENTE "MUSEO_CANT"
#define MUSEO_PUERTAS "MUSEO_PUERTAS"

#define LOGGER_DEFAULT_PATH  "./log.txt"
#define PATH_PUERTA_EXEC "./Puerta"
#define DIRECTORIO_IPC "/home/knoppix/Atadia/Simulador"

#define PERMISOS 0660


#define MUSEO 100
#define MUTEX 101
#define PUERTA_FILA 102 //las sucesivas puertas van a tener PUERTA_FILE + 2 * nro_puerta
#define PUERTA_RESP 103 //las sucesivas puertas van a tener PUERTA_RESP + 2 * nro_puerta

typedef struct {
    bool estaAbierto;
    int personasAdentro;
} Museo;

#endif	/* SIMULADOR_H */

