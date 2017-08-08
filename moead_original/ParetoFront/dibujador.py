#!/usr/bin/env python3
# Alberto Rodriguez Sanchez 
import matplotlib
import sys
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

import pandas as pd


matplotlib.style.use('ggplot') # Look Pretty

if __name__ == '__main__':
    assert len(sys.argv) > 1, "Argumentos insuficientes"
    try:
        dataset = pd.read_csv(sys.argv[1],sep=' ',header=None)
        print(dataset.head())
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        ax.set_xlabel('F1')
        ax.set_ylabel('F2')
        ax.set_zlabel('F3')
        ax.scatter(dataset[0], dataset[2], dataset[4], c='r', marker='.')
        plt.show()
    except IOError as e:
        print("I/O error({0}):{1}".format(e.errno,e.strerror))

    

# If the above line throws an error, use plt.style.use('ggplot') instead








