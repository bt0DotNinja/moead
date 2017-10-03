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
#include "decomp.h"
#include "geneticOperators.h"
#include "moead.h"

int main(int argc,char **argv){
	std::vector<std::vector<long double>> pop,pfit,parent,front,W,archivo,archfit;
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
	bool subs;
	if(argc < 11){
		std::cout << "Error, se requieren argumentos" << std::endl;
		std::cout << argv[0] <<" popSize mutRatio generaciones T funcion control semilla  archivoSalida " << std::endl;
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
	int c=std::atoi(argv[8]);
	std::ofstream dst(argv[10]);
	
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
	W=MOEAD::fromFile(argv[9],popLen,dim);
	
	/*for(int i = 0;i<pop.size();i++){
		for(int j = 0;j<pfit[i].size();j++)
			std::cout << pfit[i][j] << " ";
		std::cout << "\n";
	}*/
	

	//control over scalar functions
	std::function<long double(std::vector<long double> &, std::vector<long double> &, std::vector<long double> &)> f2=DECOMP::scalar_PBI;
	switch(c){
		case 0:
			f2=DECOMP::scalar_tcheby;
			break;
		case 1:
			f2=DECOMP::scalar_NormalTcheby;
			break;
		case 2:
			f2=DECOMP::scalar_PBI;
			break;
		case 3:
			f2=DECOMP::scalar_IPBI;
			break;
		case 4:
			f2=DECOMP::scalar_AASF;
			break;
		default:
			break;
	}

	B=MOEAD::BVector(popLen,W,T);	
	archivo=MOEAD::initFile(dim);
	archfit=MOEAD::initFile(dim);

	/******************************************************************************/
	auto startTime = std::chrono::system_clock::now();
	

	do{
		//discutir paralelismo
		//#pragma paralell for private(i)
		for(int i=0;i<popLen;i++){
			r1int=sel(e);
			r2int=sel(e);

			std::vector<std::vector<long double>> child;
			while(r1int==r2int) 
				r2int=sel(e);

			parent[0]=pop[B[i][r1int]];
			parent[1]=pop[B[i][r2int]];
			
			child=GENOPS::sbx(parent[0],parent[1],e);
			child[0]=GENOPS::rmut(child[0],tasaMut,e);
			child[1]=ff(child[0]);

			subs=MOEAD::updateNeighborn(B,W,pop,pfit,child,ideal,i,f2);
			
			if(subs)
				MOEAD::updateFile(archivo,pop,pfit,archfit,i);
				
		}	


		k++;
	}while(k<gen);

	auto endTime = std::chrono::system_clock::now();
	/******************************************************************************/
	std::chrono::duration<double> elapsed_seconds = endTime - startTime;
	tiempo=elapsed_seconds.count();

	front=PFRONT::domOnevsAll(archfit);
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
