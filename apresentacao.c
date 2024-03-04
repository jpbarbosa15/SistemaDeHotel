#include <stdio.h>
#include <stdlib.h>
#include "apresentacao.h"
#include "quarto.h"

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
