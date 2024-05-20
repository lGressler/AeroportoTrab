#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aviao.h"

// Função para criar um novo aviãozinho
Aviao* criarAviao(char *id) {
    Aviao *novoAviao = (Aviao*)malloc(sizeof(Aviao));
    strcpy(novoAviao->id, id);
    novoAviao->aterrissagens = 0;
    novoAviao->decolagens = 0;
    novoAviao->proximo = NULL;
    return novoAviao;
}
