#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

// Struct do item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n====== MENU DA MOCHILA ======\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item por nome\n");
        printf("5 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {

        case 1: // Adicionar item
            if (total >= MAX_ITENS) {
                printf("\n Mochila cheia!\n");
                break;
            }

            printf("\n Nome do item: ");
            fgets(mochila[total].nome, 30, stdin);
            mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0';

            printf("Tipo do item: ");
            fgets(mochila[total].tipo, 20, stdin);
            mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';

            printf("Quantidade: ");
            scanf("%d", &mochila[total].quantidade);
            getchar();

            total++;
            printf("Item adicionado!\n");
            break;

        case 2: { // Remover item
            if (total == 0) {
                printf("\n Mochila vazia!\n");
                break;
            }

            char nomeRemover[30];
            int encontrado = -1;

            printf("\n Nome do item a remover: ");
            fgets(nomeRemover, 30, stdin);
            nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

            for (int i = 0; i < total; i++) {
                if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                    encontrado = i;
                    break;
                }
            }

            if (encontrado == -1) {
                printf("Item nao encontrado.\n");
            } else {
                for (int i = encontrado; i < total - 1; i++) {
                    mochila[i] = mochila[i + 1];
                }
                total--;
                printf("Item removido!\n");
            }
            break;
        }

        case 3: // Listar itens
            if (total == 0) {
                printf("\n Mochila vazia.\n");
            } else {
                printf("\n==== ITENS NA MOCHILA ====\n");
                for (int i = 0; i < total; i++) {
                    printf("%d) Nome: %s | Tipo: %s | Quant: %d\n",
                           i + 1,
                           mochila[i].nome,
                           mochila[i].tipo,
                           mochila[i].quantidade);
                }
            }
            break;

        case 4: { // Buscar item por nome
            if (total == 0) {
                printf("\n Nenhum item para buscar.\n");
                break;
            }

            char nomeBusca[30];
            int achou = 0;

            printf("\n Digite o nome do item: ");
            fgets(nomeBusca, 30, stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

            for (int i = 0; i < total; i++) {
                if (strcmp(mochila[i].nome, nomeBusca) == 0) {
                    printf("\n Item encontrado!\n");
                    printf("Nome: %s\n", mochila[i].nome);
                    printf("Tipo: %s\n", mochila[i].tipo);
                    printf("Quantidade: %d\n", mochila[i].quantidade);
                    achou = 1;
                    break;
                }
            }

            if (!achou) {
                printf("Item nao encontrado.\n");
            }
            break;
        }

        case 5:
            printf("\n Saindo...\n");
            break;

        default:
            printf("\n Opçao invalida!\n");
        }

    } while (opcao != 5);

    return 0;
}