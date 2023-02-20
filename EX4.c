/*
----------------------------------------------------------
Nome: Guilherme Goncalves    
----------------------------------------------------------

Faça um programa gerenciar uma agenda de contatos. Para cada contato armazene o nome, 
o telefone e o aniversário (dia e mês). O programa deve permitir (1) inserir contato, (2) remo-
ver contato, (3) pesquisar um contato pelo nome, (4) listar todos os contatos, (5) listar os con-
tatos cujo nome inicia com uma dada letra, (6) imprimir os aniversariantes do mês. Sempre 
que o programa for encerrado, os contatos devem ser armazenados em um arquivo binário. 
Quando o programa iniciar, os contatos devem ser inicializados com os dados contidos neste 
arquivo binário.  
*/

#include <stdio.h>
#include<windows.h>
#include <ctype.h>
#define MAX 100

typedef struct {
    int dia, mes;
}DataAniversario;

typedef struct {
    int existe;
    char nome[MAX];
    char telefone[20];
    DataAniversario aniversario;
}DadosContato;


// funcao para limpar o buffer do teclado
void LimparBuffer() {
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return;
}


// funcao que cria o menu para o usuario
int Menu () {

    int opcao;

    system("cls");
    printf("---------- M E N U ----------\n");
    printf("1 - Inserir novo contato\n");
    printf("2 - Remover contato\n");
    printf("3 - Pesquisar contato pelo nome\n");
    printf("4 - Listar todos contatos\n");
    printf("5 - Listar contatos pela letra\n");
    printf("6 - Listar aniversariantes do mes\n");
    printf("Digite 0 para sair...\n\n");
    printf("---> ");
    scanf("%d", &opcao);

    return opcao;
}


// cadastra um novo contato no arquivo
void InserirContato () {

    DadosContato c;

    system("cls");
    printf("----- INSERIR NOVO CONTATO -----\n\n");

    FILE *arquivo = fopen("Agenda.dat", "ab");

    if (!arquivo) {
        printf("ERRO AO ABRIR O ARQUIVO!\n\n");
        printf("--------------------------------\n");
        printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
        LimparBuffer();
        getchar();
        return;
    }

    // leitura dos dados do contato
    printf("Nome: ");
    LimparBuffer();
    fgets(c.nome, MAX, stdin);
    c.nome[0] = toupper(c.nome[0]);
    printf("Telefone: ");
    fgets(c.telefone, MAX, stdin);
    printf("Data de aniversario (dd mm): ");
    scanf("%d %d", &c.aniversario.dia, &c.aniversario.mes);
    c.existe = 1;

    // salvando dados no arquivo
    fwrite(&c, sizeof(DadosContato), 1, arquivo);
    fclose(arquivo);

    printf("\nContato cadastrado com sucesso!\n");
    printf("--------------------------------\n");
    printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
    LimparBuffer();
    getchar();
}


// faz a exclusao logica do contato
void RemoverContato () {

    DadosContato c;
    char nome[MAX];
    int achou = 0;
    int tam;

    system("cls");
    printf("----- REMOVER CONTATO -----\n\n");

    FILE *arquivo = fopen("Agenda.dat", "r+b");

    if (!arquivo) {
        printf("ERRO AO ABRIR O ARQUIVO!\n\n");
        printf("---------------------------\n");
        printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
        LimparBuffer();
        getchar();
        return;
    }

    printf("Qual o nome do contato que deseja remover? ");
    LimparBuffer();
    fgets(nome, MAX, stdin);

    while (achou == 0 && fread(&c, sizeof(DadosContato), 1, arquivo) == 1) { // enquanto o arquivo tem registros para ler 
        if (c.existe == 1 && strcmp(nome, c.nome) == 0) {

            achou = 1; // para saber que o contato foi encontrado

            // mostra os dados do contato removido
            printf("\nNome: %s", c.nome);
            printf("Telefone: %s", c.telefone);
            printf("Data de aniversario: %d/%d", c.aniversario.dia, c.aniversario.mes);
            c.existe = 0;

            // volta para o inicio do registro e grava os dados
            tam = sizeof(DadosContato); // para nao ter problemas de conversao
            fseek(arquivo, -tam , SEEK_CUR);
            fwrite(&c, sizeof(DadosContato), 1, arquivo);
            fflush(arquivo);
            printf("\nContato removido!\n");
        }
    }
    if (achou == 0) { // se o contato nao foi encontrado
        printf("Nao existe contato com o nome %s\n", nome);
    }
    // fecha o arquivo e exibe mensagem para voltar ao menu
    fclose(arquivo);
    printf("---------------------------\n");
    printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
    getchar();
}


// pesquisa um contato pelo nome
void PesquisarNome () {

    DadosContato c;
    int achou = 0;
    char nome[MAX];

    system("cls");
    printf("----- PESQUISAR CONTATO PELO NOME -----\n\n");

    FILE *arquivo = fopen("Agenda.dat", "rb");

    if (!arquivo) {
        printf("ERRO AO ABRIR O ARQUIVO!\n\n");
        printf("---------------------------------------\n");
        printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
        LimparBuffer();
        getchar();
        return;
    }

    printf("Qual o nome do contato que deseja pesquisar? ");
    LimparBuffer();
    fgets(nome, MAX, stdin);

    while (achou == 0 && fread(&c, sizeof(DadosContato), 1, arquivo) == 1) { // enquanto o arquivo tem registros para ler 
        if (c.existe == 1 && strcmp(nome, c.nome) == 0) {

            achou = 1; // contato encontrado

            // mostra as informacoes do contato
            printf("\nNome: %s", c.nome);
            printf("Telefone: %s", c.telefone);
            printf("Data de aniversario: %d/%d\n", c.aniversario.dia, c.aniversario.mes);
        }
    }
    if (achou == 0) { // se o contato nao foi encontrado
        printf("Nao existe contato com o nome %s\n", nome);
    }

    // fecha o arquivo e exibe mensagem para voltar ao menu
    fclose(arquivo);
    printf("---------------------------------------\n");
    printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
    getchar();
}


