#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 30

typedef struct contato {
    int codigo ;
    char nome [100];
    char email [100];
    char celular [20];
} Contato;

void adicionarContato ();
void consultarContato();
void excluirContato ();
void editarContato ();

void main() {
    int opcao;
    char nome[BUFFER_SIZE];
    int fone;

    do {        
        printf("\n\n\t\tMENU");
        printf("\n1 - Cadastrar");
        printf("\n2 - Listar");
        printf("\n3 - Sair");
        printf("\nOpção: ");

        scanf("%d", &opcao);
        fflush(stdin);
        clrscr();
        switch (opcao) {
            case 1:
                system("clear||cls");
                cadastrarContato();
                break;
            case 2:
                system("clear||cls");
                consultarContato();
                break;
            case 3:
                system("clear||cls");
                excluirContato();
                break;
            case 4:
                system("clear||cls");
                editarContato();
                break;
            default:
                printf("opção inválida!");
                break;
        }
    } while (opcao != 3);
}