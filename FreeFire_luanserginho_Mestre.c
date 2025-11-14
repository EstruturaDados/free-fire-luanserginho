#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Critérios de ordenaçao
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO = 2,
    ORDENAR_PRIORIDADE = 3
} Criterio;

// Struct do item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;  // 1 a 5
} Item;

// Função de ordenaçao (Insertion Sort)
int ordenar(Item v[], int n, Criterio c) {
    int comparacoes = 0;

    for (int i = 1; i < n; i++) {
        Item chave = v[i];
        int j = i - 1;

        while (j >= 0) {

            comparacoes++; // conta comparaçao

            int comparar = 0;
            if (c == ORDENAR_NOME)
                comparar = strcmp(chave.nome, v[j].nome) < 0;
            else if (c == ORDENAR_TIPO)
                comparar = strcmp(chave.tipo, v[j].tipo) < 0;
            else if (c == ORDENAR_PRIORIDADE)
                comparar = chave.prioridade < v[j].prioridade;

            if (!comparar)
                break;

            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = chave;
    }

    return comparacoes;
}

// Busca binaria por nome
int buscaBinaria(Item v[], int n, char nomeBuscado[]) {
    int inicio = 0, fim = n - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        int cmp = strcmp(nomeBuscado, v[meio].nome);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    return -1;
}

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;
    bool ordenadoPorNome = false;

    do {
        printf("\n=========== MENU MESTRE ===========\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Ordenar mochila\n");
        printf("5 - Buscar item por nome (Busca Binaria)\n");
        printf("6 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
        case 1: // Adicionar item
            if (total >= MAX_ITENS) {
                printf("\n Mochila cheia!\n");
                break;
            }

            printf("\nNome: ");
            fgets(mochila[total].nome, 30, stdin);
            mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0';

            printf("Tipo: ");
            fgets(mochila[total].tipo, 20, stdin);
            mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';

            printf("Quantidade: ");
            scanf("%d", &mochila[total].quantidade);

            printf("Prioridade (1 a 5): ");
            scanf("%d", &mochila[total].prioridade);
            getchar();

            if (mochila[total].prioridade < 1 || mochila[total].prioridade > 5)
                mochila[total].prioridade = 3;

            total++;
            ordenadoPorNome = false;

            printf("Item adicionado!\n");
            break;

        case 2: { // Remover item
            if (total == 0) {
                printf("\n Mochila vazia.\n");
                break;
            }

            char nomeRemover[30];
            printf("\n Nome do item a remover: ");
            fgets(nomeRemover, 30, stdin);
            nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

            int pos = -1;
            for (int i = 0; i < total; i++) {
                if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                    pos = i;
                    break;
                }
            }

            if (pos == -1) {
                printf("Item nao encontrado.\n");
            } else {
                for (int i = pos; i < total - 1; i++)
                    mochila[i] = mochila[i + 1];

                total--;
                ordenadoPorNome = false;

                printf("Item removido!\n");
            }
            break;
        }

        case 3: // Listar
            if (total == 0)
                printf("\n Mochila vazia.\n");
            else {
                printf("\n=============== ITENS ===============\n");
                for (int i = 0; i < total; i++) {
                    printf("%d) Nome: %s | Tipo: %s | Qtd: %d | Prioridade: %d\n",
                           i + 1,
                           mochila[i].nome,
                           mochila[i].tipo,
                           mochila[i].quantidade,
                           mochila[i].prioridade);
                }
            }
            break;

        case 4: { // Ordenar
            printf("\n Ordenar por:\n");
            printf("1 - Nome\n");
            printf("2 - Tipo\n");
            printf("3 - Prioridade\n");
            printf("Escolha: ");

            int c;
            scanf("%d", &c);
            getchar();

            if (c < 1 || c > 3) {
                printf("\n Criterio invalido.\n");
                break;
            }

            int comps = ordenar(mochila, total, c);

            if (c == ORDENAR_NOME)
                ordenadoPorNome = true;
            else
                ordenadoPorNome = false;

            printf("\n Ordenado com sucesso!\n");
            printf("Comparaçoes feitas: %d\n", comps);

            break;
        }

        case 5: { // Buscar binária
            if (!ordenadoPorNome) {
                printf("\n Antes de buscar, você precisa ordenar por NOME.\n");
                break;
            }

            char nomeBusca[30];
            printf("\n Nome a buscar: ");
            fgets(nomeBusca, 30, stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

            int pos = buscaBinaria(mochila, total, nomeBusca);

            if (pos == -1) {
                printf("Item não encontrado.\n");
            } else {
                printf("\n ITEM ENCONTRADO:\n");
                printf("Nome: %s\n", mochila[pos].nome);
                printf("Tipo: %s\n", mochila[pos].tipo);
                printf("Quantidade: %d\n", mochila[pos].quantidade);
                printf("Prioridade: %d\n", mochila[pos].prioridade);
            }

            break;
        }

        case 6:
            printf("\n Saindo...\n");
            break;

        default:
            printf("\n Opçao invalida!\n");
        }

    } while (opcao != 6);

    return 0;
}