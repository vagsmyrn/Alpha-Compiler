# build tools
CC=gcc
FLEX=flex
BISON=bison
# gcc options
OFLAGS=-Wall -g 

# remove
RM=rm -fr

all:	symtable.o lex.c parser.c icode.o fcode.o
	$(CC) $(OFLAGS) -o compiler symtable.o lex.c parser.c icode.o fcode.o

parser.c: parser.y lex.c
	bison --yacc --defines -v parser.y

lex.c:  lex.l
	$(FLEX) lex.l

fcode.o: fcode.c
	$(CC) $(OFLAGS) -c fcode.c

icode.o: icode.c
	$(CC) $(OFLAGS) -c icode.c

symtable.o: symtable.c
	$(CC) $(OFLAGS) -c symtable.c

clean:
	$(RM) *.o lex.c parser.c parser.h parser.output compiler

