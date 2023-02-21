CC=c++
CFLAGS=-std=c++11
SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp, %.o, $(SRC))

.PHONY: clean test doc open
program: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
%.o: %.h
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
run:
	./program
test:
	./program --test
interp:
	./program --interp
print:
	./program --print
pretty-print:
	./program --pretty-print
clean:
	rm -rf *.o program
doc:
	cd documentation && doxygen
open:
	open documentation/html/index.html
