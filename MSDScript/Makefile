CC = c++
#CFLAGS = -fsanitize=undefined -O2 -g -std=c++14 #what's the meaning of these flags?
CFLAGS = -fsanitize=undefined -fno-sanitize-recover=undefined -std=c++14
#CFLAGS = -std=c++14
#SRC=$(wildcard *.cpp)
#OBJ=$(patsubst %.cpp, %.o, $(SRC))
MSD_OBJ = main.o expr.o parser.o tests.o cmdline.o val.o env.o
TEST_OBJ = fuzzTest.o ExprGen.o exec.o expr.o val.o env.o
GEN_OBJ = ExprGen.o ExprGenTest.o expr.o val.o env.o

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