// lista todos os contatos para o usuario
void ListarTodos () {

    DadosContato c;

    system("cls");
    printf("----- LISTA DE CONTATOS -----\n");

    FILE *arquivo = fopen("Agenda.dat", "rb");

    if (!arquivo) {
        printf("ERRO AO ABRIR O ARQUIVO!\n\n");
        printf("-----------------------------\n");
        printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
        LimparBuffer();
        getchar();
        return;
    }

    while (fread(&c, sizeof(DadosContato), 1, arquivo) == 1) {  // enquanto o arquivo tem registros para ler 

        // mostra os dados dos contatos que nao forma removidos logicamente
        if (c.existe == 1) { 
            printf("\n");
            printf("Nome: %s", c.nome);
            printf("Telefone: %s", c.telefone);
            printf("Data de aniversario: %d/%d\n", c.aniversario.dia, c.aniversario.mes);
        }
    }

    // fecha o arquivo e exibe mensagem para voltar ao menu
    fclose(arquivo);
    printf("\n-----------------------------\n");
    printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
    LimparBuffer();
    getchar();
}


// Lista todos os contatos que comecam com uma letra determinada pelo usuario
void ListarPorLetra () {

    DadosContato c;
    char letra;

    system("cls");
    printf("----- PESQUISA DE CONTATO POR LETRA -----\n\n");

    FILE *arquivo = fopen("Agenda.dat", "rb");

    if (!arquivo) {
        printf("ERRO AO ABRIR O ARQUIVO!\n\n");
        printf("-----------------------------------------\n");
        printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
        LimparBuffer();
        getchar();
        return;
    }

    printf("Deseja listar os contatos iniciados por qual letra? ");
    LimparBuffer();
    scanf("%c", &letra);
    letra = toupper(letra);
    printf("\n");

    while (fread(&c, sizeof(DadosContato), 1, arquivo) == 1) {  // enquanto o arquivo tem registros para ler

        // mostra os dados dos contatos que comecam com a letra determinada pelo usuario
        if (c.existe == 1 && strncmp(&letra, c.nome, 1) == 0) {
            printf("Nome %s", c.nome);
            printf("Telefone: %s", c.telefone);
            printf("Data de aniversario: %d/%d\n", c.aniversario.dia, c.aniversario.mes);
            printf("\n");
        }
    }

    // fecha o arquivo e exibe mensagem para voltar ao menu
    fclose(arquivo);
    printf("\n-----------------------------\n");
    printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
    LimparBuffer();
    getchar();
}


// Lista todos os contatos que fazem aniversario em um mes determinado pelo usuario
void ListarPorMes () {

    DadosContato c;
    int mes;

    system("cls");
    printf("----- PESQUISA DE CONTATO POR MES -----\n\n");

    FILE *arquivo = fopen("Agenda.dat", "rb");

    if (!arquivo) {
        printf("ERRO AO ABRIR O ARQUIVO!\n\n");
        printf("---------------------------------------\n");
        printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
        LimparBuffer();
        getchar();
        return;
    }

    printf("Deseja listar os contatos que fazem aniversario em qual mes? ");
    scanf("%d", &mes);
    printf("\n");

    while (fread(&c, sizeof(DadosContato), 1, arquivo) == 1) {

        // mostra os dados dos contatos que fazem aniversario no mes escolhido pelo usuario
        if (c.existe == 1 && mes == c.aniversario.mes) {
            printf("Nome %s", c.nome);
            printf("Telefone: %s", c.telefone);
            printf("Data de aniversario: %d/%d\n", c.aniversario.dia, c.aniversario.mes);
            printf("\n");
        }
    }

    // fecha o arquivo e exibe mensagem para voltar ao menu
    fclose(arquivo);
    printf("\n-----------------------------\n");
    printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
    LimparBuffer();
    getchar();
}


// remove fisicamento os registros que foram excluido logicamente
void RemocaoFisica () {

    DadosContato c;
    FILE *arquivo, *arqAux;

    arquivo = fopen("Agenda.dat", "rb");

    if (!arquivo) {
        printf("ERRO NA REMOCAO FISICA\n");
        return;
    }

    arqAux = fopen("CONTATOS.BAK", "wb");

    while (fread(&c, sizeof(DadosContato), 1, arquivo) == 1) { // enquanto o arquivo principal tem registros para ler

        // escrevendo no arquivo auxiliar os contatos que nao foram removidos logicamente
        if (c.existe == 1) {
            fwrite(&c, sizeof(DadosContato), 1, arqAux);
        }
    }

    fclose(arquivo);
    fclose(arqAux);

    remove("Agenda.dat"); // removendo o arquivo antigo
    rename("CONTATOS.BAK", "Agenda.dat"); // tornando o arquivo atualizado o principal
    printf("Exclusao fisica realizada com sucesso!\n");
}


int main () {

    int opcao;

    do {
        opcao = Menu();

        switch (opcao) {
            case 0: printf("\nPrograma encerrado...\n"); break;
            case 1: InserirContato(); break;
            case 2: RemoverContato(); break;
            case 3: PesquisarNome(); break;
            case 4: ListarTodos(); break;
            case 5: ListarPorLetra(); break;
            case 6: ListarPorMes(); break;
        default: break;
        }
    } while (opcao != 0);

    RemocaoFisica();
    printf("a----------------------------");

    return 0;
}
