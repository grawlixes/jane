# Make just the base program. 
run: clean main 

main: main.o
	g++ -O4 -fopenmp main.o -o main -ldl

main.o:
	g++ -O4 -lrt -fopenmp -Wall -Wextra -pedantic -c main.cpp

# Cleans object and binary files
clean:
	rm -f *.o main
