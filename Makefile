# Makefile for fiz

CC=gcc
CXX=c++

CFLAGS= -g
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

lex.yy.o: fiz.l y.tab.hh
	$(LEX) fiz.l
	$(CC) $(CFLAGS) -c lex.yy.c

y.tab.o: fiz.y
	$(YACC) -d fiz.y -o y.tab.cc
	$(CC) $(CFLAGS) -c y.tab.cc

cfiles:
	$(CXX) $(CFLAGS) -c func.cc
	$(CXX) $(CFLAGS) -c ast.cc
	$(CXX) $(CFLAGS) -c eval.cc
	$(CXX) $(CFLAGS) -c resolve.cc

fiz: y.tab.o lex.yy.o cfiles
	$(CC) -o fiz lex.yy.o y.tab.o func.o ast.o eval.o resolve.o $(LFL)

test: fiz
	-mocha --reporter nyan

cleantmp:
	rm -f lex.yy.c y.tab.c y.tab.h *.o

clean: cleantmp
	rm -f fiz
