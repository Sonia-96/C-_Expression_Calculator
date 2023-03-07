CC=c++
CFLAGS=-std=c++14
#SRC=$(wildcard *.cpp)
#OBJ=$(patsubst %.cpp, %.o, $(SRC))
MSD_OBJ=main.o expr.o parser.o tests.o cmdline.o val.o
TEST_OBJ=fuzz_test.o expr_gen.o exec.o expr.o
GEN_OBJ=test_expr_gen.o expr_gen.o expr_gen_test.o expr.o

.PHONY: clean test interp print pretty-print doc open_doc run fuzz_test
msdscript: $(MSD_OBJ)
	$(CC) $(CFLAGS) $^ -o $@
test_msdscript:$(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $@
test_generator:$(GEN_OBJ)
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
	rm -rf *.o msdscript test_msdscript test_generator
doc:
	cd documentation && doxygen
open_doc:
	open documentation/html/index.html
