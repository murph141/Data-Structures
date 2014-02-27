GCC = gcc
CFLAGS = -Wall -Werror -Wshadow -ggdb
SOURCES = sorting.c sorting_main.c
OBJS = $(SOURCES:.c=.o)
HDRS = pa02.h
EXECUTABLE = proj2
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

.PHONY: all clean test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -rf *.o $(EXECUTABLE) output

test: all
	$(VALGRIND) ./$(EXECUTABLE) input output
