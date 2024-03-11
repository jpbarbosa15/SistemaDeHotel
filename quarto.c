#include "quarto.h"
#include "apresentacao.h"
#include "reserva.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

const char separadorCSV = ';';
const char nomeArquivoCSV[] = "Quartos.csv";
const char nomeArquivoDAT[] = "Quartos.dat";
// char SETOR[6][] = {"Higiene", "Limpeza", "Bebidas", "Frios", "Padaria", "Açougue"};

/**
 * Rotina que lê os dados de um quarto através do teclado
 * @param p Ponteiro para um registro do tipo QUARTO, 
 * onde os dados lidos serão armazenados 
*/
void lerQuarto( QUARTO *p )
{
    printf("\n");
    separador();
    printf("Lendo um quarto \n");
    printf("Id do quarto :  ");
    scanf(" %d", &p->id);
    printf("Camas de solteiro: ");
    scanf(" %d", &p->camasSolteiro);
    printf("Camas de casal: ");
    scanf(" %d", &p->camasCasal);
    printf("Selecione o tipo de quarto (single ou duplo ou triplo)\n");
    printf("-> ");
    scanf(" %[^\n]", p->tipoQuarto);
    printf("Preço da diária: ");
    scanf(" %f", &p->valorDiaria);
    p->status = true; // assumindo sempre disponivel quando cadastrado
}

/**
 * Exibe os campos contidos em um registro do tipo QUARTO
 * @param p Registro que será exibido
 */
void exibirQuarto(QUARTO p)
{   
    printf("\n");
    separador();
    printf("Exibindo um quarto \n");
    printf("Idenficador do quarto: ");
    printf(" %u\n", p.id);
    printf("Camas de solteiro :  ");
    printf(" %u\n", p.camasSolteiro);
    printf("Camas de casal: ");
    printf(" %u\n", p.camasCasal);
    printf("Tipo de quarto: ");
    printf(" %s\n", p.tipoQuarto);    
    printf("Preço da diária: %.2f\n", p.valorDiaria);
    printf("Status: ");
    if (p.status)
        printf("Disponível\n");
    else
        printf("Indisponível\n");
    separador();
    printf("\n");
}



/**
 * Gravando os dados de um quarto no final do arquivo. Caso o arquivo
 * não exista, gera um novo arquivo com as colunas que são o cabeçalho
 * @param p Quarto que será salvo no arquivo
 */
int gravarQuartoCSV(QUARTO p)
{
    FILE *csv;
    csv = fopen(nomeArquivoCSV, "r+w");

    if (csv == NULL)
    {
        // arquivo não existe, será criado
        csv = fopen(nomeArquivoCSV, "a");
        fprintf(csv, "id;solteiro;casal;tipo;preço;status\n");
        fflush(csv);
    }
    else
        fseek(csv, 0, SEEK_END);
    // arquivo ja existe, insere apenas o dado no final do arquivo
    fprintf(csv, "%d;%d;%d;%s;%.2f;%d\n",
            p.id, p.camasSolteiro, p.camasCasal, p.tipoQuarto,
            p.valorDiaria, p.status);
    fflush(csv);
    fclose(csv);
    // salvando o cabeçalho do arquivo
    return 0;
}

