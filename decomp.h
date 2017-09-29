#ifndef _DECOMP_H_
#define _DECOMP_H_
#include<vector>
namespace DECOMP{
long double scalar_tcheby(std::vector <long double> &, std::vector<long double> &,std::vector<long double> &);
long double scalar_NormalTcheby(std::vector <long double> &, std::vector<long double> &,std::vector<long double> &);
long double scalar_PBI(std::vector <long double> &, std::vector<long double> &,std::vector<long double> &);
long double scalar_IPBI(std::vector <long double> &, std::vector<long double> &,std::vector<long double> &);
long double scalar_AASF(std::vector <long double> &, std::vector<long double> &,std::vector<long double> &);
long double innerproduct(std::vector <long double>&, std::vector <long double>&);
long double norm_vector(std::vector <long double> &);
}
#endif
