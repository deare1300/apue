#!/bin/make

CC=gcc
CUR_DIR = ${shell pwd}

BIN_DIR=bin
INCLUDE_DIR=include
OBJ_DIR=obj
SRC=src

BINS=main
LDFLAGS=
CP=cp -f
RM=rm -f
MKDIR_P=mkdir -p

SRC=$(wildcard src/*.c)
OBJS=$(SRC:.c=.o)

CFLAGS = -std=c99 -Ideps -Wall -Wno-unused-function -U__STRICT_ANSI__  -I $(CUR_DIR)/$(INCLUDE_DIR)

all:$(BIN_DIR)/$(BINS)


$(BIN_DIR)/$(BINS): $(SRC) $(OBJS)
	$(CC) $(CFLAGS) -o $@  $(OBJS) $(LDFLAGS)

%.o:%.c
	$(CC) $< -c -o $@ $(CFLAGS)

clean:
	$(foreach c, $(BINS), $(RM) $(c);)
	$RM $(OBJ_DIR)/$(OBJS)

install: $(BINS)
	$(foreach c, $(BINS), $(CP) $(c) $(BIN_DIR)/$(c);)

uninstall:
	$(foreach c, $(BINS), $(RM) $(BIN_DIR)/$(c);)

.PHONY: test all clean install uninstall
