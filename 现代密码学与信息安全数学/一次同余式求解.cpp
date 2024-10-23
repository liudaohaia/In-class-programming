#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int S[20], T[20], Q[20], R[20] ;  //初始化数组

int*  fuc();
int gcd( int a,int b);

//求模 N同余的数 
int mod(int x,int m){
	while( x <0 || x > m ){
		x = ( x + m ) % m;
		}
	return x;
}

int main() {	
	int *X;		//存 解的数组 
	while(1){
		X=fuc();
		if (X == NULL) {
            continue; // 无解时跳过
        }
        
		for(int i=0; X[i]!=-1 ;i++){	//打印 
			printf("%d ", X[i] );
		}
		printf("\n");
		free(X);
	}
	return 0;
}

//拓展欧几里得算法
int gcd( int a,int b){
	int j=1;	
    for(int i=0; i<20; i++){
    	R[i]=-1;						//设置未结束的标记 
	}
	
    R[0] = a;
    R[1] = b;
    S[0] = 1;
    S[1] = 0;
    T[0] = 0;
    T[1] = 1;
    while(R[j]!=0){
    	    j+=1;
            R[j] = R[j-2]%R[j-1];
            Q[j] = (int)floor( R[j-2]/R[j-1] ); //向下取整 
            S[j] = S[j-2]-S[j-1]*Q[j];
            T[j] = T[j-2]-T[j-1]*Q[j];
	}
	return  j-1;
}

//一次同余式求解
int*  fuc(){
	int a,b,m;
	printf("输入a：");
    scanf("%d", &a);
    printf("输入b：");
    scanf("%d", &b);
    printf("输入m：");
    scanf("%d", &m);
	
	int j = gcd(a,m);
	int gcd_a_m = R[j];
	
    if (b%gcd_a_m!=0) {
	    printf("无解");
	    return NULL;
	}
    else{
    	int a2 =a /gcd_a_m;
        int b2 =b /gcd_a_m;
        int m2 =m /gcd_a_m;
        j =gcd(a2,m2);
        int X0 =S[j];
        
		X0= mod(X0,m2);
        X0*=b2;
        X0= mod(X0,m2);
		
	    int* X=(int*)malloc( gcd_a_m*sizeof(int) );
        for (int n = 0; n < gcd_a_m; n++) {
            X[n] = X0 + (m / gcd_a_m) * n;
        }
        	X[gcd_a_m] = -1;
        return  X;
	}
}
