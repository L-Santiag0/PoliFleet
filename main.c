#include "polifleet.h"

int main(void) 
{
    Usuario* usuarios = malloc(sizeof(Usuario));
    int totalUsuarios = 1;
    Viatura* viaturas = NULL;



    // Criação do usuário administrador padrão
    strcpy(usuarios[0].nome, "admin");
    strcpy(usuarios[0].senha, "0000");
    usuarios[0].permissao = 0;

    // Laço principal do programa (controla trocas de usuarios)
    while (1) 
    {
        Usuario user = login(&usuarios, &totalUsuarios);
        int opcao = -1;
        int trocarUsuario = 0;

        // Laço do menu de opções
        do {
            menu(user);
            if (scanf("%d", &opcao) != 1) 
            {
                printf("Entrada inválida. Digite um número!\n");
                limparBuffer();
                opcao = -1; // Reseta a opção
                continue;
            }
            limparBuffer();

            switch (opcao) {
            case 1:
                if (user.permissao == 0 || user.permissao == 2)
                    viaturas = cadastrarViatura(viaturas, user);
                else
                    printf("Sem permissão.\n");
                break;
            case 2:
                listarViaturas(viaturas, user);
                break;
            case 3:
                submenuBusca();

                int opBusca;
                scanf("%d", &opBusca);
                limparBuffer();

                switch (opBusca) {
                case 1: buscarPorPlaca(viaturas, user); break;
                case 2: buscarPorTurno(viaturas, user); break;
                case 3: buscarPorPolicial(viaturas, user); break;
                }
                break;
            case 4:
                if (user.permissao == 0 || user.permissao == 2) 
                {
                    submenuAlteracao();

                    int opAlterar;
                    scanf("%d", &opAlterar);
                    limparBuffer();
                    
                    switch(opAlterar) {
                        case 1: alterarViatura(viaturas, user); break;
                        case 2: alterarViaturaBasica(viaturas, user); break;
                    }
                } else {
                     printf("Sem permissão.\n");
                }
                break;
            case 5:
                if (user.permissao == 0 || user.permissao == 2)
                    viaturas = excluirViatura(viaturas, user);
                else
                    printf("Sem permissão.\n");
                break;
            case 6:
                if (user.permissao == 0)
                    criarUsuario(&usuarios, &totalUsuarios);
                else
                    printf("Somente comando pode criar usuários.\n");
                break;
            case 7:
                limparTela();
                printf("Trocando usuário...\n");
                registrarLog("Logout", user.nome);
                trocarUsuario = 1;
                break;
            case 0:
                break; // Sai do switch
            default:
                printf("Opção inválida!\n");
            }
        } while (opcao != 0 && trocarUsuario == 0);

        // Se a opção foi 0, encerra o programa
        if (opcao == 0) {
            break; 
        }
    }

    // Liberação de memória antes de encerrar
    printf("Encerrando o programa...\n");
    while (viaturas != NULL) {
        Viatura* temp = viaturas;
        viaturas = viaturas->prox;
        free(temp);
    }

    free(usuarios);

    return 0;
}