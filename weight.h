#ifndef _WEIGHT_H_
#define _WEIGHT_H_
#include<vector>
#include<string>

namespace WEIGHT{
std::vector<std::vector<long double>> fromFile(std::string file);
std::vector<std::vector<long double>> simplexLattice(int popLen);
std::vector<std::vector<long double>> uniformDesign(int popLen);
std::vector<std::vector<long double>> randomPoints(int popLen);
std::vector<std::vector<long double>> generalizedDecomp(int popLen);
std::vector<std::vector<long double>> twoLayerWeight(int popLen);
}
#endif
