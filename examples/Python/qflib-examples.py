# qflib library examples

#%%
import qflib as qf
import numpy as np
import os

ver = qf.version()
print(f'qflib version: {ver}')
pid = os.getpid()
print(f'pid: {pid}')

name = "World"
print(qf.sayHello(name))

x = [1, 2, 3]
y = [4, 5]
op = qf.outerProd(x, y)
print(f'x: {x}\ny: {y}')
print(f'outerProd:\n{op}')
