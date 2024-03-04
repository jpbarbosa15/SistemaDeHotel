all: hotelTeste

# compilação do executavel
hotelTeste: tempo.o main.o quarto.o apresentacao.o reserva.o hospedagem.o cliente.o
#quarto.o apresentacao.o tempo.o cliente.o main.o
# Compilador faz a ligação entre os dois arquivos obj 
# 	e gera o executável
#gcc -o hotelPrototipo main.o quarto.o apresentacao.o tempo.o cliente.o -ggdb
	gcc -o hotelPrototipo main.o quarto.o cliente.o tempo.o apresentacao.o reserva.o hospedagem.o  -lm -ggdb

cliente.o: cliente.c cliente.h
	gcc -o cliente.o -c cliente.c -Wall -ggdb

tempo.o: tempo.c tempo.h
#compila o arquivo atual
	gcc -o tempo.o -c tempo.c -lm -Wall -ggdb

apresentacao.o: apresentacao.c apresentacao.h
# compila o arquivo atual
	gcc -o apresentacao.o -c apresentacao.c -Wall -ggdb

quarto.o : quarto.c quarto.h
# compila o arquivo atual
	gcc -o quarto.o -c quarto.c -Wall -ggdb

reserva.o : reserva.c reserva.h
# compila o arquivo atual
	gcc -o reserva.o -c reserva.c -Wall -ggdb

hospedagem.o : hospedagem.c hospedagem.h
	gcc -o hospedagem.o -c hospedagem.c -Wall -ggdb


main.o : main.c 
	gcc -o main.o -c main.c -Wall -ggdb

clean:
	rm -rf *.o

mrproper: clean
	rm -rf mercadoPrototipo
