#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int S[20], T[20], Q[20], R[20] ;  //��ʼ������

int*  fuc();
int gcd( int a,int b);

//��ģ Nͬ����� 
int mod(int x,int m){
	while( x <0 || x > m ){
		x = ( x + m ) % m;
		}
	return x;
}

int main() {	
	int *X;		//�� ������� 
	while(1){
		X=fuc();
		if (X == NULL) {
            continue; // �޽�ʱ����
        }
        
		for(int i=0; X[i]!=-1 ;i++){	//��ӡ 
			printf("%d ", X[i] );
		}
		printf("\n");
		free(X);
	}
	return 0;
}

//��չŷ������㷨
int gcd( int a,int b){
	int j=1;	
    for(int i=0; i<20; i++){
    	R[i]=-1;						//����δ�����ı�� 
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
            Q[j] = (int)floor( R[j-2]/R[j-1] ); //����ȡ�� 
            S[j] = S[j-2]-S[j-1]*Q[j];
            T[j] = T[j-2]-T[j-1]*Q[j];
	}
	return  j-1;
}

//һ��ͬ��ʽ���
int*  fuc(){
	int a,b,m;
	printf("����a��");
    scanf("%d", &a);
    printf("����b��");
    scanf("%d", &b);
    printf("����m��");
    scanf("%d", &m);
	
	int j = gcd(a,m);
	int gcd_a_m = R[j];
	
    if (b%gcd_a_m!=0) {
	    printf("�޽�");
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
