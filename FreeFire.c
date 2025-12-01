#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_COMP 10

// Struct do componente
struct Componente {
    char nome[30];
    char tipo[20];
    int prioridade;
    int quantidade;
};

void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
    getchar();
}

void listarComponentes(struct Componente lista[], int total) {
    printf("\n======== INVENTARIO ATUAL (%d/%d) ========\n", total, MAX_COMP);
    printf("--------------------------------------------------------------\n");
    printf("%-20s %-15s %-10s %-12s\n",
           "NOME", "|TIPO", "|QUANTIDADE", "|PRIORIDADE");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        printf("%-20s |%-15s|%-10d |%-12d\n",
            lista[i].nome,
            lista[i].tipo,
            lista[i].quantidade,
            lista[i].prioridade);
    }
}

//  ORDENAR POR NOME (BUBBLE SORT)
void ordenarPorNome(struct Componente v[], int n) {
    struct Componente aux;
    int trocou;

    do {
        trocou = 0;
        for (int i = 0; i < n - 1; i++) {
            if (strcmp(v[i].nome, v[i + 1].nome) > 0) {
                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
                trocou = 1;
            }
        }
    } while (trocou);
}

//  ORDENAR POR TIPO (INSERTION SORT)
void ordenarPorTipo(struct Componente v[], int n) {
    struct Componente chave;
    int j;

    for (int i = 1; i < n; i++) {
        chave = v[i];
        j = i - 1;

        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

//  ORDENAR POR PRIORIDADE (SELECTION SORT)
void ordenarPorPrioridade(struct Componente v[], int n) {
    int min;
    struct Componente aux;

    for (int i = 0; i < n - 1; i++) {
        min = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j].prioridade < v[min].prioridade) {
                min = j;
            }
        }

        aux = v[i];
        v[i] = v[min];
        v[min] = aux;
    }
}

//  BUSCA BINÁRIA POR NOME
int buscaBinaria(struct Componente v[], int n, char chave[]) {
    int inicio = 0, fim = n - 1, meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;

        int cmp = strcmp(v[meio].nome, chave);

        if (cmp == 0) {
            return meio;  // encontrado
        }
        else if (cmp < 0) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }
    return -1;
}

int main() {
    struct Componente comp[MAX_COMP];
    int total = 0;

    int opcao;

    int ordenadoPorNome = 0; // FLAG IMPORTANTE

    do {
        printf("\n=======================================\n");
        printf("   PLANO DE FUGA - CODIGO DA ILHA   \n");
        printf("=======================================\n");
        printf("Itens na Mochila: %d/%d\n", total, MAX_COMP);
        printf("Status ordenação por nome: %s\n\n", ordenadoPorNome ? "ORDENADO" : "NÃO ORDENADO");

        printf("1 - Adicionar Componente\n");
        printf("2 - Descartar Componente\n");
        printf("3 - Listar Componentes (Inventário)\n");
        printf("4 - Organizar Mochila (Ordenar Componentes)\n");
        printf("5 - Busca Binaria por Componente-Chave (por nome)\n");
        printf("0 - ATIVAR TORRE DE FUGA (Sair)\n");
        printf("--------------------------------\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

        // ADICIONAR COMPONENTE
        case 1: {
            if (total >= MAX_COMP) {
                printf("\nLimite máximo de componentes atingido.\n");
                break;
            }

            printf("\n--- Coletando Novo Componente ---\n");

            printf("Nome: ");
            scanf("%s", comp[total].nome);

            printf("Tipo: ");
            scanf("%s", comp[total].tipo);

            printf("Quantidade: ");
            scanf("%d", &comp[total].quantidade);

            printf("Prioridade (1-10): ");
            scanf("%d", &comp[total].prioridade);

            total++;

            ordenadoPorNome = 0; // nova inserção bagunça a ordem

            printf("\nComponente adicionado com sucesso!\n");
            listarComponentes(comp, total);
            printf("--------------------------------------------------------------\n");

            pausar();
            break;
        }

        // REMOVER COMPONENTE
        case 2: {
            if (total == 0) {
                printf("\nNenhum componente para descartar.\n");
                break;
            }

            char nomeRemover[30];
            int encontrado = 0;

            printf("\n--- Remover Componente ---\n");
            printf("Nome do componente a remover: ");
            scanf("%s", nomeRemover);

            for (int i = 0; i < total; i++) {
                if (strcmp(comp[i].nome, nomeRemover) == 0) {
                    encontrado = 1;

                    for (int j = i; j < total - 1; j++) {
                        comp[j] = comp[j + 1];
                    }

                    total--;
                    ordenadoPorNome = 0;

                    printf("\nComponente removido com sucesso!\n");
                    listarComponentes(comp, total);
                    pausar();
                    break;
                }
            }

            if (!encontrado) {
                printf("Componente não encontrado.\n");
            }
            break;
        }

        // LISTAR
        case 3: {
            if (total == 0) {
                printf("\nNenhum componente cadastrado.\n");
                break;
            }

            listarComponentes(comp, total);
            pausar();
            break;
        }

        // ORGANIZAR (ORDENAR COMPONENTES)
        case 4: {
            int subop;

            system("clear");

            printf("\n====== Estrategia de Organizacao ======\n");
            printf("Como deseja ordenar os componentes?\n");
            printf("1. Por Nome (Ordem Alfabética)\n");
            printf("2. Por Tipo\n");
            printf("3. Por Prioridade de Montagem\n");
            printf("0. Cancelar\n");
            printf("===============================\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &subop);

            switch (subop) {
            case 1:
                ordenarPorNome(comp, total);
                ordenadoPorNome = 1;
                printf("\nComponentes ordenados por NOME!\n");
                listarComponentes(comp, total);
                break;

            case 2:
                ordenarPorTipo(comp, total);
                ordenadoPorNome = 0;
                printf("\nComponentes ordenados por TIPO!\n");
                listarComponentes(comp, total);
                break;

            case 3:
                ordenarPorPrioridade(comp, total);
                ordenadoPorNome = 0;
                printf("\nComponentes ordenados por PRIORIDADE!\n");
                listarComponentes(comp, total);
                break;

            case 0:
                printf("\nOrdenação cancelada.\n");
                break;

            default:
                printf("\nOpção inválida.\n");
            }

            pausar();
            break;
        }

        // BUSCA BINÁRIA
        case 5: {
            if (!ordenadoPorNome) {
                printf("\nALERTA: A busca binária requer que os componentes estejam ordenados por NOME.\n");
                printf("Use a Opcao 4 para organizar os componentes primeiro.\n");
                pausar();
                break;
            }

            char chave[30];
            printf("\n--- Busca Binária por Componente-Chave ---\n");
            printf("Digite o nome do componente: ");
            scanf("%s", chave);

            int pos = buscaBinaria(comp, total, chave);

            if (pos == -1) {
                printf("\nComponente NÃO encontrado!\n");
            } else {
                printf("\n=== Componente-Chave Encontrado! ===\n");
                printf("Nome: %s, ", comp[pos].nome);
                printf("Tipo: %s, ", comp[pos].tipo);
                printf("Qtd: %d, ", comp[pos].quantidade);
                printf("Prio: %d\n", comp[pos].prioridade);
            }

            pausar();
            break;
        }

        case 0:
            printf("\nEncerrando o sistema...\n");
            break;

        default:
            printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}