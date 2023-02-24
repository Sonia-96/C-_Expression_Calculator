CC=c++
CFLAGS=-std=c++11
SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp, %.o, $(SRC))
MSD_OBJ=main.o expr.o parser.o tests.o cmdline.o
TEST_OBJ=fuzzTest.o expr_gen.o exec.o expr.o

.PHONY: clean test interp print pretty-print doc open
msdscript: $(MSD_OBJ)
	$(CC) $(CFLAGS) $^ -o $@
test_msdscript:$(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $@
%.o: %.h
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
run:
	./msdscript
test:
	./msdscript --test
interp:
	./msdscript --interp
print:
	./msdscript --print
pretty-print:
	./msdscript --pretty-print
clean:
	rm -rf *.o program
doc:
	cd documentation && doxygen
open:
	open documentation/html/index.html
