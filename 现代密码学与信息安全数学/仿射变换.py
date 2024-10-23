map = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
              'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
              'U', 'V', 'W', 'X', 'Y', 'Z', '\0']

ch=eval(input("加密1，解密2："))
#定义a，b，N
a=9
b=10
N=26

for i in range(N):
    if (a*i)%N ==1:
        ani=i
        break

if ch==1:
    m=input().upper()
    #thenationalsecurityagency
    sumc=''
    for i in m:
        for j in range (N):
            if map[j]==i:
                c=(j*a+b ) %N
                # 这里加密公式自己写
                sumc=sumc+map[c]
                print(  f'{i}={j}->{c}={map[c]}')
                break
    print(f'm*{a}+{b}  %{N}')
    print('加密为：'+sumc)
elif ch==2:
    c=input().upper()
    #YWPKXYHVKXONPTJCHYBXLPKTB
    summ=''
    for i in c:
        for j in range (N):
            if map[j]==i:
                m=((j-b )*ani) %N
                # 这里解密公式自己写
                summ=summ+map[m]
                print(  f'{i}={j}->{m}={map[m]}')
                break
    print(f'(c-{b})*{ani}  %{N}')
    print('解密为：'+summ)