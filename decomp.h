#ifndef _DECOMP_H_
#define _DECOMP_H_
#include<vector>
namespace DECOMP{
long double scalar_tcheby(std::vector <long double> &fit, std::vector<long double> &pesos,std::vector<long double> &ideal);
long double scalar_NormalTcheby(std::vector <long double> &fit, std::vector<long double> &pesos,std::vector<long double> &ideal);
long double scalar_PBI(std::vector <long double> &fit, std::vector<long double> &pesos,std::vector<long double> &ideal);
long double scalar_IPBI(std::vector <long double> &fit, std::vector<long double> &pesos,std::vector<long double> &nadir);
long double innerproduct(std::vector <long double>&vec1, std::vector <long double>&vec2);
long double norm_vector(std::vector <long double> &x);
}
#endif
