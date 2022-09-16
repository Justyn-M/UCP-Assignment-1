CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
OBJ = main.o ops.o
EXEC = escape


ifdef DEBUG_PRINT
CFLAGS += -D DEBUG
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c macros.h ops.h
	$(CC) -c main.c $(CFLAGS)

ops.o : ops.c ops.h macros.h
	$(CC) -c ops.c $(CFLAGS)

clean :
	rm -f $(OBJ) $(EXEC)