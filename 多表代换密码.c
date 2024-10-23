#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//设置映射表，如果是乱序的字典，需要利用结构体 来构造表 
char map[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
              'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
              'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};
//设置密钥A,B。 
int A[3][3] ={{11,2,19}
			,{5,23,25}
			,{20,7,17}};
int ANI[3][6];
int B[3][1]	={{0}
			,{0}
			,{0}};
//以 n个字母 为1组 
int n=3;	//行数
int N=26;
//上面的自定义----------------------------------------------------
int cols; // 列数 

//求模 N同余的数 
int mod(int x){
	while( x <0 || x > N ){
		x = ( x + N ) % N;
		}
	return x;
}

int S[20], T[20], Q[20], R[20] ;  //初始化欧几里得的数组
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

//求逆元，针对 a x = 1 mod 26 求解
int  ni_fuc(int a){
	int b = 1; 
	int m = N;
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
        int X =S[j];
        
		X%=m2;
        X*=b2;
        X%=m2;
        return  mod(X);	//防止负数 
	}
}

//求逆矩阵
void getnijuzhen(){
	//赋初值 
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			ANI[i][j]=A[i][j];
		}	
	}
	for(int i=0; i<n; i++){
		for(int j=n; j<2*n; j++){
			if(i+n==j){ ANI[i][j]=1; }
			else{ ANI[i][j]=0; }
		}	
	}
		//循环3次，一次一行 
	for(int i=0; i<n; i++){
		int niyuan = ni_fuc( ANI[i][i] ) ;
				
		for( int j=0; j<2*n; j++){
			ANI[i][j] =  mod( niyuan*ANI[i][j] ) ;
		}
		for ( int i2=0; i2<n; i2++){
			if(i2!=i){
				int bei = ANI[i2][i];
				for ( int j=0; j<2*n; j++){
					ANI[i2][j] = mod ( ANI[i2][j]-bei*ANI[i][j] );
				}			
			}
		}
	}
	
} 

//加密 A[3][3] * M[3][1] + B[3][1]  mod N 
int** encode( int **X , int **Y){


	for(int Yj=0; Yj<cols; Yj++){
		int Yi=0;
		for(int i=0; i<n; i++){
			int j=0;
			Y[Yi][Yj] = A[i][j]*X[j][Yj];
			j++;
			for(; j<n; j++){
				Y[Yi][Yj] += A[i][j]*X[j][Yj];
			}
			Y[Yi][Yj] +=B[Yi][Yj];
			Y[Yi][Yj] = mod( Y[Yi][Yj] );
			Yi++;
		}
	}
	
	return Y;
}

//输入明文字符-->明文数字矩阵-->密文数字矩阵-->密文字符 
char* MingToMi( char* ming){
	
	int num=0; 
	for(int i=0; ming[i]!='\n'; i++){
		if(isalpha(ming[i])!=0){
			num++;	//统计字母数量
		}
	}
	char mingwen[num];	//明文字符串 
	//转大写，去空格
	for(int i=0,j=0; ming[i]!='\n' ; i++){
		if (islower((unsigned char)ming[i])) {
    		ming[i] = toupper((unsigned char)ming[i]);
		} 
		if(isalpha(ming[i])!=0){
			mingwen[j]=ming[i];
			j++;
		}
	}
	
	cols = floor(num/n);	

	int **M =  malloc(n * sizeof(int*));	//明文数字矩阵
	for(int i=0; i<n; i++){
		M[i] = malloc(cols * sizeof(int));
	} 
	//明文字符串 转 明文数字矩阵
	int count =0;
	for(int j=0; j<cols; j++){
		for(int i=0; i<n; i++){
			 
			for(int k=0; k<27; k++){
				if(map[k]==mingwen[count]){
					M[i][j]=k;
					count++;
					break;
				}
			}
		} 	
	}	
	//密文数字矩阵
	
	int **C =  malloc(n * sizeof(int*));
	for(int i=0; i<n; i++){
		C[i] = malloc(cols * sizeof(int));
	}
	C=encode( M,C);
	
//	密文字符串 
	char *MI =(char* ) malloc( num*sizeof(char ) );
	//密文数字矩阵 转 密文字符串 
	
	int COUNT =0;
	for(int j=0; j<cols; j++){
		for(int i=0; i<n; i++){
			//字符转数字 
			for(int k=0; k<27; k++){
				if(C[i][j]==k){
					MI[COUNT]=map[k];
					COUNT++;
					break;
				}
			}
		} 	
	}
	MI[COUNT]='\0';
	//释放 M 内存 
	for (int i = 0; i < n; i++) {
        free(M[i]); 
    }
    free(M);
	//释放 C 内存 
	for (int i = 0; i < n; i++) {
        free(C[i]); 
    }
    free(C);
    
	return MI;
}

