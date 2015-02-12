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
	$(LEX) --outfile lex.yy.cc fiz.l
	$(CXX) $(CFLAGS) -c lex.yy.cc

y.tab.o: fiz.y
	$(YACC) -d fiz.y -o y.tab.cc
	$(CXX) $(CFLAGS) -c y.tab.cc

cfiles:
	$(CXX) $(CFLAGS) -c func.cc
	$(CXX) $(CFLAGS) -c ast.cc

fiz: y.tab.o lex.yy.o cfiles
	$(CXX) -o fiz lex.yy.o y.tab.o func.o ast.o $(LFL)

test: fiz
	-mocha --reporter nyan

cleantmp:
	rm -f lex.yy.cc y.tab.cc y.tab.hh *.o

clean: cleantmp
	rm -f fiz
