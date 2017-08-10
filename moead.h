#ifndef _MOEAD_H_
#define _MOEAD_H_
#include<vector>

namespace MOEAD{
// scalarizing functions for decomposition methods

std::vector<long double> initIdeal(int dim);
std::vector<long double> updateIdealReference(std::vector<std::vector<long double>> &);
std::vector<long double> updateIdealFixed(std::vector<std::vector<long double>> &);
std::vector<long double> updateIdealExact(std::vector<std::vector<long double>> &);
std::vector<vector<int>> BVector(int popLen, std::vector<std::vector<long double>> &W, int T);
std::vector<vector<long double>> initFile(int popLen);
std::vector<std::vector<long double>> isBetter(std::vector<std::vector<long double>> &sons,std::vector<std::vector<long double>> &B, int, std::function<std::vector<long double>(std::vector<long double> &)>);
std::vector<std::vector<long double>> updateFile(std::vector<std::vector<long double>&,std::vector<std::vector<long double>> &);
long double euclideanDistance(std::vector<long double> &,std::vector<long double> &);
}
#endif
