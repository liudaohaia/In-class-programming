import math

def getfactor():
    n=int(input("n:"))
    prime_factors=[]
    prime=[]
    num=[1]*(n+1)#全标记为1
    for i in range(2,int(math.sqrt(n))+1 ):
        if num[i]!=-1:
            for j in range(2*i, n+1,i):
                num[j]=-1 #合数标记为-1
    for k in range (2, n+1):
        if num[k]!=-1:
            prime.append( k )
    flag=1
    while flag==1:
        flag=0
        for k in range(0,len(prime) ):
            if n%prime[k]==0:
                flag=1
                prime_factors.append(prime[k])
                n//=prime[k]
                break
    return prime_factors
while True:
    print(getfactor())