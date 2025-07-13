#include "polifleet.h"

// INICIO MENU
void menu(Usuario user) 
{
    printf("\n-=-=-=- MENU POLIFLEET (%s) -=-=-=-\n", user.nome);
    if (user.permissao == 0) // Comando
    {
        printf("[ 1 ] Cadastrar Viatura\n");
        printf("[ 2 ] Listar Viaturas\n");
        printf("[ 3 ] Buscar Viatura\n");
        printf("[ 4 ] Alterar Dados da Viatura\n");
        printf("[ 5 ] Excluir Viatura\n");
        printf("[ 6 ] Criar Novo Usuário\n");
    } else if(user.permissao <= 1) // Operador
    {
        printf("[ 2 ] Listar Viaturas\n");
        printf("[ 3 ] Buscar Viatura\n");
        printf("[ 4 ] Alterar Dados da Viatura\n");
    } else { // T.I, manutenção
        printf("[ 1 ] Cadastrar Viatura\n");
        printf("[ 2 ] Listar Viaturas\n");
        printf("[ 3 ] Buscar Viatura\n");
        printf("[ 4 ] Alterar Dados da Viatura\n");
        printf("[ 5 ] Excluir Viatura\n");
    }
    printf("[ 7 ] Trocar de Usuário\n");
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

// SUBMENU ALTERACAO
void submenuAlteracao() 
{
    printf("\n-=-=-=- ALTERAÇÃO DE VIATURA -=-=-=-\n");
    printf("[ 1 ] Alterar todos os dados\n");
    printf("[ 2 ] Alterar dados básicos (Turno/Policial)\n");
    printf("[ 0 ] Voltar\n");
    printf("Escolha: ");
}

// INICIO CADASTRAR VIATURA 
// Cadastra e adiciona a viatura em uma lista.
Viatura* cadastrarViatura(Viatura* v, Usuario u) 
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

    // Inicializando o identificador. Por enqunato temos a placa como identificador único.
    strcpy(novaViatura->identificador, novaViatura->placa);

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

    // Controle de logs, escreve no nosso arquivo o que foi modificado e por quem foi feito
    char logMsg[100];
    sprintf(logMsg, "Cadastro da viatura placa %s", novaViatura->placa);
    registrarLog(logMsg, u.nome);

    limparTela();

    printf("\nViatura cadastrada com sucesso!\n\n");

    return v;
}

// INICIO LISTAR VIATURA
void listarViaturas(Viatura* v, Usuario u) 
{
    limparTela();
    if(v == NULL)
    {
        printf("Nenhuma viatura cadastrada no sistema!\n");
        return;
    }

    printf("\n-=-=-=-=- Lista de Viaturas -=-=-=-=-\n");

    int i = 1;
    while (v != NULL) 
    {
        printf("\nViatura %d:\n", i++);
        exibirViatura(v, u);
        v = v->prox;
    }
}

// INICIO BUSCAR POR PLACA
void buscarPorPlaca(Viatura* v, Usuario u) 
{
    limparTela();
    char placaBusca[TAM];
    int encontrado = 0;

    printf("Digite a placa a ser encontrada: ");
    scanf("%49[^\n]", placaBusca);
    limparBuffer();
    limparTela();

    while(v != NULL)
    {
        if(strcmp(v->placa, placaBusca) == 0) // compara as duas strings
        {
            exibirViatura(v, u);
            encontrado = 1;
        }
        v = v->prox;
    }

    if (!encontrado)
        printf("Nenhuma viatura com essa placa foi encontrada.\n");
}

// INICIO BUSCA POR TURNO
void buscarPorTurno(Viatura *v, Usuario u) 
{
    limparTela();
    int turnoBusca;
    int encontrado = 0;

    printf("Digite o turno (0, 1 ou 2): ");
    scanf("%d", &turnoBusca);
    limparBuffer();
    limparTela();

    while(v != NULL)
    {
        if(v->turno == turnoBusca) // compara os dois turnos (0 a 2)
        {
            exibirViatura(v, u);
            encontrado = 1;
        }
        v = v->prox;
    }

    if (!encontrado)
        printf("Nenhuma viatura com esse turno foi encontrada.\n");
}

