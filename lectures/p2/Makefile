main: main.o echo.o
	g++ -std=c++14 main.o echo.o -o main

main.o: main.cc echo.h
	g++ -std=c++14 -Wall -g -c main.cc

echo.o: echo.cc echo.h
	g++ -std=c++14 -Wall -g -c echo.cc

.PHONY: clean

clean:
	rm main.o echo.o main
