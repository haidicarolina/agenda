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

void incluirContato ();
void listarContato();
void excluirContato ();
void editarContato ();
void verificaArquivo();
int finalizar();
void clrscr();
int proximoId();
int file;
int numeroContatos = 0;

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
        verificaArquivo();
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
                incluirContato(contato.nome, contato.celular, contato.email);
                getchar();
                clrscr();
                break;
            case 2:
                clrscr();
                listarContato();
                getchar();
                fflush(stdin);
                break;
            case 3:
                clrscr();
                editarContato();
                getchar();
                fflush(stdin);
                break;
            case 4:
                clrscr();
                excluirContato();
                getchar();
                fflush(stdin);
                break;
            case 5:
                clrscr();
                finalizar();
                break;
            default:
                printf("opção inválida!");
                break;
        }
    } while (opcao != 5);
}

void incluirContato(char nome[BUFFER_SIZE],char tel[BUFFER_SIZE],char email[BUFFER_SIZE]){
    int id = proximoId();
    FILE *arquivo = fopen("agenda.txt","a");
        
    fprintf(arquivo, "%d %d %s %s %s\n", id, 1, nome, tel, email);
    fclose(arquivo);
}

void listarContato(){
    int codigo;
    int ativo;
    char nome[BUFFER_SIZE];
    char email[BUFFER_SIZE];
    char tel[BUFFER_SIZE];
    numeroContatos = 0;
    if (file > 0) {
        FILE *arquivo = fopen("agenda.txt","r");
        clrscr();
        printf("--------------------------------------------------------\n");
        printf("-------------------------CONTATOS------------------------\n");
        printf("--------------------------------------------------------\n\n");
        while (1)
        {
            fscanf(arquivo, "%d %d %s %s %s", &codigo, &ativo, nome, email, tel);
            if( feof(arquivo) )
                break;

            printf("Id: %d Nome: %s - Tel: %s Email: %s \n", codigo, nome, email, tel);
            numeroContatos = numeroContatos + 1;
        }
        if (numeroContatos == 0) {
            printf("Nenhum contato disponível");
        }
        fclose(arquivo);
    }
    else {
        printf("Nenhum contato disponível");
    }

}

int finalizar(){
    clrscr();
    printf("--------------------------------------------------------\n");
    printf("--------------------FINALIZANDO PROGRAMA----------------\n");
    printf("--------------------------------------------------------\n\n");
    return 0;
}

void excluirContato (){
    int opcao;
    int codigo;
    int ativo;
    char nome[BUFFER_SIZE];
    char email[BUFFER_SIZE];
    char tel[BUFFER_SIZE];
    if (file > 0) {   
        FILE *arquivo = fopen("agenda.txt","r");
        FILE *copia = fopen("copia.txt","a");
        printf("\n\n\t\tEscolha o contato a ser excluído pelo seu id\n");
        printf("\n");
        listarContato();
        if (numeroContatos > 0){
            printf("\nOpção: ");
            scanf("%d", &opcao);
            
            while (!feof(arquivo))
            {
                fscanf(arquivo, "%d %d %s %s %s", &codigo, &ativo, nome, email, tel);
                if(codigo != opcao) {
                    fprintf(copia, "%d %d %s %s %s\n", codigo, ativo, nome, email, tel);
                }
            }
            
            fclose(arquivo);
            fclose(copia);
            remove("agenda.txt");
            rename("copia.txt", "agenda.txt");
            printf("Contato excluído com sucesso");
        }
    }
    else {
        printf("Nenhum contato disponível");
    }
}

void editarContato (){
    int opcao;
    int codigo;
    int ativo;
    char nome[BUFFER_SIZE];
    char email[BUFFER_SIZE];
    char tel[BUFFER_SIZE];

    if (file > 0) {
        FILE *arquivo = fopen("agenda.txt","r");
        FILE *copia = fopen("copia.txt","a");
        printf("\n\n\t\tEscolha o contato a ser editado pelo seu id\n");
        printf("\n");
        listarContato();

        if (numeroContatos > 0) {
            printf("\nOpção: ");
            scanf("%d", &opcao);

            while (!feof(arquivo))
            {
                fscanf(arquivo, "%d %d %s %s %s", &codigo, &ativo, nome, email, tel);

                if(codigo == opcao) {
                    printf("\nDigite o novo nome: ");
                    scanf("%s", nome);
                    printf("\nDigite o novo telefone: ");
                    scanf("%s", tel);
                    printf("\nDigite o novo email: ");
                    scanf("%s", email);
                    fprintf(copia, "%d %d %s %s %s\n", codigo, ativo, nome, email, tel);
                    break;
                }
                else {
                    fprintf(copia, "%d %d %s %s %s\n", codigo, ativo, nome, email, tel);
                }
            }
            fclose(arquivo);
            fclose(copia);
            remove("agenda.txt");
            rename("copia.txt", "agenda.txt");
        }
    }
    else {
        printf("Nenhum contato disponível");
    }
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

void verificaArquivo(){
    FILE *arquivo = fopen("agenda.txt","r");

    if (!arquivo){
        file = 0;
    }
    else {
        file = 1;
    }
}
