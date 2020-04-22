excBinaryFile: main.o
    g++ $@ $^

.PHONY: clean

clean: SHELL := /bin/bash
clean:
    @if [ -a main.o ]; then rm -v main.o; fi
