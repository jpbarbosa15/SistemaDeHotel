#ifndef __HOSPEDAGEM_H__
#define  __HOSPEDAGEM_H__

#include "tempo.h"

enum CAMPOS_HOSPEDAGEM {IDRESERVA_HOSPEDAGEM=0, CPF_HOSPEDAGEM,CHECKIN_HOSPEDAGEM,CHECKOUT_HOSPEDAGEM, STATUS_HOSPEDAGEM, PRECOTOTAL_HOSPEDAGEM};


typedef struct HOSPEDAGEM
{
     /* Identificação da reserva do cliente */
    unsigned int id;
    /* CPF do cliente que fez a reserva */
    char CPF[16];
   /* Data de entrada do cliente */
    DATA checkin;
    /* Data de saída do cliente */
    DATA checkout;    
    /* Status da hospedagem - Se ativa ou finalizada */
    char status[12];
    /* Valor total da hospedagem */
    float precoTotal;
} HOSPEDAGEM;

/**
 * Função que verifica a quantidade de hospedagens salvas no arquivo CSV
 * @return Retorna a quantidade de hospedagens encontrada
*/
int quantidadeHospedagensCSV();



/**
 * Lê os dados armazenados no arquivo Hospedagens.csv e guarda as informações num vetor dinâmico 
 * representa pela lista
 * @param lista Vetor com todos os dados de hospedagens colocados no arquivo "Hospedagens.csv"
 * @return Retorna a quantidade de hospedagens lidas
*/
int lerHospedagensCSV( HOSPEDAGEM *lista );

/**
 * Exibe os campos de uma hospedagem
 * @h Variável com os dados da hospedagem
*/
void exibirHospedagem(HOSPEDAGEM h);


/**
 * Rotina que faz o checkin do cliente pelo ID da Reserva
 * @param id Identificação da reserva
*/
void checkinHospedagem(int id);

/**
 * Grava os dados de uma hospedagem no arquivo CSV
 * @param h Variável com os dados da hospedagem
*/
void GravarHospedagemCSV(HOSPEDAGEM h);

/**
 * Rotina que faz o chekout do cliente pelo ID da Reserva
 * @param id Identificação da reserva
*/
void checkoutHospedagemID(int id);

/**
 * Rotina que faz o chekout do cliente pelo ID do Quarto
 * @param idQuarto Identificação do quarto
*/
void checkoutHospedagemIDQuarto(int idQuarto);

/**
 * Lista todas as hospedagens de um cliente
 * @param CPF CPF do cliente
*/
void ListarHospedagensCliente(char *CPF);
#endif