#ifndef ___CGI_H___
#define ___CGI_H___

/**
@file cgi.h
Macros úteis para gerar CGIs
*/

#include <stdio.h>

/**
* Caminho para as imagens
*/
#define IMAGE_PATH							"http://localhost/images/"

/**
\brief Macro para começar o html
*/
#define COMECAR_HTML						printf("Content-Type: text/html\n\n<!DOCTYPE html><html lang='PT'><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'><link rel=stylesheet href='../estilos.css' type='text/css'><title>GandaGalo</title><script src='../javascript.js'></script></head>\n")

/**
\brief Macro para abrir um svg
@param tamx O comprimento do svg
@param tamy A altura do svg
*/
#define ABRIR_SVG(tamx, tamy)				printf("<svg width=%d height=%d>\n", tamx, tamy)
/**
\brief Macro para fechar um svg
*/
#define FECHAR_SVG							printf("</svg>\n")

/**
\brief Macro para criar uma imagem
@param X A coordenada X do canto superior esquerdo
@param Y A coordenada Y do canto superior esquerdo
@param ESCALA A escala da imagem
@param FICHEIRO O caminho para o link do ficheiro
*/
#define IMAGEM(X, Y, ESCALA, FICHEIRO)		printf("<image x=%d y=%d width=%d height=%d xlink:href=%s%s />\n", \
												ESCALA * X, ESCALA* Y, ESCALA, ESCALA, IMAGE_PATH, FICHEIRO)

/**
\brief Macro para criar um quadrado
@param X A coordenada X do canto superior esquerdo
@param Y A coordenada Y do canto superior esquerdo
@param ESCALA A escala do quadrado
@param COR A cor de preenchimento do quadrado
*/
#define QUADRADO(X, Y, ESCALA, COR)			printf("<rect x=%d y=%d width=%d height=%d fill=%s />\n", \
												ESCALA * X, ESCALA* Y, ESCALA, ESCALA, COR)

/**
\brief Macro para abrir um link
@param link O caminho para o link
*/
#define ABRIR_LINK(link)					printf("<a xlink:href=%s>\n", link)

/**
\brief Macro para fechar o link
*/
#define FECHAR_LINK							printf("</a>\n")
#define FECHAR_HTML							printf("<footer><p class='rodape' >Diogo Ribeiro & Francisco Peixoto @ LI2 2018</></footer></html>\n")


#define ABRIR_DIV_BUTTONS             		printf("<div class='buttons'>\n")
#define FECHAR_DIV             		        printf("</div>\n")
#define DIV_CLEAR             		        printf("<div class='clear'></div>\n")
#define BOTAO_JOGO(tabuleiro, texto)      	printf(" <button onclick='getUser(this.id)'' type='button' class='btnmenu' id='%s'>%s</button>\n", tabuleiro, texto)
#define BOTAO_LINK_normal(link, texto)		printf(" <a href=%s class='small'><button type='button' class='btn'>%s</button></a>\n", link, texto)
#define BOTAO_LINK_medio(link, texto)		printf(" <a href=%s class='medium'><button type='button' class='btnm'>%s</button></a>\n", link, texto)
#define BOTAO_LINK_grande(link, texto)		printf(" <a href=%s class='big'><button type='button' class='btng'>%s</button></a>\n", link, texto)
#define botao_valor_teste(link, texto)		printf(" <a href=%s><button type='button' class='btng'>%d</button></a>\n", link, texto)
#define LOGO             		            printf(" <img src='../images/ganda_galo.png' alt='GandaGalo' class='center'><br> \n")


#endif
