#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#---------------------------- PARAMETROS-----------------------
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#parametros generales
PARAMETROS = g++ -Wall -g
PROYECT = .
RELEASE = $(PROYECT)/Release
OBJECTS = $(PROYECT)/Objects
PROCESOS = initializer puerta
SRC = ./Simulador

#parametros para la compilacion del proceso initializer
PATH_INIT = ./Simulador
OBJETOS_INIT = semaforo.o Logger.o
INIT_SOURCE = initializer.cpp
INIT_EXE = initializer

all: $(PROYECTO)

#////////////////////////INITIALIZER////////////////////
initializer: carpetas
	@echo
	#-----------compilando ninio-----------
	@echo 
	#1.compilando dependencias
	for i in $(OBJETOS_INIT); do $(PARAMETROS) -c $(PATH_INIT)/$${i%.*}.cpp $(OBJECTS);done 
	#2.creando ejecutable ninio
	#$(PARAMETROS) $(OBJETOS_INIT) $(PATH_INIT)/$(INIT_SOURCE) -o $(RELEASE)/$(INIT_EXE)

	#3.eliminando archivos temporales
	#rm -f $(OBJETOS_NINIO)


#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#---------------------------- Otros Comandos -------------------------------
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

carpetas:
	mkdir -p $(RELEASE)mak
	mkdir -p $(OBJECTS)


clean: clear
	rm -f -r $(RELEASE) *.o

$(PROYECTO): $(PROCESOS)
	
