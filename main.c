/*        -=-=-=-=- POLIFLEET - Gerenciamento de Viaturas -=-=-=-=-
    Código Inicial Básico: Como ainda não utilizaremos ponteiros ou coisas mais 
    avançadas, então, o código se baseia em funções e structs, que foram os assuntos 
    abordados inicialmente em LP2. Por esse motivo, os vetores terão tamanhos fixos. 

*/
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX_VIATURAS 10
#define TAM 50

typedef struct {
    char tipoVeiculo[TAM]; // Carro, moto..
    char placa[TAM];
    char renavam[TAM]; // Número de Registro do DETRAN.
    char cor[TAM];
    int quilometragem;
    char status[TAM]; // Se está ativo, em manunteção..
    int categoria; // Se o carro é a paisana, oficial ou base móvel.
    int turno;     
    char nomePolicial[TAM];
    int permissao; // comando, manutenção, TI..
} Viatura;

// Protótipos
void menu();
void submenuBusca();
int cadastrarViatura(Viatura[], int);
void listarViaturas(Viatura[], int);
void limparBuffer();
void buscarPorPlaca(Viatura[], int);
void buscarPorTurno(Viatura[], int);
void buscarPorPolicial(Viatura[], int);
void limparTela();

// INICIO MAIN
int main(void) 
{
    Viatura viaturas[MAX_VIATURAS];
    int totalViaturas = 0;
    int opcao;

    do {
        menu();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) 
        {
            case 1:
                if (totalViaturas < MAX_VIATURAS) 
                    totalViaturas = cadastrarViatura(viaturas, totalViaturas);
                else 
                    printf("Limite máximo de viaturas atingido!\n");
                break;

            case 2:
                listarViaturas(viaturas, totalViaturas);
                break;

            case 3:
                submenuBusca();
                int opBusca;
                scanf("%d", &opBusca);
                limparBuffer();

                switch (opBusca) 
                {
                    case 1:
                        buscarPorPlaca(viaturas, totalViaturas);
                        break;
                    case 2:
                        buscarPorTurno(viaturas, totalViaturas);
                        break;
                    case 3:
                        buscarPorPolicial(viaturas, totalViaturas);
                        break;
                    case 0:
                        printf("Voltando ao menu principal...\n");
                        break;
                    default:
                        printf("Opção inválida!\n");
                }
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// INICIO MENU
void menu() 
{
    printf("\n-=-=-=- MENU POLIFLEET -=-=-=-\n");
    printf("[ 1 ] Cadastrar Viatura\n");
    printf("[ 2 ] Listar Viaturas\n");
    printf("[ 3 ] Buscar Viatura\n");
    printf("[ 0 ] Sair\n");
    printf("Escolha: ");
}

// INICIO SUBMENU BUSCA
void submenuBusca() 
{
    printf("\n-=-=-=- BUSCAR VIATURA -=-=-=-\n");
    printf("[ 1 ] Buscar por Placa\n");
    printf("[ 2 ] Buscar por Turno\n");
    printf("[ 3 ] Buscar por Policial\n");
    printf("[ 0 ] Voltar ao menu principal\n");
    printf("Escolha: ");
}

// INICIO CADASTRAR VIATURA
int cadastrarViatura(Viatura v[], int total) 
{
    limparTela();
    printf("\n-=-=-=-=- Cadastro da Viatura %d -=-=-=-=-\n", total + 1);

    printf("\nCertifique-se de adicionar os dados corretamente.\n");
    printf("Caso haja algum erro, o status ficará como \"desconhecida\".\n\n");

    printf("Qual o tipo de veiculo (Ex.: Carro, Moto..): ");
    scanf("%49[^\n]", v[total].tipoVeiculo);
    limparBuffer();

    printf("Placa: ");
    scanf("%49[^\n]", v[total].placa);
    limparBuffer();

    printf("Renavam: "); // Número de Registro do DETRAN
    scanf("%49[^\n]", v[total].renavam);
    limparBuffer();

    printf("Cor: ");
    scanf("%49[^\n]", v[total].cor);
    limparBuffer();

    printf("Quilometragem: ");
    scanf("%d", &v[total].quilometragem);
    limparBuffer();

    printf("Status (Ex.: ativo, manutenção..): ");
    scanf("%49[^\n]", v[total].status);
    limparBuffer();

    printf("Categoria (0 = paisana, 1 = oficial, 2 = base móvel): ");
    scanf("%d", &v[total].categoria);
    limparBuffer();

    printf("Turno (0 = manhã, 1 = tarde, 2 = noite): ");
    scanf("%d", &v[total].turno);
    limparBuffer();

    printf("Policial responsável: ");
    scanf("%49[^\n]", v[total].nomePolicial);
    limparBuffer();

    printf("Permissão (0 = comando, 1 = operador, 2 = manutenção, 3 = TI): ");
    scanf("%d", &v[total].permissao);
    limparBuffer();

    limparTela();
    printf("\nViatura cadastrada com sucesso!\n\n");

    return total + 1;
}

// INICIO LISTAR VIATURA
void listarViaturas(Viatura v[], int total) 
{
    limparTela();
    printf("\n-=-=-=-=- Lista de Viaturas -=-=-=-=-\n");

    for (int i = 0; i < total; i++) 
    {
        printf("\nViatura %d:\n", i + 1);
        printf("Tipo: %s\n", v[i].tipoVeiculo);
        printf("Placa: %s\n", v[i].placa);
        printf("Renavam: %s\n", v[i].renavam);
        printf("Cor: %s\n", v[i].cor);
        printf("Quilometragem: %d km\n", v[i].quilometragem);
        printf("Status: %s\n", v[i].status);

        printf("Categoria: ");
        switch (v[i].categoria) 
        {
            case 0: printf("Paisana\n"); break;
            case 1: printf("Oficial\n"); break;
            case 2: printf("Base móvel\n"); break;
            default: printf("Desconhecida\n");
        }

        printf("Turno: %d\n", v[i].turno);
        switch (v[i].turno) 
        {
            case 0: printf("manhã\n"); break;
            case 1: printf("tarde\n"); break;
            case 2: printf("noite\n"); break;
            default: printf("Desconhecido\n");
        }

        printf("Policial: %s\n", v[i].nomePolicial);
        
        printf("Permissão: ");
        switch (v[i].permissao) 
        {
            case 0: printf("Comando\n"); break;
            case 1: printf("Operador\n"); break;
            case 2: printf("Manutenção\n"); break;
            case 3: printf("TI\n"); break;
            default: printf("Desconhecida\n");
        }
    }
}

// INICIO BUSCAR POR PLACA
void buscarPorPlaca(Viatura v[], int total) 
{
    char placaBusca[TAM];
    int encontrado = 0;

    printf("Digite a placa a ser encontrada: ");
    scanf("%49[^\n]", placaBusca);
    limparBuffer();
    limparTela();

    for (int i = 0; i < total; i++) 
    {
        if (strcmp(v[i].placa, placaBusca) == 0) 
        {
            listarViaturas(&v[i], 1);
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("Nenhuma viatura com essa placa foi encontrada.\n");
}

// INICIO BUSCA POR TURNO
void buscarPorTurno(Viatura v[], int total) 
{
    int turnoBusca;
    int encontrado = 0;

    printf("Digite o turno (0, 1 ou 2): ");
    scanf("%d", &turnoBusca);
    limparBuffer();
    limparTela();

    for (int i = 0; i < total; i++) 
    {
        if (v[i].turno == turnoBusca) 
        {
            listarViaturas(&v[i], 1);
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("Nenhuma viatura com esse turno foi encontrada.\n");
}

// INICIO BUSCAR POR POLICIAL
void buscarPorPolicial(Viatura v[], int total) 
{
    char policialBusca[TAM];
    int encontrado = 0;

    printf("Digite o nome do policial: ");
    scanf("%49[^\n]", policialBusca);
    limparBuffer();
    limparTela();

    for (int i = 0; i < total; i++) 
    {
        if (strstr(v[i].nomePolicial, policialBusca) != NULL) 
        {
            listarViaturas(&v[i], 1);
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("Nenhuma viatura com esse policial foi encontrada.\n");
}

// INICIO LIMPAR BUFFER
void limparBuffer() 
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// INICIO LIMPAR TELA
void limparTela()
{
    system("clear");
}