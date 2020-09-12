#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

typedef struct contato {
    int codigo;
    int ativo;
    char nome [BUFFER_SIZE];
    char email [BUFFER_SIZE];
    char celular [BUFFER_SIZE];
} Contato;

Contato contato;
Contato contatos[BUFFER_SIZE];

void incluirContato();
void listarContato();
void excluirContato();
void alterarContato();
int finalizar();
void clrscr();
int proximoId();
void entradaDados();
void fileInToArray();

void main() {
    int opcao;
    char userInput[BUFFER_SIZE];

    do {        
        printf("\n\n\t\tMENU");
        printf("\n1 - Incluir");
        printf("\n2 - Excluir");
        printf("\n3 - Alterar");
        printf("\n4 - Listar");
        printf("\n5 - Finalizar");
        printf("\nOpção: ");
        sscanf(fgets(userInput, BUFFER_SIZE-1, stdin),"%d", &opcao);
        getchar();
        fflush(stdin);
        fileInToArray();
        clrscr();
        switch (opcao) {
            case 1:
                fflush(stdin);
                printf("\nopcao: %d", opcao);
                entradaDados();
                incluirContato(contato.nome, contato.celular, contato.email);
                clrscr();
                break;
            case 2:
                clrscr();
                excluirContato();
                getchar();
                fflush(stdin);
                break;
            case 3:
                clrscr();
                alterarContato();
                break;
            case 4:
                clrscr();
                listarContato();
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
    FILE *agenda = fopen("agenda.txt","a");
    fprintf(agenda, "%d;%d;%s;%s;%s\n", id, 1, nome, tel, email);
    fclose(agenda);
}

void listarContato(){
    FILE *arquivo = fopen("agenda.txt","r");
    char str[128];
    int result;
    char nome[BUFFER_SIZE];
    char tel[BUFFER_SIZE];
    char email[BUFFER_SIZE];
    int id, del, i = 0;
    int tamanho = proximoId();

    printf("\t--------------------------------------------------------\n");
    printf("\t------------------------CONTATOS------------------------\n");
    printf("\t--------------------------------------------------------\n\n");

    printf("  ID\t\t\tNOME\t\t\t\tTELEFONE\t\tEMAIL\n\n");

    for (int j = 0; j < tamanho-1; j++)
    {
        if (contatos[i].ativo != 0)
        {
            printf("%2d", contatos[i].codigo);
            printf(" %40s", contatos[i].nome);
            printf(" %24s", contatos[i].celular);
            printf(" %30s", contatos[i].email);
        }
        i++;
    }

    fclose(arquivo);
    getchar();
}

int finalizar(){
    clrscr();
    printf("--------------------------------------------------------\n");
    printf("--------------------FINALIZANDO PROGRAMA----------------\n");
    printf("--------------------------------------------------------\n\n");
    getchar();
    return 0;
}

void excluirContato (){
    FILE *arquivo = fopen("agenda.txt","r");
    FILE *copia = fopen("copia.txt","a");
    int opcao = 0, i = 0;
    int tamanho = proximoId();
    clrscr();
    printf("--------------------------------------------------------\n");
    printf("--------------------EXCLUIR CONTATO---------------------\n");
    printf("--------------------------------------------------------\n\n");
    printf("\n\n\t\tEscolha o contato a ser excluído pelo seu id\n");
    listarContato();
    printf("\nOpção: ");
    
    scanf("%d", &opcao);

    for (int j = 0; j < tamanho-1; j++)
    {
        if (opcao != contatos[i].codigo)
        {
            fprintf(copia, "%d;%d;%s;%s;%s", contatos[i].codigo, contatos[i].ativo, contatos[i].nome, contatos[i].celular, contatos[i].email);
        }else
        {
            fprintf(copia, "%d;%d;%s;%s;%s", contatos[i].codigo, 0, contatos[i].nome, contatos[i].celular, contatos[i].email);
        }
        i++;
    }
    fclose(arquivo);
    fclose(copia);
    remove("agenda.txt");
    rename("copia.txt", "agenda.txt");

}

void fileInToArray (){
    FILE *arquivo = fopen("agenda.txt","r");

    if (!arquivo)
    {
        printf("nao foi possível abrir o arquivo!");
        exit(0);
    }

    char buff[1024];
    int row_count = 0;
    int filed_count = 0;

    int i = 0;
    while (fgets(buff, 1023, arquivo))
    {
        filed_count = 0;
        row_count++;
        char *field = strtok(buff, ";");
        while (field)
        {
            if(filed_count == 0) contatos[i].codigo = atoi(field);
            if(filed_count == 1) contatos[i].ativo = atoi(field);
            if(filed_count == 2) strcpy(contatos[i].nome, field);
            if(filed_count == 3) strcpy(contatos[i].celular, field);
            if(filed_count == 4) strcpy(contatos[i].email, field);

            field = strtok(NULL, ";");
            filed_count++;
        }
        i++;
    }

    for (int j = 0; j < row_count; j++)
    {
        printf("ID: %d, Ativo: %d, Nome: %s, Tel: %s, Email: %s\n", contatos[j].codigo, contatos[j].ativo, contatos[j].nome, contatos[j].celular, contatos[j].email);
    }

    fclose(arquivo);
}

void alterarContato (){
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

void entradaDados(){
    char userInput[BUFFER_SIZE];
    printf("\nDigite um nome: ");
    sscanf(fgets(userInput, BUFFER_SIZE-1, stdin),"%[^\n]", contato.nome);
    printf("\nDigite um telefone: ");
    sscanf(fgets(userInput, BUFFER_SIZE-1, stdin),"%[^\n]", contato.celular);
    printf("\nDigite um email: ");
    sscanf(fgets(userInput, BUFFER_SIZE-1, stdin),"%[^\n]", contato.email);
    fflush(stdin);
 }