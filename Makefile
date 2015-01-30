# Makefile for fiz

CC=gcc

CFLAGS= -g
LEX=flex
YACC=yacc
LFL=-lfl

# OS detection, since -ldl on OS X is -ll
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LFL = -ldl
endif
ifeq ($(UNAME_S),Darwin)
	LFL = -ll
endif


all: fiz

lex.yy.o: fiz.l y.tab.h
	$(LEX) fiz.l
	$(CC) -c lex.yy.c

y.tab.o: fiz.y
	$(YACC) -d fiz.y
	$(CC) -c y.tab.c

fiz: y.tab.o lex.yy.o
	$(CC) -o fiz lex.yy.o y.tab.o $(LFL)

clean:
	rm -f lex.yy.c y.tab.c y.tab.h fiz *.o
