# Makefile for fiz

CC=gcc

CFLAGS= -g
LEX=flex
YACC=yacc
LFL=-lfl

# OS detection, since -ldl on OS X is -ll
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LFL = -lfl
endif
ifeq ($(UNAME_S),Darwin)
	LFL = -ll
endif


all: fiz cleantmp

keeptmp: fiz

lex.yy.o: fiz.l y.tab.h
	$(LEX) fiz.l
	$(CC) -c lex.yy.c

y.tab.o: fiz.y
	$(YACC) -d fiz.y
	$(CC) -c y.tab.c

func.o:
	$(CC) -c func.c

ast.o:
	$(CC) -c ast.c

eval.o:
	$(CC) -c eval.c

resolve.o:
	$(CC) -c resolve.c

fiz: y.tab.o lex.yy.o func.o ast.o eval.o resolve.o
	$(CC) -o fiz lex.yy.o y.tab.o func.o ast.o eval.o resolve.o $(LFL)

cleantmp:
	rm -f lex.yy.c y.tab.c y.tab.h *.o

clean: cleantmp
	rm -f fiz
