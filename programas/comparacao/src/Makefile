default:
	g++ img.cpp -c
	g++ local.cpp -c
	g++ igftt.cpp -c 
	g++ main.cpp -std=c++11 -o compara img.o local.o igftt.o `pkg-config --libs --cflags opencv`

clean:
	rm compara *.o
