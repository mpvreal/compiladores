#	Projeto
PROJ = l5e2

#	.c
C_SOURCE = $(wildcard *.cpp)

#	.h
H_SOURCE = $(wildcard *.hpp)

#	.o
OBJ = $(C_SOURCE:.cpp = .o)

#	Compilador
CC = g++

#	Flags
CC_FLAGS = -fstack-protector-all	\
		   -g						\
		   -fstack-check

#	Compilação e linkagem
$(PROJ): $(OBJ)
	$(CC) -o $@ $^
	
%.o: %.cpp %.hpp
	$(CC) -o $@ $< $(CC_FLAGS)
	
main.o: *.cpp *.hpp $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)