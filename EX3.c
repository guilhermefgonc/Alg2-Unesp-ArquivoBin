/*
----------------------------------------------------------
Nome: Guilherme Goncalves      
----------------------------------------------------------

Escreva um programa que crie e/ou manipule um arquivo com os seguintes campos: NOME 
DO FUNCIONÁRIO, NÚMERO DA FIRMA, SEXO, IDADE, CARGO, SALÁRIO, NÚMERO DE 
DEPENDENTES e GRAU DE INSTRUÇÃO. O programa deve permitir a inclusão, a consulta 
e a remoção de registros, assim como a alteração dos campos de um determinado registro. 
O nome do arquivo deve ser fornecido pelo usuário, e o programa deve permitir reprocessa-
mento.
*/

#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#define MAX 100


typedef struct {
    char nome[MAX], cargo[MAX], grau[MAX], sexo;
    int numFirma, idade, numDependentes, existe;
    double salario;
}DadosFuncionario;


// funcao para limpar o buffer do teclado
void LimparBuffer() {
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return;
}


// funcao que cria o menu
int Menu () {

    int opcao;

    system("cls");
    printf("---------- M E N U ----------\n");
    printf("1 - Cadastrar novo funcionario\n");
    printf("2 - Remover funcionario\n");
    printf("3 - Alterar dados de um funcionario\n");
    printf("4 - Consultar dados de um funcionario\n");
    printf("Digite 0 para sair...\n\n");
    printf("---> ");
    scanf("%d", &opcao);

    return opcao;
}


// funcao para cadastra o funcionario no arquivo
void CadastrarFuncionario (char nomeArq[]) {

    DadosFuncionario f;

    system("cls");
    printf("----- CADASTRO DE FUNCIONARIO -----\n\n");
    
    FILE *arquivo = fopen(nomeArq, "ab");

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
        fgets(f.nome, MAX, stdin);
        printf("Numero da firma: ");
        scanf("%d", &f.numFirma);
        printf("Sexo (M/F): ");
        LimparBuffer();
        scanf("%c", &f.sexo);
        printf("Idade: ");
        scanf("%d", &f.idade);
        printf("Cargo: ");
        LimparBuffer();
        fgets(f.cargo, MAX, stdin);
        printf("Salario: ");
        scanf("%lf", &f.salario);
        printf("Numero de dependentes: ");
        scanf("%d", &f.numDependentes);
        printf("Grau de instrucao: ");
        LimparBuffer();
        fgets(f.grau, MAX, stdin);
        f.existe = 1;

        // salvando funcionario no arquivo
        fwrite(&f, sizeof(DadosFuncionario), 1, arquivo);
        fclose(arquivo);
        printf("\nFuncionario cadastrado com sucesso!\n");
        printf("-----------------------------------\n");
        printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
        getchar();
    }
}


// realiza a exclusao logica do funcionario
void RemoverFuncionario (char nomeArq[]) {

    DadosFuncionario f;
    char nome[MAX];
    int achou = 0;
    int tam;

    system("cls");
    printf("----- REMOVER FUNCIONARIO -----\n\n");

    FILE *arquivo = fopen(nomeArq, "r+b");

    if (!arquivo) {
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
        getchar();
    }
    else {
        printf("Qual o nome do funcionario que deseja remover? ");
        LimparBuffer();
        fgets(nome, MAX, stdin);
        
        while (achou == 0 && fread(&f, sizeof(DadosFuncionario), 1, arquivo) == 1) { // enquanto tem registros pra ler
            if (f.existe == 1 && strcmp(f.nome, nome) == 0) {                        
                achou = 1;

                // mostra os dados do funcionario que foi removido
                printf("\nDados do funcionario removido:\n\n");
                printf("Nome: %s", f.nome);
                printf("Numero da firma: %d\n", f.numFirma);
                printf("Sexo (M/F): %c\n", f.sexo);
                printf("Idade: %d\n", f.idade);
                printf("Cargo: %s", f.cargo);
                printf("Salario: %.2lf\n", f.salario);
                printf("Numero de dependentes: %d\n", f.numDependentes);
                printf("Grau de instrucao: %s", f.grau);
                f.existe = 0;

                // volta para o inicio do registro e grava os dados
                tam = sizeof(DadosFuncionario);
                fseek(arquivo, -tam , SEEK_CUR);
                fwrite(&f, sizeof(DadosFuncionario), 1, arquivo);
                fflush(arquivo);
                printf("\nFuncionario removido!\n");
            }
        }
        if (achou == 0) {
            printf("Nao existe funcionario com o nome %s\n", nome);
        }
        fclose(arquivo);
        printf("-------------------------------\n");
        printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
        getchar();
    }
}


