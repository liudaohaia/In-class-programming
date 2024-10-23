import math
import io 
import sys 
sys.stdout=io.TextIOWrapper(sys.stdout.buffer,encoding='utf8')

#形如 x^2=a (mod p) 
#符号 (a/p)
a=int(input("输入整数a："))
p=int(input("输入素数模p："))

def lgd(a,p):
    if a==1:
        return 1
    if a==-1:
        return (-1)**int( (p-1)/2 )
    if a==2: 
        return (-1)**int( (p**2-1)/8 )
    if a>p:
        return lgd(a%p ,p)
    if math.isqrt(a)**2==a:
        return 1
    for i in range (2,a):
        if a% i==0:
            return lgd(i,p) * lgd( int(a/i) ,p)
    return (-1)**int( ((a-1)/2)*((p-1)/2) ) * lgd(p,a)

print(lgd(a,p))