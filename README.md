# RODAR O APLICATIVO:

```bash
1- ~/Documents/EDAero/./compile.sh
2- ~/Documents/EDAero/bin/EDAero
``` 

# NECESSÁRIO PARA RODAR O APP:

```bash

É necessario possuir o [MSYS2](<https://www.msys2.org/>) (gcc) para rodar o app no vs code
após instalar abra o terminal MSYS2 e execute os comandos:
pacman -Syu
pacman -Su
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
```

```bash

Para executar o script:

no terminal:
--> chmod +x ~/Documents/EDAero/compile.sh
--> ~/Documents/EDAero/./compile.sh

```

```bash
Para recompilar o código após uma alteração e rodar novamente:
1- ~/Documents/EDAero/./compile.sh
2- ~/Documents/EDAero/bin/EDAero

```

# EXPLICAÇÃO DA ESTRUTURA: 

O programa do terminal aéreo EDAero foi criado com o uso da linguagem C, com o intuito de controlar as operações de saída e chegada das aeronaves. A arquitetura do software foi projetada para ser flexível e otimizada, utilizando listas encadeadas para armazenar informações dinâmicas e filas para gerenciar as operações em tempo real. Abaixo, apresentamos a estrutura do programa de forma minuciosa.

## Estrutura de dados:
- Lista de aviões (LDISP):
    - Nota: A lista de aviões registrados é uma lista vinculada de listas vinculadas. Cada nó da primeira lista (ListaAvioes) representa a primeira letra do código da aeronave, e cada nó desta lista contém outra lista vinculada (Avião) de aviões começando com aquela letra.

    ```c++
        typedef struct Aviao {
            char id[6]; // Código do aviãozinho
            int aterrissagens;
            int decolagens;
            struct Aviao *proximo;
        } Aviao;

        typedef struct ListaAvioes {
            char letra; // Letra inicial dos códigos dos aviões
            Aviao *primeiro;
            struct ListaAvioes *proximo;
        } ListaAvioes;
    ```

 - Filas de operações (FDEC & FATE):
    - Nota: As filas de decolagem (FDEC) e pouso (FATE) são usadas para gerenciar a sequência em que as aeronaves realizam as operações. Cada fila é uma lista vinculada simples, com novos aviões adicionados no final e removidas no início.

    ```c++
        typedef struct Fila {
            Aviao *primeiro;
            Aviao *ultimo;
        } Fila;
    ```

## Relatório de Operações:

Nota: O relatório de operações registra todas as decolagens e pousos realizados. CCada operação é armazenada em uma lista vinculada, contendo informações como tipo de operação, código do aviao e tempo de operação.

```c++
typedef struct Operacao {
    char id[6];
    char tipo[12];
    char horario[20];
    struct Operacao *proximo;
} Operacao;
```

## Implementação das Listas Encadeadas

A manipulação das listas encadeadas na aplicação é feita utilizando referências e ponteiros para gerenciar dinamicamente a alocação de memória e a navegação entre os nodos.
Criação de um Avião:
Nota: Ao cadastrar um avião, um novo nodo Aviao é criado com alocação dinâmica de memória.

```c++
Aviao* criarAviao(char *id) {
    Aviao *novoAviao = (Aviao*)malloc(sizeof(Aviao));
    strcpy(novoAviao->id, id);
    novoAviao->aterrissagens = 0;
    novoAviao->decolagens = 0;
    novoAviao->proximo = NULL;
    return novoAviao;
}
```

## LDISP:
Nota: A inserção de um avião na LDISP envolve encontrar a lista pela letra inicial do código do avião. Se a lista não existir, é craida uma nova. Após isso, o avião é posto na lista de aviões correspondente.

```c++
void cadastra_aviao(Aeroporto *aeroporto, char *idAviao) {
    char letraInicial = idAviao[0];
    ListaAvioes *letraAtual = aeroporto->LDISP, *letraAnterior = NULL;
    
    // Procura a lista correspondente à letra inicial
    while (letraAtual != NULL && letraAtual->letra != letraInicial) {
        letraAnterior = letraAtual;
        letraAtual = letraAtual->proximo;
    }
    
    // Se a lista não existir, cria uma nova
    if (letraAtual == NULL) {
        letraAtual = (ListaAvioes*)malloc(sizeof(ListaAvioes));
        letraAtual->letra = letraInicial;
        letraAtual->primeiro = NULL;
        letraAtual->proximo = NULL;
        
        if (letraAnterior == NULL) {
            aeroporto->LDISP = letraAtual;
        } else {
            letraAnterior->proximo = letraAtual;
        }
    }
    
    // Insere o avião na lista
    Aviao *novoAviao = criarAviao(idAviao);
    novoAviao->proximo = letraAtual->primeiro;
    letraAtual->primeiro = novoAviao;
}
```

## Enfileirar e desenfileirar (FDEC & FATE):
Nota: Quando um avião é autorizado a decolar ou pousar, ele é adicionado ao final da fila correspondente. A remoção da fila ocorre no início da fila.

```c++
void autoriza_decolar(Aeroporto *aeroporto, char *idAviao) {
    // ... (Localiza o avião na LDISP e enfileira em FDEC)
}

void decolar(Aeroporto *aeroporto) {
    if (aeroporto->FDEC.primeiro == NULL) {
        printf("Nenhum avião para decolar.\n");
        return;
    }
    
    Aviao *decolarAviao = aeroporto->FDEC.primeiro;
    aeroporto->FDEC.primeiro = decolarAviao->proximo;
    if (aeroporto->FDEC.primeiro == NULL) {
        aeroporto->FDEC.ultimo = NULL;
    }
    
    decolarAviao->decolagens++;
    
    // Registra a operação
    Operacao *novaOperacao = criarOperacao(decolarAviao->id, "decolagem");
    novaOperacao->proximo = aeroporto->relatorio;
    aeroporto->relatorio = novaOperacao;
    
    printf("Avião %s decolou.\n", decolarAviao->id);
}
```

## Manipulação de Estruturas Dinâmicas
A manipulação de estruturas dinâmicas na aplicação envolve a alocação e desalocação de memória conforme necessário, utilizando ponteiros para gerenciar a conexão entre nodos.
Alocação Dinâmica de Memória:
Usamos malloc para alocar memória para novos nodos quando aviões são cadastrados ou operações são registradas.

```c++
Exemplo:
Aviao* novoAviao = (Aviao*)malloc(sizeof(Aviao));
```

## Uso de Referências/Ponteiros:
Ponteiros são usados para navegar entre nodos nas listas encadeadas e para enfileirar/desenfileirar aviões nas filas.

```c++
Exemplo:
novoAviao->proximo = letraAtual->primeiro;
letraAtual->primeiro = novoAviao;
```

## Desalocação de Memória:
A memória alocada dinamicamente é liberada quando aviões são removidos da LDISP ou quando a aplicação termina.

```c++
Exemplo:
free(aviaoAtual);
```
