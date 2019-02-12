CC = gcc
BIN = cssg

$(BIN) : main.c
	$(CC) $^ -o $@

check:
	./$(BIN) test.txt

clean:
	rm $(BIN)
