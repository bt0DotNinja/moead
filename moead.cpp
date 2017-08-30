#include <vector>
#include <cmath>
//TODO #include <gurobi_c++.h>
#include <queue>
#include <utility>
#include <functional>
#include <algorithm>
#include "pfront.h"
#include "moead.h"

class CompareDist
{
public:
    bool operator()(pair<int,long double> n1,pair<int,long double> n2) {
        return n1.second<n2.second;
    }
};

long double MOEAD::euclideanDistance(std::vector<long double> &a,std::vector<long double> &b){
	long res=0;
	for(int i=0;i<a.size();i++)
		res+=std::pow(a[i] - b[i],2);
	return std::sqrt(res)
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
std::vector<long double> MOEAD::updateIdeal(std::vector<std::vector<long double>> &archivo, int popSize, std::vector<long double> ideal){
	int n = ideal.size();
	std::vector<long double> res=ideal;
	for(int i=0;i<popSize;i++)
		for(int j=0;j<n)
			if(res[j]>archivo[i][j])
				res[i]=archivo[i][j];
	return res;
}
std::vector<vector<int>> MOEAD::BVector(int popLen,std::vector<std::vector<long double>> &W, int T){
	std::vector<std::vector<int>> B;
	for(int i=0;i<W.size();i++){
		priority_queue<pair<int, long double>,vector<pair<int,long double>>,CompareDist> pq;
		std::vector<long double> tmp;
		for(int j=0;j<W.size();j++){
			if(i==j)
				continue;
				
			pair<int,long double> actual(j,euclideanDistance(W[i],W[j]));
			pq.push(actual);
		}
		for(int j=0;j<T;j++){
			tmp.push_back(pq.top().first);
			pq.pop();
		}
		B.push_back(tmp);
		free(pq);
		free(tmp);
	}
		
	return B;
}
std::vector<vector<long double>> MOEAD::initFile(int popLen, int dim){
	std::vector<std::vector<long double>> B(popLen,vector<long double>(dim,1.0e30));
	return B;	
}

void MOEAD::UpdateNeighborn(std::vector<std::vector<long double>> &B, std::vector<std::vector<long double>> &pop,std::vector<long double> &val, std::vector<long double> &ideal, int id, std::function<long double(std::vector<long double> &, std::vector<long double> &)> ff){
	long double f1 = ff(val,ideal);

	for(int i=0;i<B[id].size();i++){
		long double f2=ff(pop[B[id][i]], ideal);
		if(f1<f2)
			pop[B[id][i]]=val;
	}
}

void MOEAD::updateFile(std::vector<std::vector<long double>>&archive,std::vector<std::vector<long double>> &pop,std::vector<std::vector<long double>> &pfit,std::vector<std::vector<long double>> &archfit, int id){

	std::vector<int> index = PFRONT::domIndex(pfit[id], archfit);
	if(!index.empty()){
		for(int i= index.size(); i>=0; i--){
			archive.erase(i);
			archfit.erase(i);
		}
		archive.push_back(pop[id]);
		archfit.push_back(pfit[id]);
	}

}

