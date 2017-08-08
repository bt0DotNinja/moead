#!/usr/bin/env python
# Alberto Rodriguez Sanchez 
import pylab
import numpy as np
import sys


if __name__ == '__main__':
    assert len(sys.argv) > 1, "Argumentos insuficientes"
    try:
        pylab.plotfile(sys.argv[1], delimiter=' ', cols=(0, 1),names=('f1', 'f2'))
        pylab.show()
    except IOError as e:
        print "I/O error({0}):{1}".format(e.errno,e.strerror)

    



