CC = gcc
BIN = cssg

$(BIN) : main.c global.c parsefile.c strstack.c
	$(CC) $^ -o $@

check:
	./$(BIN) testfiles/test.txt

clean:
	rm $(BIN)
