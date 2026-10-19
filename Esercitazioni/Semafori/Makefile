all: semafori

semafori: main.o semafori.o
	gcc main.o semafori.o -o semafori

main.o: main.c semafori.h
	gcc -c main.c -o main.o

semafori.o: semafori.c semafori.h
	gcc -c semafori.c -o semafori.o

clean:
	rm -f *.o
	rm -f semafori
