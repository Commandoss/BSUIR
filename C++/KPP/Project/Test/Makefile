# This makefile is for running tests test.cpp
#
# For correct operation you need:
#	1. go to catalog ../Project
#	2. register in the console make -f test/makefile
#
# Created by Belousov Ilya on 16.08.21.

CC = g++
VERSION = -std=c++2a
OBJ = test.o
HEADER = Header/filesys.h Header/predicates.h
FILE = Files/file.txt
CFLAGS = -IHeader -Wall

start: $(OBJ) $(HEADER)
	./Build/test --log_level=test_suite
#	./Build/test

test.o: $(HEADER)
	$(CC) $(VERSION) $(CFLAGS) test/test.cpp -o Build/test
