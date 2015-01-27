# Makefile for fiz

CC=gcc

CFLAGS= -g
LEX=flex
YACC=yacc

all: fiz

lex.yy.o: fiz.l y.tab.h
	$(LEX) fiz.l
	$(CC) -c lex.yy.c

y.tab.o: fiz.y
	$(YACC) -d fiz.y
	$(CC) -c y.tab.c

fiz: y.tab.o lex.yy.o
	$(CC) -o fiz lex.yy.o y.tab.o -lfl

clean:
	rm -f lex.yy.c y.tab.c y.tab.h fiz *.o

