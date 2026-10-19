eseguibile: main.o procedure.o monitor_hoare.o
	gcc -o eseguibile  main.o procedure.o monitor_hoare.o

main.o: main.c header.h
	gcc -o main.o -c   main.c

procedure.o: procedure.c header.h
	gcc -o procedure.o -c   procedure.c

monitor.o: monitor_hoare.c monitor_hoare.h
	gcc -o monitor_hoare.o -c   monitor_hoare.c

clean:
	rm -f eseguibile
	rm -f *.o
