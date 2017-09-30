all: test

test: main.o moead.o pfront.o metrics.o benchmarks.o geneticOperators.o decomp.o 
	g++ -g main.o pfront.o metrics.o benchmarks.o moead.o decomp.o geneticOperators.o -std=c++11 -fopenmp -O3 -lm -o test
moead.o: moead.cpp
	g++ -g -O3 -std=c++11 -c -o moead.o moead.cpp -fopenmp 
main.o: main.cpp
	g++ -g -O3 -std=c++11 -c -o main.o main.cpp
pfront.o: pfront.cpp
	g++ -g -O3 -std=c++11 -c -o pfront.o pfront.cpp -fopenmp 
metrics.o: metrics.cpp
	g++ -g -O3 -std=c++11 -c -o metrics.o metrics.cpp -fopenmp 
geneticOperators.o: geneticOperators.cpp
	g++ -g -O3 -std=c++11 -c -o geneticOperators.o geneticOperators.cpp -fopenmp 
decomp.o: decomp.cpp
	g++ -g -O3 -std=c++11 -c -o decomp.o decomp.cpp -fopenmp 
benchmarks.o: benchmarks.cpp
	g++ -g -O3 -std=c++11 -c -o benchmarks.o benchmarks.cpp -fopenmp 
clean:
	rm *.o test
debug:
	valgrind --leak-check=full --track-origins=yes  ./test 300 10 250 20 4 0 0 0 sp300_dim3.txt resultado.txt
run:
	./test 300 10 250 20 4 0 0 0 sp300_dim3.txt resultado.txt
