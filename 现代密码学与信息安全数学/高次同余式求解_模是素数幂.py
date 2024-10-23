#形如A[n]*x^n+A[n-1]*x^(n-1)+.....+A[1]*x+A[0]  =  0  (mod p^a)
import math
import io 
import sys 
sys.stdout=io.TextIOWrapper(sys.stdout.buffer,encoding='utf8')

a=int(input("输入模数的幂："))
p=int(input("输入模数的底："))
n=int(input("输入多项式的最高次幂："))
A=[0]*(n+1)
for i in range(n+1):
    A[i]=int(input("输入"+str(i)+"次项的系数："))

def f(x):   #f(x)
    y=0
    for i in range(n+1):
        y+=A[i] * (x**i)
    return y
def inv_f(x): #mod p下 f'(x)的逆元 
    y=0
    i=1
    while i<=n: #f(x)求导   
        y+=i* A[i] * (x**(i-1))
        i+=1
    return pow(y,-1,p)  

X=[0]*(a+1)
t=[0]*(a+1)
for i in range(a):
    if f(i)%p ==0:
        X[1]=i
ai=1
while(ai<a):
    t[ai]=int( -f(X[ai])*inv_f(X[1])/(p**ai) ) % p
    X[ai+1]=( X[ai]+t[ai]*(p**ai) ) % (p**(ai+1))
    ai+=1 
print(X[a])

