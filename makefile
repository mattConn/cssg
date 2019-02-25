CC = gcc
BIN = cssg
# no def. flags; pass as cli arg
FLAGS = 

$(BIN) : main.c global.c parsefile.c strstack.c
	$(CC) $^ $(FLAGS) -o $@

check:
	./$(BIN) testfiles/test.txt

clean:
	rm $(BIN)
