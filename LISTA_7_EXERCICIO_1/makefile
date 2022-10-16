#	Projeto
PROJ = l7e1

#	Compilador
CC = g++

#	.cc
C_SOURCE = $(PROJ).yy.cc

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