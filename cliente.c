#include "cliente.h"
#include "tempo.h"

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


void lerCliente(CLIENTE *c)
{
    char data[14];
    printf("Digite o CPF: ");
    scanf("%s", c->CPF);
    printf("Digite o Nome: ");
    scanf(" %[^\n]s", c->nome);
    printf("Digite a Data de Nascimento (dd/mm/aaaa): ");
    scanf(" %[^\n]s", data);
    printf("Digite a Idade: ");
    scanf("%d", &c->idade);
    printf("Digite o Endereço: ");
    scanf(" %[^\n]s", c->endereco);
    printf("Digite a Cidade: ");
    scanf(" %[^\n]s", c->cidade);
    printf("Digite o Estado: ");
    scanf(" %[^\n]s", c->estado);

    StringToData(data, &c->dataNascimento);

}

void gravarClienteCSV(CLIENTE c)
{   
    char Data[50];
    char nomeArquivo[] = "Clientes.csv";
    FILE *csv;
    csv = fopen(nomeArquivo, "r+w");
    if (csv == NULL)
    {
        // arquivo não existe, será criado
        csv = fopen(nomeArquivo, "a");
        fprintf(csv, "CPF;Nome;DataNascimento;Idade;Endereco;Cidade;Estado\n");
        fflush(csv);
    } else
        fseek(csv, 0, SEEK_END);
    // arquivo ja existe, insere apenas o dado no final do arquivo
    DataToString(c.dataNascimento, Data, false);
    
    fprintf(csv, "%s;%s;%s;%d;%s;%s;%s\n",
        c.CPF, c.nome, Data, c.idade, c.endereco, c.cidade, c.estado);
    fflush(csv);
    fclose(csv);
    
}


void AlterarCliente(char *CPF)
{
    CLIENTE lista[100];
    int qtde = lerClientesCSV(lista);
    deletarCliente(CPF);
    CLIENTE c = buscarClientePorCPF(CPF, lista, qtde);
    if (strcmp(c.CPF, "0") != 0)
    {
        exibirCliente(c);
        printf("Digite o novo Endereço: ");
        scanf(" %[^\n]s", c.endereco);
        printf("Digite a nova Cidade: ");
        scanf(" %[^\n]s", c.cidade);
        printf("Digite o novo Estado: ");
        scanf(" %[^\n]s", c.estado);
        gravarClienteCSV(c);
    }
    else
    {
        printf("\n");
        printf("Cliente não encontrado\n");
        printf("\n");
    }
}


void deletarCliente(char *CPF)
{
    CLIENTE lista[100];
    int qtde = lerClientesCSV(lista);
    remove("Clientes.csv");
    for (int i = 0; i < qtde; i++)
    {
        if (strcmp(CPF, lista[i].CPF) != 0)
        {
            gravarClienteCSV(lista[i]);
        }
    }
    
}

