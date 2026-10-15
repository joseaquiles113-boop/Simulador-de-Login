#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct conta{
    char nome[201];
    int senha;
    struct conta *proximo;
}conta;

typedef struct{
    conta *inicio;
    int tam;
}Lista;

void cadastrarConta(Lista *lista, const char *nome, int senha);
conta *buscaSenha(Lista *lista, int senha);
void limpar();

int main(){
    Lista lista;

    char nome[201];
    int senha, op;

    lista.inicio = NULL;
    lista.tam = 0;

    do{
        puts("\n--- SISTEMA DE LOGIN ---\n");
        puts("1 - Cadastrar\n2 - Login\n0 - Sair");
        scanf("%d", &op);
        limpar();

        switch(op){
            case 1:
                limpar();
                puts("Digite o seu nome completo:");
                scanf("%200[^\n]", nome);
                limpar();
                puts("Crie uma senha:");
                scanf("%d", &senha);
                limpar();
                cadastrarConta(&lista, nome, senha);
                printf("Cadastro feito com sucesso!\nNumero de usuarios cadastrados: %d\n", lista.tam);
                break;
            case 2:
                puts("Digite sua senha:");
                scanf("%d", &senha);
                limpar();
                buscaSenha(&lista, senha);
                break;
        }
    }while(op != 0);

    lista.inicio = NULL;
    lista.tam = 0;

    return 0;
}

void cadastrarConta(Lista *lista, const char *nome, int senha){
    conta *nova = (conta *)malloc(sizeof(conta));

    if (nova == NULL) return;  

    strncpy(nova->nome, nome, sizeof(nova->nome) - 1);
    nova->nome[sizeof(nova->nome) - 1] = '\0'; 
    
    nova->senha = senha;
    nova->proximo = lista->inicio;
    lista->inicio = nova;
    lista->tam++;
}

conta *buscaSenha(Lista *lista, int senha){
    conta *atual = lista->inicio;

    while(atual != NULL && atual->senha != senha){
        atual = atual->proximo;
    }

    if(atual == NULL){
        puts("Nenhuma conta foi encontrada!");
    }else{
        printf("Nome completo: %s\nSenha: %d", atual->nome, atual->senha);
    }

    return atual;
}

void limpar(){
    int c;
    while((c = getchar ()) != '\n' && c != EOF);
}