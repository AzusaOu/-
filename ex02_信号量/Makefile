CC=main.o copy.o get.o put.o
public: $(CC) public.h   
	gcc $(CC) -o SIGNAL -lpthread   
main.o: main.c public.h   
	gcc -c main.c -lpthread   
copy.o: copy.c public.h   
	gcc -c copy.c   
get.o: get.c public.h   
	gcc -c get.c   
put.o: put.c public.h   
	gcc -c put.c

