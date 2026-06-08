FLAGS= -Wall -Werror -Wextra -g
CC= gcc
OUT= kasm
FILES= out/files.o
PARSER= out/parser.o
TOKENS= out/tokens.o
TOKENIZER= out/tokenizer.o
ASSEMBLER= out/assembler.o
O_FILES= $(FILES) $(PARSER) $(TOKENS) $(TOKENIZER) $(ASSEMBLER)

build: files parser tokens tokenizer assembler
	$(CC) $(O_FILES) -o $(OUT)

files:
	$(CC) $(FLAGS) -c src/files.c -o $(FILES)

parser:
	$(CC) $(FLAGS) -c src/parser.c -o $(PARSER)

tokens:
	$(CC) $(FLAGS) -c src/tokens.c -o $(TOKENS)

tokenizer:
	$(CC) $(FLAGS) -c src/tokenizer.c -o $(TOKENIZER)

assembler:
	$(CC) $(FLAGS) -c src/assembler.c -o $(ASSEMBLER)

clean:
	rm -f *.o $(OUT)