// INICIO BUSCAR POR POLICIAL
void buscarPorPolicial(Viatura *v, Usuario u) 
{
    limparTela();
    char policialBusca[TAM];
    int encontrado = 0;

    printf("Digite o nome do policial: ");
    scanf("%49[^\n]", policialBusca);
    limparBuffer();
    limparTela();

    while(v != NULL)
    {
        if(strstr(v->nomePolicial, policialBusca)) // compara as duas strings
        {
            exibirViatura(v, u);
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

// INICIO ALTERAR VIATURA (mudar os dados completos)
void alterarViatura(Viatura *v, Usuario u) 
{
    char placa[TAM];
    printf("Digite a placa da viatura que deseja alterar: ");
    scanf("%49[^\n]", placa);
    limparBuffer();

    Viatura* temp = v;
    while (temp != NULL) 
    {
        if (strcmp(v->placa, placa) == 0)  // compara as duas strings
        {
            printf("\n-=-=- Alterando dados da viatura %s -=-=-\n", placa);

            printf("Qual o tipo de veiculo (Ex.: Carro, Moto..): ");
            scanf("%49[^\n]", temp->tipoVeiculo);
            limparBuffer();

            printf("Renavam: "); // Número de Registro do DETRAN
            scanf("%49[^\n]", temp->renavam);
            limparBuffer();

            printf("Cor: ");
            scanf("%49[^\n]", temp->cor);
            limparBuffer();

            printf("Quilometragem: ");
            scanf("%d", &temp->quilometragem);
            limparBuffer();

            printf("Quilometragem da última revisão: ");
            scanf("%d", &temp->ultimaRevisaoKM);
            limparBuffer();

            printf("Status (Ex.: ativo, manutenção..): ");
            scanf("%49[^\n]", temp->status);
            limparBuffer();

            printf("Categoria (0 = paisana, 1 = oficial, 2 = base móvel): ");
            scanf("%d", &temp->categoria);
            limparBuffer();

            printf("Turno (0 = manhã, 1 = tarde, 2 = noite): ");
            scanf("%d", &temp->turno);
            limparBuffer();

            printf("Policial responsável: ");
            scanf("%49[^\n]", temp->nomePolicial);
            limparBuffer();

            printf("Permissão (0 = comando, 1 = operador, 2 = manutenção, 3 = TI): ");
            scanf("%d", &temp->permissao);
            limparBuffer();

            printf("Data de vencimento do IPVA:\n");
            lerData(&temp->vencimentoIPVA);

            printf("Data de vencimento do Licenciamento:\n");
            lerData(&temp->vencimentoLicenciamento);

            printf("Data de vencimento do Seguro:\n");
            lerData(&temp->vencimentoSeguro);

            // Registro de logs, escreve no arquivo
            char logMsg[100];
            sprintf(logMsg, "Alteração completa da viatura placa %s", temp->placa);
            registrarLog(logMsg, u.nome);

            limparTela();
            
            printf("Dados da viatura alterados com sucesso!\n");

            return;
        }
        temp = temp->prox;
    }
    limparTela();
    printf("Viatura com placa %s não encontrada.\n", placa);
}

// INICIO EXCLUIR VIATURA
Viatura* excluirViatura(Viatura *v, Usuario u)
{
    char placa[TAM];
    printf("Digite a placa da viatura a ser excluída: ");
    scanf("%49[^\n]", placa);
    limparBuffer();

    Viatura *anterior = NULL, *atual = v;

    while (atual != NULL) 
    {
        if (strcmp(atual->placa, placa) == 0) // compara as duas strings
        {
            if (anterior == NULL) 
                v = atual->prox;
            else 
                anterior->prox = atual->prox;

            free(atual);
            limparTela();
            printf("Viatura excluída com sucesso.\n");

            char logMsg[100];
            sprintf(logMsg, "Exclusão da viatura placa %s", placa);
            registrarLog(logMsg, u.nome);

            return v;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Viatura não encontrada.\n");

    return v;
}

// INICIO LER DATA
void lerData(Data* d) 
{
    int dia = 31;

    printf("Ano (acima de 1900): ");
    while (scanf("%d", &d->ano) != 1 || d->ano < 1900) // Controle de erro para só entrar com inteiros
    {                                                  // acima de 1900.
        printf("ERRO: Informe um ano válido!\nAno (acima de 1900): ");
        limparBuffer();
    }

    limparBuffer();
    
    printf("Mês (1-12): ");
    while (scanf("%d", &d->mes) != 1 || d->mes < 1 || d->mes > 12) // Controle de erro para só entrar
    {                                                              // com inteiros entre 1 e 12.
        printf("ERRO: Informe um mês válido!\nMês (1-12): ");
        limparBuffer();
    }

    limparBuffer();

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
    while (scanf("%d", &d->dia) != 1 || d->dia < 1 || d->dia > dia) // Controle de erro para entrar
    {                                                               // com inteiros de 1 até 
        printf("ERRO: Informe um dia válido!\nDia (1-%d): ", dia);  // o dia especificado
        limparBuffer();
    }

    limparBuffer();
}

// INICIO EXIBIR DATA (dd/mm/aaaa)
void exibirData(Data d) 
{
    printf("%02d/%02d/%04d\n", d.dia, d.mes, d.ano); 
}

// INICIO EXIBIR VIATURA
void exibirViatura(Viatura* v, Usuario u) 
{
    if (v->categoria == 0 && u.permissao > 1) // Só podem ver as viaturas a paisana 
    {                                          // quem tiver permissão
        printf("Identificação: [RESTRITO - VIATURA PAISANA]\n");
        printf("Status: %s\n", v->status);
        printf("Responsável: %s\n", v->nomePolicial);
        return;
    }

    printf("Identificador: %s\n", v->identificador);
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

    printf("Vencimento Licenciamento: "); exibirData(v->vencimentoLicenciamento);
    if(dataVencida(v->vencimentoLicenciamento))
        printf("ALERTA: LICENCIAMENTO VENCIDO!\n");

    printf("Vencimento Seguro: "); exibirData(v->vencimentoSeguro); 
    if(dataVencida(v->vencimentoSeguro))
        printf("ALERTA: SEGURO VENCIDO!\n");

    // Aviso de manutenção preventiva básica
    // Necessária uma revisão a cada 10_000 km
    int manuntencaoPreventiva = (v->quilometragem - v->ultimaRevisaoKM);
    if (manuntencaoPreventiva >= 10000)
        printf("ALERTA: Revisão preventiva recomendada (%dkm desde a última).\n", manuntencaoPreventiva);
}

// INICIO DATA VENCIDA
int dataVencida(Data d) 
{
    time_t t = time(NULL);  // Tempo medido em segundos desde (01/01/1970).
    struct tm* hoje = localtime(&t); // Converte os segundos em dia, mes e ano atuais.
                                    // estrutura da biblioteca time.h

    if (d.ano < hoje->tm_year + 1900) // Só começa a contar os anos a partir de 1900, por isso +1900.
        return 1;

    if (d.ano == hoje->tm_year + 1900 && d.mes < hoje->tm_mon + 1) // Os meses vão de 1 a 11, então +1
        return 1;

    if (d.ano == hoje->tm_year + 1900 && d.mes == hoje->tm_mon + 1 && d.dia < hoje->tm_mday)
        return 1;

    return 0;
}

// INICIO ALTERAR DADOS BÁSICOS (Turno e Policial)
void alterarViaturaBasica(Viatura* v, Usuario u) 
{
    char tempIdentificador[TAM];
    printf("Digite o código identificador da viatura: ");
    scanf("%49s", tempIdentificador);
    limparBuffer();

    Viatura* temp = v;
    while (temp != NULL) {
        if (strcmp(temp->identificador, tempIdentificador) == 0) // compara as duas strings
        {
            printf("Novo nome do policial responsável: ");
            scanf("%49[^\n]", temp->nomePolicial);
            limparBuffer();

            printf("Novo turno (0=manhã, 1=tarde, 2=noite): ");
            scanf("%d", &temp->turno);
            limparBuffer();

            char logMsg[100];
            sprintf(logMsg, "Alteração básica da viatura %s", temp->identificador);
            registrarLog(logMsg, u.nome);

            limparTela();

            printf("Alterações básicas aplicadas com sucesso.\n");

            return;
        }

        temp = temp->prox;
    }
    printf("Viatura não encontrada.\n");
}

// INICIO CRIAR USUÁRIO
void criarUsuario(Usuario** usuarios, int* totalUsuarios) 
{
    *usuarios = realloc(*usuarios, (*totalUsuarios + 1) * sizeof(Usuario)); 

    if(!*usuarios)
    {
        printf("Erro ao alocar memória para novo usuário!\n");
        return;
    }


    printf("\n-=-=- CADASTRO DE NOVO USUÁRIO -=-=-\n");

    printf("Nome de usuário: ");
    scanf("%49s", (*usuarios)[*totalUsuarios].nome);
    limparBuffer();

    printf("Senha: ");
    scanf("%49s", (*usuarios)[*totalUsuarios].senha);
    limparBuffer();

    printf("Permissão (0=Comando, 1=Operador, 2=Manutenção, 3=TI): ");
    scanf("%d", &(*usuarios)[*totalUsuarios].permissao);
    limparBuffer();

    limparTela();
    printf("Usuário cadastrado com sucesso.\n");
    (*totalUsuarios)++;
}

// INICIO LOGIN
// Atualização: Caso somente o usuário estiver correto, mostra um aviso de senha incorreta
Usuario login(Usuario** usuarios, int* totalUsuarios) 
{
    char nome[TAM], senha[TAM];
    Usuario usuarioLogado = {"", "", -1};

    while(1)
    {
        printf("\n== LOGIN POLIFLEET ==\n");
        printf("Usuário: ");
        scanf("%49s", nome);
        limparBuffer();

        printf("Senha: ");
        scanf("%49s", senha);
        limparBuffer();

        for (int i = 0; i < *totalUsuarios; i++) 
        {
            limparTela();

            if (strcmp((*usuarios)[i].nome, nome) == 0) 
            {
                if(strcmp((*usuarios)[i].senha, senha) == 0)
                {
                    usuarioLogado = (*usuarios)[i];

                    printf("Login bem-sucedido como %s\n", usuarioLogado.nome);
                    registrarLog("Login", usuarioLogado.nome);

                    return usuarioLogado;
                } else {
                    printf("ACESSO NEGADO! Senha incorreta.\n");
                }
            } else {
                printf("FALHA NO LOGIN: Usuário não está cadastrado no sistema.\n");
            }
        }
    }
    limparTela();
}

// REGISTRO DE LOGS
void registrarLog(const char* acao, const char* usuario) 
{
    FILE* arq = fopen("log_acessos.txt", "a"); // "a" serve para acrescentar
    
    if (!arq) 
    {
        perror("Erro ao abrir arquivo de log");
        return;
    }

    time_t t = time(NULL); // tempo atual em segundos
    struct tm* tempo = localtime(&t); // pega o dia, mes e ano atual com base nos segundos.
                                    // estrutura da biblioteca time.h

    fprintf(arq, "%02d/%02d/%04d %02d:%02d - %s: %s\n",
        tempo->tm_mday, tempo->tm_mon + 1, tempo->tm_year + 1900,
        tempo->tm_hour, tempo->tm_min, usuario, acao);

    fclose(arq);
}