CC=main.o fcfs.o rr.o feedback.o
public: $(CC) public.h
	gcc $(CC) -o DIAODU
main.o: main.c public.h
	gcc -c main.c
fcfs.o: fcfs.c public.h
	gcc -c fcfs.c
rr.o: rr.c public.h
	gcc -c rr.c
feedback.o: feedback.c public.h
	gcc -c feedback.c

