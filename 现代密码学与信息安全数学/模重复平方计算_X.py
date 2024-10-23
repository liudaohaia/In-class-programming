import math
import io 
import sys 
sys.stdout=io.TextIOWrapper(sys.stdout.buffer,encoding='utf8')

b = int( input("输入底数：") )
n = int( input("输入指数：") )
m = int( input("输入模数：") )
A = []
B = []
N = []
#指数化二进制
while(n!=0):
    N.append( n%2 )
    n = math.floor( n/2 )
k = len(N)
# 求b的n方
B.append(b) #B[0]
A.append( (B[0] ** N[0]) ) #A[0]
i = 1
while(i<k):
    B.append(B[i-1] ** 2)   #B[i]
    B[i]%=m
    A.append( A[i-1] * (B[i] ** N[i]) )     #A[i]
    A[i]%=m
    i+=1
    
print(A[i-1])

