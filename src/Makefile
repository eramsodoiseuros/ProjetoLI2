CFLAGS=-std=c11 -Wall -Wextra -pedantic -g
FICHEIROS=cgi.h estado.c estado.h verifica.c verifica.h extras.c extras.h ficheiro.c ficheiro.h grelha.c grelha.h exemplo.c Makefile
EXECUTAVEL=GandaGalo

install: $(EXECUTAVEL)
	sudo cp $(EXECUTAVEL) /usr/lib/cgi-bin
	sudo chmod -R a+rwx /var/www/html
	touch install

$(EXECUTAVEL): exemplo.o estado.o verifica.o ficheiro.o extras.o grelha.o 
	cc -o $(EXECUTAVEL) exemplo.o estado.o verifica.o ficheiro.o extras.o grelha.o 

imagens:
	sudo mkdir -p /var/www/html/images
	sudo cp *.png /var/www/html/images

users:
	sudo mkdir -p /var/www/html/users
	sudo cp user.txt /var/www/html/users

estilos:
	sudo cp *.css /var/www/html

tabuleiros:
	sudo cp *.txt /var/www/html

user:
	sudo cp user.txt /var/www/html/users

javascript:
	sudo cp *.js /var/www/html

tudo:
	make imagens
	make users
	make estilos
	make tabuleiros
	make javascript
	make mp3
	make user

mp3:
	sudo cp *.mp3 /var/www/html

GandaGalo.zip: $(FICHEIROS)
	zip -9 GandaGalo.zip $(FICHEIROS)

doc:
	doxygen -g
	doxygen

clean:
	rm -rf *.o $(EXECUTAVEL) Doxyfile latex html install

estado.o:   estado.c estado.h
verifica.o: verifica.c verifica.h
extras.o:   extras.c extras.h ficheiro.h
ficheiro.o: ficheiro.c ficheiro.h
grelha.o:   grelha.c grelha.h ficheiro.h extras.h
exemplo.o:  exemplo.c cgi.h estado.h verifica.h ficheiro.h extras.h grelha.h
