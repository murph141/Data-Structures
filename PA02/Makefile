GCC = gcc
CFLAGS = -Wall -Werror -Wshadow -ggdb -O3
SOURCES = sorting.c sorting_main.c
OBJS = $(SOURCES:.c=.o)
HDRS = pa02.h
EXECUTABLE = proj2
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

.PHONY: all clean test_insert test_select test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -rf *.o $(EXECUTABLE)

# Fix these tests
#
test_insert: all
	$(VALGRIND) ./$(EXECUTABLE) i input seq.txt output.txt

test_select: all
	$(VALGRIND) ./$(EXECUTABLE) s input seq.txt output.txt

test:
	@echo
	@echo "Use make test_insert or make test_select"
	@echo
