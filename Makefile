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
fiz:   y.tab.o lex.yy.o func.o ast.o parser.o fiz.o
	$(CXX) -o fiz *.o $(LFL)
test:  fiz
	mocha --reporter nyan
force: clean fiz
clean:
	rm -f *.yy.* *.tab.* *.o
	rm -f fiz

%.o:      %.cc
	$(CXX) $(CFLAGS) -c $^
y.tab.o:  fiz.y
	$(YACC) -d fiz.y
	$(CXX) $(CFLAGS) -x c++ -c y.tab.c
lex.yy.o: fiz.l y.tab.h
	$(LEX) fiz.l
	$(CXX) $(CFLAGS) -x c++ -c lex.yy.c
