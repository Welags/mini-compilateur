
CC = gcc
CFLAGS = -Wall -g -Isrc -Iobj

PARSER = tpc
LEXER  = tpc

all : obj bin bin/tpcc

bin/tpcc: obj/tpc.o obj/tpc_lex.o obj/tree.o obj/symbol_table.o obj/generateur_asm.o
	$(CC) -o $@ $^ $(CFLAGS) -lfl

anonymous: _anonymous.o
	gcc -o anonymous _anonymous.o -nostartfiles -no-pie

obj/tpc.o: obj/tpc.c src/tree.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj/tpc_lex.o: obj/tpc_lex.c obj/tpc.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj/tree.o: src/tree.c src/tree.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj/symbol_table.o: src/symbol_table.c src/symbol_table.h src/tree.h
	$(CC) -c -o $@ $< $(CFLAGS)

_anonymous.o: _anonymous.asm
	nasm -f elf64 -o _anonymous.o _anonymous.asm

	
obj/tpc.c obj/tpc.h: src/tpc.y
	bison -d -o obj/tpc.c $<


obj/tpc_lex.c: src/tpc.lex obj/tpc.h
	flex -o obj/tpc_lex.c $<

obj/generateur_asm.o: src/generateur_asm.c src/tree.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj bin:
	mkdir -p obj bin

clean:
	rm -f obj/*.o obj/*.c obj/*.h bin/tpcc
