#ifndef AEROPORTO_H
#define AEROPORTO_H

#include "aviao.h"
#include "fila.h"
#include "lista_avioes.h"
#include "operacao.h"

typedef struct Aeroporto {
    ListaAvioes *LDISP;
    Fila FATE;
    Fila FDEC;
    Operacao *relatorio;
} Aeroporto;

void cadastra_aviao(Aeroporto *aeroporto, char *idAviao);
void avioes_cadastrados(Aeroporto *aeroporto, char letra);
void autoriza_decolar(Aeroporto *aeroporto, char *idAviao);
void decolar(Aeroporto *aeroporto);
void autoriza_aterrissar(Aeroporto *aeroporto, char *idAviao);
void aterrissar(Aeroporto *aeroporto);
void proximas_decolagens(Aeroporto *aeroporto);
void proximas_aterrissagens(Aeroporto *aeroporto);
void relatorio_aeroporto(Aeroporto *aeroporto);
void remover_aviao(Aeroporto *aeroporto, char *idAviao);
void consultar_historico(Aeroporto *aeroporto, char *idAviao);

#endif // AEROPORTO_H
