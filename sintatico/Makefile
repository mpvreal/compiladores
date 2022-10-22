FLEX=flex
BISON=bison
CC=gcc
CFLAGS=
LIBS=

PROGRAMA = sintatico
LEXICO = lexico.l
SINTATICO = sintatico.y

CC_FLAGS = -std=c99					\
		   -I.						\
		   -w

$(PROGRAMA): $(LEXICO) $(SINTATICO)
	$(FLEX) $(LEXICO)
	$(BISON) -d $(SINTATICO)
	$(CC) *.c $(CC_FLAGS) -o $(PROGRAMA)

clean:
	rm -f *.c
	rm -f lexico.exe lexico