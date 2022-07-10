#ifndef ___VERIFICA_H___
#define ___VERIFICA_H___

/**
@file verifica.h
Contém as funções de validação do jogo
*/

/**
\brief Função que verifica a condição diagonal do Jogo:
@param estado
@returns 0 se a grelha está dentro do padrão,
@returns 1 se a grelha não é valida.
@returns 3 se algo correr muito mal.
*/
int diagonais(const ESTADO *e);

/**
\brief Função que verifica a condição horizontal do Jogo:
@param estado
@returns 0 se a grelha está dentro do padrão,
@returns 1 se a grelha não é valida,
@returns 3 se algo correr muito mal.
*/
int horizontais(const ESTADO *e);

/**
\brief Função que verifica a condição vertical do Jogo:
@param estado
@returns 0 se a grelha está dentro do padrão,
@returns 1 se a grelha não é valida,
@returns 3 se algo correr muito mal.
*/
int verticais(const ESTADO *e);

/**
\brief Função que valida se um jogo acabou, classificando-o se tiver acabado:
@param estado
@returns 0 se a grelha está dentro do padrão,
@returns 1 se a grelha não é valida,
@returns 3 se algo correr muito mal.
*/
int valida(ESTADO e);

/**
\brief Função que devolve se certa casa da grelha tem de ter um X.
@param Estado, int coluna, int linha
@returns 0 se a casa não tem de ter um X,
@returns 1 se a casa tem de ter um X.
*/
int itsX(const ESTADO *e, int c, int l);

/**
\brief Função que devolve se certa casa da grelha tem de ter um O.
@param Estado, int coluna, int linha
@returns 0 se a casa não tem de ter um O,
@returns 1 se a casa tem de ter um O.
*/
int itsO(const ESTADO *e, int c, int l);

/**
\brief Função que identifica se há dois O seguidos numa posição relativa à casa.
@param Estado, int coluna, int linha
@returns 0 se for falso,
@returns 1 se for verdadeiro.
*/
int itsXX(const ESTADO *e, int c, int l);

/**
\brief Função que identifica se há dois O seguidos numa posição relativa à casa.
@param Estado, int coluna, int linha
@returns 0 se for falso,
@returns 1 se for verdadeiro.
*/
int itsOO(const ESTADO *e, int c, int l);

/**
\brief Função que ajuda o jogador a preencher uma peça vazia, com base na função valida.
@param Estado
@returns Estado com ajuda
*/
ESTADO ajudas(ESTADO *e);

/**
\brief Função que resolve o jogo, aplicando ajudas até as ajudas não conseguirem progredir ou o puzzle acabar.
@param Estado
@returns Estado (puzzle completo)
*/
ESTADO solver(ESTADO e);

#endif
