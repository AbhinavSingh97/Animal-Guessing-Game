CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = guess
OBJS = guess.o readline.o
all : $(MAIN)

$(MAIN) : $(OBJS) guess.h 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

mytr.o : guess.c guess.h
	$(CC) $(CFLAGS) -c guess.c
	
readline.o : readline.c readline.h
	$(CC) $(CFLAGS) -c readline.c
clean :
	rm *.o $(MAIN) core
