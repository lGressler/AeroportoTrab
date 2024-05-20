#include <stdio.h>
#include "aeroporto.h"


void menu() {
    Aeroporto aeroporto = {NULL, {NULL, NULL}, {NULL, NULL}, NULL};
    int opcao;
    char idAviao[6];
    char letra;
    
    do {
        printf("\n1. Cadastrar aviao\n2. Listar avioes cadastrados\n3. Autorizar decolagem\n4. Executar decolagem\n5. Autorizar aterrissagem\n6. Executar aterrissagem\n7. Proximas decolagens\n8. Proximas aterrissagens\n9. Relatorio do aeroporto\n10. Remover aviao cadastrado\n11. Consultar historico de operacoes de um aviao\n0. Sair\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                printf("Digite o ID do aviao: ");
                scanf("%s", idAviao);
                cadastra_aviao(&aeroporto, idAviao);
                break;
            case 2:
                printf("Digite a letra inicial ou '*' para todos: ");
                scanf(" %c", &letra);
                if (letra == '*') letra = '\0';
                avioes_cadastrados(&aeroporto, letra);
                break;
            case 3:
                printf("Digite o ID do aviao: ");
                scanf("%s", idAviao);
                autoriza_decolar(&aeroporto, idAviao);
                break;
            case 4:
                decolar(&aeroporto);
                break;
            case 5:
                printf("Digite o ID do aviao: ");
                scanf("%s", idAviao);
                autoriza_aterrissar(&aeroporto, idAviao);
                break;
            case 6:
                aterrissar(&aeroporto);
                break;
            case 7:
                proximas_decolagens(&aeroporto);
                break;
            case 8:
                proximas_aterrissagens(&aeroporto);
                break;
            case 9:
                relatorio_aeroporto(&aeroporto);
                break;
            case 10:
                printf("Digite o ID do aviao a ser removido: ");
                scanf("%s", idAviao);
                remover_aviao(&aeroporto, idAviao);
                break;
            case 11:
                printf("Digite o ID do aviao para consultar o historico: ");
                scanf("%s", idAviao);
                consultar_historico(&aeroporto, idAviao);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}
