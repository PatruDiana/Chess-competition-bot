CC = g++
CFLAGS = -std=c++11 -Wall

all:
	$(CC) $(CFLAGS) main.cpp -o gicu.out

run:
	"./gicu.out"

clean:
	rm gicu.out
