SRC=src/
BIN=bin/
CC=gcc
CFLAGS=-W -Wall
EXEC=DFA_DES
GDB=gdb --args


.PHONY: clean


run:
	./$(EXEC) message.txt chiffre.txt chiffres_faux.txt

debug: DES.o init.o main.o
	$(CC) -o -gstabs $(EXEC) $(BIN)*.o
	$(GDB) ./-gstabs message.txt chiffre.txt chiffres_faux.txt

compile: DES.o init.o key.o main.o
	$(CC) -o $(EXEC) $(BIN)*.o

DES.o: $(SRC)DES.c
	$(CC) -o $(BIN)$@ -c $< $(CFLAGS)

init.o: $(SRC)init.c
	$(CC) -o $(BIN)$@ -c $< $(CFLAGS)

key.o: $(SRC)key.c
	$(CC) -o $(BIN)$@ -c $< $(CFLAGS)

main.o: $(SRC)main.c
	$(CC) -o $(BIN)$@ -c $< $(CFLAGS)



clean:
	rm -rf $(BIN)*

mrproper: clean
	rm $(EXEC)
