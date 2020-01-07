#*****************************************************************
# File:   Makefile
# Author: Andrés Gavín Murillo, 716358
# Author: Darío Ferrer Chueca, 721132
# Date:   Enero 2020
# Coms:   Algoritmia para Problemas Difíciles - Práctica 1
#         Ejecutar "make" para compilar (o "make -f Makefile")
#         Ejecutar "make clean" para limpiar (borrar lo que genere)
#*****************************************************************

#---------------------------------------------------------
# macros
RM = /bin/rm -f  # para limpiar
CC = g++         # compilador
#---------------------------------------------------------
# compilación y enlazado ("linkado")
CPPFLAGS=-I. -O3 -std=c++11 -fmax-errors=1 # opciones compilación
#---------------------------------------------------------
# vars
EJEC = practica1
MAIN = main
PR = Producto
CP = ConjuntoProductos

all: ${EJEC}
#---------------------------------------------------------
# "linkar"
${EJEC}: ${MAIN}.o ${PR}.o ${CP}.o
	${CC} ${MAIN}.o ${PR}.o ${CP}.o -o ${EJEC} ${CPPFLAGS}

#---------------------------------------------------------
# compilar
${MAIN}.o: ${MAIN}.cpp ${PR}.hpp ${PR}.cpp ${CP}.hpp ${CP}.cpp
	${CC} -c ${MAIN}.cpp ${CPPFLAGS}

${PR}.o: ${PR}.hpp ${PR}.cpp
	${CC} -c ${PR}.cpp ${CPPFLAGS}

${CP}.o: ${CP}.hpp ${CP}.cpp
	${CC} -c ${CP}.cpp ${CPPFLAGS}

#---------------------------------------------------------
# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	$(RM) ${MAIN}.o ${PR}.o ${CP}.o ${EJEC}
