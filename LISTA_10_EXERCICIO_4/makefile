#	Projeto
PROJ = l10e4

#	.c
SOURCES = $(wildcard *.cpp)

#	.h
HEADERS = $(wildcard *.hpp)

#	.o
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

#	Compilador
CC = g++

#	Flags
CC_FLAGS = -fstack-protector-all	\
		   -fstack-check			\
		   -std=c++11

#	Linkagem dos arquivos .o
$(PROJ): $(OBJECTS)
	$(CC) $^ -o $@

# Compilação de cada arquivo .c em .o
%.o: %.cpp %.hpp
	$(CC) -c $< -o $@ $(CC_FLAGS)