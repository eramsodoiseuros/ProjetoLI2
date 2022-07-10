/**
@file exemplo.c
Esqueleto do programa
*/

#include <stdlib.h>
#include <string.h>
#include "cgi.h"
#include "estado.h"
#include "verifica.h"
#include "ficheiro.h"
#include "extras.h"

#define MAX_BUFFER	  10240
#define GRELHA		  4
#define TAM			  40

int numeroAjudas = 10;

/**
Função responsável por inicializar o jogo.
*/
void inicializa(char *link) {
	
	int pjogada = 1;
	char *user = &link[1];
	char facil[MAX_BUFFER], medio[MAX_BUFFER], dificil[MAX_BUFFER], userfile[MAX_BUFFER];

	sprintf(facil, "1%s", user);
	sprintf(medio, "2%s", user);
	sprintf(dificil, "3%s", user); 
	sprintf(userfile, "/var/www/html/users/%s.txt", user);

	if(strcmp(link, facil) == 0) pjogada = checkUserJogo(user, userfile, 1);
	else if(strcmp(link, medio) == 0) pjogada = checkUserJogo(user, userfile, 2);
	else if(strcmp(link, dificil) == 0) pjogada = checkUserJogo(user, userfile, 3);
 
	preparaUserStart(pjogada);
}

/**
Função principal do programa.
@returns 0 se tudo correr bem
*/
int main() {
	
	char *s = getenv("QUERY_STRING");
	int query = processaQuery(s);

	if (query == 0) menu();
	else if (query == 1) inicializa(s);

	return 0;
}
