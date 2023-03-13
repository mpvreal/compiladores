FLEX=flex
BISON=bison
CC=g++
CFLAGS=
LIBS=

PROGRAMA = gerador
LEXICO = lexico.l
SINTATICO = sintatico.y

CC_FLAGS = -std=c++11				\
		   -I.						\
		   -w

$(PROGRAMA): $(LEXICO) $(SINTATICO)
	$(FLEX) -o lex.yy.cc $(LEXICO)
	$(BISON) -o sintatico.yy.cc -d $(SINTATICO)
	$(CC) *.cc $(CC_FLAGS) -o $(PROGRAMA)

debug: $(LEXICO) $(SINTATICO)
	$(FLEX) -d -o lex.yy.cc $(LEXICO)
	$(BISON) -v -t -Wcounterexamples -o sintatico.yy.cc -d $(SINTATICO)
	$(CC) *.cc $(CC_FLAGS) -g -o $(PROGRAMA)

clean:
	rm -f lex.yy.cc sintatico.yy.cc sintatico.tab.cc sintatico.yy.hh sintatico.tab.h $(PROGRAMA)
	rm -f lexico.exe lexico