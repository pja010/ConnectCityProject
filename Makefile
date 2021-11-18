CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

EXECS = project project2

all: $(EXECS)

project: project.c

project2: project2.c

.PHONY: clean
clean:
	/bin/rm -rf $(EXECS)

