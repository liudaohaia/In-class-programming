
import math
import io 
import sys 
sys.stdout=io.TextIOWrapper(sys.stdout.buffer,encoding='utf8')

#拓展欧几里得算法
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
    return  S[j],T[j],R[j]  #S,T,(a,b)
#一次同余式求解
def fuc():
    a=int(input("输入a："))
    b=int(input("输入b："))
    m=int(input("输入m："))
    S,T,gcd_a_m=gcd(a,m)
    if b%gcd_a_m!=0 :
        print("无解")
    else:
        a2=a/gcd_a_m
        b2=b/gcd_a_m
        m2=m/gcd_a_m
        X0,T,gcd_a2_m2=gcd(a2,m2)
        X0%=m2
        X0*=b2
        X0%=m2
        X=[0]*gcd_a_m
        t=0
        while(t<gcd_a_m):
            X[t]=X0+(m/gcd_a_m)*t
            t+=1
    return  [int(num) for num in X]

while True:
    print(fuc())