#ifndef ___GERAR_H___
#define ___GERAR_H___

/**
@file gerar.h
Ficheiro que contém o código relativo a gerar tabuleiros
*/

/**
\briefFunção que determina se a grelha está cheia.
@param ESTADO*/
int cheia(const ESTADO *e);

/**
\briefFunção que determina se uma posição da grelha é conflituosa.
@param ESTADO, int, int*/
int conflito(ESTADO *e, int c, int l);

/**
\briefFunção que verifica se existem 3 peças iguais seguidas.
@param ESTADO, int, int*/
int itsT(ESTADO *e, int c, int l);

/**
\briefFunção que bloqueia as peças que tornam o tabuleiro invalido.
@param ESTADO*/
void bloqueia(ESTADO *e);

/**
\brief Função que verifica se já existem peças para bloquear:
@param estado
@returns 0 se a grelha não é valida,
@returns 1 se a grelha está dentro do padrão,
*/
int vBloq(const ESTADO *e);

/**
\brief Função que preenche uma grelha vazia.
@param linhas, colunas
@returns ESTADO
*/
void preenche(int linhas, int colunas);

/**
\brief Função que a um tabuleiro preenchido, retira peças até se tornar uma grelha semi-preenchida de solução unica.
@param ESTADO
@returns ESTADO
*/
void geraFacil(ESTADO e);

/**
\brief Função que a um tabuleiro preenchido, retira peças até se tornar uma grelha semi-preenchida de solução unica.
@param ESTADO
@returns ESTADO
*/
void geraDificil(ESTADO e);


#endif
