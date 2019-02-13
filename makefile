CC = gcc
BIN = cssg

$(BIN) : main.c global.c
	$(CC) $^ -o $@

check:
	./$(BIN) testfiles/test.txt

clean:
	rm $(BIN)
