SRC=src
BIN=bin
INCLUDE=include

CC=g++
CXXFLAGS=-Wall -Wextra -std=c++17 -pedantic -I$(INCLUDE) -MMD -MP

src=$(wildcard $(SRC)/*.cc)
bin=$(patsubst $(SRC)/%.cc, $(BIN)/%, $(src))

# build targets
all: $(bin)

# build rules
$(BIN)/%: $(SRC)/%.cc
	$(CC) $(CXXFLAGS) -o $@ $< -lstdc++fs

-include $(patsubst $(SRC)/%.cc, $(BIN)/%.d, $(src))

# clean rule
.PHONY: clean

clean:
	rm -f $(BIN)/*
