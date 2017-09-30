#!/usr/bin/env python3
# Alberto Rodriguez Sanchez 2017

from fractions import gcd
import itertools as it
import numpy as np
from scipy.linalg import norm
from scipy.linalg import hadamard
from scipy.optimize import minimize
import sys

def generalizedDecomp(referenceParetoSet, fun):
    '''
    Generalized decomposition
    Giagkiozis, I., Purshouse, R. C., & Fleming, P. J. (2013, March). "Generalized decomposition".
    In International Conference on Evolutionary Multi-Criterion Optimization (pp. 428-442). 
    Springer, Berlin, Heidelberg.
    '''
    result=[]
    cons=({'type': 'eq', 'fun' : lambda x: np.array(x).sum() - 1, 'jac':lambda x: 0  })
    H=len(referenceParetoSet)
    x0=np.arange(float(H)+1)
    x0 /= H
    for p in referenceParetoSet:
        ref=np.array(fun(p))
        evalfun= lambda x: norm(x*ref, np.Inf)
        w=minimize(evalfun, x0, method='nelder-mead', constraints=cons ,options={'xtol': 1e-8, 'disp': True})
        result.append(w)
    return result

def uniformDesign(N,dim):
    '''
    Uniform Design
    R. Wang, T. Zhang, B. Guo, "An enhanced MOEA/D using uniform directions
    and a pre-organization procedure". Proc. IEEE Congress on Evolutionary
    Computation, Cancun, Mexico, 2013, pp. 2390–2397.
    '''
    def udCD(u,N,dim):
        '''The centered L2-discrepancy'''
        magic = (13.0/12.0)**dim        
        
        s1 = 0
        for k in range(N):
            tmp=1
            for i in range(dim):
                tmp*=2+abs(u[k][i]-0.5)-(abs(u[k][i]-0.5))**2
            s1+=tmp
        
        s1*=(2**(1-dim)/N)
        s2=0
        for k in range(N):
            sp=0
            for j in range(N):
                tmp=1
                for i in range(dim):
                    tmp*=1 + 0.5*(abs(u[k][i]-0.5) + abs(u[j][i]-0.5) - abs(u[k][i] - u[j][i]))
                sp+=tmp
            s2+=sp
        s2*=1/(N**2)

        return abs(magic - s1 + s2)

    def constructUn(h,N,dim):
        '''good lattice point method'''
        u=[]
        for i in range(1,N+1):
            tmp=[]
            for j in range(dim):
                val=(i*h[j])%N
                if val == 0:
                    val=N
                tmp.append(val)
            u.append(tmp)
        return u
    
    noFactors = [x for x in range(1,N) if gcd(x,N)==1]
    comb=it.combinations(noFactors,dim) 
    H=[x for x in comb]
    minl2=10**100
    U=[]
    for h in H:
        candidate=constructUn(h,N,dim)
        for i in range(N):
            for j in range(dim):
                candidate[i][j]=(candidate[i][j]-0.5)/N
        val = udCD(candidate,N,dim)
        if val < minl2:
            minl2=val
            U=candidate
    #Generate weights from U_N(h)
    lbd=[]
    for k in range(len(U)):
        tmp=[]
        for i in range(dim):
            if i == 0:
                val=1-U[k][i]**(1.0/(dim-1))
            elif i < dim-1:
                val=1-U[k][i]**(1.0/(dim-(i+1)))
                for j in range(i):
                    val*=U[k][j]**(1/(dim-(j+1)))
            else:
                val=1
                for j in range(dim-1):
                    val*=U[k][j]**(1/(dim-(j+1)))
            tmp.append(val)
        lbd.append(tmp)
            
    return lbd

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
    for item in it.product(ref,repeat=dim-1):
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
    #assert len(sys.argv) > 4, "Argumentos insuficientes: H1 H2 dim resultfile"
    
    result = simplexLattice(int(sys.argv[1]),int(sys.argv[2]))
    #np.savetxt(sys.argv[5],np.c_[result],fmt='%.10f', header=str(len(result))+' '+sys.argv[3])
    np.savetxt(sys.argv[3],np.c_[result],fmt='%.10f')
    
