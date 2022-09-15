CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
OBJ = main.o 
EXEC = escape


ifdef DEBUG_PRINT
CFLAGS += -D DEBUG
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c macros.h
	$(CC) -c main.c $(CFLAGS)

clean :
	rm -f $(OBJ) $(EXEC)