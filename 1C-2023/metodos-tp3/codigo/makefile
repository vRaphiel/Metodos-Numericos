all: tp3

tp3: main.o
	g++ -g $^ -o $@ -std=c++14 -O3 -Woverflow

main.o: main.cpp main.h
	g++ -g -c $< -o $@ -std=c++14 -O3 -Woverflow
	
.PHONY: clean
clean:
	rm -f *.o
	rm -f tp3