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
void mostrarContas(Lista *lista);
void pesquisarUsuario(Lista *lista, const char *nome);
void limpar();

int main() {
    Lista lista;

    char nome[201];
    int senha, opcao;

    lista.inicio = NULL;
    lista.tam = 0;

    do {
        puts("\n--- SISTEMA DE LOGIN ---\n");
        puts("1 - Cadastrar\n2 - Login\n3 - Excluir conta\n4 - Quantidade de usuarios cadastrados");
        puts("5 - Mostrar todos os usuarios cadastrados\n6 - Pesquisar um usuario\n0 - Sair");
        scanf("%d", &opcao);
        limpar();

        switch (opcao) {
            case 1:
                puts("Digite o seu nome:");
                scanf(" %200[^\n]", nome);
                limpar();
                puts("Crie uma senha:");
                scanf("%d", &senha);
                limpar();
                cadastrarConta(&lista, nome, senha);

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

            case 5:
                mostrarContas(&lista);

                break;

            case 6:
                puts("Nome do usuario:");
                scanf("%200[^\n]", nome);
                limpar();
                pesquisarUsuario(&lista, nome);

                break;

            default:
                if (opcao != 0) {
                    puts("Opcao invalida!");
                }

                break;
        }
    } while (opcao != 0);

    lista.inicio = NULL;
    lista.tam = 0;

    return 0;
}

void cadastrarConta(Lista *lista, const char *nome, int senha) {
    conta *nova = (conta *)malloc(sizeof(conta));
    conta *verificacao = lista->inicio;

    while(verificacao != NULL && (strcmp(verificacao->nome, nome)) != 0){
        verificacao = verificacao->proximo;
    }if(verificacao != NULL){
        puts("Esse nome ja esta em uso, tente novamente");
    }else{
        if (nova == NULL) return;

        strncpy(nova->nome, nome, sizeof(nova->nome) - 1);
        nova->nome[sizeof(nova->nome) - 1] = '\0';

        nova->senha = senha;
        nova->proximo = lista->inicio;
        lista->inicio = nova;
        lista->tam++;
        puts("Cadastro feito com sucesso!");
    }
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

void mostrarContas(Lista *lista){
    conta *proximo = lista->inicio;

    if(proximo == NULL){
        puts("Nenhum usuario encontrado");
    }else{
        if(lista->tam == 1){
            printf("Nome: %s", proximo->nome);
        }else{
            while(proximo != NULL){
                printf("Nome: %s\n", proximo->nome);
                proximo = proximo->proximo;
            }
        }
    }
}

void pesquisarUsuario(Lista *lista, const char *nome){
    conta *atual = lista->inicio;

    while(atual != NULL && (strcmp(atual->nome, nome)) != 0){
        atual = atual->proximo;
    }if(atual == NULL){
        puts("Nenhum usuario encontrado com esse nome");
    }else{
        printf("Nome: %s", atual->nome);
    }
}

void limpar() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}