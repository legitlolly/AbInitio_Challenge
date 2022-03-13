# Makefile

EXE=Solution

CC=gcc
CFLAGS= -std=c99
LIBS = -lm

all: $(EXE)

$(EXE): $(EXE).c
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	rm -f $(EXE)

run:
	./$(EXE)


