import math
import io 
import sys 
sys.stdout=io.TextIOWrapper(sys.stdout.buffer,encoding='utf8')

p=int(input('p:'))
prime_factors=[]
a=[] #原根
def getfactor(n):   #求素因数
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
getfactor(p-1)

for g in range(2,p):    #求原根g
    flag=1
    for i in range(0, len(prime_factors)):
        if ( g**( (p-1)//prime_factors[i] ) ) %p==1:
            flag=0
            break
    if flag!=0:
        a.append(g)
        break

for g in range(2,p):   #求所有原根
    flag=1
    for i in range(0, len(prime_factors)):
        if g%prime_factors[i]==0:
            flag=0
            break
    if flag!=0:
        a.append(  (a[0]**g)%p   )
print(a)