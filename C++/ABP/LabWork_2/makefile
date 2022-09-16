#	Makefile
#-Rpass=loop-vectorize
CC = g++
VERSION = -std=c++20

#Project Name
PROJECT_NAME := LabWork_2
OUTPATH = build

OUTPATH := $(abspath $(OUTPATH))
BASEDIR := $(abspath ./)

#OBJ = reader.o
#HEADER = matrix/matrix.hpp
#CFLAGS = -IHEADER -O3 -Rpass=loop-vectorize -mfpmath=sse -ftree-vectorize -fassociative-math -DNDEBUG
CFLAGS = -IHEADER -DNDEBUG -O3

start:
	$(CC) $(VERSION) $(CFLAGS) main.cpp -o $(OUTPATH)/main
	$(OUTPATH)/main

