#include "reserva.h"
#include <stdio.h>
#include <stdlib.h>
#include "apresentacao.h"
#include "cliente.h"
#include "quarto.h"
#include <string.h>
#include <ctype.h>


/**
 * Rotina que devolve o id a ser utilizado no próximo id de cadastro de reserva
 * @return Retorna o próximo ID a ser utilizado 
*/
unsigned int obterProximoIdReserva()
{
    char nomeArquivo[] = "idReserva.dat";
    FILE *f = fopen(nomeArquivo, "r+wb");
    unsigned  id=1;
    unsigned int v;
    int size;
    if (f != NULL)
    {
        size = fread(&v,sizeof(unsigned int),1, f);
        if (size > 0)
        {
            v++;
            id = v;
        }
        fseek(f,0,SEEK_SET);
        fwrite(&v, sizeof(unsigned int), 1, f);    
        fflush(f);
        fclose(f);
    }
    else
    {
        f = fopen(nomeArquivo,"wb");
        fwrite(&id, sizeof(unsigned int), 1, f);
        fclose(f);
    }
    return id;
}

bool verificaSobreposicaoReserva(DATA entradaPrevista, DATA saidaPrevista, DATA checkin, DATA checkout)
{
    bool ret = false;
    if ( DataCmp(saidaPrevista, checkin) < 0) 
        ret = true;
    else if ( DataCmp(entradaPrevista, checkout) > 0)
        ret = true;
    
    return ret;
}

