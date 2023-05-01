# #	Projeto
# PROJ = regalloc

#	.c
SOURCES = $(wildcard *.cc)
#	.h
HEADERS = $(wildcard *.h)
#	.o
# OBJECTS = $(patsubst %.cc, %.o, $(SOURCES))

# #	Compilador
# CC = g++

# #	Flags
# CC_FLAGS = -fstack-protector-all	\
# 		   -fstack-check			\
# 		   -std=c++11				\
# 		   -I.					 	\
# 		   -Wall					\
# 		   -g

# #	Linkagem dos arquivos .o
# $(PROJ): $(OBJECTS) $(HEADERS)
# 	$(CC) -o $@ $^

# # Compilação de cada arquivo .c em .o
# %.o: %.cc %.h
# 	$(CC) $< $(CC_FLAGS) -o $@

# #	Remove os arquivos .o
# clean:
# 	rm -f *.o
# 	rm -f regalloc

regalloc: $(SOURCES) $(HEADERS)
	g++ -std=c++11 -Wall -g -fstack-protector-all -fstack-check -I. -o regalloc *.cc