#ifndef POLIFLEET_H
#define POLIFLEET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM 50

//-=-=-=-=-=-=- DEFINIÇÕES DAS ESTRUTURAS -=-=-=-=-=-=-

typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct RegistroTurno {
    int turno;
    char nomePolicial[TAM];
    struct RegistroTurno* prox;
} RegistroTurno;

typedef struct Usuario {
    char nome[TAM];
    char senha[TAM];
    int permissao; // 0=comando, 1=operador, 2=manutenção, 3=TI
} Usuario;

typedef struct Viatura {
    char tipoVeiculo[TAM];
    char placa[TAM];
    char renavam[TAM]; // Registro nacional do Detran
    char cor[TAM];
    int quilometragem;
    int ultimaRevisaoKM;
    char status[TAM];
    int categoria; // paisana, oficial, base móvel
    int turno;
    char nomePolicial[TAM];
    int permissao; // comando, t.i, manutenção..
    Data vencimentoIPVA;
    Data vencimentoLicenciamento;
    Data vencimentoSeguro;
    char identificador[TAM]; // Para as viaturas à paisana
    float litrosAbastecidos;
    float kmUltimoAbastecimento;
    float consumoMedio;
    RegistroTurno* historico;
    struct Viatura* prox;
} Viatura;


//-=-=-=-=-=-=-=- PROTÓTIPOS DAS FUNÇÕES -=-=-=-=-=-=-=-=-

void menu(Usuario user); // Menu Principal
void submenuBusca(); // Menu buscar por: placa, nome, turno
void submenuAlteracao(); // Alterar: dados completos ou troca de turno
void submenuAbastecimento(); // Menu abastecimento
Viatura* cadastrarViatura(Viatura* v, Usuario u); // Cadastra e adiciona a viatura em uma lista
void listarViaturas(Viatura* v, Usuario u); // Mostra todas as viaturas
void limparBuffer();
void buscarPorPlaca(Viatura* v, Usuario u); // Parte do menu BUSCAR
void buscarPorTurno(Viatura* v, Usuario u); // Parte do menu BUSCAR
void buscarPorPolicial(Viatura* v, Usuario u); // Parte do menu BUSCAR
void limparTela();
void alterarViatura(Viatura* v, Usuario u); // Altera todos os dados de uma viatura, exceto a placa.
Viatura* excluirViatura(Viatura* v, Usuario u); // Retira uma viatura da lista e libera o espaço
void lerData(Data* d); // Lê a data para os vencimentos
void exibirData(Data d); // Mostra a data no formato dd/mm/aaaa
void exibirViatura(Viatura* v, Usuario u); // Mostra somente uma viatura específica
int dataVencida(Data d); // Verificação da data atual com a informada no cadastro da viatura
void alterarViaturaBasica(Viatura* v, Usuario u); // Troca de efetivo
void registrarLog(const char* acao, const char* usuario); // Escreve o histórico de tudo em um arquivo
void criarUsuario(Usuario** usuarios, int* totalUsuarios); // Funçõao exclusiva do comando
Usuario login(Usuario** usuarios, int* totalUsuarios); // Valida o login
void liberarViaturas(Viatura* v); // Libera a lista de viaturas utilizando recursividade
void registrarAbastecimento(Viatura* v, Usuario u); // Altera somente os dados de abastecimento

#endif // POLIFLEET_H