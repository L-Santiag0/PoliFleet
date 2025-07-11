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
    RegistroTurno* historico;
    struct Viatura* prox;
} Viatura;


//-=-=-=-=-=-=-=- PROTÓTIPOS DAS FUNÇÕES -=-=-=-=-=-=-=-=-

void menu(Usuario user);
void submenuBusca();
void submenuAlteracao();
Viatura* cadastrarViatura(Viatura* v, Usuario u);
void listarViaturas(Viatura* v, Usuario u);
void limparBuffer();
void buscarPorPlaca(Viatura* v, Usuario u);
void buscarPorTurno(Viatura* v, Usuario u);
void buscarPorPolicial(Viatura* v, Usuario u);
void limparTela();
void alterarViatura(Viatura* v, Usuario u);
Viatura* excluirViatura(Viatura* v, Usuario u);
void lerData(Data* d);
void exibirData(Data d);
void exibirViatura(Viatura* v, Usuario u);
int dataVencida(Data d);
void alterarViaturaBasica(Viatura* v, Usuario u);
void registrarLog(const char* acao, const char* usuario);
void criarUsuario(Usuario** usuarios, int* totalUsuarios);
Usuario login(Usuario** usuarios, int* totalUsuarios);

#endif // POLIFLEET_H