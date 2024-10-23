import io 
import sys 
sys.stdout=io.TextIOWrapper(sys.stdout.buffer,encoding='utf8')
import math
n = 100
prime_numbers = []
num = [1] * (n + 1)  #全标记为1
for i in range(2, int(math.sqrt(n)) + 1):
    if num[i]!=-1:
        for j in range(2*i, n + 1, i):
            num[j] = -1  # 合数标记为-1 
for k in range (2, n+1):
    if num[k]!=-1:
        prime_numbers.append( k ) 
print("500以内的素数有：", prime_numbers)