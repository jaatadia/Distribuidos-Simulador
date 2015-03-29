#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#---------------------------- PARAMETROS-----------------------
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#parametros generales
PARAMETROS = g++ -Wall -g
PROYECTO = Simulador
PROYECT = .
RELEASE = $(PROYECT)/Release
OBJECTS = $(PROYECT)/Objects
PROCESOS = Initializer Puerta Destroyer Cerrar Abrir
SRC = ./Simulador

OBJETOS = semaforo.o Logger.o Parser.o

#parametros para la compilacion del proceso initializer
OBJETOS_INIT = semaforo.o Logger.o Parser.o
INIT_SOURCE = Initializer.cpp
INIT_EXE = Initializer

#parametros para la compilacion del proceso Destroyer
OBJETOS_DEST = semaforo.o Logger.o Parser.o
DEST_SOURCE = Destroyer.cpp
DEST_EXE = Destroyer

#parametros para la compilacion del proceso puerta
OBJETOS_PUERTA = semaforo.o Logger.o
PUERTA_SOURCE = Puerta.cpp
PUERTA_EXE = Puerta

#parametros para la compilacion del proceso abrir
OBJETOS_ABRIR = semaforo.o Logger.o
ABRIR_SOURCE = Abrir.cpp
ABRIR_EXE = Abrir

#parametros para la compilacion del proceso cerrar
OBJETOS_CERRAR = semaforo.o Logger.o
CERRAR_SOURCE = Cerrar.cpp
CERRAR_EXE = Cerrar


all: $(PROYECTO)

#////////////////////////Objetos////////////////////
Objetos:
	@echo
	#-----------compilando-----------
	for i in $(OBJETOS); do $(PARAMETROS) $(SRC)/$${i%.*}.cpp -c -o $(OBJECTS)/$$i;done 

#////////////////////////INITIALIZER////////////////////
Initializer: carpetas Objetos
	@echo
	#-----------compilando-----------
	var="";for i in $(OBJETOS_INIT); do var="$$var $(OBJECTS)/$$i";done;$(PARAMETROS) $$var $(SRC)/$(INIT_SOURCE) -o $(RELEASE)/$(INIT_EXE)


#////////////////////////Destroyer////////////////////
Destroyer: carpetas Objetos
	@echo
	#-----------compilando-----------
	var="";for i in $(OBJETOS_DEST); do var="$$var $(OBJECTS)/$$i";done;$(PARAMETROS) $$var $(SRC)/$(DEST_SOURCE) -o $(RELEASE)/$(DEST_EXE)




#////////////////////////Puerta////////////////////
Puerta: carpetas Objetos
	@echo
	#-----------compilando-----------
	var="";for i in $(OBJETOS_PUERTA); do var="$$var $(OBJECTS)/$$i";done;$(PARAMETROS) $$var $(SRC)/$(PUERTA_SOURCE) -o $(RELEASE)/$(PUERTA_EXE)

#////////////////////////Abrir////////////////////
Abrir: carpetas Objetos
	@echo
	#-----------compilando-----------
	var="";for i in $(OBJETOS_ABRIR); do var="$$var $(OBJECTS)/$$i";done;$(PARAMETROS) $$var $(SRC)/$(ABRIR_SOURCE) -o $(RELEASE)/$(ABRIR_EXE)

#////////////////////////Cerrar////////////////////
Cerrar: carpetas Objetos
	@echo
	#-----------compilando-----------
	var="";for i in $(OBJETOS_CERRAR); do var="$$var $(OBJECTS)/$$i";done;$(PARAMETROS) $$var $(SRC)/$(CERRAR_SOURCE) -o $(RELEASE)/$(CERRAR_EXE)

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#---------------------------- Otros Comandos -------------------------------
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

carpetas:
	mkdir -p $(RELEASE)
	mkdir -p $(OBJECTS)
	cp ./IPC_RM.sh $(RELEASE)
	cp ./museo.cfg $(RELEASE)


clean:
	rm -f -r $(RELEASE)
	rm -f -r $(OBJECTS)
	./IPC_RM.sh

$(PROYECTO): $(PROCESOS)
	
