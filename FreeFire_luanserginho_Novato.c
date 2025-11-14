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
    int total = 0;  // quantidade de itens cadastrados
    int opcao;

    do {
        printf("\n========== MENU DA MOCHILA ==========\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpa Enter

        switch(opcao) {
        case 1: // Adicionar
            if (total >= MAX_ITENS) {
                printf("\n Mochila cheia! Nao e possivel adicionar mais itens.\n");
                break;
            }

            printf("\nNome do item: ");
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
                printf("\n Nenhum item para remover.\n");
                break;
            }

            char nomeRemover[30];
            int encontrado = -1;

            printf("\nDigite o nome do item a remover: ");
            fgets(nomeRemover, 30, stdin);
            nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

            // busca simples
            for (int i = 0; i < total; i++) {
                if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                    encontrado = i;
                    break;
                }
            }

            if (encontrado == -1) {
                printf("Item não encontrado!\n");
            } else {
                // move todos para tras
                for (int i = encontrado; i < total - 1; i++) {
                    mochila[i] = mochila[i + 1];
                }
                total--;
                printf("✔ Item removido com sucesso!\n");
            }
            break;
        }

        case 3: // Listar
            if (total == 0) {
                printf("\n⚠ Mochila vazia.\n");
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

        case 4:
            printf("\nSaindo...\n");
            break;

        default:
            printf("\n⚠ Opção invalida!\n");
        }

    } while (opcao != 4);

    return 0;
}