FLAGS= -Wall -Werror -Wextra -g
CC= gcc
OUT= kasm

build: files parser tokens tokenizer assembler
	$(CC) files.o parser.o tokens.o tokenizer.o assembler.o -o $(OUT)

files:
	$(CC) $(FLAGS) -c src/files.c -o files.o

parser:
	$(CC) $(FLAGS) -c src/parser.c -o parser.o

tokens:
	$(CC) $(FLAGS) -c src/tokens.c -o tokens.o

tokenizer:
	$(CC) $(FLAGS) -c src/tokenizer.c -o tokenizer.o

assembler:
	$(CC) $(FLAGS) -c src/assembler.c -o assembler.o

clean:
	rm -f *.o $(OUT)


