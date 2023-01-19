CC=c++
CFLAGS=-std=c++11
SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp, %.o, $(SRC))

.PHONY: clean test
program: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
%.o: %.h
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
test:
	./program --test
clean:
	rm -rf *.o program
