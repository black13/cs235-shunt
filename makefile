CC = g++
CFLAGS = -g -Wall -std=c++11

default: lab3

lab3: ExpressionManager.o main.o
	$(CC) $(CFLAGS) -o lab3 ExpressionManager.o main.o

ExpressionManager.o: ExpressionManager.cpp ExpressionManager.h ExpressionManagerInterface.h 
	$(CC) $(CFLAGS) -c ExpressionManager.cpp

main.o: main.cpp ExpressionManager.h 
	$(CC) $(CFLAGS) -c main.cpp

clean:
	$(RM) lab3 *.o *.~
