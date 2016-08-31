SRC_FILES = AES128_Wrapper.c
CC_FLAGS = -Wall -Wextra -g -std=c11
LD_FLAGS = -lssl -lcrypto
CC = clang
TARGET = AES128_Wrapper

all:
	    ${CC} ${SRC_FILES} ${CC_FLAGS} ${LD_FLAGS} -o ${TARGET}

.PHONY: clean

clean:
	    rm -f $(TARGET) *.o
