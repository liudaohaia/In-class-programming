import math
import io 
import sys 
sys.stdout=io.TextIOWrapper(sys.stdout.buffer,encoding='utf8')

def gcd(a,b):
    j=-1
    S, T, Q, R = ([-1] * 20 for _ in range(4))  #初始化列表
    R[-2] = a
    R[-1] = b
    S[-2] = 1
    S[-1] = 0
    T[-2] = 0
    T[-1] = 1
    R[j+1] = a%b
    Q[j+1] = math.floor( a/b )
    while(R[j+1]!=0):
            j+=1
            R[j+1] = R[j-1]%R[j]
            Q[j+1] = math.floor( R[j-1]/R[j] )
            S[j] = S[j-2]-S[j-1]*Q[j]
            T[j] = T[j-2]-T[j-1]*Q[j]
    print(f"s: {S[j]}  t: {T[j]}  (a,b): {R[j]}")  #S,T,(a,b) //S[j]  T[j]  R[j]

a=int(input("输入a："))
b=int(input("输入b："))
gcd(a,b);