// permite o usuario alterar um funcionario dado um nome
void AlterarFuncionario (char nomeArq[]) {

    DadosFuncionario f;
    char nome[MAX];
    int achou = 0;
    int tam;

    system("cls");
    printf("----- ALTERAR CADASTRO -----\n");
    
    FILE *arquivo = fopen(nomeArq, "r+b");

    if (!arquivo) {
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
        getchar();
    }
    else {
        printf("Qual o nome do funcionario que deseja alterar? ");
        LimparBuffer();
        fgets(nome, MAX, stdin);

        while (achou == 0 && fread(&f, sizeof(DadosFuncionario), 1, arquivo) == 1) {
            if (f.existe == 1 && strcmp(f.nome, nome) == 0) {

                // leitura dos dados
                achou = 1;
                printf("\nNome: %s", f.nome);
                printf("Numero da firma: ");
                scanf("%d", &f.numFirma);
                printf("Sexo (M/F): ");
                LimparBuffer();
                scanf("%c", &f.sexo);
                printf("Idade: ");
                scanf("%d", &f.idade);
                printf("Cargo: ");
                LimparBuffer();
                fgets(f.cargo, MAX, stdin);
                printf("Salario: ");
                scanf("%lf", &f.salario);
                printf("Numero de dependentes: ");
                scanf("%d", &f.numDependentes);
                printf("Grau de instrucao: ");
                LimparBuffer();
                fgets(f.grau, MAX, stdin);

                // volta pro inicio do registro e grava os dados alterados
                tam = sizeof(DadosFuncionario);
                fseek(arquivo, -tam, SEEK_CUR);
                fwrite(&f, sizeof(DadosFuncionario), 1, arquivo);
                fflush(arquivo);
                printf("\nAlteracao realizada!\n");
            }
        }
        if (achou == 0) {
            printf("Nao existe funcionario com o nome %s\n", nome);
        }
        fclose(arquivo);
        printf("----------------------------\n");
        printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
        getchar();
    } 
}


// permite que o usuario consulte um funcionario dado um nome
void ConsultarFuncionario (char nomeArq[]) {

    DadosFuncionario f;
    char nome[MAX];
    int achou = 0;
    int tam;

    system("cls");
    printf("----- CONSULTAR FUNCIONARIO -----\n");
    
    FILE *arquivo = fopen(nomeArq, "rb");

    if (!arquivo) {
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
        getchar();
    }
    else {
        printf("Qual o nome do funcionario que deseja consultar? ");
        LimparBuffer();
        fgets(nome, MAX, stdin);
        printf("\n");

        while (achou == 0 && fread(&f, sizeof(DadosFuncionario), 1, arquivo)) {
            if (f.existe == 1 && strcmp(f.nome, nome) == 0) {

                // mostra os dados do funcionario
                achou = 1;
                printf("Dados do funcionario:\n\n");
                printf("Nome: %s", f.nome);
                printf("Numero da firma: %d\n", f.numFirma);
                printf("Sexo (M/F): %c\n", f.sexo);
                printf("Idade: %d\n", f.idade);
                printf("Cargo: %s", f.cargo);
                printf("Salario: %.2lf\n", f.salario);
                printf("Numero de dependentes: %d\n", f.numDependentes);
                printf("Grau de instrucao: %s", f.grau);
                printf("\n");
            }
        }
        if (achou == 0) {
            printf("Nao existe funcionario com o nome %s\n", nome);
        }
        fclose(arquivo);
        printf("---------------------------------\n");
        printf("Pressione a tecla 'ENTER' para voltar ao menu...\n");
        getchar();
    }
}


// remove fisicamento os registros que foram excluido logicamente
void ExclusaoFisica (char nomeArq[]) {

    DadosFuncionario f;
    FILE *arquivo, *arqAux;

    arquivo = fopen(nomeArq, "rb");

    if (!arquivo) {
        printf("ERRO NA REMOCAO FISICA\n");
    }
    else {
        
        arqAux = fopen("FUNCIONARIOS.BAK", "wb");

        while (fread(&f, sizeof(DadosFuncionario), 1, arquivo) == 1) { // enquanto tem registros para ler

            // selecionando os funcionario que nao foram excluidos logicamente
            if (f.existe == 1) {
                fwrite(&f, sizeof(DadosFuncionario), 1, arqAux); // copiando dados no arquivo auxiliar
            }
        }
        fclose(arquivo);
        fclose(arqAux);
        
        remove(nomeArq); // removendo o arquivo antigo
        rename("FUNCIONARIOS.BAK", nomeArq); // tornando o o arquivo auxiliar como principal
        printf("Exclusao fisica realizada com sucesso!\n");
    }
}


int main () {

    char nomeArquivo[MAX];
    int opcao;

    printf("Digite o nome desejado para o arquivo: ");
    gets(nomeArquivo);

    do {
        opcao = Menu();

        switch (opcao) {
            case 0: printf("\nPrograma encerrado...\n"); break;
            case 1: CadastrarFuncionario(nomeArquivo); break;
            case 2: RemoverFuncionario(nomeArquivo); break;
            case 3: AlterarFuncionario(nomeArquivo); break;
            case 4: ConsultarFuncionario(nomeArquivo); break;
        default: break;
        }
    } while (opcao != 0);
    
    ExclusaoFisica(nomeArquivo);
    printf("-----------------------------");

    return 0;
}
