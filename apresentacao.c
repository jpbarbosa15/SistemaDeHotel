#include <stdio.h>
#include <stdlib.h>
#include "apresentacao.h"
#include "quarto.h"
#include "cliente.h"
#include "tempo.h"
#include "reserva.h"
#include "hospedagem.h"

const int TAM_SEPARADOR = 40;

void separador()
{
    for (int i = 0 ; i< TAM_SEPARADOR; i++ )
        printf("#");
    printf("\n");
}


int MenuPrincipal()
{
    int opcao;
    // system("clear"); <- opcao caso Linux 
    // system("cls"); // <- opcao caso Windows
    separador();
    printf("1. Reservas\n2. Clientes\n3. Hospedagem\n4. Quartos\n9. Sair\n");
    separador();
    printf("\nOpção -> ");
    scanf("%d", &opcao);
    return opcao;
}

void menuQuartos(){
    system("clear");
    int opcao = 0;
    printf("1. Novo Quarto\n2. Alterar Quarto\n3. Deletar Quarto\n9. Sair\n");
    separador();
    printf("\nOpção -> ");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        system("clear");
        QUARTO q;
        lerQuarto(&q);
        gravarQuartoCSV(q);
        printf("\n");
        printf("Quarto gravado com sucesso\n");
        break;
    
    case 2:
        system("clear");
        int id;
        printf("Digite o id do quarto para alterar: ");
        scanf("%d", &id);
        AlterarQuarto(id);
        break;

    case 3:
        system("clear");
        int idDel;
        printf("Digite o id do quarto para deletar: ");
        scanf("%d", &idDel);
        deletarQuarto(idDel);
        break;
    case 9:
        break;        
    default:
        break;
    }
}


void menuClientes(){
    system("clear");
    int opcao = 0;
    printf("1. Novo Cliente\n2. Alterar Cliente\n3. Deletar Cliente\n9. Sair\n");
    separador();
    printf("\nOpção -> ");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        system("clear");
        CLIENTE c;
        lerCliente(&c);
        gravarClienteCSV(c);
        printf("\n");
        printf("Cliente gravado com sucesso\n");
        break;
    
    case 2:
        system("clear");
        char cpf[16];
        printf("Digite o CPF do cliente para alterar: ");
        scanf("%s", cpf);
        AlterarCliente(cpf);
        printf("\n");
        printf("Cliente alterado com sucesso\n");
        printf("\n");
        break;

    case 3:
        system("clear");
        char cpfDel[16];
        printf("Digite o CPF do cliente para deletar: ");
        scanf("%s", cpfDel);
        deletarCliente(cpfDel);
        printf("\n");
        printf("Cliente deletado com sucesso\n");
        printf("\n");
        break;
    case 9:
        break;        
    default:
        break;
    }
   
}



void menuReserva(){
        system("clear");
        int opcao = 0;
        printf("1. Quartos Disponiveis Para Reserva\n2. Reservar Quarto\n3. Cancelar Reserva Por Id\n4. Cancelar Reserva Por CPF e Checkin\n5. Buscar Reserva\n9. Sair\n");
        separador();
        printf("\nOpção -> ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            system("clear");
            DATA entrada, saida;
            printf("Digite a data de entrada (dd/mm/aaaa): ");
            scanf("%d/%d/%d", &entrada.dia, &entrada.mes, &entrada.ano);
            printf("Digite a data de saida (dd/mm/aaaa): ");
            scanf("%d/%d/%d", &saida.dia, &saida.mes, &saida.ano);
            listarQuartosDisponiveisComBaseNaData(entrada, saida);
            break;
        case 2:
            system("clear");
            RESERVA r;
            char cpf[16], tipoquarto[10], checkinchar[50], checkoutchar[50];
            DATA checkin, checkout;
            bool verificacao;
            printf("Digite o CPF do cliente: ");
            scanf("%s", cpf);
            printf("Digite o tipo do quarto: ");
            scanf("%s", tipoquarto);
            printf("Digite a data de entrada (dd/mm/aaaa): ");
            scanf("%s", checkinchar);
            printf("Digite a data de saida (dd/mm/aaaa): ");
            scanf("%s", checkoutchar);
            StringToData(checkinchar, &checkin);
            StringToData(checkoutchar, &checkout);
            verificacao = reservarQuarto(cpf, tipoquarto, checkin, checkout, &r);
            if (verificacao == true){
                gravarReservaCSV(r);
            }
            
            break;
        case 3:
            system("clear");
            int id;
            printf("Digite o id da reserva para cancelar: ");
            scanf("%d", &id);
            cancelarReservaPorID(id);
            break;
        case 4:
            system("clear");
            char cpfDel[16], checkincharDel[50];
            DATA checkinDel;
            printf("Digite o CPF do cliente para cancelar a reserva: ");
            scanf("%s", cpfDel);
            printf("Digite a data de entrada (dd/mm/aaaa): ");
            scanf("%s", checkincharDel);
            StringToData(checkincharDel, &checkinDel);
            cancelarReservaPorCPFeDAta(cpfDel, checkinDel);
            break;
        case 5:
            system("clear");
            char cpfBusca[16];
            printf("Digite o CPF do cliente para buscar a reserva: ");
            scanf("%s", cpfBusca);
            ListarReservaCliente(cpfBusca);
            break;
        case 9:
            break;        
        default:
            break;
        }
    }


void menuHospedagem(){
    system("clear");
    int opcao = 0;
    printf("1. Checkin\n2. Checkout\n3. Buscar Hospedagens\n9. Sair\n");
    separador();
    printf("\nOpção -> ");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        system("clear");
        int id;
        printf("Digite o id da reserva para fazer o checkin: ");
        scanf("%d", &id);
        checkinHospedagem(id);
        break;
    case 2:
        
        break;
    case 3:
        
        break;
    case 9:
        break;        
    default:
        break;
    }
}