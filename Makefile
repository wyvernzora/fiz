# Makefile for fiz
CXX  = c++

CFLAGS = -g

LEX  = flex
YACC = yacc
LFL  = -lfl

# OS detection, since -lfl on OS X is -ll
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LFL = -ll
endif

all:   fiz
fiz:   main.o libfiz.a
	$(CXX) -o fiz main.o libfiz.a $(LFL)
test:  fiz
	mocha --reporter nyan
force: clean fiz
clean:
	rm -f lex.* *.tab.* *.o
	rm -f fiz libfiz.a

libfiz.a: y.tab.o lex.fiz.o func.o ast.o parser.o fiz.o
	ar rvs libfiz.a y.tab.o lex.fiz.o func.o ast.o parser.o fiz.o

%.o:      %.cc
	$(CXX) $(CFLAGS) -c $^
y.tab.o:  fiz.y
	$(YACC) -p fiz -d fiz.y
	$(CXX) $(CFLAGS) -x c++ -c y.tab.c
lex.fiz.o: fiz.l y.tab.h
	$(LEX) -P fiz fiz.l
	$(CXX) $(CFLAGS) -x c++ -c lex.fiz.c