int quantidadeQuartosCSV()
{
    FILE *csv;
    char linha[1000];
    csv = fopen(nomeArquivoCSV, "r");
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


/**
 * Leitura de dados do CSV para registros
 * @param lista Ponteiro para um vetor de registros
 * com os dados que estão no arquivo
 * @return Retorna a quantidade de quartos cadastrados
 */
int lerQuartosCSV(QUARTO *lista)
{
    
    FILE *csv;
    char linha[1000];
    char *campos;
    const char s[2] = ";";
    int contadorLinha = 0;
   
    csv = fopen(nomeArquivoCSV, "r");
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
                //printf(" %s\n", campos);
                switch (campoAtual)
                {
                case 0:
                    lista[i].id = atoi(campos);
                    break;
                case 1:
                    lista[i].camasSolteiro = atoi(campos);
                    break;
                case 2:
                    lista[i].camasCasal = atoi(campos);
                    break;
                case 3:
                    strcpy(lista[i].tipoQuarto, campos);                    
                    break;
                case 4:
                    lista[i].valorDiaria = atof(campos);
                    break;
                case 5:
                    lista[i].status = atoi(campos);
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
        printf("Erro - Arquivo %s não encontrado\n", nomeArquivoCSV);
        return -1;
    }
}

/**
 * Grava um registro de QUARTO em um arquivo binário
 * @param p Quarto que será salvo no arquivo
 */
int gravarQuartoDAT( QUARTO p)
{
    FILE *dat;
    dat = fopen(nomeArquivoDAT, "a+b");
    if (dat == NULL)
    {
        // arquivo não existe, será criado
        printf("Criando arquivo %s\n", nomeArquivoDAT);
        dat = fopen(nomeArquivoDAT, "ab");
    }
    fwrite(&p, sizeof(QUARTO), 1, dat);
    fflush(dat);
    fclose(dat);
    return 0;
}

/**
 * Retorna a quantidade de quartos que estão salvos no arquivo DAT
 * @return Quantidade de quartos salvos
*/
int quantidadeQuartosDAT( )
{
    int qtde = 0;
    QUARTO dummy;
    FILE *dat;
    dat = fopen(nomeArquivoDAT, "rb");
    if (dat != NULL)
    {
        while (fread(&dummy, sizeof(QUARTO), 1, dat) > 0)
            qtde++;

        return qtde;
    }
    else
    {
        return 0;
    }
}

/**
 * Leitura de dados do arquivo binário para registros
 * @param lista Ponteiro para um vetor de registros
 * com os dados que estão no arquivo
 * @return Retorna a quantidade de quartos cadastrados
 */
int lerQuartosDAT(QUARTO *lista)
{
    int qtde = 0;
    FILE *dat;
    dat = fopen(nomeArquivoDAT, "rb");
    if (dat != NULL)
    {
        while (fread(&lista[qtde], sizeof(QUARTO), 1, dat) > 0)
        {
            // exibirProduto(lista[qtde]);
            qtde++;
        }
        return qtde;
    }
    else
    {
        printf("Erro - Arquivo %s não encontrado\n", nomeArquivoDAT);
        return -1;
    }
}


void buscarQuartosPorTipo(char *tipoQuarto, QUARTO *lista, int qtd, QUARTO *listaSaida, int *qTipo)
{    
    *qTipo = 0;
    for (int i = 0 ; i < qtd ; i++)
    {
        if (strcmp(lista[i].tipoQuarto, tipoQuarto) == 0)
        {
            listaSaida[*qTipo] = lista[i];
            (*qTipo)++;
        }
    }    
}



void AlterarQuarto(int id)
{
    int Alterou = 0;
    QUARTO *lista;
    int qtdQuartos = quantidadeQuartosCSV();
    lista = (QUARTO *)malloc(qtdQuartos * sizeof(QUARTO));
    lerQuartosCSV(lista);
    remove(nomeArquivoCSV);
    for (int i = 0; i < qtdQuartos; i++)
    {
        if (lista[i].id == id)
        {
            printf("Camas de solteiro: ");
            scanf(" %d", &lista[i].camasSolteiro);
            printf("Camas de casal: ");
            scanf(" %d", &lista[i].camasCasal);
            printf("Selecione o tipo de quarto (single ou duplo ou triplo)\n");
            printf("-> ");
            scanf(" %[^\n]", lista[i].tipoQuarto);
            Alterou = 1;
        }
        gravarQuartoCSV(lista[i]);
        
    }
    
    free(lista);
    
    if (Alterou == 0)
    {
        printf("\n");
        printf("Quarto não encontrado\n");
        printf("\n");
    } else {
        printf("\n");
        printf("Quarto alterado com sucesso\n");
        printf("\n");
    }
    
}


void deletarQuarto(int id)
{   
    int deletou = 0;
    QUARTO *lista;
    int qtdQuartos = quantidadeQuartosCSV();
    lista = (QUARTO *)malloc(qtdQuartos * sizeof(QUARTO));
    lerQuartosCSV(lista);
    remove(nomeArquivoCSV);
    for (int i = 0; i < qtdQuartos; i++)
    {
        if (lista[i].id != id)
        {
            gravarQuartoCSV(lista[i]);
        } else {
            deletou = 1;
        }
    }
    free(lista);

    if (deletou == 0)
    {
        printf("\n");
        printf("Quarto não encontrado\n");
        printf("\n");
    } else {
        printf("\n");
        printf("Quarto deletado com sucesso\n");
        printf("\n");
    }
    
}


void AlterarStatusQuarto(int id, bool status)
{
    QUARTO *lista;
    int qtdQuartos = quantidadeQuartosCSV();
    lista = (QUARTO *)malloc(qtdQuartos * sizeof(QUARTO));
    lerQuartosCSV(lista);
    deletarQuarto(id);
    for (int i = 0; i < qtdQuartos; i++)
    {
        if (lista[i].id == id)
        {
            lista[i].status = status;
            gravarQuartoCSV(lista[i]);
        }
        
        
    }
    
    free(lista);
    
}


QUARTO buscarQuartoID(int id){
    QUARTO *lista;
    int qtdQuartos = quantidadeQuartosCSV();
    lista = (QUARTO *)malloc(qtdQuartos * sizeof(QUARTO));
    lerQuartosCSV(lista);
    QUARTO q;
    for (int i = 0; i < qtdQuartos; i++)
    {
        if (lista[i].id == id)
        {
            q = lista[i];
        }
    }
    free(lista);
    return q;
}