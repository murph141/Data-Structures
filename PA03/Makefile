GCC = gcc
CFLAGS = -Wall -Werror -Wshadow -ggdb -O3
SOURCES = pa03.c
OBJS = $(SOURCES:.c=.o)
HDRS = pa03.h
EXECUTABLE = proj3
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose
LATEX = WriteUp

.PHONY: all clean test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -rf *.o $(EXECUTABLE) output ${LATEX}.{pdf,aux,log}

test: all
	$(VALGRIND) ./$(EXECUTABLE) input output

latex: $(LATEX).tex
	pdflatex $(LATEX)
