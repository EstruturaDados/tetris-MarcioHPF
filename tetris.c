#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5  // Tamanho fixo da fila

// Estrutura que representa uma peça do jogo
struct Peca {
    char tipo;  // Tipo da peça ('I', 'O', 'T', 'L')
    int id;     // Identificador único
};

// Estrutura da fila circular
struct Fila {
    struct Peca pecas[MAX_FILA];
    int inicio;
    int fim;
    int tamanho;
};

// Funções do sistema
void inicializarFila(struct Fila *fila);
int filaVazia(struct Fila *fila);
int filaCheia(struct Fila *fila);
void enqueue(struct Fila *fila, struct Peca nova);
void dequeue(struct Fila *fila);
void exibirFila(struct Fila *fila);
struct Peca gerarPeca(int id);

int main() {
    struct Fila fila;
    inicializarFila(&fila);

    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    int idAtual = 0;

    // Inicializa a fila com 5 peças iniciais
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&fila, gerarPeca(idAtual++));
    }

    int opcao;
    do {
        printf("\n=== FILA DE PEÇAS FUTURAS - TETRIS STACK ===\n");
        exibirFila(&fila);
        printf("\n1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&fila);
                break;
            case 2:
                if (!filaCheia(&fila)) {
                    enqueue(&fila, gerarPeca(idAtual++));
                } else {
                    printf("Fila cheia! Não é possível adicionar nova peça.\n");
                }
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

/* Inicializa a fila vazia */
void inicializarFila(struct Fila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
}

/* Retorna 1 se a fila estiver vazia, 0 caso contrário */
int filaVazia(struct Fila *fila) {
    return (fila->tamanho == 0);
}

/* Retorna 1 se a fila estiver cheia, 0 caso contrário */
int filaCheia(struct Fila *fila) {
    return (fila->tamanho == MAX_FILA);
}

/* Insere uma nova peça no final da fila (enqueue) */
void enqueue(struct Fila *fila, struct Peca nova) {
    if (filaCheia(fila)) {
        printf("Fila cheia! Não é possível inserir nova peça.\n");
        return;
    }

    fila->pecas[fila->fim] = nova;
    fila->fim = (fila->fim + 1) % MAX_FILA;  // Movimento circular
    fila->tamanho++;
}

/* Remove a peça da frente da fila (dequeue) */
void dequeue(struct Fila *fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }

    struct Peca jogada = fila->pecas[fila->inicio];
    printf("\nPeça jogada: [%c %d]\n", jogada.tipo, jogada.id);

    fila->inicio = (fila->inicio + 1) % MAX_FILA;  // Movimento circular
    fila->tamanho--;
}

/* Exibe todas as peças atualmente na fila */
void exibirFila(struct Fila *fila) {
    printf("\nFila de peças:\n");

    if (filaVazia(fila)) {
        printf("[Fila vazia]\n");
        return;
    }

    int i = fila->inicio;
    for (int count = 0; count < fila->tamanho; count++) {
        printf("[%c %d] ", fila->pecas[i].tipo, fila->pecas[i].id);
        i = (i + 1) % MAX_FILA;
    }
    printf("\n");
}

/* Gera uma nova peça com tipo aleatório e id único */
struct Peca gerarPeca(int id) {
    struct Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.tipo = tipos[rand() % 4];  // Escolhe um tipo aleatório
    nova.id = id;
    return nova;
}
