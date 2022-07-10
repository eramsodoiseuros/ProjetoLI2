#ifndef ___FICHEIRO_H___
#define ___FICHEIRO_H___

/**
@file ficheiro.h
Contém as funções relativas à escrita e leitura em ficheiros
*/

/**
\brief nção que preenche o ficheiro user com o nome do jogador, o tabuleiro selecionado e com as jogadas e ancoras.
@param utilizador, tabuleiro, jogada, ancora
*/
void printUserFile(char *utilizador, int tab, int jogada, int ancora);

/**
\brief Esta função tem como finalidade, dado um numero de uma linha, remover todas as jogadas que se encontram depois dessa dada linha.
Para isso é copiado o conteúdo do ficheiro original para um temporário até à linha dada, e depois é alterado o nome do ficheiro temporario para o nome do ficheiro original, assim substituindo este.
@param utilizador, linha
*/
void tiraJogadasFicheiro(char *utilizador, int linha);

/**
\brief Função que dado o utilizador, o tabuleiro, a jogada e a ancora, escreve esses valores no ficheiro user.txt e invoca a função tiraJogadasFicheiro.
@param utilizador, tabuleiro, jogada, ancora
*/
void atualizaUserFile(char *utilizador, int tabuleiro, int jogada, int ancora);

/**
\brief Função que gera o ESTADO.
@param ESTADO, linhas, colunas, ficheiro com o mapa
@returns ESTADO 
*/
ESTADO geraESTADO(ESTADO e, int linha, int coluna, FILE *file);


/**
\brief Função que le o tabuleiro a partir de um ficheiro e retorna o estado gerado.
@param Nome do ficheiro a abrir
@returns Estado 
*/
ESTADO loadFile(char *args);

/**
\brief Esta função tem como finalidade retornar o valor da ancora mais recente que se encontra no estado da ultima linha do ficheiro que contem as jogadas do utilizador.
@param jogada, utilizador
@returns Um int com o vavor da ancora mais recente
*/
int getAncora(int jogada, char *utilizador);

/**
\brief EFunção que verifica se o utilizador ativo é o mesmo da última vez e se o tabuleiro também é o mesmo.
@param utilizador, ficheiro user, tabuleiro
@returns  (para inicializar a variavel pjogada)
*/
int checkUserJogo(char *user, char *userfile, int tab);

/**
\brief Eunção que irá ler os valores do ficheiro user e atualiza-los e de seguida iniciar o jogo.
@param pjpgada
*/
void preparaUserStart(int pjogada);

#endif