#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct conta {
    char nome[201];
    int senha;
    struct conta *proximo;
} conta;

typedef struct {
    conta *inicio;
    int tam;
} Lista;

void cadastrarConta(Lista *lista, const char *nome, int senha);
conta *buscaConta(Lista *lista, const char *nome, int senha);
void exclusaoConta(Lista *lista, const char *nome, int senha);
void limpar();

int main() {
    Lista lista;

    char nome[201];
    int senha, op;

    lista.inicio = NULL;
    lista.tam = 0;

    do {
        puts("\n--- SISTEMA DE LOGIN ---\n");
        puts("1 - Cadastrar\n2 - Login\n3 - Excluir conta\n4 - Quantidade de usuarios cadastrados\n0 - Sair");
        scanf("%d", &op);
        limpar();

        switch (op) {
            case 1:
                puts("Digite o seu nome completo:");
                scanf(" %200[^\n]", nome);
                limpar();
                puts("Crie uma senha:");
                scanf("%d", &senha);
                limpar();
                cadastrarConta(&lista, nome, senha);
                puts("Cadastro feito com sucesso!");

                break;

            case 2:
                puts("Digite seu nome:");
                scanf(" %200[^\n]", nome);
                limpar();
                puts("Digite sua senha:");
                scanf("%d", &senha);
                limpar();
                buscaConta(&lista, nome, senha);

                break;

            case 3:
                puts("Digite seu nome:");
                scanf(" %200[^\n]", nome);
                limpar();
                puts("Digite sua senha:");
                scanf("%d", &senha);
                limpar();
                exclusaoConta(&lista, nome, senha);

                break;

            case 4:
                printf("Quantidade de usuarios cadastrados: %d\n", lista.tam);

                break;

            default:
                if (op != 0) {
                    puts("Opcao invalida!");
                }

                break;
        }
    } while (op != 0);

    lista.inicio = NULL;
    lista.tam = 0;

    return 0;
}

void cadastrarConta(Lista *lista, const char *nome, int senha) {
    conta *nova = (conta *)malloc(sizeof(conta));

    if (nova == NULL) return;

    strncpy(nova->nome, nome, sizeof(nova->nome) - 1);
    nova->nome[sizeof(nova->nome) - 1] = '\0';

    nova->senha = senha;
    nova->proximo = lista->inicio;
    lista->inicio = nova;
    lista->tam++;
}

conta *buscaConta(Lista *lista, const char *nome, int senha) {
    conta *atual = lista->inicio;

    while (atual != NULL && atual->nome != nome && atual->senha != senha) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        puts("Nenhuma conta foi encontrada!");
    } else {
        printf("Bem vindo(a), %s!\nSenha: %d", atual->nome, atual->senha);
    }

    return atual;
}

void exclusaoConta(Lista *lista, const char *nome, int senha) {
    conta *inicio = lista->inicio;
    conta *contaARemover = NULL;

    if (inicio != NULL && lista->inicio->nome == nome && lista->inicio->senha == senha) {
        contaARemover = lista->inicio;
        lista->inicio = contaARemover->proximo;
    } else {
        while (inicio != NULL && inicio->proximo != NULL && (strcmp(inicio->proximo->nome, nome) != 0 && inicio->proximo->senha != senha)) {
            inicio = inicio->proximo;
        }if (inicio != NULL && inicio->proximo != NULL) {
            contaARemover = inicio->proximo;
            inicio->proximo = contaARemover->proximo;
        }
    }

    if (contaARemover != NULL) {
        free(contaARemover);
        lista->tam--;
    }
}

void limpar() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}