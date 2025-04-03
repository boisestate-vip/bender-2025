
# compiler
CC := gcc

# compiler and linker flags
CC_FLAGS := -g
LINKER_FLAGS := -g -lm -lsystemd 

# name of the program
DAEMON_NAME := benderd
CLI_NAME := bender
MAGMA_NAME := magma

# program source files
SRC_FILES := src/communication.c src/base64.c src/gost.c src/util.c
OBJ_FILES := $(SRC_FILES:.c=.o)

all: make_bin $(DAEMON_NAME) $(CLI_NAME) $(MAGMA_NAME)

$(DAEMON_NAME): $(OBJ_FILES) Makefile
	$(CC) $(OBJ_FILES) $(CC_FLAGS) src/benderd.c $(LINKER_FLAGS) -o bin/$@

$(CLI_NAME): $(OBJ_FILES) Makefile
	$(CC) $(OBJ_FILES) $(CC_FLAGS) src/bender.c $(LINKER_FLAGS) -o bin/$@

$(MAGMA_NAME): $(OBJ_FILES) Makefile
	$(CC) $(OBJ_FILES) $(CC_FLAGS) src/magma.c $(LINKER_FLAGS) -o bin/$@

.c.o: 
	$(CC) -c $(CC_FLAGS) $< -o $@ -g

make_bin:
	mkdir -p bin

install:
	cp bin/$(DAEMON_NAME) /usr/sbin && cp bin/$(CLI_NAME) /usr/bin && cp bin/$(MAGMA_NAME) /usr/bin

clean:
	rm -f OBJ_FILES && rm -rf bin
