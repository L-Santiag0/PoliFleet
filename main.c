/*        -=-=-=-=- POLIFLEET - Gerenciamento de Viaturas -=-=-=-=-
    Código modificado: Adicionado alerta de vencimento de documentos

*/
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>

#define TAM 50

// INICIO STRUCT DATA
typedef struct Data{
    int dia;
    int mes;
    int ano;
} Data;

// INICIO STRUCT VIATURA
typedef struct Viatura{
    char tipoVeiculo[TAM]; // Carro, moto..
    char placa[TAM];
    char renavam[TAM]; // Número de Registro do DETRAN.
    char cor[TAM];
    int quilometragem;
    int ultimaRevisaoKM;
    char status[TAM]; // Se está ativo, em manunteção..
    int categoria; // Se o carro é a paisana, oficial ou base móvel.
    int turno;     
    char nomePolicial[TAM];
    int permissao; // comando, manutenção, TI..
    Data vencimentoIPVA;
    Data vencimentoLicenciamento;
    Data vencimentoSeguro;
    struct Viatura* prox;
} Viatura;

// Protótipos
void menu(); 
void submenuBusca();
Viatura* cadastrarViatura(Viatura*);
void listarViaturas(Viatura*);
void limparBuffer();
void buscarPorPlaca(Viatura*);
void buscarPorTurno(Viatura*);
void buscarPorPolicial(Viatura*);
void limparTela();
void alterarViatura(Viatura*);
Viatura* excluirViatura(Viatura*);
void lerData(Data*);
void exibirData(Data);
void exibirViatura(Viatura*);
int dataVencida(Data);

