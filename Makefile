excBinaryFile: main.o binaryFile.o bst.o bstNode.o
    g++ $@ $^

.PHONY: clean

clean: SHELL := /bin/bash
clean:
    @if [ -a excBinaryFile]; then rm -v excBinaryFile; fi
    @if [ -a main.o ]; then rm -v main.o; fi
    @if [ -a binaryFile.o ]; then rm -v binaryFile.o; fi
    @if [ -a bst.o ]; then rm -v bst.o; fi
    @if [ -a bstNode.o ]; then rm -v bstNode.o; fi
