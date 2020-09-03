#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 30

typedef struct contato {
    int codigo;
    int ativo;
    char nome [100];
    char email [100];
    char celular [20];
} Contato;

Contato contato;

void adicionarContato ();
void consultarContato();
void excluirContato ();
void editarContato ();
int sair();
void clrscr();
int proximoId();

void main() {
    int opcao;

    do {        
        printf("\n\n\t\tMENU");
        printf("\n1 - Cadastrar");
        printf("\n2 - Listar");
        printf("\n3 - Editar");
        printf("\n4 - Excluir");
        printf("\n5 - Sair");
        printf("\nOpção: ");

        scanf("%d", &opcao);
        fflush(stdin);
        clrscr();
        switch (opcao) {
            case 1:
                printf("\nDigite um nome: ");
                scanf("%s", contato.nome);
                printf("\nDigite um telefone: ");
                scanf("%s", contato.celular);
                printf("\nDigite um email: ");
                scanf("%s", contato.email);
                adicionarContato(contato.nome, contato.celular, contato.email);
                getchar();
                clrscr();
                break;
            case 2:
                clrscr();
                consultarContato();
                getchar();
                fflush(stdin);
                break;
            case 3:
                clrscr();
                editarContato();
                break;
            case 4:
                clrscr();
                excluirContato();
                break;
            case 5:
                clrscr();
                sair();
                break;
            default:
                printf("opção inválida!");
                break;
        }
    } while (opcao != 5);
}

void adicionarContato(char nome[BUFFER_SIZE],char tel[BUFFER_SIZE],char email[BUFFER_SIZE]){
    int id = proximoId();
    FILE *arquivo = fopen("agenda.txt","a");
    fprintf(arquivo, "%d %d %s %s %s\n", id, 1, nome, tel, email);
    fclose(arquivo);
}

void consultarContato(){
    FILE *arquivo = fopen("agenda.txt","r");
    char nome[BUFFER_SIZE];
    int tel;
    while (!feof(arquivo))
    {
        fscanf(arquivo, "%s %d ", nome, &tel);
        printf("Nome: %s - Tel: %d\n", nome, tel);
    }
    fclose(arquivo);
}

int sair(){
    clrscr();
    printf("--------------------------------------------------------\n");
    printf("--------------------FINALIZANDO PROGRAMA----------------\n");
    printf("--------------------------------------------------------\n\n");
    getchar();
    return 0;
}

void excluirContato (){
    printf("oi");
}

void editarContato (){
    printf("tchau");
}

int proximoId(){
    FILE *arquivo = fopen("agenda.txt","r");
    char c, letra = '\n';
    int vezes = 1;
    while(fread (&c, sizeof(char), 1, arquivo)) {
        if(c == letra) {
            vezes++;
        }
    }
    fclose(arquivo);
    return vezes;
}
/**< LIMPA A TELA */

void clrscr()
{
    system("@cls||clear");
}
