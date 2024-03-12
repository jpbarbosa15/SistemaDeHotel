#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hospedagem.h"
#include "tempo.h"
#include "reserva.h"
#include "quarto.h"
#include "time.h"

int quantidadeHospedagensCSV()
{
    char nomeArquivo[] = "Hospedagens.csv";
    FILE *csv;
    char linha[1000];
    csv = fopen(nomeArquivo, "r");
    if (csv != NULL)
    {
        // lendo o cabeçalho do arquivo
        fscanf(csv, " %[^\n]s", linha);
        int contadorLinha = 0;
        while (fscanf(csv, " %[^\n]s", linha) != EOF)
        {
            contadorLinha++;
        }
        fclose(csv);
        return contadorLinha;
    }
    else
    {
        // arquivo não existe
        return 0;
    }
}

//-----------------------------------------------------------------------------

int lerHospedagensCSV(HOSPEDAGEM *lista)
{
    char nomeArquivo[] = "Hospedagens.csv";
    FILE *csv;
    char linha[1000];
    char *campos;
    const char s[2] = ";";
    int contadorLinha = 0;
    csv = fopen(nomeArquivo, "r");
    if (csv != NULL)
    {
        // fim dos registros, reabrindo para ler os dados
        fseek(csv, 0, SEEK_SET);
        // lendo o cabeçalho do arquivo
        fscanf(csv, " %[^\n]s", linha);
        // alocando memoria para os registros lidos

        int i = 0;
        while (fscanf(csv, " %[^\n]s", linha) != EOF)
        {
            // separando os dados de uma linha
            campos = strtok(linha, s);
            int campoAtual = 0;
            while (campos != NULL)
            {
                
                switch (campoAtual)
                {
                case IDRESERVA_HOSPEDAGEM:
                    lista[i].id = atoi(campos);
                case CPF_HOSPEDAGEM:
                    strcpy(lista[i].CPF, campos);
                    break;
                case CHECKIN_HOSPEDAGEM:
                    StringToData(campos, &lista[i].checkin);
                    break;
                case CHECKOUT_HOSPEDAGEM:
                    StringToData(campos, &lista[i].checkout);
          //-----------------------------------------------------------------------------          break;
                case STATUS_HOSPEDAGEM:
                    strcpy(lista[i].status, campos);
                    break;
                case PRECOTOTAL_HOSPEDAGEM:
                    lista[i].precoTotal = atof(campos);
                    break;

                default : 
                    break;
                }
                campos = strtok(NULL, s);
                campoAtual++;
            }
            i++;
            // dados do setor;
        }
        contadorLinha = i;
        return contadorLinha;
    }
    else
    {
        printf("Erro - Arquivo %s não encontrado\n", nomeArquivo);
        return -1;
    }
}

//-----------------------------------------------------------------------------

void exibirHospedagem(HOSPEDAGEM h)
{
   char temp[12];
   printf("##################################### \n");
   printf("ID : %d\n",h.id);
   printf("------------------------------------- \n");
   printf("CPF: %s\n", h.CPF);
   printf("------------------------------------- \n");
   DataToString(h.checkin, temp, false);
   printf("Check in: %s\n", temp);   
   printf("------------------------------------- \n");
   DataToString(h.checkout, temp, false);
   printf("Check out: %s\n", temp);   
   printf("------------------------------------- \n");
   printf("Status: %s\n", h.status);   
   printf("------------------------------------- \n");
   printf("Valor total: R$%.2f\n", h.precoTotal);   
   printf("------------------------------------- \n");
   printf("##################################### \n");
}


void GravarHospedagemCSV(HOSPEDAGEM h)
{
    FILE *csv;
    char nomeArquivo[] = "Hospedagens.csv";
    csv = fopen(nomeArquivo, "r+w");
    if (csv == NULL)
    {
        // arquivo não existe, será criado
        csv = fopen(nomeArquivo, "a");
        fprintf(csv,"idReserva;CPF;Checkin;Checkout;Status;Total\n");
        fflush(csv);
    }else{
        fseek(csv, 0, SEEK_END);
    }
    //Arquivo ja existe
    char temp[12];
    fprintf(csv, "%d;%s;", h.id, h.CPF);
    DataToString(h.checkin, temp, false);
    fprintf(csv, "%s;", temp);
    DataToString(h.checkout, temp, false);
    fprintf(csv, "%s;%s;%.2f\n", temp, h.status, h.precoTotal);
    fclose(csv);
    
    
}

void checkinHospedagem(int id)
{
    bool verificacao;
    RESERVA r;
    HOSPEDAGEM h;

    verificacao = BuscarReservaID(id, &r);
    exibirReserva(r);
    if (verificacao == true)
    {
        h.id = r.id;
        strcpy(h.CPF, r.CPF);
        h.checkin = r.checkin;
        h.checkout = r.checkout;
        strcpy(h.status, "Ativa");
        h.precoTotal = 0.0;
        AlterarStatusQuarto(r.idQuarto, false);
        GravarHospedagemCSV(h);
        
    } else {
        printf("Reserva não encontrada\n");
    }
    
}


