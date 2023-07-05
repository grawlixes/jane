# Make just the base program. 
run: clean main 

all: clean main2

main: main.o
	g++ -std=c++17 -O4 main.o -o main

main2:
	g++ -std=c++17 -O4 -Wall -Wextra -pedantic -c main.cpp
	g++ -std=c++17 -O4 -Wall -Wextra -pedantic -c main2.cpp
	g++ -std=c++17 -O4 -Wall -Wextra -pedantic -c main3.cpp
	g++ -std=c++17 -O4 -Wall -Wextra -pedantic -c main4.cpp
	g++ -std=c++17 -O4 main.o -o main
	g++ -std=c++17 -O4 main2.o -o main2
	g++ -std=c++17 -O4 main3.o -o main3
	g++ -std=c++17 -O4 main4.o -o main4

main.o:
	g++ -std=c++17 -O4 -Wall -Wextra -pedantic -c main.cpp

# Cleans object and binary files
clean:
	rm -f *.o main main2 main3 main4
