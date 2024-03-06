#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quarto.h"
#include "apresentacao.h"
#include "tempo.h"
#include "reserva.h"
#include "hospedagem.h"
#include "cliente.h"


int main(int argc, char const *argv[])
{
    int opcao = 0;
    do
    {
        opcao = MenuPrincipal();
        switch (opcao)
        {
        case 1:
            menuReserva();
            break;
        case 2:
            menuClientes();
            break;
        case 3:
            // menuHospedagem();
            break;
        case 4:
            menuQuartos();
            break;
        case 9:
            printf("Saindo do Sistema\n");
            break;
        default:
            printf("\n");
            printf("Opção inválida!\n");
            printf("\n");
            break;
        }
    } while (opcao != 9);
    return 0;
}


