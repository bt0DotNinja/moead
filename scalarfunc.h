#ifndef __SCALARFUNC_H_
#define __SCALARFUNC_H_

namespace SCALAR{
// scalarizing functions for decomposition methods
double scalar_tcheby(vector <long double> &y_obj, vector <long double> &namda, TIndividual* nbi_node);
double scalar_NormalTcheby(vector <long double> &y_obj, vector <long double> &namda, TIndividual* nbi_node);
double scalar_PBI(vector <long double> &y_obj, vector <long double> &namda, TIndividual* nbi_node);
}


#endif
