#include <iostream>
#include <cstdio>
#include <fstream>
#include <limits>
#include <iomanip>
#include <sstream>
#include <string>
#include <functional>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include "pfront.h"
#include "metrics.h"
#include "benchmarks.h"
#include "scalarfunc.h"
#include "geneticOperators.h"

int main(int argc,char **argv){
	std::vector<std::vector<long double>> pop,pfit,parent, children,front;
	std::vector<std::vector<std::vector<long double>>> NDS;
	std::random_device rdev{};
	std::mt19937 e{rdev()};
	std::vector<long double> ref={11.0,11.0};
	std::vector<long double> onezero={1.0,0};
	std::vector<long double> zeroone={0.0,1};
	long double hyper,igen;
	double tiempo;
	int r1int,r2int,cmp,k=0,sdebug=0;

	parent.resize(2);

	if(argc < 9){
		std::cout << "Error, se requieren argumentos" << std::endl;
		std::cout << argv[0] <<" popSize mutRatio CrossRatio generaciones funcion control semilla archivoSalida " << std::endl;
		std::cout << " 1 ZDT2" << std::endl;
		std::cout << " 2 ZDT3" << std::endl;
		std::cout << " 3 ZDT6" << std::endl;
		std::cout << " 4 DTLZ2" << std::endl;
		std::cout << " Otro ZDT2" << std::endl;
		return -1;
	}
	double tasaMut=std::atof(argv[2])/100.0;
	double tasaCruza=std::atof(argv[3])/100.0;
	int gen= std::atoi(argv[4]);
	int popLen =std::atoi(argv[1]);
	int funObj= std::atoi(argv[5]);
	static std::uniform_int_distribution<int> uid(0,popLen-1);
	int control=std::atoi(argv[6]);
	int semilla=std::atoi(argv[7]);
	std::ofstream dst(argv[8]);
	
	if(!!control)
		e.seed(semilla);
	
	std::function<std::vector<long double>(std::vector<long double> &)> ff=BENCHMARKS::ZDT2;
	switch(funObj){
		case 2:
			ff=BENCHMARKS::ZDT3;
			break;
		case 3:
			ff=BENCHMARKS::ZDT6;
			break;
		case 4:
			ff=BENCHMARKS::DTLZ2;
			break;
		default:
			break;
	}
	
	pop=BENCHMARKS::genPop(popLen,2,e);
	pfit=BENCHMARKS::rank(pop,ff);

	/******************************************************************************/
	auto startTime = std::chrono::system_clock::now();
	

	do{
	


	k++;
	}while(k<gen);

	auto endTime = std::chrono::system_clock::now();
	/******************************************************************************/
	std::chrono::duration<double> elapsed_seconds = endTime - startTime;
	tiempo=elapsed_seconds.count();

	front=PFRONT::domOnevsAll(pfit);
	std::sort(front.begin(),front.end());
	front.erase( std::unique( front.begin(), front.end() ), front.end() );
	
	hyper=METRICS::hypervol2d(front,ref);

	for(int i=0;i<front.size();i++){
               for(int j=0;j< front[i].size()-1;j++)
                        dst<< front[i][j] << ' ';
               dst << std::endl;
        }

	dst.close();

	std::cout <<std::setprecision(std::numeric_limits<long double>::digits10 + 1);
	

	std::cout << hyper << " " << tiempo << "s" << std::endl;

return 0;
}
