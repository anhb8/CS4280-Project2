CC = gcc
CFLAGS = -Wall -g

SRC = scanner.h parser.h lex.h token.h tree.h node.h constant.h

OBJ = scanner.o parser.o tree.o
MASTER_OBJ = main.o

MASTER = frontEnd

OUTPUT = $(MASTER)

all: $(OUTPUT)

%.o: %.c $(STANDARD) $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(MASTER): $(MASTER_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $(MASTER_OBJ) $(OBJ) -o $(MASTER)

clean: 
	rm -f $(OUTPUT) *.o output.log a.out
