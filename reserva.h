#ifndef __RESERVA_H__
#define __RESERVA_H__

#include "tempo.h"
#include <stdbool.h>

enum CAMPOS_RESERVA {ID_RESERVA=0,CPF_RESERVA, CHECKIN_RESERVA,CHECKOUT_RESERVA,TIPOQUARTO_RESERVA, IDQUARTO_RESERVA, STATUS_RESERVA  };

typedef struct RESERVA
{
    /* Identificação da reserva do cliente */
    unsigned int id;
    /* CPF do cliente que fez a reserva */
    char CPF[16];
    /* Data de provavel entrada do cliente */
    DATA checkin;
    /* Data de provavel saída do cliente */
    DATA checkout;
    /* Tipo de quarto reservado */
    char tipoQuarto[7]; // "Single", "Duplo", "Triplo"
    /* Identificação do quarto */
    unsigned int idQuarto;
    /* Status da reserva. Pode estar 'ativa' ou 'cancelada' */
    char status[11];   
} RESERVA;



/**
 * Rotina que devolve o id a ser utilizado no próximo id de cadastro de reserva
 * @return Retorna o próximo ID a ser utilizado 
*/
unsigned int obterProximoIdReserva();


/**
 * Exibe uma reserva na tela do usuário
 * @param r Reserva que será exibida
*/
void exibirReserva( RESERVA r );


/**
 * Função que verifica se um periodo de reserva de um quarto (entradaPrevista e saidaPrevista) se sobrepõem com 
 * outro período de checkin e checkout de um quarto 
 * @param entradaPrevista Data inicial do periodo da reserva que se deseja registrar
 * @param saidaPrevista Data final do periodo da reserva que se deseja registrar
 * @param checkin Data inicial de uma reserva registrada
 * @param checkout Data final de uma reserva registrada
 * @return Retorna true se o periodo não se está sobreposto e false se está sobreposto 
*/
bool verificaSobreposicaoReserva(DATA entradaPrevista, DATA saidaPrevista, DATA checkin, DATA checkout);


/**
 * Função que verifica a quantidade de reservas salvas no arquivo CSV
 * @return Retorna a quantidade de reservas encontrada
*/
int quantidadeReservasCSV();


/**
 * Lê os dados armazenados no arquivo Reservas.csv e guarda as informações num vetor dinâmico 
 * representa pela lista
 * @param lista Vetor com todos os dados de reserva colocados no arquivo Reservas.csv
 * @return Retorna a quantidade de reservas lidas
*/
int lerReservasCSV( RESERVA *lista );


/**
 * Exibi os dados de uma reserva
 * @param r Reserva que será exibida
*/
void exibirReserva(RESERVA r);


/**
 * Rotina que verifica se existe quarto disponível para o cliente 
 * do tipo e data que ele precisa
 * @param CPF CPF do cliente 
 * @param tipoQuarto
 * @param checkin
 * @param checkout
 * @param mReserva Parâmetro que armazenará os dados da reserva caso seja possível fazê-la. 
 * Caso contrário retornará NULL;
 * @return Retorna true se for possivel reservar o quarto e false caso contrário
*/
bool reservarQuarto(char *CPF, char *tipoQuarto, DATA checkin, DATA checkout, RESERVA *mReserva);


/**
 * Gravando os dados de uma reserva no final do arquivo. Caso o arquivo
 * não exista, gera um novo arquivo com as colunas que são o cabeçalho
 * @param r Reserva que será salva no arquivo
 */
int gravarReservaCSV(RESERVA r);


/**
 * Gravando os dados de uma reserva no final do arquivo binário. Caso o arquivo
 * não exista, gera um novo arquivo 
 * @param r Reserva que será salva no arquivo
 */
int gravarReservaDAT(RESERVA r);

/**
 * Retorna a quantidade de reservas que estão salvas no arquivo DAT
 * @return Quantidade de reservas salvos
*/
int quantidadeReservasDAT( );

/**
 * Leitura de dados do arquivo binário para registros
 * @param lista Ponteiro para um vetor de registros
 * com os dados que estão no arquivo
 * @return Retorna a quantidade de quartos cadastrados
 */
int lerReservasDAT(RESERVA *lista);

#endif
