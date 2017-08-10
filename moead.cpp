#include <vector>
#include <cmath>
//TODO #include <gurobi_c++.h>
#include "moead.h"

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
	std::vector<std::vector<long double>> B;
	std::vector<long double> tmp;
	for(int i=0;i<popLen;i++){
		for(int j=0;j<popLen;
	}
		
	return B;
}
std::vector<vector<long double>> MOEAD::initFile(int popLen, int dim){
	std::vector<std::vector<long double>> B(popLen,vector<long double>(dim,1.0e30));
	return f;	
}
std::vector<std::vector<long double>> MOEAD::isBetter(std::vector<std::vector<long double>> &sons,std::vector<std::vector<long double>> &B, int, std::function<std::vector<long double>(std::vector<long double> &)>);
std::vector<std::vector<long double>> updateFile(std::vector<std::vector<long double>&,std::vector<std::vector<long double>> &);

