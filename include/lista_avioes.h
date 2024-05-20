#ifndef LISTA_AVIOES_H
#define LISTA_AVIOES_H

#include "aviao.h"

typedef struct ListaAvioes {
    char letra; // Letra inicial do codigos dos avioes
    Aviao *primeiro;
    struct ListaAvioes *proximo;
} ListaAvioes;

#endif // LISTA_AVIOES_H
