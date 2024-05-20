#ifndef OPERACAO_H
#define OPERACAO_H

typedef struct Operacao {
    char id[6];
    char tipo[12]; // "decola" ou "pousa"
    char horario[20];
    struct Operacao *proximo;
} Operacao;

Operacao* criarOperacao(char *id, char *tipo);

#endif // OPERACAO_H
