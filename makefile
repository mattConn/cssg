CC = gcc
BIN = cssg
FLAGS = -D VERSION=\"v0.1.1\" -D BUILD_DATE=\"$$(date +%m/%d/%Y)\"

$(BIN) : main.c global.c parsefile.c strstack.c
	$(CC) $^ $(FLAGS) -o $@

check:
	./$(BIN) testfiles/test.txt

clean:
	rm $(BIN)
