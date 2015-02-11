# Makefile for fiz

CC=gcc

CFLAGS= -std=gnu99 -g
LEX=flex
YACC=yacc
LFL=-lfl

# OS detection, since -lfl on OS X is -ll
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LFL = -ll
endif


all: fiz cleantmp test

noclean: fiz test

lex.yy.o: fiz.l y.tab.h
	$(LEX) fiz.l
	$(CC) $(CFLAGS) -c lex.yy.c

y.tab.o: fiz.y
	$(YACC) -d fiz.y
	$(CC) $(CFLAGS) -c y.tab.c

cfiles:
	$(CC) $(CFLAGS) -c func.c
	$(CC) $(CFLAGS) -c ast.c
	$(CC) $(CFLAGS) -c eval.c
	$(CC) $(CFLAGS) -c resolve.c

fiz: y.tab.o lex.yy.o cfiles
	$(CC) -o fiz lex.yy.o y.tab.o func.o ast.o eval.o resolve.o $(LFL)

test: fiz
	-mocha --reporter nyan

cleantmp:
	rm -f lex.yy.c y.tab.c y.tab.h *.o

clean: cleantmp
	rm -f fiz
