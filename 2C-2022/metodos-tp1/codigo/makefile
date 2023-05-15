all: tp1

tp1: main.o matriz.o eliminacionGausseana.o
	g++ -g $^ -o $@ -std=c++14 -O3

main.o: main.cpp main.h matriz.h eliminacionGausseana.h
	g++ -g -c $< -o $@ -std=c++14 -O3

matriz.o: matriz.cpp matriz.h
	g++ -g -c $< -o $@ -std=c++14 -O3

eliminacionGausseana.o: eliminacionGausseana.cpp eliminacionGausseana.h matriz.h
	g++ -g -c $< -o $@ -std=c++14 -O3

.PHONY: clean
clean:
	rm -f *.o
	rm -f tp1
