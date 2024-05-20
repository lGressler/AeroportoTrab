#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "aeroporto.h"
#include "aviao.h"
#include "fila.h"
#include "lista_avioes.h"
#include "operacao.h"

// Implementações das funções de Aeroporto: 
void cadastra_aviao(Aeroporto *aeroporto, char *idAviao) {
    char letraInicial = idAviao[0];
    ListaAvioes *letraAtual = aeroporto->LDISP, *letraAnterior = NULL;
    
    // Procura a lista correspondente à letra inicial
    while (letraAtual != NULL && letraAtual->letra < letraInicial) {
        letraAnterior = letraAtual;
        letraAtual = letraAtual->proximo;
    }
    
    // Se a lista da letra inicial não existe, cria
    if (letraAtual == NULL || letraAtual->letra != letraInicial) {
        ListaAvioes *novaLetra = (ListaAvioes*)malloc(sizeof(ListaAvioes));
        novaLetra->letra = letraInicial;
        novaLetra->primeiro = NULL;
        novaLetra->proximo = letraAtual;
        
        if (letraAnterior == NULL) {
            aeroporto->LDISP = novaLetra;
        } else {
            letraAnterior->proximo = novaLetra;
        }
        letraAtual = novaLetra;
    }
    
    // Insere o aviao na lista ordenada pela identificação
    Aviao *novoAviao = criarAviao(idAviao);
    Aviao *aviaoAtual = letraAtual->primeiro, *aviaoAnterior = NULL;
    
    while (aviaoAtual != NULL && strcmp(aviaoAtual->id, idAviao) < 0) {
        aviaoAnterior = aviaoAtual;
        aviaoAtual = aviaoAtual->proximo;
    }
    
    if (aviaoAnterior == NULL) {
        letraAtual->primeiro = novoAviao;
    } else {
        aviaoAnterior->proximo = novoAviao;
    }
    novoAviao->proximo = aviaoAtual;

}

void avioes_cadastrados(Aeroporto *aeroporto, char letra) {
    ListaAvioes *letraAtual = aeroporto->LDISP;
    
    while (letraAtual != NULL) {
        if (letra == '\0' || letraAtual->letra == letra) {
            Aviao *aviaoAtual = letraAtual->primeiro;
            while (aviaoAtual != NULL) {
                printf("ID: %s, Aterrissagens: %d, Decolagens: %d\n", aviaoAtual->id, aviaoAtual->aterrissagens, aviaoAtual->decolagens);
                aviaoAtual = aviaoAtual->proximo;
            }
        }
        letraAtual = letraAtual->proximo;
    }
}

void autoriza_decolar(Aeroporto *aeroporto, char *idAviao) {
    Aviao *novoAviao = criarAviao(idAviao);
    if (aeroporto->FDEC.ultimo == NULL) {
        aeroporto->FDEC.primeiro = novoAviao;
        aeroporto->FDEC.ultimo = novoAviao;
    } else {
        aeroporto->FDEC.ultimo->proximo = novoAviao;
        aeroporto->FDEC.ultimo = novoAviao;
    }
}

void decolar(Aeroporto *aeroporto) {
    if (aeroporto->FDEC.primeiro == NULL) {
        printf("Nenhuma decolagem autorizada.\n");
        return;
    }
    
    Aviao *aviaoDecolado = aeroporto->FDEC.primeiro;
    aeroporto->FDEC.primeiro = aviaoDecolado->proximo;
    if (aeroporto->FDEC.primeiro == NULL) {
        aeroporto->FDEC.ultimo = NULL;
    }
    
    // Atualiza a contagem de decolagens no LDISP
    ListaAvioes *letraAtual = aeroporto->LDISP;
    while (letraAtual != NULL && letraAtual->letra != aviaoDecolado->id[0]) {
        letraAtual = letraAtual->proximo;
    }
    
    if (letraAtual != NULL) {
        Aviao *aviaoAtual = letraAtual->primeiro;
        while (aviaoAtual != NULL && strcmp(aviaoAtual->id, aviaoDecolado->id) != 0) {
            aviaoAtual = aviaoAtual->proximo;
        }
        if (aviaoAtual != NULL) {
            aviaoAtual->decolagens++;
        }
    }
    
    // Adiciona ao relatorio de operaçoes
    Operacao *novaOperacao = criarOperacao(aviaoDecolado->id, "decolagem");
    novaOperacao->proximo = aeroporto->relatorio;
    aeroporto->relatorio = novaOperacao;
    
    free(aviaoDecolado);
}

void autoriza_aterrissar(Aeroporto *aeroporto, char *idAviao) {
    Aviao *novoAviao = criarAviao(idAviao);
    if (aeroporto->FATE.ultimo == NULL) {
        aeroporto->FATE.primeiro = novoAviao;
        aeroporto->FATE.ultimo = novoAviao;
    } else {
        aeroporto->FATE.ultimo->proximo = novoAviao;
        aeroporto->FATE.ultimo = novoAviao;
    }
}

