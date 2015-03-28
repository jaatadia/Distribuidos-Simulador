/* 
 * File:   Simulador.h
 * Author: knoppix
 *
 * Created on March 26, 2015, 1:53 PM
 */

#ifndef SIMULADOR_H
#define	SIMULADOR_H

#define DIRECTORIO_IPC "/home/knoppix/Atadia/Simulador"
#define PERMISOS 0660


#define MUSEO 100
#define MUTEX 101

#define PATH_PUERTA_EXEC "./Puerta"
#define CANT_PUERTAS 2

static const int  PUERTA_FILA[2] = {102,104};
static const int  PUERTA_RESP[2] = {103,105};
static const char*  PARAM_PUERTA[2] = {"0","1"};

typedef struct {
    bool estaAbierto;
    int personasAdentro;
} Museo;

#endif	/* SIMULADOR_H */

