#	Projeto
PROJ = cstats

#	Compilador
CC = gcc

#	.cc
C_SOURCE = $(PROJ).yy.c

#	.h
H_SOURCE = $(wildcard *.h)

#	.l
L_SOURCE = $(PROJ).l

#	Flags
CC_FLAGS = -fstack-protector-all	\
		   -fstack-check

#	Compilação e linkagem
$(PROJ): $(C_SOURCE)
	$(CC) $< -o $@ $(CC_FLAGS)

$(C_SOURCE): $(L_SOURCE) $(H_SOURCE)
	flex -o $@ $<