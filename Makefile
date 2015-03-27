#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#---------------------------- PARAMETROS-----------------------
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#parametros generales
PARAMETROS = g++ -Wall -g
PROYECTO = Simulador
PROYECT = .
RELEASE = $(PROYECT)/Release
OBJECTS = $(PROYECT)/Objects
PROCESOS = Initializer Puerta
SRC = ./Simulador

#parametros para la compilacion del proceso initializer
OBJETOS_INIT = semaforo.o Logger.o
INIT_SOURCE = Initializer.cpp
INIT_EXE = Initializer

#parametros para la compilacion del proceso initializer
OBJETOS_PUERTA = semaforo.o Logger.o
PUERTA_SOURCE = Puerta.cpp
PUERTA_EXE = Puerta


all: $(PROYECTO)

#////////////////////////INITIALIZER////////////////////
Initializer: carpetas
	@echo
	#-----------compilando-----------
	@echo 
	#1.compilando dependencias
	for i in $(OBJETOS_INIT); do $(PARAMETROS) $(SRC)/$${i%.*}.cpp -c -o $(OBJECTS)/$$i;done 
	#2.creando ejecutable
	var="";for i in $(OBJETOS_INIT); do var="$$var $(OBJECTS)/$$i";done;$(PARAMETROS) $$var $(SRC)/$(INIT_SOURCE) -o $(RELEASE)/$(INIT_EXE)

#////////////////////////Puerta////////////////////
Puerta: carpetas
	@echo
	#-----------compilando-----------
	@echo 
	#1.compilando dependencias
	for i in $(OBJETOS_PUERTA); do $(PARAMETROS) $(SRC)/$${i%.*}.cpp -c -o $(OBJECTS)/$$i;done 
	#2.creando ejecutable
	var="";for i in $(OBJETOS_PUERTA); do var="$$var $(OBJECTS)/$$i";done;$(PARAMETROS) $$var $(SRC)/$(PUERTA_SOURCE) -o $(RELEASE)/$(PUERTA_EXE)




#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#---------------------------- Otros Comandos -------------------------------
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

carpetas:
	mkdir -p $(RELEASE)
	mkdir -p $(OBJECTS)
	cp ./IPC_RM.sh $(RELEASE)


clean:
	rm -f -r $(RELEASE)
	rm -f -r $(OBJECTS)
	./IPC_RM.sh

$(PROYECTO): $(PROCESOS)
	
