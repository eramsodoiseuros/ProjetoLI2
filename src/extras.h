#ifndef ___EXTRAS_H___
#define ___EXTRAS_H___

/**
@file extras.h
Contém as funções relativas a elementos extra do jogo
*/

/**
\brief Esta função imprime no ecrã a mensagem de vitória ou de derrota e elimina o ficheiro do utilizador dado o utilizador, o tabuleiro e o inteiro que representa o resultado, quando o jogo termina.
@param utilizador, tabuleiro, jogada, resultado
*/
void mensagemFinal(char *utilizador, int tabuleiro, int jogada, int result);

/**
\brief Função que dada a QUERY_STR verifica se esta está vazia.
@param QUERY_STR
@returns 1 caso a QUERY_STR não esteja vazia e 0 se estiver vazia
*/
int processaQuery (char *args);

/**
\brief Lê o valor fornecido e segundo as regras do jogo retorna o valor corresponde à ação de clicar.
@param VALOR
@returns O VALOR
*/
VALOR atualiza(VALOR v);

/**
\brief Esta função tem como finalidade, dado um numero de coluna e linha e um estado, criar o link atualizado.
@param linhas, colunas, ESTADO
*/
void criaLink (int l, int c, ESTADO e);

/**
\brief Função que escreve os botões menu, voltar e ajuda no ecrã.
@param jogada, ESTADO, ficheiro utilizador
*/
void botoesMenuVoltarAjuda(int jogada, ESTADO e, char *userfile);

/**
\brief Função que escreve os botões colocar e regressar ancora no ecrã.
@param link, jogada, valorAncora, setAncora regressaDeAncora, ficheiro de utilizador
*/
void botoesColocarRegressarAncora(char *link, int jogada, int valorAncora, char *setAncora, char *regressaDeAncora, char *userfile);

/**
\brief Função que escreve os botões do jogo com os respetivos links no ecrã.
@param link, jogada, valorAncora, ESTADO, setAncora regressaDeAncora, ficheiro de utilizador
*/
void botoesJogo(char *link, int jogada, int valorAncora, ESTADO e, char *setAncora, char *regressaDeAncora, char *userfile);

/**
\brief Função que escreve os elementos do jogo com os respetivos links no ecrã.
@param link, tabuleiro, jogada, valorAncora, ESTADO, setAncora regressaDeAncora, ficheiro de utilizador
*/
void printGame(char *link, int tabuleiro, int jogada, int valorAncora, ESTADO e, char *setAncora, char *regressaDeAncora, char *userfile);

/**
\brief Função que escreve os botões com os respetivos links para iniciar o jogo.
@returns 0
*/
int menu();

#endif