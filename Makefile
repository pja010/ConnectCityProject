CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

EXECS = connect_city optimized_connect_city

all: $(EXECS)

connect_city: connect_city.c

connect_city2: optimized_connect_city.c

.PHONY: clean
clean:
	/bin/rm -rf $(EXECS)

