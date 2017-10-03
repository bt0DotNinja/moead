#include <vector>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <functional>
#include <algorithm>
#include "pfront.h"
#include "moead.h"


std::vector<std::vector<long double>> MOEAD::fromFile(std::string file,int N,int dim){
	std::ifstream in;
	in.open(file,std::ios_base::in);
	std::vector<std::vector<long double>> result(N,std::vector<long double> (dim,0));
	for(int i=0;i<N;i++)
		for(int j=0;j<dim;j++)
			in >> result[i][j];
	return result;
}

class CompareDist
{
public:
    bool operator()(std::pair<int,long double> n1,std::pair<int,long double> n2) {
        return n1.second<n2.second;
    }
};

long double MOEAD::euclideanDistance(std::vector<long double> &a,std::vector<long double> &b){
	long double res=0;
	for(int i=0;i<a.size();i++)
		res+=std::pow(a[i] - b[i],2);
	return std::sqrt(res);
}

// scalarizing functions for decomposition methods
std::vector<long double> MOEAD::initIdealReference(int dim){
	std::vector<long double> res(dim);
	for(int i=0;i<dim;i++){
		res[i]=1.0e30;
	}
	return res;
}

std::vector<long double> MOEAD::initIdealFixed(int dim){
	std::vector<long double> res(dim);
	for(int i=0;i<dim;i++){
		res[i]=0.0;
	}
	return res;
}
std::vector<long double> MOEAD::initIdealExact(int dim){
	std::vector<long double> res(dim);
	//GRBEnv env;
        //GRBModel modelo(env);
	//GRBLinExpr obj;
	for(int i=0;i<dim;i++){
		res[i]=1.0e30;
	}
	return res;
}
std::vector<long double> MOEAD::updateIdeal(std::vector<std::vector<long double>> &archivo, int popSize, std::vector<long double>& ideal){
	int n = ideal.size();
	std::vector<long double> res=ideal;
	for(int i=0;i<popSize;i++)
		for(int j=0;j<n;j++)
			if(res[j]>archivo[i][j])
				res[i]=archivo[i][j];
	return res;
}
std::vector<std::vector<int>> MOEAD::BVector(int popLen,std::vector<std::vector<long double>> &W, int T){
	std::vector<std::vector<int>> B;
	std::vector<int> tmp;
	for(int i=0;i<W.size();i++){
		std::priority_queue<std::pair<int, long double>,std::vector<std::pair<int,long double>>,CompareDist> pq;
		for(int j=0;j<W.size();j++){
			if(i==j)
				continue;
				
			std::pair<int,long double> actual(j,euclideanDistance(W[i],W[j]));
			pq.push(actual);
		}
		for(int j=0;j<T;j++){
			tmp.push_back(pq.top().first);
			pq.pop();
		}
		B.push_back(tmp);
		tmp.clear();
	}
		
	return B;
}
std::vector<std::vector<long double>> MOEAD::initFile(int dim){
	std::vector<std::vector<long double>> B(1,std::vector<long double>(dim,1.0e30));
	return B;	
}

bool MOEAD::updateNeighborn(std::vector<std::vector<int>> &B,std::vector<std::vector<long double>> &W,std::vector<std::vector<long double>>&pop, std::vector<std::vector<long double>> &pfit,std::vector<std::vector<long double>> &val, std::vector<long double> &ideal, int id, std::function<long double(std::vector<long double> &, std::vector<long double> &, std::vector<long double> &)> ff){
	
	long double f1 = ff(val[1],W[id],ideal);
	bool flag=false;
	for(int i=0;i<B[id].size();i++){
		long double f2=ff(pfit[B[id][i]], W[id], ideal);
		if(f1<f2){
			pop[B[id][i]]=val[0];
			pfit[B[id][i]]=val[1];
			flag=true;
		}
	}
	return flag;
}

void MOEAD::updateFile(std::vector<std::vector<long double>>&archive,std::vector<std::vector<long double>> &pop,std::vector<std::vector<long double>> &pfit,std::vector<std::vector<long double>> &archfit, int id){
	
	std::vector<int> index;
	index=PFRONT::domIndex(archfit,pfit[id]);
		
	if(!index.empty()){
		if(index[0]!=-1){
			for(int i= index.size()-1; i>=0; i--){
				archive.erase(archive.begin()+i);
				archfit.erase(archfit.begin()+i);
			}	
			archive.push_back(pop[id]);
			archfit.push_back(pfit[id]);
		}
	}
	else{
		archive.push_back(pop[id]);
		archfit.push_back(pfit[id]);

	}
}
