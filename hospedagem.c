#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hospedagem.h"

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
                printf(" %s\n", campos);
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