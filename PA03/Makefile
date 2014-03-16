GCC = gcc
CFLAGS = -Wall -Werror -Wshadow -Wbad-function-cast -ggdb
SOURCES = packing.c main.c
OBJS = $(SOURCES:.c=.o)
HDRS = packing.h
EXECUTABLE = proj3
LOGFILE = log
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose --log-file=$(LOGFILE)
LATEX = WriteUp

.PHONY: all clean test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

test: all
	$(VALGRIND) ./$(EXECUTABLE) input output

latex: $(LATEX).tex
	pdflatex $(LATEX)

clean:
	rm -rf *.o $(EXECUTABLE) output ${LATEX}.{pdf,aux,log} $(LOGFILE)
