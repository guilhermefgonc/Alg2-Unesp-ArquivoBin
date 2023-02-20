/*
----------------------------------------------------------
LISTA 2 - EX 1

Nome: Guilherme Goncalves       
----------------------------------------------------------

Declare um arquivo com registros que contém os seguintes campos: NÚMERO DA CONTA, 
NOME DO CLIENTE, SALDO e DATA DA ÚLTIMA OPERAÇÃO. Faça um programa que ca-
dastre e consulte os registros deste arquivo. 
*/

#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#define MAX 100


typedef struct {
    int dia, mes, ano;
}DataOperacao;

typedef struct {
    int conta;
    char nome[MAX];
    double saldo;
    DataOperacao data;
}RegistroCliente;

RegistroCliente Lista[MAX];
int quant = 0; // para saber quantas cadastros foram realizados


// funcao para limpar o buffer do teclado
void LimparBuffer() {
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return;
}


// funcao que mostra para o usuario como utilizar o programa
void GuiaUsuario(){

    printf("--------------- GUIA DO USUARIO ---------------\n\n");
    printf("\tBem vindo ao Guia do Usuario!\n\n");
    printf("Para utilizar o programa corretamente,\n");
    printf("eh necessario que antes de cadastrar qualquer\n");
    printf("novo cliente, seja realizada a leitura do arquivo\n");
    printf("(eh possivel fazer isso com a opcao 4 do menu).\n");
    printf("Depois disso, podera cadastrar e consultar a lista\n");
    printf("de clientes normalmente.\n");
    printf("Antes de fechar o programa, tambem deve ser feito o\n");
    printf("salvamento no arquivo (opcao 3 no menu).\n");
    printf("\n-----------------------------------------------\n");

    printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
    LimparBuffer();
    getchar();
}


// funcao que cria o menu de opcoes para o usuario  
int menu (int opcao) {

    system("cls");
    printf("---------- MENU ----------\n");
    printf("1 - Cadastrar cliente\n");
    printf("2 - Consultar clientes\n");
    printf("3 - Salvar os dados no arquivo\n");
    printf("4 - Ler os dados do arquivo\n");
    printf("5 - Abrir o Guia do Usuario\n");
    printf("Digite 0 para sair...\n");
    printf("---> ");
    scanf("%d", &opcao);

    return opcao;
}


// funcao que faz a leitura do cadastro do cliente
void CadastrarCliente () {

    int sair;
    RegistroCliente cliente;

    // leitura de dados do cliente
    system("cls");
    printf("----- CADASTRO DE CLIENTES -----\n\n");
    printf("Nome: ");
    LimparBuffer();
    fgets(cliente.nome, MAX, stdin);
    cliente.nome[0] = toupper(cliente.nome[0]);
    printf("Saldo: ");
    scanf("%lf", &cliente.saldo);
    printf("Data da operacao (dd/mm/aaaa): ");
    scanf("%d %d %d", &cliente.data.dia, &cliente.data.mes, &cliente.data.ano);
    printf("Seu numero de conta eh: %d", cliente.conta = quant + 1);
    Lista[quant] = cliente;
    quant++;
    printf("\n--------------------------------\n");
    printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
    LimparBuffer();
    getchar();
}


// funcao para consultar os dados que estao no vetor Lista
void ConsultarCadastros () {

    system("cls");
    printf("----- LISTA DE CLIENTES -----\n\n");

    for (int i = 0; i < quant; i++) {
        printf("Nome: %s",Lista[i].nome);
        printf("Saldo: %.2lf\n", Lista[i].saldo);
        printf("Data da operacao: %d/%d/%d\n", Lista[i].data.dia, Lista[i].data.mes, Lista[i].data.ano);
        printf("Numero da conta: %d\n", Lista[i].conta);
        printf("\n");
    }

    printf("-----------------------------\n");
    printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
    LimparBuffer();
    getchar();
}


// funcao para salvar os dados do cliente em arquivo binario
void SalvarEmArquivo () {

    system("cls");
    FILE *arquivo = fopen("listaClientes.dat", "wb");

    printf("----- SALVANDO DADOS NO ARQUIVO... -----\n\n");

    if (!arquivo) {
        printf("\tERRO AO ABRIR O ARQUIVO!\n");
    }
    else {
        fprintf(arquivo, "%d\n", quant);
        fwrite(Lista, sizeof(RegistroCliente), quant, arquivo);
        fclose(arquivo);
        printf("\tSALVO COM SUCESSO!\n");
    }

    printf("\n----------------------------------------\n");
    printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
    LimparBuffer();
    getchar();
}


// funcao que faz a leitura dos dados do arquivo
void LerDoArquivo () {

    system("cls");
    FILE *arquivo = fopen("listaClientes.dat", "rb");
    printf("----- LENDO DADOS DO ARQUIVO... -----\n\n");

    if (!arquivo) {
        printf("\tERRO AO ABRIR O ARQUIVO!\n");
    }
    else {
        fscanf(arquivo, "%d\n", &quant);
        fread(Lista, sizeof(RegistroCliente), quant, arquivo);
        fclose(arquivo);
        printf("\tLEITURA REALIZADA COM SUCESSO!\n");
    }

    printf("\n-------------------------------------\n");
    printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
    LimparBuffer();
    getchar();
}


int main () {

    int opcao;

    do {
        opcao = menu(opcao);
        
        switch (opcao)
        {
        case 0:
            printf("Programa encerrado...\n");
            printf("--------------------------");
            break;
        case 1:
            CadastrarCliente();
            break;
        case 2:
            ConsultarCadastros();
            break;
        case 3:
            SalvarEmArquivo();
            break;
        case 4:
            LerDoArquivo();
            break;
        case 5:
            GuiaUsuario();
            break;
        default:
            break;
        }

    } while (opcao != 0);
    
    return 0;
}
