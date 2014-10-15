CC = gcc
OBJ = primes.o 
FLAGS = -Wall -std=c99 -g -o
LIB = -lpthread

primes: $(OBJ)
	$(CC) $(OBJ) $(LIB) $(FLAGS) $@

.c.o:
	$(CC) -g -c $<

clean:
	rm *.o primes 
