#ifndef AVIAO_H
#define AVIAO_H

typedef struct Aviao {
    char id[6]; // Codigo do aviaozinho
    int aterrissagens;
    int decolagens;
    struct Aviao *proximo;
} Aviao;

Aviao* criarAviao(char *id);

#endif // AVIAO_H
