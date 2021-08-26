CC = g++
VERSION = -std=c++2a
OBJ = main.o
HEADER = Header/filesys.h Header/predicates.h
FILE = Files/file.txt
CFLAGS = -IHeader -Wall

start: $(OBJ) $(HEADER)
	./build/main ${FILE}

main.o: Source/main.cpp $(HEADER)
	$(CC) $(VERSION) $(CFLAGS) Source/main.cpp -o Build/main
