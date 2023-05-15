all: tp3

tp3: main.o matriz.o
	g++ -g -I ./eigen $^ -o $@ -std=c++14 -O3

main.o: main.cpp main.h
	g++ -g -I ./eigen -c $< -o $@ -std=c++14 -O3

matriz.o: matriz.cpp matriz.h
	g++ -g -I ./eigen -c $< -o $@ -std=c++14 -O3

.PHONY: clean
clean:
	rm -f *.o
	rm -f tp3
