#ifndef __QUARTO_H__
#define __QUARTO_H__

#include <stdio.h>
#include <stdbool.h>
#include "tempo.h"




typedef  struct QUARTO {
    /* Identificação do quarto */
    unsigned int id;
    /* Quantidade de camas de solteiro estão no quarto*/
    unsigned int camasSolteiro;
    /* Quantidade de camas de casal estão no quarto*/
    unsigned int camasCasal;
    /* Tipo de quarto */
    char tipoQuarto[7]; // "Single", "Duplo", "Tripo"
    /* Valor da diária */
    float valorDiaria;
    /* Status de ocupacao do quarto */
    bool status ;
} QUARTO;



/**
 * Rotina que lê os dados de um quarto através do teclado
 * @param p Ponteiro para um registro do tipo QUARTO, 
 * onde os dados lidos serão armazenados 
*/
void lerQuarto( QUARTO *p );

/**
 * Exibe os campos contidos em um registro do tipo QUARTO
 * @param p Registro que será exibido
 */
void exibirQuarto(QUARTO p);

/**
 * Gravando os dados de um quarto no final do arquivo. Caso o arquivo
 * não exista, gera um novo arquivo com as colunas que são o cabeçalho
 * @param p Quarto que será salvo no arquivo
 */
int gravarQuartoCSV(QUARTO p);

/**
 * Retorna a quantidade de quartos  que estão salvos no arquivo CSV
 * @return Quantidade de quartos salvos
*/
int quantidadeQuartosCSV();

/**
 * Leitura de dados do CSV para registros
 * @param lista Ponteiro para um vetor de registros
 * com os dados que estão no arquivo
 * @return Retorna a quantidade de quartos cadastrados
 */
int lerQuartosCSV(QUARTO *lista);

/**
 * Grava um registro de QUARTO em um arquivo binário
 * @param p Quarto que será salvo no arquivo
 */
int gravarQuartoDAT( QUARTO p);


/**
 * Retorna a quantidade de quartos que estão salvos no arquivo DAT
 * @return Quantidade de quartos salvos
*/
int quantidadeQuartosDAT( );


/**
 * Leitura de dados do arquivo binário para registros
 * @param lista Ponteiro para um vetor de registros
 * com os dados que estão no arquivo
 * @return Retorna a quantidade de quartos cadastrados
 */
int lerQuartosDAT(QUARTO *lista);


/**
 * Busca os quartos existente de um determinado tipo
 * @param tipoQuarto Tipo de quarto desejado
 * @param lista Lista com todos os tipos de quartos existente;
 * @param qtdeQuartos Quantidade de quartos cadastrados
 * @param listaSaida Lista quartos de tipo QUARTO com informações encontrada 
 * com o quarto desejado. Retorna NULL caso não existam quartos do tipo desejado.
 * @param qTipo Quantidade de quartos encontrados do tipo desejado
*/
void buscarQuartosPorTipo(char *tipoQuarto, QUARTO *lista, int qtd, QUARTO *listaSaida, int *qTipo);

/**
 * Altera a quantidade de camas e o tipo do quarto
 * @param id Id do quarto que será alterado
*/
void AlterarQuarto(int id);

/**
 * Deleta um quarto do arquivo
 * @param id Id do quarto que será deletado
*/
void deletarQuarto(int id);

#endif