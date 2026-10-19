all: eseguibile

eseguibile: procedure.o main.o
			gcc -o eseguibile procedure.o main.o
 			
procedure.o: procedure.c header.h
			gcc -c procedure.c
			 
main.o: procedure.c header.h
			gcc -c main.c
		
		
			
