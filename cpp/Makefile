SRC=src
BIN=bin

CC=g++
CXXFLAGS=-Wall -Wextra -std=c++11 -pedantic

src=$(wildcard $(SRC)/*.cc)
bin=$(patsubst $(SRC)/%.cc, $(BIN)/%, $(src))

all: $(bin)

$(BIN)/%: $(SRC)/%.cc
	$(CC) $(CXXFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm $(BIN)/*
