#include "cliente.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int quantidadeClientesCSV()
{
    char nomeArquivo[] = "Clientes.csv";
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


int lerClientesCSV( CLIENTE *lista )
{
    char nomeArquivo[] = "Clientes.csv";
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
                case CPF_CLI:
                    strcpy(lista[i].CPF, campos);
                    break;
                case NOME_CLI:
                    strcpy(lista[i].nome, campos);
                    break;
                case DATA_NASC_CLI:
                    StringToData(campos, &lista[i].dataNascimento);
                    break;
                case IDADE_CLI:
                    lista[i].idade = atoi(campos);
                    break;
                case ENDERECO_CLI:
                    strcpy(lista[i].endereco, campos);
                    break;
                case CIDADE_CLI:
                    strcpy(lista[i].cidade, campos);
                    break;
                case ESTADO_CLI:
                    strcpy(lista[i].estado, campos);
                    break;                                       
                default:
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


void exibirCliente(CLIENTE c)
{
    char data[14];
    printf("######################################\n");
    printf("CPF: %s\n", c.CPF);
    printf("------------------------------------- \n");        
    printf("Nome: %s\n", c.nome);
    printf("------------------------------------- \n");        
    DataToString(c.dataNascimento,data, false);
    printf("Data de Nascimento: %s\n",data);
    printf("------------------------------------- \n");        
    printf("Idade: %d\n", c.idade );
    printf("------------------------------------- \n");        
    printf("Endereço: %s\n", c.endereco);
    printf("------------------------------------- \n");        
    printf("Cidade/Estado: %s - %s\n", c.cidade, c.estado);
    printf("######################################\n");
}

CLIENTE buscarClientePorCPF(char *CPF, CLIENTE *l, int qtde)
{
    CLIENTE c;
    strcpy(c.CPF, "0");
    bool achou = false;
    int i = 0 ;
    while(i < qtde && !achou )     
    {
        printf("CPF: %s\n", l[i].CPF);
        if (strcmp(CPF, l[i].CPF) == 0 )
        {
            achou = true;
            c =  l[i];
        }
        else
            i++;
    }
    return c;    
}