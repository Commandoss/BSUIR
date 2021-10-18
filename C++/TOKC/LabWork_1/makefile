#	Makefile

CC = g++
VERSION = -std=c++2a

#Project Name
PROJECT_NAME := SerialPort
OUTPATH = build

OUTPATH := $(abspath $(OUTPATH))
BASEDIR := $(abspath ./)

#OBJ = reader.o
HEADER = SerialPorts/SerialPorts.hpp SerialPorts/SerialPorts.cpp
CFLAGS = -IHEADER -Wall

start: writer.o
	./build/writer

writer.o:
	$(CC) $(VERSION) $(CFLAGS) Source/writer.cpp -o build/writer
	
SerialPortsLib.o
	

#reader.o: main.cpp $(HEADER)
#	$(CC) $(VERSION) $(CFLAGS) main.cpp -o main

