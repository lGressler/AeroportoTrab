#!/bin/bash

# Navega pra pasta src
cd src

# Compila os arquivos C
gcc -c aeroporto.c -I../include -o aeroporto.o
gcc -c aviao.c -I../include -o aviao.o
gcc -c fila.c -I../include -o fila.o
gcc -c lista_avioes.c -I../include -o lista_avioes.o
gcc -c operacao.c -I../include -o operacao.o
gcc -c main.c -I../include -o main.o

mkdir -p ../bin

gcc aeroporto.o aviao.o fila.o lista_avioes.o operacao.o main.o -o ../bin/EDAero

rm *.o

cd ..

echo "Compilation complete. Run ./bin/EDAero to execute the program."
