#!/usr/bin/env python3
# Alberto Rodriguez Sanchez 2017


from itertools import product
import numpy as np
import sys

def simplexLattice(H,dim):
    ''' 
    Multi-layered Simplex-lattice Design
    K. Li et al. (2014), "An Evolutionary Many-Objective Optimization
    Algorithm Based on Dominance and Decomposition",
    IEEE Trans. Evol. Comp. 19(5):694-716, 2015. DOI: 10.1109/TEVC.2014.2373386
    ''' 
    ref=np.arange(float(H)+1)
    ref /= H
    
    result = []
    #External Layer
    for item in product(ref,repeat=dim-1):
        s = np.sum(item)
        tmp = 1.0 - s
        if tmp<0.0:
            continue
        if tmp+s==1.0:
            item=list(item)
            item.append(tmp) 
            result.append(item)
    
    
    return result

def mlsimplexLattice(H1,H2,dim,sf):
    ''' 
    Multi-layered Simplex-lattice Design
    K. Li et al. (2014), "An Evolutionary Many-Objective Optimization
    Algorithm Based on Dominance and Decomposition",
    IEEE Trans. Evol. Comp. 19(5):694-716, 2015. DOI: 10.1109/TEVC.2014.2373386
    ''' 
    
    B=simplexLattice(H1,dim) 
    I=simplexLattice(H2,dim) 
    
    for i in range(len(I)):
        for j in range(dim):
            I[i][j]=((1.0-sf)/dim)+(sf*I[i][j])

    B.extend(I)
    return B
    

if __name__=='__main__':
    assert len(sys.argv) > 4, "Argumentos insuficientes: H1 H2 dim resultfile"
    result = mlsimplexLattice(int(sys.argv[1]),int(sys.argv[2]),int(sys.argv[3]),float(sys.argv[4]))
    np.savetxt(sys.argv[5],np.c_[result],fmt='%.10f', header=str(len(result))+' '+sys.argv[3])
    
