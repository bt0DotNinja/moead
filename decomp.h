#ifndef _DECOMP_H_
#define _DECOMP_H_
#include<vector>
namespace DECOMP{
long double scalar_tcheby(std::vector <long double> &fit, std::vector<long double> &pesos, int objetivo);
long double scalar_NormalTcheby(std::vector <long double> &fit, std::vector<long double> &pesos, int objetivo);
long double scalar_PBI(std::vector <long double> &fit, std::vector<long double> &pesos, int objetivo);
}
#endif
