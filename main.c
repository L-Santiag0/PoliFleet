#include "polifleet.h"

int main(void) 
{
    Usuario* usuarios = malloc(sizeof(Usuario));
    Usuario user;
    int opcaoSubMenus, trocarUsuario, totalUsuarios = 1, opcao = 1;
    Viatura* viaturas = NULL;

    //Vetor de ponteiros para as funções de buscar viaturas
    void (*ptr_FuncaoBusca[])(Viatura*, Usuario) = {buscarPorPlaca, buscarPorTurno, buscarPorPolicial};

    //Vetor de ponteiros para as funções de alterar dados das viaturas
    void (*ptr_FuncaoAlterar[])(Viatura*, Usuario) = {alterarViatura, alterarViaturaBasica};

    //Vetor de ponteiros para as funções de usuarios
    void (*ptr_FuncaoUsuario[])(Usuario**, int*) = {criarUsuario, listarUsuarios, excluirUsuario};
    
    // Criação do usuário administrador padrão
    strcpy(usuarios[0].nome, "admin");
    strcpy(usuarios[0].senha, "0000");
    usuarios[0].permissao = 0;

    // Laço principal do programa (controla trocas de usuarios)
    while (opcao != 0) 
    {
        user = login(&usuarios, &totalUsuarios);
        opcao = -1;
        trocarUsuario = 0;

        // Laço do menu de opções
        do {
            menu(user);
            if (scanf("%d", &opcao) != 1) 
            {
                printf("Entrada invalida. Digite um numero!\n");
                limparBuffer();
                opcao = -1; // Reseta a opção
                continue;
            }
            limparBuffer();

            switch (opcao) {
            case 1:
                if (user.permissao != 1)
                    viaturas = cadastrarViatura(viaturas, user);
                break;
            case 2:
                listarViaturas(viaturas, user);
                break;
            case 3:
                limparTela();
                submenuBusca();

                while (scanf("%d", &opcaoSubMenus) !=1 || opcaoSubMenus < 0 || opcaoSubMenus > 3)
                {
                    limparTela();
                    printf("Valor Invalido! Tente novamente:\n");
                    submenuBusca();
                    limparBuffer();
                }

                limparBuffer();
                if (opcaoSubMenus != 0)
                    ptr_FuncaoBusca[--opcaoSubMenus](viaturas, user);
                
                break;
            case 4:
                if (user.permissao != 1) 
                {
                    submenuAlteracao();

                    while (scanf("%d", &opcaoSubMenus) != 1 || opcaoSubMenus < 0 || opcaoSubMenus > 2)
                    {
                        limparTela();
                        printf("Valor Invalido! Tente novamente:\n");
                        submenuAlteracao();
                        limparBuffer(); 
                    }
               
                    limparBuffer();

                    if (opcaoSubMenus != 0)
                        ptr_FuncaoAlterar[--opcaoSubMenus](viaturas, user);   
                    
                } else {
                     ptr_FuncaoAlterar[1](viaturas, user); // Operador só tem permissão para 
                }                                          // alterar dados básicos
                break;
            case 5:
                if (user.permissao != 1)
                    viaturas = excluirViatura(viaturas, user);
                break;
            case 6:
                if (user.permissao == 0)
                {
                    limparTela();
                    submenuUsuarios();

                while (scanf("%d", &opcaoSubMenus) !=1 || opcaoSubMenus < 0 || opcaoSubMenus > 3)
                {
                    limparTela();
                    printf("Valor Invalido! Tente novamente:\n");
                    submenuUsuarios();
                    limparBuffer();
                }
                limparTela();
                limparBuffer();

                if (opcaoSubMenus != 0)
                    ptr_FuncaoUsuario[--opcaoSubMenus](&usuarios, &totalUsuarios);
                }

                break;
            case 7:
                registrarAbastecimento(viaturas, user);
                break;
            case 8:
                limparTela();

                printf("Trocando usuario...\n");

                registrarLog("Logout", user.nome);
                trocarUsuario = 1;

                break;
            case 0:
                break; // Sai do switch
            default:
                printf("Opcao invalida!\n");
            }
        } while (opcao != 0 && trocarUsuario == 0);
    }

    // Liberação de memória antes de encerrar
    printf("Encerrando o programa...\n");
    
    liberarViaturas(viaturas);
    free(usuarios);

    return 0;
}