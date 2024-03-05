#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include "tempo.h"

enum CAMPOS_CLIENTE {CPF_CLI=0, NOME_CLI, DATA_NASC_CLI, IDADE_CLI, ENDERECO_CLI, CIDADE_CLI, ESTADO_CLI, PONTOS_CLI};

typedef struct CLIENTE
{
    char CPF[16];
    char nome[51];
    DATA dataNascimento;
    int idade;
    char endereco[101];
    char cidade[101];
    char estado[3];
} CLIENTE;


/**
 * Retorna a quantidade de clientes existentes no cadastro
 * @return Quantidade de clientes encontrados no cadastro
*/
int quantidadeClientesCSV();

/**
 * Leitura de dados do CSV para registros 
 * @param lista Ponteiro para um vetor de registros de clientes 
 * com os dados que estão no arquivo
 * @return Retorna a quantidade de clientes cadastrados
*/
int lerClientesCSV( CLIENTE *lista );

/**
 * Função que exibe os dados de um cliente
 * @param c Registo com os dados de um cliente 
*/
void exibirCliente(CLIENTE c);

/**
 * busca os dados do cliente a partir do cpf dele. 
 * @param CPF CPF que está sendo buscado 
 * @param l lista de clientes em memória
 * @param qtde quantidade de clientes na lista
 * @return Retorna os dados do cliente caso seja encontrado. 
 * Caso contrario retorna cliente com CPF valor "inválido"
*/
CLIENTE buscarClientePorCPF(char *CPF, CLIENTE *l, int qtde);

/**
 * Rotina que lê os dados de um cliente através do teclado
 * @param c Ponteiro para um registro do tipo CLIENTE, 
 * onde os dados lidos serão armazenados 
*/
void lerCliente(CLIENTE *c);

/**
 * Gravando os dados de um cliente no final do arquivo. Caso o arquivo
 * não exista, gera um novo arquivo com as colunas que são o cabeçalho
 * @param c Cliente que será salvo no arquivo
*/
void gravarClienteCSV(CLIENTE c);

/**
 * Função que Altera um cliente do arquivo
 * @param CPF CPF do cliente que será Alterado
*/
void AlterarCliente(char *CPF);


/**
 * Função que deleta um cliente do arquivo
 * @param CPF CPF do cliente que será deletado
*/
void deletarCliente(char *CPF);


#endif