void aterrissar(Aeroporto *aeroporto) {
    if (aeroporto->FATE.primeiro == NULL) {
        printf("Nenhuma aterrissagem autorizada.\n");
        return;
    }
    
    Aviao *aviaoAterrisado = aeroporto->FATE.primeiro;
    aeroporto->FATE.primeiro = aviaoAterrisado->proximo;
    if (aeroporto->FATE.primeiro == NULL) {
        aeroporto->FATE.ultimo = NULL;
    }
    
    // Atualiza a contagem de pousos no LDISP
    ListaAvioes *letraAtual = aeroporto->LDISP;
    while (letraAtual != NULL && letraAtual->letra != aviaoAterrisado->id[0]) {
        letraAtual = letraAtual->proximo;
    }
    
    if (letraAtual != NULL) {
        Aviao *aviaoAtual = letraAtual->primeiro;
        while (aviaoAtual != NULL && strcmp(aviaoAtual->id, aviaoAterrisado->id) != 0) {
            aviaoAtual = aviaoAtual->proximo;
        }
        if (aviaoAtual != NULL) {
            aviaoAtual->aterrissagens++;
        }
    }
    
    // Adiciona ao relatorio de operaçoes
    Operacao *novaOperacao = criarOperacao(aviaoAterrisado->id, "aterrissagem");
    novaOperacao->proximo = aeroporto->relatorio;
    aeroporto->relatorio = novaOperacao;
    
    free(aviaoAterrisado);
}

void proximas_decolagens(Aeroporto *aeroporto) {

    Aviao *aviaoAtual = aeroporto->FDEC.primeiro;
    while (aviaoAtual != NULL) {
        printf("Decolagem: %s\n", aviaoAtual->id);
        aviaoAtual = aviaoAtual->proximo;
    }
}

void proximas_aterrissagens(Aeroporto *aeroporto) {

    Aviao *aviaoAtual = aeroporto->FATE.primeiro;
    while (aviaoAtual != NULL) {
        printf("Aterrissagem: %s\n", aviaoAtual->id);
        aviaoAtual = aviaoAtual->proximo;
    }
}

void relatorio_aeroporto(Aeroporto *aeroporto) {
    Operacao *operacaoAtual = aeroporto->relatorio;
    while (operacaoAtual != NULL) {
        printf("ID: %s, Operação: %s, Horário: %s\n", operacaoAtual->id, operacaoAtual->tipo, operacaoAtual->horario);
        operacaoAtual = operacaoAtual->proximo;
    }
}

void remover_aviao(Aeroporto *aeroporto, char *idAviao) {
    char letraInicial = idAviao[0];
    ListaAvioes *letraAtual = aeroporto->LDISP, *letraAnterior = NULL;
    
    // Procura a lista correspondente à letra inicial
    while (letraAtual != NULL && letraAtual->letra != letraInicial) {
        letraAnterior = letraAtual;
        letraAtual = letraAtual->proximo;
    }
    
    if (letraAtual == NULL) {
        printf("Avião não encontrado.\n");
        return;
    }
    
    // Procura o aviao na lista
    Aviao *aviaoAtual = letraAtual->primeiro, *aviaoAnterior = NULL;
    while (aviaoAtual != NULL && strcmp(aviaoAtual->id, idAviao) != 0) {
        aviaoAnterior = aviaoAtual;
        aviaoAtual = aviaoAtual->proximo;
    }
    
    if (aviaoAtual == NULL) {
        printf("Avião não encontrado.\n");
        return;
    }
    
    // Remove o aviao da lista
    if (aviaoAnterior == NULL) {
        letraAtual->primeiro = aviaoAtual->proximo;
    } else {
        aviaoAnterior->proximo = aviaoAtual->proximo;
    }
    
    free(aviaoAtual);
    printf("Avião %s removido com sucesso.\n", idAviao);
    
    // Se a lista de avioes dessa letra estiver vazia, remove a lista
    if (letraAtual->primeiro == NULL) {
        if (letraAnterior == NULL) {
            aeroporto->LDISP = letraAtual->proximo;
        } else {
            letraAnterior->proximo = letraAtual->proximo;
        }
        free(letraAtual);
    }
}

void consultar_historico(Aeroporto *aeroporto, char *idAviao) {
    Operacao *operacaoAtual = aeroporto->relatorio;
    int encontrado = 0;
    
    while (operacaoAtual != NULL) {
        if (strcmp(operacaoAtual->id, idAviao) == 0) {
            printf("ID: %s, Operação: %s, Horário: %s\n", operacaoAtual->id, operacaoAtual->tipo, operacaoAtual->horario);
            encontrado = 1;
        }
        operacaoAtual = operacaoAtual->proximo;
    }
    
    if (!encontrado) {
        printf("Nenhuma operação encontrada para o avião %s.\n", idAviao);
    }
}
