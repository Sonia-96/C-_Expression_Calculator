CC=c++
CFLAGS=-std=c++11
SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp, %.o, $(SRC))

.PHONY: clean
msdscript: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
%.o: %.h
clean:
	rm -r *.o msdscript