// INICIO MAIN
int main(void) 
{
    Viatura* viaturas = NULL;
    int opcao;

    do {
        menu();
        if(scanf("%d", &opcao) != 1)
            printf("Entrada inválida. Digite um número!\n");
        limparBuffer();

        switch (opcao) 
        {
            case 1:
                viaturas = cadastrarViatura(viaturas);
                break;

            case 2:
                listarViaturas(viaturas);
                break;

            case 3:
                submenuBusca();
                int opBusca;
                if(scanf("%d", &opBusca) != 1)
                    printf("Entrada inválida. Digite um número!\n");
                limparBuffer();

                switch (opBusca) 
                {
                    case 1:
                        buscarPorPlaca(viaturas);
                        break;
                    case 2:
                        buscarPorTurno(viaturas);
                        break;
                    case 3:
                        buscarPorPolicial(viaturas);
                        break;
                    case 0:
                        printf("Voltando ao menu principal...\n");
                        break;
                    default:
                        printf("Opção inválida!\n");
                }
                break;

            case 4:
                alterarViatura(viaturas);
                break;
            
            case 5:
                viaturas = excluirViatura(viaturas);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    while(viaturas != NULL)
    {
        Viatura* temp = viaturas;
        viaturas = viaturas -> prox;
        free(temp);
    }

    return 0;
}

// INICIO MENU
void menu() 
{
    printf("\n-=-=-=- MENU POLIFLEET -=-=-=-\n");
    printf("[ 1 ] Cadastrar Viatura\n");
    printf("[ 2 ] Listar Viaturas\n");
    printf("[ 3 ] Buscar Viatura\n");
    printf("[ 4 ] Alterar Viatura\n");
    printf("[ 5 ] Excluir Viatura\n");
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
Viatura* cadastrarViatura(Viatura* v) 
{
    limparTela();

    Viatura* novaViatura = (Viatura*) malloc(sizeof(Viatura));

    if(!novaViatura)
    {
        printf("ERRO: memoria insuficiente!\n");
        return v;
    }

    printf("\n-=-=-=-=- Cadastro da Viatura  -=-=-=-=-\n");

    printf("\nCertifique-se de adicionar os dados corretamente.\n");
    printf("Caso haja algum erro, o status ficará como \"desconhecida\".\n\n");

    printf("Qual o tipo de veiculo (Ex.: Carro, Moto..): ");
    scanf("%49[^\n]", novaViatura->tipoVeiculo);
    limparBuffer();

    printf("Placa: ");
    scanf("%49[^\n]", novaViatura->placa);
    limparBuffer();

    printf("Renavam: "); // Número de Registro do DETRAN
    scanf("%49[^\n]", novaViatura->renavam);
    limparBuffer();

    printf("Cor: ");
    scanf("%49[^\n]", novaViatura->cor);
    limparBuffer();

    printf("Quilometragem atual: ");
    scanf("%d", &novaViatura->quilometragem);
    limparBuffer();

    printf("Quilometragem da última revisão: ");
    scanf("%d", &novaViatura->ultimaRevisaoKM);
    limparBuffer();

    printf("Status (Ex.: ativo, manutenção..): ");
    scanf("%49[^\n]", novaViatura->status);
    limparBuffer();

    printf("Categoria (0 = paisana, 1 = oficial, 2 = base móvel): ");
    scanf("%d", &novaViatura->categoria);
    limparBuffer();

    printf("Turno (0 = manhã, 1 = tarde, 2 = noite): ");
    scanf("%d", &novaViatura->turno);
    limparBuffer();

    printf("Policial responsável: ");
    scanf("%49[^\n]", novaViatura->nomePolicial);
    limparBuffer();

    printf("Permissão (0 = comando, 1 = operador, 2 = manutenção, 3 = TI): ");
    scanf("%d", &novaViatura->permissao);
    limparBuffer();

    printf("Data de vencimento do IPVA:\n");
    lerData(&novaViatura->vencimentoIPVA);

    printf("\nData de vencimento do Licenciamento:\n");
    lerData(&novaViatura->vencimentoLicenciamento);

    printf("\nData de vencimento do Seguro:\n");
    lerData(&novaViatura->vencimentoSeguro);

    novaViatura->prox = v;
    v = novaViatura;

    limparTela();

    printf("\nViatura cadastrada com sucesso!\n\n");

    return v;
}

// INICIO LISTAR VIATURA
void listarViaturas(Viatura* v) 
{
    limparTela();
    printf("\n-=-=-=-=- Lista de Viaturas -=-=-=-=-\n");

    int i = 1;
    while (v != NULL) 
    {
        printf("\nViatura %d:\n", i++);
        exibirViatura(v);
        v = v->prox;
    }
}

// INICIO BUSCAR POR PLACA
void buscarPorPlaca(Viatura* v) 
{
    char placaBusca[TAM];
    int encontrado = 0;

    printf("Digite a placa a ser encontrada: ");
    scanf("%49[^\n]", placaBusca);
    limparBuffer();
    limparTela();

    while(v != NULL)
    {
        if(strcmp(v->placa, placaBusca) == 0)
        {
            exibirViatura(v);
            encontrado = 1;
        }
        v = v->prox;
    }

    if (!encontrado)
        printf("Nenhuma viatura com essa placa foi encontrada.\n");
}

// INICIO BUSCA POR TURNO
void buscarPorTurno(Viatura *v) 
{
    int turnoBusca;
    int encontrado = 0;

    printf("Digite o turno (0, 1 ou 2): ");
    scanf("%d", &turnoBusca);
    limparBuffer();
    limparTela();

    while(v != NULL)
    {
        if(v->turno == turnoBusca)
        {
            exibirViatura(v);
            encontrado = 1;
        }
        v = v->prox;
    }

    if (!encontrado)
        printf("Nenhuma viatura com esse turno foi encontrada.\n");
}

// INICIO BUSCAR POR POLICIAL
void buscarPorPolicial(Viatura *v) 
{
    char policialBusca[TAM];
    int encontrado = 0;

    printf("Digite o nome do policial: ");
    scanf("%49[^\n]", policialBusca);
    limparBuffer();
    limparTela();

    while(v != NULL)
    {
        if(strstr(v->nomePolicial, policialBusca))
        {
            exibirViatura(v);
            encontrado = 1;
        }
        v = v->prox;
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

// INICIO ALTERAR VIATURA (mudar os dados)
void alterarViatura(Viatura *v) 
{
    char placa[TAM];
    printf("Digite a placa da viatura que deseja alterar: ");
    scanf("%49[^\n]", placa);
    limparBuffer();

    while (v != NULL) 
    {
        if (strcmp(v->placa, placa) == 0) {
            printf("\n-=-=- Alterando dados da viatura %s -=-=-\n", placa);

            printf("Qual o tipo de veiculo (Ex.: Carro, Moto..): ");
            scanf("%49[^\n]", v->tipoVeiculo);
            limparBuffer();

            printf("Renavam: "); // Número de Registro do DETRAN
            scanf("%49[^\n]", v->renavam);
            limparBuffer();

            printf("Cor: ");
            scanf("%49[^\n]", v->cor);
            limparBuffer();

            printf("Quilometragem: ");
            scanf("%d", &v->quilometragem);
            limparBuffer();

            printf("Quilometragem da última revisão: ");
            scanf("%d", &v->quilometragem);
            limparBuffer();

            printf("Status (Ex.: ativo, manutenção..): ");
            scanf("%49[^\n]", v->status);
            limparBuffer();

            printf("Categoria (0 = paisana, 1 = oficial, 2 = base móvel): ");
            scanf("%d", &v->categoria);
            limparBuffer();

            printf("Turno (0 = manhã, 1 = tarde, 2 = noite): ");
            scanf("%d", &v->turno);
            limparBuffer();

            printf("Policial responsável: ");
            scanf("%49[^\n]", v->nomePolicial);
            limparBuffer();

            printf("Permissão (0 = comando, 1 = operador, 2 = manutenção, 3 = TI): ");
            scanf("%d", &v->permissao);
            limparBuffer();

            printf("Data de vencimento do IPVA:\n");
            lerData(&v->vencimentoIPVA);

            printf("Data de vencimento do Licenciamento:\n");
            lerData(&v->vencimentoLicenciamento);

            printf("Data de vencimento do Seguro:\n");
            lerData(&v->vencimentoSeguro);
            return;
        }
        v = v->prox;
    }
    printf("Viatura com placa %s não encontrada.\n", placa);
}

// INICIO EXCLUIR VIATURA
Viatura* excluirViatura(Viatura *v)
{
    char placa[TAM];
    printf("Digite a placa da viatura a ser excluída: ");
    scanf("%49[^\n]", placa);
    limparBuffer();

    Viatura *anterior = NULL, *atual = v;

    while (atual != NULL) 
    {
        if (strcmp(atual->placa, placa) == 0) 
        {
            if (anterior == NULL) 
                v = atual->prox;
            else 
                anterior->prox = atual->prox;

            free(atual);
            limparTela();
            printf("Viatura excluída com sucesso.\n");

            return v;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Viatura não encontrada.\n");

    return v;
}

// INICIO LER DATA CORRIGIR PARA LIMPAR O BUFFER CORRETAMENTE
void lerData(Data* d) 
{
    int dia = 31;

    printf("Ano (acima de 1900): ");
    while (scanf("%d", &d->ano) != 1 || d->ano < 1900)
    {
        printf("ERRO: Informe um ano válido!\nAno (acima de 1900): ");
        limparBuffer();
    }
    
    printf("Mês (1-12): ");
    while (scanf("%d", &d->mes) != 1 || d->mes < 1 || d->mes > 12)
    {
        printf("ERRO: Informe um mês válido!\nMês (1-12): ");
        limparBuffer();
    }

    if (d->mes == 4 || d->mes == 6 || d->mes == 9 || d->mes == 11)
    {
        dia = 30;

    } else if( d->mes == 2)
    {
        if(!((d->ano % 4 == 0 && d->ano % 100 != 0) || d->ano % 400 == 0))
            dia = 28;
        else 
            dia = 29;
    }
    
    printf("Dia (1-%d): ", dia);
    while (scanf("%d", &d->dia) != 1 || d->dia < 1 || d->dia > dia)
    {
        printf("ERRO: Informe um dia válido!\nDia (1-%d): ", dia);
        limparBuffer();
    }

    limparBuffer();
}

// INICIO EXIBIR DATA
void exibirData(Data d) 
{
    printf("%02d/%02d/%04d\n", d.dia, d.mes, d.ano);
}

// INICIO EXIBIR VIATURA
void exibirViatura(Viatura* v) 
{
    printf("Tipo: %s\n", v->tipoVeiculo);
    printf("Placa: %s\n", v->placa);
    printf("Renavam: %s\n", v->renavam);
    printf("Cor: %s\n", v->cor);
    printf("Quilometragem: %d km\n", v->quilometragem);
    printf("Status: %s\n", v->status);

    printf("Categoria: ");
    switch (v->categoria) 
    {
        case 0: printf("Paisana\n"); break;
        case 1: printf("Oficial\n"); break;
        case 2: printf("Base móvel\n"); break;
        default: printf("Desconhecida\n");
    }

    printf("Turno: %d\n", v->turno);
    switch (v->turno) 
    {
        case 0: printf("manhã\n"); break;
        case 1: printf("tarde\n"); break;
        case 2: printf("noite\n"); break;
        default: printf("Desconhecido\n");
    }

    printf("Policial: %s\n", v->nomePolicial);
    
    printf("Permissão: ");
    switch (v->permissao) 
    {
        case 0: printf("Comando\n"); break;
        case 1: printf("Operador\n"); break;
        case 2: printf("Manutenção\n"); break;
        case 3: printf("TI\n"); break;
        default: printf("Desconhecida\n");
    }

    printf("Vencimento IPVA: "); exibirData(v->vencimentoIPVA); 
    if(dataVencida(v->vencimentoIPVA))
        printf("ALERTA: IPVA VENCIDO!\n");
    else
        printf("\n");

    printf("Vencimento Licenciamento: "); exibirData(v->vencimentoLicenciamento);
    if(dataVencida(v->vencimentoLicenciamento))
        printf("ALERTA: LICENCIAMENTO VENCIDO!\n");
    else
        printf("\n");

    printf("Vencimento Seguro: "); exibirData(v->vencimentoSeguro); 
    if(dataVencida(v->vencimentoSeguro))
        printf("ALERTA: SEGURO VENCIDO!\n");
    else
        printf("\n");

    // Aviso de manutenção preventiva básica
    if ((v->quilometragem - v->ultimaRevisaoKM) >= 10000)
        printf("ALERTA: Revisão preventiva recomendada.\n");
}

// INICIO DATA VENCIDA
int dataVencida(Data d) 
{
    time_t t = time(NULL);
    struct tm* hoje = localtime(&t);

    if (d.ano < hoje->tm_year + 1900) 
        return 1;

    if (d.ano == hoje->tm_year + 1900 && d.mes < hoje->tm_mon + 1) 
        return 1;

    if (d.ano == hoje->tm_year + 1900 && d.mes == hoje->tm_mon + 1 && d.dia < hoje->tm_mday)
        return 1;

    return 0;
}