int quantidadeReservasCSV()
{
    char nomeArquivo[] = "Reservas.csv";
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


int lerReservasCSV( RESERVA *lista )
{
    char nomeArquivo[] = "Reservas.csv";
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
                case ID_RESERVA: 
                    lista[i].id = atoi(campos);  
                    break;              
                case CPF_RESERVA:
                    strcpy(lista[i].CPF, campos);
                    break;
                case CHECKIN_RESERVA:
                    StringToData(campos, &lista[i].checkin);
                    break;
                case CHECKOUT_RESERVA:
                    StringToData(campos, &lista[i].checkout);
                    break;                    
                case TIPOQUARTO_RESERVA:
                    strcpy(lista[i].tipoQuarto, campos);
                    break;
                case IDQUARTO_RESERVA:
                    lista[i].idQuarto = atoi(campos);
                    break;

                case STATUS_RESERVA:
                    strcpy(lista[i].status, campos);
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


void exibirReserva(RESERVA r)
{
   char temp[12];
   printf("##################################### \n");
   printf("ID : %d\n",r.id);
   printf("-------------------------------------- \n");        
   DataToString(r.checkin, temp, false);
   printf("Check in: %s\n", temp);   
   printf("------------------------------------- \n");
   DataToString(r.checkout, temp, false);
   printf("Check out: %s\n", temp);   
   printf("------------------------------------- \n");
   printf("Número do quarto: %d\n", r.idQuarto);      
   printf("------------------------------------- \n");
   printf("Tipo de quarto: %s\n", r.tipoQuarto);      
   printf("------------------------------------- \n");      
   printf("Status: %s\n", r.status);   
   printf("------------------------------------- \n");
   printf("##################################### \n");
}


/**
 * Rotina que verifica se existe quarto disponível para o cliente 
 * do tipo e data que ele precisa
 * @param CPF CPF do cliente
 * @param tipoQuarto Tipo de quarto desejado
 * @param checkin Data de entrada
 * @param checkout Data de saida
 * @param mReserva Parâmetro que armazenará os dados da reserva caso seja possível fazê-la.  * 
 * @return Retorna true se for possivel reservar o quarto e false caso contrário
*/
bool reservarQuarto(char *CPF, char *tipoQuarto, DATA checkin, DATA checkout, RESERVA *mReserva)
{    
    CLIENTE  *listaClientes, temp;
    int qClientes = quantidadeClientesCSV();
    // aloca temporariamente a lista de clientes para poder buscar
    listaClientes = (CLIENTE *) malloc(sizeof(CLIENTE) * qClientes );
    lerClientesCSV(listaClientes);
    temp  = buscarClientePorCPF(CPF, listaClientes, qClientes);
    free(listaClientes);
    if (strcmp(temp.CPF, "0") != 0 )
    {
        // cliente cadastrado buscando quartos
        QUARTO *listaQuartos, *listaTipoQuarto = NULL;
        int qQuartos = quantidadeQuartosCSV();
        // aloca temporariamente a lista de quartos para poder buscar
        listaQuartos = (QUARTO *) malloc(sizeof(QUARTO) * qQuartos );
        lerQuartosCSV(listaQuartos);
        listaTipoQuarto = (QUARTO *) malloc(sizeof(QUARTO) * qQuartos);
        int qQuartosDoTipo;
        buscarQuartosPorTipo(tipoQuarto, listaQuartos,qQuartos, listaTipoQuarto, &qQuartosDoTipo );
        free(listaQuartos);
        listaTipoQuarto = (QUARTO * ) realloc(listaTipoQuarto, sizeof(QUARTO) * qQuartosDoTipo );
        // obtendo os quartos que estão reservados no periodo que se deseja fazer a reserva
        RESERVA *lReservas ;
        RESERVA *ReservadosNoPeriodo;
        int qReservas = quantidadeReservasCSV();
        int qReservados=0;
        lReservas = (RESERVA *) malloc(sizeof(RESERVA) * qReservas);
        ReservadosNoPeriodo = (RESERVA *) malloc(sizeof(RESERVA) * qReservas);
        lerReservasCSV(lReservas);      
        // separando os quartos reservados no periodo pedido pelo cliente
        for (int i = 0; i < qReservas; i++)
        {
            bool flag = verificaSobreposicaoReserva(checkin, checkout, lReservas[i].checkin, lReservas[i].checkout ) ;
            char tipo[7]; // "Single", "Duplo", "Tripo"
            strcpy(tipo, lReservas[i].tipoQuarto);
            if ( flag == false && (strcmp(tipo, tipoQuarto) == 0) )
            {
                // QUARTO FOI RESERVADO NO PERIODO QUE O CLIENTE DESEJA, VERIFICANDO SE É 
                ReservadosNoPeriodo[qReservados] = lReservas[i];
                qReservados++;
            }
        }
        bool QuartoEncontrado = false;
        int q=0;
        while( !QuartoEncontrado && q < qQuartosDoTipo)
        {
            int r=0;
            int c = 0;
            while (r < qReservados && c==0 ) 
            {               
                if (listaTipoQuarto[q].id == ReservadosNoPeriodo[r].idQuarto )
                    c++;
                r++;
            }
            if (c == 0)
            {
              mReserva->id = obterProximoIdReserva();
              strcpy(mReserva->CPF, CPF);
              mReserva->checkin = checkin;
              mReserva->checkout = checkout;              
              strcpy(mReserva->tipoQuarto, tipoQuarto);
              mReserva->idQuarto = listaTipoQuarto[q].id;
              strcpy(mReserva->status, "ativa");
              QuartoEncontrado = true;    
            }
            q++;
        }

        return QuartoEncontrado;

    }
    else
    {
        printf("Cliente não encontrado.\n ");
        printf("Cadastre o cliente antes de fazer a reserva\n");
        return false;
    }
}

/**
 * Gravando os dados de uma reserva no final do arquivo. Caso o arquivo
 * não exista, gera um novo arquivo com as colunas que são o cabeçalho
 * @param r Reserva que será salva no arquivo
 */
int gravarReservaCSV(RESERVA r)
{
    FILE *csv;
    char nomeArquivoCSV[] = "Reservas.csv";
    csv = fopen(nomeArquivoCSV, "r+w");
    char strCheckIn[20];
    char strCheckOut[20];
    DataToString(r.checkin, strCheckIn,false);
    DataToString(r.checkout, strCheckOut, false);
    if (csv == NULL)
    {
        // arquivo não existe, será criado
        printf("Criando arquivo %s\n", nomeArquivoCSV);
        csv = fopen(nomeArquivoCSV, "a");
        fprintf(csv, "IdReserva; CPF; Checkin; Checkout;TipoQuarto;IdQuarto;Status\n");
        fflush(csv);
    }
    else
        fseek(csv, 0, SEEK_END);
    // arquivo ja existe, insere apenas o dado no final do arquivo
    fprintf(csv, "%d;%s;%s;%s;%s;%d;%s\n",
            r.id, r.CPF, strCheckIn, strCheckOut,r.tipoQuarto,r.idQuarto,r.status);
    fflush(csv);
    fclose(csv);
    // salvando o cabeçalho do arquivo
    return 0;
}

/**
 * Gravando os dados de uma reserva no final do arquivo binário. Caso o arquivo
 * não exista, gera um novo arquivo 
 * @param r Reserva que será salva no arquivo
 */
int gravarReservaDAT(RESERVA r)
{
    FILE *dat;
    char nomeArquivoDAT[] = "Reservas.dat";
    dat = fopen(nomeArquivoDAT, "a+b");
    if (dat == NULL)
    {
        // arquivo não existe, será criado
        printf("Criando arquivo %s\n", nomeArquivoDAT);
        dat = fopen(nomeArquivoDAT, "ab");
    }
    fwrite(&r, sizeof(RESERVA), 1, dat);
    fflush(dat);
    fclose(dat);
    return 0;
}

/**
 * Retorna a quantidade de reservas que estão salvas no arquivo DAT
 * @return Quantidade de reservas salvos
*/
int quantidadeReservasDAT( )
{
    int qtde = 0;
    RESERVA dummy;
    FILE *dat;
    char nomeArquivoDAT[] = "Reservas.dat";
    dat = fopen(nomeArquivoDAT, "rb");
    if (dat != NULL)
    {
        while (fread(&dummy, sizeof(RESERVA), 1, dat) > 0)
            qtde++;
        fclose(dat);
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
int lerReservasDAT(RESERVA *lista)
{
    int qtde = 0;
    FILE *dat;
    char nomeArquivoDAT[] = "Reservas.dat";
    dat = fopen(nomeArquivoDAT, "rb");
    if (dat != NULL)
    {
        while (fread(&lista[qtde], sizeof(RESERVA), 1, dat) > 0)
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
