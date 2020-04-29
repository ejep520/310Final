CC			 := g++
CFLAGS		 := 
SOURCES 	 := main.cpp binaryFile.cpp bst.cpp bstNode.cpp customErrorClass.cpp
OBJECTS		 := main.o binaryFile.o bst.o bstNode.o customErrorClass.o

excBinaryFile: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

main.o: main.cpp binaryFile.h bst.h bstNode.h customErrorClass.h
	$(CC) -o $@ -c $< $(CFLAGS)

binaryFile.o: binaryFile.cpp binaryFile.h 
	$(CC) -o $@ -c $< $(CFLAGS)

bst.o: bst.cpp bst.h
	$(CC) -o $@ -c $< $(CFLAGS)	

bstNode.o: bstNode.cpp bstNode.h
	$(CC) -o $@ -c $< $(CFLAGS)

customErrorClass.o: customErrorClass.cpp customErrorClass.h
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean: SHELL := /bin/bash
clean:
	@if [ -a excBinaryFile ]; then rm -v excBinaryFile; fi;
	@if [ -a main.o ]; then rm -v main.o; fi;
	@if [ -a binaryFile.o ]; then rm -v binaryFile.o; fi;
	@if [ -a bst.o ]; then rm -v bst.o; fi;
	@if [ -a bstNode.o ]; then rm -v bstNode.o; fi;
	@if [ -a customErrorClass.o ]; then rm -v customErrorClass; fi;
