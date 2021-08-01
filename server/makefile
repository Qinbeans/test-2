CC = clang++
BUILD = bin
TARG := $(BUILD)
DATE = $(shell date '+%Y-%m-%d' )
TIME = $(shell date '+%H:%M')
FILE := server-$(DATE)
CFLAG := -std=c++17 -Ofast  -I include
LFLAG := -lpthread -lenet

ifeq ($(OS),Windows_NT)
	CC := clang++
	PLAT := Windows
else
	OS = $(shell uname -s)
	ifeq ($(OS), Linux)
		PLAT := Linux
	else
		PLAT := Mac
		CFLAG += -I include
		LFLAG += -L lib/$(PLAT)
	endif
endif


TARG := $(TARG)/$(PLAT)/$(FILE)
OBJ = $(patsubst src/%.cpp,$(BUILD)/$(PLAT)/%.o,$(wildcard src/*.cpp))

all: $(TARG) $(OBJ)

$(TARG):$(OBJ)
	$(CC) -o $(TARG) $(OBJ) $(LFLAG)

$(OBJ): bin/$(PLAT)/%.o:src/%.cpp
	$(CC) -c $(CFLAG) $< -o $@

clean:
	rm $(BUILD)/$(PLAT)/*.o
	rm $(TARG)

init:
	mkdir $(BUILD)/$(PLAT)