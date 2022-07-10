#ifndef ___GRELHA_H___
#define ___GRELHA_H___

/**
@file grelha.h
Contém as funções relativas à grelha e ao ESTADO
*/

/**
Função que inicializa o estado.
Esta função está vazia
@returns Um novo estado
*/
ESTADO inicializarEstado();

/**
Lê o estado a partir da variável de ambiente QUERY_STR. Caso não seja passado um valor, chama a função loadFile.
@param args O valor da variável (o que é passado depois de ? no URL)
@returns O estado
*/
ESTADO ler_estado(char *args);

/**
\brief Esta função é a responsãvel pela lógica do jogo em aspetos como saber se regressa de ancora ou se coloca ancora.
@param utilizador, tabuleiro, jogada, ancora, QUERY_STR, valorAncora, setAncora, regressaDeAncora
*/
void SetRegressaAncora(char *utilizador, int tabuleiro, int jogada, int ancora, char *s, int valorAncora, char *setAncora, char *regressaDeAncora);

/**
\brief Esta função é a intermediária entre a função grelha e as funções reponsáveis por cada elemento.
@param utilizador, tabuleiro, jogada, ancora, QUERY_STR
*/
void printGrelha(char *utilizador, int tabuleiro, int jogada, int ancora, char *s);

/**
\brief Esta função é a responsável por imprimir no ecrã a grelha para jogar e todos os respetivos elementos. Para isso receb como parâmetros o nome do utilizador, o tabuleiro, a jogada atual e a ancora mais recente.
@returns 0
@param utilizador, tabuleiro, jogada, ancora
*/
int grelha(char *utilizador, int tabuleiro, int jogada, int ancora);

#endif