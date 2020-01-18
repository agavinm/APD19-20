#*****************************************************************
# File:   Makefile
# Author: Andrés Gavín Murillo, 716358
# Author: Darío Ferrer Chueca, 721132
# Date:   Enero 2020
# Coms:   Algoritmia para Problemas Difíciles - Práctica 2
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
EJEC = practica2
MAIN = main
VS = VectorSufijos
BW = BurrowsWheeler
AR = arbol
HE = heap
HU = huffman

all: ${EJEC}
#---------------------------------------------------------
# "linkar"
${EJEC}: ${MAIN}.o ${VS}.o ${BW}.o ${AR}.o ${HE}.o ${HU}.o
	${CC} ${MAIN}.o ${VS}.o ${BW}.o ${AR}.o ${HE}.o ${HU}.o -o ${EJEC} ${CPPFLAGS}

#---------------------------------------------------------
# compilar
${MAIN}.o: ${MAIN}.cpp ${VS}.hpp ${VS}.cpp ${BW}.hpp ${BW}.cpp Huffman-AB1/${AR}.hpp Huffman-AB1/${AR}.cpp Huffman-AB1/${HE}.hpp Huffman-AB1/${HE}.cpp Huffman-AB1/${HU}.hpp Huffman-AB1/${HU}.cpp
	${CC} -c ${MAIN}.cpp ${CPPFLAGS}

${VS}.o: ${VS}.hpp ${VS}.cpp
	${CC} -c ${VS}.cpp ${CPPFLAGS}

${BW}.o: ${BW}.hpp ${BW}.cpp
	${CC} -c ${BW}.cpp ${CPPFLAGS}

${AR}.o: Huffman-AB1/${AR}.hpp Huffman-AB1/${AR}.cpp
	${CC} -c Huffman-AB1/${AR}.cpp ${CPPFLAGS}

${HE}.o: Huffman-AB1/${HE}.hpp Huffman-AB1/${HE}.cpp
	${CC} -c Huffman-AB1/${HE}.cpp ${CPPFLAGS}

${HU}.o: Huffman-AB1/${HU}.hpp Huffman-AB1/${HU}.cpp
	${CC} -c Huffman-AB1/${HU}.cpp ${CPPFLAGS}

#---------------------------------------------------------
# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	$(RM) ${MAIN}.o ${VS}.o ${BW}.o ${AR}.o ${HE}.o ${HU}.o
