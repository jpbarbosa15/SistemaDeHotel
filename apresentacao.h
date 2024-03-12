#ifndef __APRESENTACAO_H__
#define __APRESENTACAO_H__



/**
 * Cria um separador de linhas para exibição
*/
void separador();

/**
 * Gera o menu principal e retorna a opção desejada pelo usuário
 * @return Retorna o item escolhido pelo o usuário
*/
int MenuPrincipal();

/**
 * Gera o menu de quartos e realizada a rotina escolhida pelo usuario
*/
void menuQuartos();
/**
 * Gera o menu de clientes e realizada a rotina escolhida pelo usuario
*/
void menuClientes();

/**
 * Gera o menu de reservas e realizada a rotina escolhida pelo usuario
*/
void menuReserva();
/**
 * Gera o menu de hospedagem e realizada a rotina escolhida pelo usuario
*/
void menuHospedagem();

#endif