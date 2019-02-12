CC = gcc
BIN = cssg

$(BIN) : main.c
	$(CC) $^ -o $@

check:
	./$(BIN) testfiles/test.txt

clean:
	rm $(BIN)
