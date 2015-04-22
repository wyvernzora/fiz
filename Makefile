ODIR    = obj
SDIR    = src
HDIR    = inc
TDIR    = tmp
DEBUG   = 3

OUT     = flip
INC     = -Iinc
CFLAGS  = -g
LDFLAGS = -lfl

CXX     = g++
LEX     = flex
YACC    = yacc
ECHO    = /bin/echo
MKDIR   = mkdir -p

# OS detection, since -lfl on OS X is -ll
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDFLAGS = -ll
endif

all: $(OUT)

.PHONY: force
force: clean $(OUT)
	@rm -rf $(TDIR)

# --------------------------------------------------------------------------- #
# Compilation and linking of the httpd executable.                            #
# --------------------------------------------------------------------------- #

SRCS    = $(shell find $(SDIR) -type f -name "*.cc")
OBJS    = $(patsubst $(SDIR)/%.cc, $(ODIR)/%.o,   $(SRCS))
DEPS    = $(patsubst $(SDIR)/%.cc, $(ODIR)/%.dep, $(SRCS))

YACC_O  = $(ODIR)/parser/y.tab.o
LEX_O   = $(ODIR)/parser/lex.fiz.o

.deps: $(DEPS)

$(ODIR)/%.dep: $(SDIR)/%.cc
	@printf "Analyzing  %-25s" $(notdir $<)...
	@$(CXX) $(CFLAGS) -I$(HDIR) -I$(patsubst $(ODIR)/%,$(HDIR)/%,$(@D)) -MM $^ >> .deps
	@printf "\033[1;32mDone!\033[0m\n"

-include .deps

$(OUT): $(OBJS) $(YACC_O) $(LEX_O)
	@printf "Linking    %-25s" $(@F)...
	@$(CXX) $(LDFLAGS) -o $(OUT) $(OBJS) $(YACC_O) $(LEX_O)
	@printf "\033[1;32mDone!\033[0m\n"

$(ODIR)/%.o: $(SDIR)/%.cc
	@printf "Compiling  %-25s" $(notdir $<)...
	@$(MKDIR) $(@D)
	@$(CXX) $(CFLAGS) -DDEBUG=$(DEBUG) -o $@ -c $< -I$(HDIR) -I$(patsubst $(ODIR)/%,$(HDIR)/%,$(@D))
	@printf "\033[1;32mDone!\033[0m\n"

$(YACC_O): $(SDIR)/parser/fiz.y
	@printf "Processing %-25s" $(notdir $<)...
	@$(YACC) -p fiz -d $<
	@$(MKDIR) $(@D)
	@$(CXX) $(CFLAGS) -x c++ -c y.tab.c -Iinc -Iinc/parser -I. -o $@
	@printf "\033[1;32mDone!\033[0m\n"

$(LEX_O): $(SDIR)/parser/fiz.l
	@printf "Processing %-25s" $(notdir $<)...
	@$(LEX) -P fiz $<
	@$(MKDIR) $(@D)
	@$(CXX) $(CFLAGS) -x c++ -c lex.fiz.c -Iinc -Iinc/parser -I. -o $@
	@printf "\033[1;32mDone!\033[0m\n"



# --------------------------------------------------------------------------- #
# Cleanup.                                                                    #
# --------------------------------------------------------------------------- #
.PHONY: clean clean-deps
clean-deps:
	@printf "Cleaning   %-25s" "dependencies"...
	@rm -f .deps
	@printf "\033[1;32mDone!\033[0m\n"

clean: clean-deps
	@printf "Cleaning   %-25s" "binaries"...
	@rm -rf $(ODIR) $(TDIR)
	@rm -f $(OUT)
	@rm -f *.tab.* lex.fiz.c
	@printf "\033[1;32mDone!\033[0m\n"
