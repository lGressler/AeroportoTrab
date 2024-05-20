#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "operacao.h"

// Função para obter o horário atual como string
void obterHorarioAtual(char *buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d", 
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, 
            tm.tm_hour, tm.tm_min, tm.tm_sec);
}

// Função para criar uma nova operação
Operacao* criarOperacao(char *id, char *tipo) {
    Operacao *novaOperacao = (Operacao*)malloc(sizeof(Operacao));
    strcpy(novaOperacao->id, id);
    strcpy(novaOperacao->tipo, tipo);
    obterHorarioAtual(novaOperacao->horario);
    novaOperacao->proximo = NULL;
    return novaOperacao;
}
