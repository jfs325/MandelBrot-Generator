STD=--std=c++17 -pthread
GCC=g++
OBJ=obj
BIN=bin

mandelbrot: src/mandelbrot.cpp src/bitMap.cpp
	${GCC} ${STD} -o bin/mandelbrot src/mandelbrot.cpp src/bitMap.cpp

e0.bmp: bin/mandelbrot
	./bin/mandelbrot -2 1 -1.5 1.5 e0.bmp

e1.bmp: bin/mandelbrot
	./bin/mandelbrot -0.5 0 0.3 1.2 e1.bmp

e2.bmp: bin/mandelbrot
	./bin/mandelbrot 0.3 0.4 0.6 0.7 e2.bmp	

e3.bmp: bin/mandelbrot
	./bin/mandelbrot -0.2 0.0 -1.0 -0.9 e3.bmp

e4.bmp: bin/mandelbrot
	./bin/mandelbrot -0.05 -0.01 -1.01 -0.97 e4.bmp	

clean:
	rm -f /bin/mandelbrot
	rm -f e0.bmp
	rm -f e1.bmp
	rm -f e2.bmp
	rm -f e3.bmp
	rm -f e4.bmp

