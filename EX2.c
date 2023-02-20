/*
----------------------------------------------------------
Nome: Guilherme Goncalves      
----------------------------------------------------------

Supondo-se que em um sistema computacional bancário exista um arquivo de acesso direto 
e que cada registro gravado use como chave o número da conta do cliente, escreva um pro-
grama que, lendo um número da conta de um cliente, escreva o número da conta, o nome e 
o saldo deste cliente.
*/

#include <stdio.h>
#include <windows.h>
#define MAX 100


// registros para cadastro do cliente
typedef struct {
    char nome[MAX];
    int conta;
    double saldo;
}Cliente;


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
    printf("1 - Cadastrar novo cliente\n");
    printf("2 - Consultar conta\n");
    printf("Digite 0 para sair...\n\n");
    printf("---> ");
    scanf("%d", &opcao);

    return opcao;
}


// cadastra o cliente no arquivo
void CadastrarCliente () {

    Cliente c;
    system("cls");
    printf("----- CADASTRO DE CLIENTE -----\n\n");
    
    FILE *arquivo = fopen("ClientesBanco.dat", "ab");
    if (!arquivo) {
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
        LimparBuffer();
        getchar();
    }
    else {
        // leitura dos dados
        printf("Nome: ");
        LimparBuffer();
        fgets(c.nome, MAX, stdin);
        printf("Saldo: ");
        scanf("%lf", &c.saldo);
        printf("Numero da conta: ");
        scanf("%d", &c.conta);

        // salvando novo cliente no arquivo
        fwrite(&c, sizeof(Cliente), 1, arquivo);
        fclose(arquivo);
        printf("\nCliente cadastrado com sucesso!\n");

        printf("-------------------------------\n");
        printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
        LimparBuffer();
        getchar();
    }
}


// consulta o cliente de acordo com o numero da conta
void ConsultarCliente () {

    Cliente c;
    int num;
    int achou = 0;

    system("cls");
    printf("----- CONSULTA DE CLIENTES -----\n\n");
    FILE *arquivo =  fopen("ClientesBanco.dat", "rb");

    if (!arquivo) {
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
        LimparBuffer();
        getchar();
    }
    else {
        printf("Digite o numero da conta: ");
        scanf("%d", &num);
        printf("\n");

        while (fread(&c, sizeof(Cliente), 1, arquivo) == 1) {
            if (c.conta == num) {
                printf("Nome: %s", c.nome);
                printf("Saldo: %.2lf\n", c.saldo);
                printf("Numero da conta: %d\n", c.conta);
                printf("\n");
                achou = 1;
            }
        }
        if (achou == 0) {
            printf("Este numero de conta nao existe!\n");
        }
        fclose(arquivo);
    }

    printf("--------------------------------\n");
    printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
    LimparBuffer();
    getchar();
}


int main () {

    int opcao;
    
    do {
        opcao = Menu();

        switch (opcao) {
            case 0: printf("\nPrograma encerrado...\n"); break;
            case 1: CadastrarCliente(); break;
            case 2: ConsultarCliente(); break;
            default: break;
        }
    } while (opcao != 0);

    printf("-----------------------------");
    return 0;
}
