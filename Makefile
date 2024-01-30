# Esame di Programmazione C++ 2023/2024 Gennaio
CC = g++
CFLAGS = -Wall -std=c++11

TARGET = main.exe
OBJ = main.o

MAIN = main.cpp
TEMPLATES = set.hpp

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) 

$(OBJ): $(MAIN) $(TEMPLATES)
	$(CC) $(CFLAGS) -c $(MAIN) -o $(OBJ)