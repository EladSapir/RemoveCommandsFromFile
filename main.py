""""
import random
n=input('insert n:')
def randX(n):
    for x in range(0,n):
        print(f'{random.randint(0, 257):08b}')
randX(int(n))
"""

"""
def numbers(x):
    s=set(str(x))
    s.remove('.')
    print(s)
numbers(3.2522)
"""

"""
def power(n):
    for i in range(n):
        if(i*i==n):
            print(i)
power(25)
"""

"""tirgul 3"""

"""
def integral(a,b,f):
    x=0
    for i in range (0,1000):
        x=x+(((b-a)/1000)*f(a+i*((b-a)/1000)))
    return x

def f1(x):
    return 3*x
print(integral(-1,100,f1))
"""



















