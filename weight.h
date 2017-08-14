#ifndef _WEIGHT_H_
#define _WEIGHT_H_
#include<vector>
#include<string>

namespace WEIGHT{
std::vector<vector<long double>> fromFile(string file)
std::vector<vector<long double>> simplexLattice(int popLen);
std::vector<vector<long double>> uniformDesign(int popLen);
std::vector<vector<long double>> randomPoints(int popLen);
std::vector<vector<long double>> generalizedDecomp(int popLen);
std::vector<vector<long double>> twoLayerWeight(int popLen);
}
#endif
