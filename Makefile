main.t: main.t.cpp
	g++ -std=c++0x -Wall -o main.t main.t.cpp -Iinclude/ -I. lib/liblua5.1.so -ldl

r:
	./main.t

