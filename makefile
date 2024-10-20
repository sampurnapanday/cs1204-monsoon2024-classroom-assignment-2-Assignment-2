default: main.out

main.out: main.cpp
	g++ main.cpp -o main.out

clean:
	rm -f main.out

