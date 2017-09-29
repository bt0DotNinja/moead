#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include "decomp.h"

long double DECOMP::innerproduct(std::vector <long double>&vec1, std::vector <long double>&vec2)
{
    long double sum = 0;
	for(int i=0; i<vec1.size(); i++)
		sum+= vec1[i]*vec2[i];
	return sum;
}

long double DECOMP::norm_vector(std::vector <long double> &x)
{
	long double sum = 0;
	for(int i=0;i<x.size();i++)
        sum = sum + x[i]*x[i];
    return sqrt(sum);
}

long double DECOMP::scalar_tcheby(std::vector <long double> &y_obj, std::vector <long double> &namda,std::vector<long double> &idealpoint)
{

	long double fvalue = 0;
	int numObjectives=y_obj.size();
	// Tchebycheff approach
		double max_fun = -1.0e+30;
		for(int n=0; n<numObjectives; n++)
		{
			double diff = std::fabs(y_obj[n] - idealpoint[n] );
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

long double DECOMP::scalar_NormalTcheby(std::vector <long double> &y_obj, std::vector <long double> &namda,std::vector<long double> &idealpoint){
	// normalized Tchebycheff approach
		int numObjectives=y_obj.size();
		long double fvalue = 0;
		std::vector <long double> scale;
		for(int i=0; i<numObjectives; i++)
		{
			long double min = 1.0e+30, max = -1.0e+30;
			for(int j=0; j<numObjectives; j++)
			{
				long double tp = y_obj[i];
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


long double DECOMP::scalar_PBI(std::vector<long double> &y_obj, std::vector<long double> &namda, std::vector<long double> &idealpoint){
	// Boundary intersection approach
		long double fvalue = 0;
		int numObjectives=y_obj.size();
		// normalize the weight vector (line segment)
		std::vector <long double> nmd(numObjectives);
		long double nd = norm_vector(namda);
		for(int i=0; i<numObjectives; i++)
			nmd[i] = namda[i]/nd;

		std::vector <long double> realA(numObjectives);
		std::vector <long double> realB(numObjectives);

		// difference beween current point and reference point
		for(int n=0; n<numObjectives; n++)
			realA[n] = (y_obj[n] - idealpoint[n]);

		// distance along the line segment
		double d1 = fabs(innerproduct(realA,nmd));

		// distance to the line segment
		for(int n=0; n<numObjectives; n++)
			realB[n] = (y_obj[n] - (idealpoint[n] + d1*nmd[n]));
		long double d2 = norm_vector(realB);

		fvalue = d1 + 5*d2;

	return fvalue;
}
long double DECOMP::scalar_IPBI(std::vector <long double> &y_obj, std::vector<long double> &namda,std::vector<long double> &nadir){
	// Inverted Boundary intersection approach
		long double fvalue = 0;
		int numObjectives=y_obj.size();
		std::vector <long double> nmd(numObjectives);
		// normalize the weight vector (line segment)
		long double nd = norm_vector(namda);
		for(int i=0; i<numObjectives; i++)
			nmd[i] = namda[i]/nd;

		std::vector <long double> realA(numObjectives);
		std::vector <long double> realB(numObjectives);

		// difference beween current point and reference point
		for(int n=0; n<numObjectives; n++)
			realA[n] = (nadir[n] - y_obj[n]);

		// distance along the line segment
		double d1 = fabs(innerproduct(realA,nmd));

		// distance to the line segment
		for(int n=0; n<numObjectives; n++)
			realB[n] = (y_obj[n] - (nadir[n] + d1*nmd[n]));
		long double d2 = norm_vector(realB);

		fvalue = 5*d2 - d1;

}
long double DECOMP::scalar_AASF(std::vector <long double> &y_obj, std::vector<long double> &namda,std::vector<long double> &param){

		int numObjectives=y_obj.size();
		std::vector <long double> realA(numObjectives);
		
		for(int i=0; i<numObjectives; i++)
			realA[i] = y_obj[i]/namda[i];
		
	return *std::max_element(realA.begin(),realA.end()) + param[0]*std::accumulate(realA.begin(),realA.end(),0.0f);
}
