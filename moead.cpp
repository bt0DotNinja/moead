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
long double MOEAD::scalar_Tcheby(vector <long double> &y_obj, vector <long double> &namda,vector<long double> idealpoint,int numObjetives )
{

	double fvalue = 0;
    
	// Tchebycheff approach
		double max_fun = -1.0e+30;
		for(int n=0; n<numObjectives; n++)
		{
			double diff = fabs(y_obj[n] - idealpoint[n] );
			double feval;
			if(namda[n]==0) 
				feval = 0.00001*diff;
			else
			    feval = diff*namda[n];
			if(feval>max_fun) max_fun = feval;

		}
		
		fvalue = max_fun;
	return fvalue;
}

long double MOEAD::scalar_NormalTcheby(vector <long double> &y_obj, vector <long double> &namda,vector<long double> idealpoint,int numObjetives){
	// normalized Tchebycheff approach
		vector <long double> scale;
		for(int i=0; i<numObjectives; i++)
		{
			long double min = 1.0e+30, max = -1.0e+30;
			for(int j=0; j<numObjectives; j++)
			{
				long double tp = nbi_node[j].y_obj[i];
				if(tp>max) max = tp;
				if(tp<min) min = tp;
			}
			scale.push_back(max-min);
			if(max-min==0) return 1.0e+30;
		}

		long double max_fun = -1.0e+30;
		for(int n=0; n<numObjectives; n++)
		{
			long double diff = (y_obj[n] - idealpoint[n])/scale[n];
			long double feval;
			if(namda[n]==0) 
				feval = 0.0001*diff;
			else
			    feval = diff*namda[n];
			if(feval>max_fun) max_fun = feval;

		}
		fvalue = max_fun;
	return fvalue;
}


long double MOEAD::scalar_PBI(std::vector<long double> &y_obj, std::vector<long double> &namda, std::vector<long double> idealpoint, int numObjetivos){
	//* Boundary intersection approach

		// normalize the weight vector (line segment)
		long double nd = norm_vector(namda);
		for(int i=0; i<numObjectives; i++)
			namda[i] = namda[i]/nd;

		std::vector <long double> realA(numObjectives);
		std::vector <long double> realB(numObjectives);

		// difference beween current point and reference point
		for(int n=0; n<numObjectives; n++)
			realA[n] = (y_obj[n] - idealpoint[n]);

		// distance along the line segment
		double d1 = fabs(innerproduct(realA,namda));

		// distance to the line segment
		for(n=0; n<numObjectives; n++)
			realB[n] = (y_obj[n] - (idealpoint[n] + d1*namda[n]));
		long double d2 = norm_vector(realB);

		fvalue = d1 + 5*d2;

	return fvalue;
}
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
std::vector<vector<long double>> MOEAD::WVector(int popLen,int dim, int tip){

	switch(tip){
		case(0):

			break;
		case(1):
			break;
		case(2):
			break;
		default:
			break;
	}
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

