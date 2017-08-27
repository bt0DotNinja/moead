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
#include "moead.h"

int main(int argc,char **argv){
	std::vector<std::vector<long double>> pop,pfit,parent,front,W,archivo;
	std::vector<std::vector<int>> B;
	std::random_device rdev{};
	std::mt19937 e{rdev()};
	std::vector<long double> ideal;
	std::vector<long double> ref={11.0,11.0};
	std::vector<long double> onezero={1.0,0};
	std::vector<long double> zeroone={0.0,1};
	long double hyper;
	double tiempo;
	int r1int,r2int,cmp,dim,k=0,sdebug=0;

	parent.resize(2);

	if(argc < 9){
		std::cout << "Error, se requieren argumentos" << std::endl;
		std::cout << argv[0] <<" popSize mutRatio generaciones T funcion control semilla archivoSalida " << std::endl;
		std::cout << " 1 ZDT2" << std::endl;
		std::cout << " 2 ZDT3" << std::endl;
		std::cout << " 3 ZDT6" << std::endl;
		std::cout << " 4 DTLZ2" << std::endl;
		std::cout << " Otro ZDT2" << std::endl;
		return -1;
	}
	double tasaMut=std::atof(argv[2])/100.0;
	int gen= std::atoi(argv[3]);
	int popLen =std::atoi(argv[1]);
	int funObj= std::atoi(argv[5]);
	int T= std::atoi(argv[4]);
	static std::uniform_int_distribution<int> uid(0,popLen-1);
	static std::uniform_int_distribution<int> sel(0,T-1);
	int control=std::atoi(argv[6]);
	int semilla=std::atoi(argv[7]);
	std::ofstream dst(argv[8]);
	
	if(!!control)
		e.seed(semilla);
	
	std::function<std::vector<long double>(std::vector<long double> &)> ff=BENCHMARKS::ZDT2;
	switch(funObj){
		case 2:
			ff=BENCHMARKS::ZDT3;
			dim=2;
			break;
		case 3:
			ff=BENCHMARKS::ZDT6;
			dim=2;
			break;
		case 4:
			ff=BENCHMARKS::DTLZ2;
			dim=3;
			break;
		default:
			dim=2;
			break;
	}
	
	ideal=MOEAD::initIdealFixed(dim);
	pop=BENCHMARKS::genPop(popLen,dim,e);
	pfit=BENCHMARKS::rank(pop,ff);
	//control over weight generation
	switch(c){
		case 0:
			W=WEIGHT::simpleLattice(popLen);
			break;
		case 1:
			W=WEIGHT::uniformDesign(popLen);
			break;
		case 2:
			W=WEIGHT::randomPoints(popLen);
			break;
		case 3:
			W=WEIGHT::generalizedDecomp(popLen);
			break;
		case 4:
			W=WEIGHT::twoLayerWeight(popLen);
			break;
		default:
			W=WEIGHT::simpleLattice(popLen);
			break;
	}

	B=MOEAD::BVector(popLen,W,T);	
	archivo=MOEAD::initFile(popLen);
	/******************************************************************************/
	auto startTime = std::chrono::system_clock::now();
	

	do{
		//discutir paralelismo
		#pragma paralell for private(i)
		for(int i=0;i<popLen;i++){
			r1int=sel(e);
			r2int=sel(e);

			std::vector<long double> childs;
			while(r1int==r2int) 
				r2int=sel(e);
			parent[0]=B[i][r1int];
			parent[1]=B[i][r2int];
			
			childs=GENOPS::sbx(parent[0],parent[1],e);
			childs[0]=GENOPS::rmut(childs[0],tasaMut,e);
			MOEAD::UpdateReference(childs,B,pop,ff);
			pfit=BENCHMARKS::rank(pop,ff);
			MOEAD::UpdateFile(pop,pfit,archivo,ff);

		}	


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
               dst << "\n";
        }

	dst.close();

	std::cout <<std::setprecision(std::numeric_limits<long double>::digits10 + 1);
	std::cout << hyper << " " << tiempo << "s\n";

return 0;
}
