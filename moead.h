#ifndef _MOEAD_H_
#define _MOEAD_H_
#include<vector>
#include<string>

namespace MOEAD{
std::vector<std::vector<long double>> fromFile(std::string file);
std::vector<long double> initIdealReference(int dim);
std::vector<long double> initIdealFixed(int dim);
std::vector<long double> initIdealExact(int dim);
std::vector<long double> updateIdealReference(std::vector<std::vector<long double>> &);
std::vector<long double> updateIdeal(std::vector<std::vector<long double> >&, int, std::vector<long double> &);
std::vector<std::vector<int>> BVector(int, std::vector<std::vector<long double>> &W, int);
std::vector<std::vector<long double>> initFile(int);
long double euclideanDistance(std::vector<long double> &,std::vector<long double> &);
void updateFile(std::vector<std::vector<long double>>&,std::vector<std::vector<long double>> &,std::vector<std::vector<long double>> &,std::vector<std::vector<long double>> &, int);
bool updateNeighborn(std::vector<std::vector<int>> &,std::vector<std::vector<long double>> &,std::vector<std::vector<long double>> &,std::vector<std::vector<long double>> &,std::vector<std::vector<long double>> &, std::vector<long double> &, int,std::function<long double(std::vector<long double> &, std::vector<long double> &, std::vector<long double> &)> );
}
#endif
