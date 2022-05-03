# Make just the base program. 
run: clean main 

main: main.o
	g++ -std=c++11 -O4 main.o -o main

main.o:
	g++ -std=c++11 -O4 -Wall -Wextra -pedantic -c main.cpp

# Cleans object and binary files
clean:
	rm -f *.o main
