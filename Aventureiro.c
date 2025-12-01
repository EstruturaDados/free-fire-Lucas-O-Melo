#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

// Estrutura para representar um item da mochila
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
    getchar();
}

void listarItens(struct Item mochila[], int total) {
    printf("\n======== ITENS NA MOCHILA (%d/%d) ========\n", total, MAX_ITENS);
    printf("-----------------------------------------\n");
    printf("%-15s %-15s %-10s\n", "NOME", "|TIPO", "|QUANTIDADE");
    printf("-----------------------------------------\n");

    for (int i = 0; i < total; i++) {
        printf("%-15s |%-15s|%-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

int main() {
    struct Item mochila[MAX_ITENS];
    int total = 0; // quantidade atual de itens cadastrados

    int opcao;

    do {
        printf("\n================================\n");
        printf("    MOCHILA DE SOBREVIVENCIA   \n");
        printf("================================\n");
        printf("Itens na mochila: %d/%d itens\n\n", total, MAX_ITENS);
        printf("1 - Adicionar item (Loot)\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item por nome\n");   // <-- NOVA OPÇÃO
        printf("0 - Sair\n");
        printf("--------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1: {
            if (total >= MAX_ITENS) {
                printf("\nMochila cheia! Nao e possível adicionar mais itens.\n");
                break;
            }

            printf("\n--- Adicionar Item ---\n");
            printf("Nome: ");
            scanf("%s", mochila[total].nome);

            printf("Tipo (arma, municao, cura, etc.): ");
            scanf("%s", mochila[total].tipo);

            printf("Quantidade: ");
            scanf("%d", &mochila[total].quantidade);

            total++;
            printf("\nItem adicionado com sucesso!\n");

            // MOSTRAR LISTA
            listarItens(mochila, total);  
            printf("-----------------------------------------\n");     
            
            pausar();
            break;
        }

        case 2: {
            if (total == 0) {
                printf("\nA mochila está vazia. Nada para remover.\n");
                break;
            }

            char nomeRemover[30];
            int encontrado = 0;

            printf("\n--- Remover Item ---\n");
            printf("Nome do item a remover: ");
            scanf("%s", nomeRemover);

            for (int i = 0; i < total; i++) {
                if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                    encontrado = 1;

                    // deslocar todos os itens posteriores 1 posição para trás
                    for (int j = i; j < total - 1; j++) {
                        mochila[j] = mochila[j + 1];
                    }

                    total--;
                    printf("\nItem removido com sucesso!\n");

                    listarItens(mochila, total);
                    pausar();
                    break;
                }
            }

            if (!encontrado) {
                printf("Item nao encontrado na mochila.\n");
            }
            break;
        }

        case 3:
            if (total == 0) {
                printf("\nA mochila está vazia.\n");
            } else {
                listarItens(mochila, total);
            }
            break;

        // --------------- NOVO CASE: BUSCA SEQUENCIAL ------------------
        case 4: {
            if (total == 0) {
                printf("\nA mochila está vazia.\n");
                break;
            }

            char nomeBuscar[30];
            int achou = 0;

            printf("\n--- Buscar Item na Mochila ---\n");
            printf("Digite o nome do item: ");
            scanf("%s", nomeBuscar);

            for (int i = 0; i < total; i++) {
                if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
                    achou = 1;

                    printf("\n--- Item encontrado! ---\n");
                    printf("Nome: %s\n", mochila[i].nome);
                    printf("Tipo: %s\n", mochila[i].tipo);
                    printf("Quantidade: %d\n", mochila[i].quantidade);

                    break;
                }
            }

            if (!achou) {
                printf("\nItem não encontrado na mochila.\n");
            }

            pausar();
            break;
        }
        // --------------------------------------------------------------

        case 0:
            printf("\nEncerrando o programa...\n");
            break;

        default:
            printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}