void checkoutHospedagemID(int id)
{
    
    int verificacao = 0;
    HOSPEDAGEM *lista;
    int qtdHospedagens = quantidadeHospedagensCSV();
    lista = (HOSPEDAGEM *)malloc(qtdHospedagens * sizeof(HOSPEDAGEM));
    lerHospedagensCSV(lista);
    remove("Hospedagens.csv");
    for (int i = 0; i < qtdHospedagens; i++)
    {
        if (lista[i].id == id)
        {
            //Busca a reserva associada a Hospedagem por ID
            RESERVA r;
            BuscarReservaID(id,&r);
            
            //Busca o quarto associado com a reserva
            QUARTO q = buscarQuartoID(r.idQuarto);
            exibirQuarto(q);
            //Calcula o valor total da hospedagem
            int dias = diferencaDiasDatas(lista[i].checkin,lista[i].checkout);
            float valor = dias * q.valorDiaria;
            
            //Atualiza o valor da hospedagem
            lista[i].precoTotal = valor;
            
            //Atualiza o status da hospedagem
            strcpy(lista[i].status, "Finalizada");
            GravarHospedagemCSV(lista[i]);
            verificacao = 1;
            
        } else {
            GravarHospedagemCSV(lista[i]);
        }
    }
    free(lista);
    if (verificacao == 1)
    {
        printf("\n");
        printf("Checkout realizado com sucesso\n");
        printf("\n");
    } else {
        printf("\n");
        printf("Hospedagem não encontrada\n");
        printf("\n");
    }
    
}



void checkoutHospedagemIDQuarto(int idQuarto){
    int verificacao = 0;
    int codigoReserva;
    RESERVA *lista;
    // Busca uma lista das reservas no arquivos reservas.csv
    int qtdReservas = quantidadeReservasCSV();
    lista = (RESERVA *)malloc(qtdReservas * sizeof(RESERVA));
    lerReservasCSV(lista);
    
    //Verifica se o quarto esta associado a alguma reserva e se estiver armazena o id da reserva
    for (int i = 0; i < qtdReservas; i++)
    {
        if (lista[i].idQuarto == idQuarto)
        {
            codigoReserva = lista[i].id;
            verificacao = 1;            
        }
    }
    free(lista);

    if (verificacao == 1 )
    {   
        //Cria a lista com todas as hospedagens e remove o arquivo hospedagens.csv 
        //Altera a hospedagem que vai ser cancelada
        //Salva todas as hospedagens no arquivo de novo
        HOSPEDAGEM *listaHospedagem;
        int qtdHospedagens = quantidadeHospedagensCSV();
        listaHospedagem = (HOSPEDAGEM *)malloc(qtdHospedagens * sizeof(HOSPEDAGEM));
        lerHospedagensCSV(listaHospedagem);
        remove("Hospedagens.csv");

        //Verifica a lista e altera a hospedagem que vai ser cancelada
        for (int i = 0; i < qtdHospedagens; i++)
        {
            if (listaHospedagem[i].id == codigoReserva)
            {
                //calcula o valor total da hospedagem
                QUARTO q = buscarQuartoID(idQuarto);
                int dias = diferencaDiasDatas(listaHospedagem[i].checkin,listaHospedagem[i].checkout);
                float valor = dias * q.valorDiaria;
                //altera o valor da hospedagem 
                listaHospedagem[i].precoTotal = valor;
                //altera o status da hospedagem
                strcpy(listaHospedagem[i].status, "Finalizada");
                //salva a hospedagem no arquivo
                GravarHospedagemCSV(listaHospedagem[i]);
                
                printf("\n");
                printf("Hospedagem Finalizada com sucesso\n");
                printf("\n");
                
            } else {
                GravarHospedagemCSV(listaHospedagem[i]);
            }
        }
        free(listaHospedagem);

    }else{
        printf("\n");
        printf("Hospedagem não encontrada\n");
        printf("\n");
    }
    

}


void ListarHospedagensCliente(char *CPF)
{
    int contador = 0;
    HOSPEDAGEM *lista;
    int qtdHospedagens = quantidadeHospedagensCSV();
    lista = (HOSPEDAGEM *)malloc(qtdHospedagens * sizeof(HOSPEDAGEM));
    lerHospedagensCSV(lista);
    for (int i = 0; i < qtdHospedagens; i++)
    {
        if (strcmp(lista[i].CPF, CPF) == 0)
        {
            char temp[12];
            printf("##################################### \n");
            printf("ID : %d\n",lista[i].id);
            DataToString(lista[i].checkin, temp, false);
            printf("Check in: %s\n", temp);   
            printf("------------------------------------- \n");
            DataToString(lista[i].checkout, temp, false);
            printf("Check out: %s\n", temp);   
            printf("------------------------------------- \n");
            printf("Valor total: R$%.2f\n", lista[i].precoTotal);
            contador++;   
        }
    }
    free(lista);
    if(contador == 0){
        printf("\n");
        printf("Nenhuma hospedagem encontrada\n");
        printf("\n");
    }
}