//解密 A-1[3][3] * （c[3][1] - B[3][1]） mod N 
int** decode( int **X , int **Y){
	
	for(int Yj=0; Yj<cols; Yj++){
		int Yi=0;
		for(int i=0; i<n; i++){
			int j=0;
			Y[Yi][Yj] = ANI[i][j+n] * ( X[j][Yj]-B[Yi][Yj] );
			j++;
			for(; j<n; j++){
				Y[Yi][Yj] += ANI[i][j+n] * ( X[j][Yj]-B[Yi][Yj] ) ;
			}
			Y[Yi][Yj] = mod( Y[Yi][Yj] );
			Yi++;
		}
	}
	return Y;
}

//输入密文字符-->密文数字矩阵-->明文数字矩阵-->明文字符 
char* MiToMing( char *mi){
	getnijuzhen();	//求逆矩阵 
	
	int num=0; 
	for(int i=0; mi[i]!='\n'; i++){
		if(isalpha(mi[i])!=0){
			num++;	//统计字母数量
		}
	}
	char miwen[num];	//密文字符串 
	//转大写，去空格
	for(int i=0,j=0; mi[i]!='\n' ; i++){
		if (islower((unsigned char)mi[i])) {
    		mi[i] = toupper((unsigned char)mi[i]);
		} 
		if(isalpha(mi[i])!=0){
			miwen[j]=mi[i];
			j++;
		}
	}
	
	cols = floor(num/n);	
	
	int **c =  malloc(n * sizeof(int*));	//密文数字矩阵
	for(int i=0; i<n; i++){
		c[i] = malloc(cols * sizeof(int));
	} 
	//密文字符串 转 密文数字矩阵
	int count =0;
	for(int j=0; j<cols; j++){
		for(int i=0; i<n; i++){
			 
			for(int k=0; k<27; k++){
				if(map[k]==miwen[count]){
					c[i][j]=k;
					count++;
					break;
				}
			}
		} 	
	}
	
	//明文数字矩阵
	int **m =  malloc(n * sizeof(int*));
	for(int i=0; i<n; i++){
		m[i] = malloc(cols * sizeof(int));
	}
	m=decode( c,m);
	
//	明文字符串 
	char *MING =(char* ) malloc( num*sizeof(char ) );
	//明文数字矩阵 转 明文字符串 
	
	int COUNT =0;
	for(int j=0; j<cols; j++){
		for(int i=0; i<n; i++){
			//字符转数字 
			for(int k=0; k<27; k++){
				if(m[i][j]==k){
					MING[COUNT]=map[k];
					COUNT++;
					break;
				}
			}
		} 	
	}
	MING[COUNT]='\0';
	//释放 m 内存 
	for (int i = 0; i < n; i++) {
        free(m[i]); 
    }
    free(m);
	//释放 c 内存 
	for (int i = 0; i < n; i++) {
        free(c[i]); 
    }
    free(c);
    
	return MING;
}

int main() {
	char ming[100];	//明文
	char mi[100];	//密文
	while(1){
		printf("\n加密，选择[1]\n");
		printf("解密，选择[2]\n");
		printf("退出，选择[0]\n");
		int choose;
		printf("请输入：");
		scanf("%d",&choose);
		
		char huanhang;
		huanhang=getchar();
		
		switch(choose){
			case 1:
				printf("输入明文：");
				fgets(ming, sizeof(ming), stdin);
				char* MI;
				MI = MingToMi(ming);
				printf("%s",MI);
				free(MI);
		 		break;
		 	case 2:
				printf("输入密文：");
				fgets(mi, sizeof(mi), stdin);
				char* MING;
				MING = MiToMing(mi);
				printf("%s",MING);
		 		free(MING);
				break;
		 	case 0:
		 		break;
			default:
		 		break;	
			}
	}

//	YOUR PIN NO IS FOUR ONE TWO SIX
	return 0;
}
