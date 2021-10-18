CC = g++
VERSION = -std=c++2a
OBJ = LinuxM.o
#HEADER =
BOOST = -I/usr/local/Cellar/boost/1.76.0/include/
#FILE
CFLAGS = -Wall

# I - имена библиотек include
# L - путь к библитекам dylib

start: $(OBJ)
	./main

LinuxM.o:
	$(CC) $(VERSION) $(BOOST) $(CFLAGS) source/main.cpp -o main
