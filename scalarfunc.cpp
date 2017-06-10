#include<vector>
#include<cmath>
#include "scalarfunc.h"

// scalarizing functions for decomposition methods
long double scalar_Tcheby(vector <long double> &y_obj, vector <long double> &namda,vector<long double> idealpoint,int numObjetives )
{

	double fvalue = 0;
    
	// Tchebycheff approach
	if(!strcmp(strFunctionType,"_TCH1"))
	{
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
	}
	return fvalue;
}

long double scalar_NormalTcheby(vector <long double> &y_obj, vector <long double> &namda,vector<long double> idealpoint,int numObjetives){
	// normalized Tchebycheff approach
	if(!strcmp(strFunctionType,"_TCH2"))
	{
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
	}
	return fvalue;
}


long double SCALAR::scalar_PBI(vector <long double> &y_obj, vector <long double> &namda, vector<long double> idealpoint, int numObjetivos){
	//* Boundary intersection approach
	if(!strcmp(strFunctionType,"_PBI"))
	{

		// normalize the weight vector (line segment)
		long double nd = norm_vector(namda);
		for(int i=0; i<numObjectives; i++)
			namda[i] = namda[i]/nd;

		vector <long double> realA(numObjectives);
		vector <long double> realB(numObjectives);

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

	}

	return fvalue;
}
