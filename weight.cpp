#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include "weight.h" 

/*fast choose function*/
unsigned nChoosek( unsigned n, unsigned k )
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    int result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}


void combination_with_repetiton(int H, int dim, const vector<std::vector<long double>>& result ){
        H--;
	dim--;
	int r=0;
        vector<int> v;
	std::iota(v,v+dim,0);
        while (true){
                for (int i = 0; i < dim; ++i){                //vai um
                        if (v[i] > H){
                                v[i + 1] += 1;
                                for (int k = i; k >= 0; --k){
                                        v[k] = v[i + 1];
                                }
                                //v[i] = v[i + 1];
                        }
                }

                if (v[dim] > 0)
                        break;
                //print_vector(v, bolas, v_sabores);
		for(int i=0;i<dim;i++)
			result[r][i]=(long double) v[i]/(H+1);	
                v[0] += 1;
		r++;
        }
}

/* Simplex Lattice Design
 * I. Das, J. Dennis (1998), "Normal Boundary Intersection - A New Method
 * for Generating the Pareto Surface in Nonlinear Multicriteria Optimization
 * Problems", SIAM J. Optim., 8(3), 631-657. DOI: 10.1137/S1052623496307510
 *
 *
 */
std::vector<vector<long double>> WEIGHT::simplexLattice(int H, int T,int dim){
	int N = nChoosek(H+dim-1,dim-1);
	long double t;
	std::vector<std::vector<long double>> result(N,std::vector<long double> (dim,0));
	combination_with_repetiton(H,dim,result);
	for(int i=N-1;i>=0;i--){
		t=1-std::accumulate(result.begin(),result.end()-1,0);
		if(t<=1)
			result[i][dim-1]=t;
		else:
			result.erase(i);
	}
	return result;
}

/*  Uniform Design
 *  R. Wang, T. Zhang, B. Guo, "An enhanced MOEA/D using uniform directions
 *  and a pre-organization procedure". Proc. IEEE Congress on Evolutionary
 *  Computation, Cancun, Mexico, 2013, pp. 2390–2397.
*/
std::vector<vector<long double>> WEIGHT::uniformDesign(int popLen){



}

std::vector<vector<long double>> WEIGHT::randomPoints(int popLen){
std::vector<std::vector<long double>> result(N,std::vector<long double> (dim,0));

}


std::vector<vector<long double>> WEIGHT::generalizedDecomp(int popLen){
}

/* Multi-layered Simplex-lattice Design
 * K. Li et al. (2014), "An Evolutionary Many-Objective Optimization
 * Algorithm Based on Dominance and Decomposition",
 * IEEE Trans. Evol. Comp. 19(5):694-716, 2015. DOI: 10.1109/TEVC.2014.2373386
*/
std::vector<vector<long double>> WEIGHT::multiLayeredWeight(int popLen){

}

std::vector<vector<long double>> WEIGHT::fromFile(string file){
	int N,dim;
	ifstream in;
	in.open(file,ios_base::in);
	in >> N;
	in >> dim;
	std::vector<std::vector<long double>> result(N,std::vector<long double> (dim,0));
	for(int i=0;i<N;i++)
		for(int j=0;j<dim;j++)
			cin >> result[i][j];
	return result;
}


