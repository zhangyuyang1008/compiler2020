#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
//文件指针
FILE * fd;

//输入串 
char T[1010]; 

//读入符号
char charNow;

//符号栈
char S[1010];


//优先关系矩阵 
int priority[7][7]; 

//初始化优先关系矩阵  大于：2，小于：1，等于：0，不存在=-1 
void init_priority(){
	priority[0][0]=2;
	priority[0][1]=1;
	priority[0][2]=1;
	priority[0][3]=2;
	priority[0][4]=1;
	priority[0][5]=2;
	
	priority[1][0]=2;
	priority[1][1]=2;
	priority[1][2]=1;
	priority[1][3]=2;
	priority[1][4]=1;
	priority[1][5]=2;
	
	priority[2][0]=1;
	priority[2][1]=1;
	priority[2][2]=1;
	priority[2][3]=0;
	priority[2][4]=1;
	priority[2][5]=-1;
	
	priority[3][0]=2;
	priority[3][1]=2;
	priority[3][2]=-1;
	priority[3][3]=2;
	priority[3][4]=-1;
	priority[3][5]=-1;
	
	priority[4][0]=2;
	priority[4][1]=2;
	priority[4][2]=-1;
	priority[4][3]=2;
	priority[4][4]=-1;
	priority[4][5]=2;
	
	priority[5][0]=1;
	priority[5][1]=1;
	priority[5][2]=1;
	priority[5][3]=-1;
	priority[5][4]=1;
	priority[5][5]=0;
}

//求算符在优先关系矩阵中的下标 
int index_c(char c){
	int i;
	switch (c){
		case '+': i=0; break;
		case '*': i=1; break;
		case '(': i=2; break;
		case ')': i=3; break;
		case 'i': i=4; break;
		case '#': i=5; break;
		default : i=-1;break;
	}
	return i;
}

//栈内与栈外进行比较的符号
char cmp; 


//栈内元素个数
int s; 

//push
void push(char c){
	S[s]=c;
	s++;
}

//pop
char pop(){
	s--;
	char c=S[s];
	S[s]='\0';
	return c;
}

int cmp_s;
 
 
//分析函数
void getopg(){
	//初始化用到的变量 
	s=0;
	int i=0;
	memset(S,0,sizeof(char)*1009);
	memset(T,0,sizeof(char)*1009);
	fgets(T,1009,fd);	//会读入换行符
	push('#');
	int pos=strlen(T)-2;
	T[pos]='#';
	T[pos+1]='\0';
	//去掉换行符 
	for(i=0;i<strlen(T);i++){
		charNow=T[i];
		cmp_s=s-1;
		cmp=S[cmp_s];
		if(charNow=='#'&&cmp!='N'&&cmp!='i'&&cmp!=')'){
			printf("RE\n");
			return;
		}
		while(cmp=='N'){
			cmp_s--;
			cmp=S[cmp_s];
		} 
		if(cmp=='#'&&charNow=='#') return;
		if(index_c(charNow)==-1){
			//对于不能识别的符号 
			printf("E\n");
			exit(0);
		}
		else if(priority[index_c(cmp)][index_c(charNow)]==-1){
			//对于无法比较优先级的情况 
			printf("E\n");
			exit(0);
		}
		else{
			//正常情况，规约素短语 
			if(priority[index_c(cmp)][index_c(charNow)]==1||priority[index_c(cmp)][index_c(charNow)]==0){
				//当优先级关系为<或= 
				push(charNow);
				printf("I%c\n",charNow);
			}
			else{
				//当优先级为>，进行规约
				char y=charNow;
				while(true){
					char x=pop();
					if(x=='N') continue;
					if(priority[index_c(x)][index_c(y)]==2||priority[index_c(x)][index_c(y)]==0){
						y=x;
						continue;
					}
					if(priority[index_c(x)][index_c(y)]==1){
						push(x);
						//成功规约 
						printf("R\n");
						i--; 
						push('N');
						break;
					} 
				}
			} 
		} 
		
	}
} 

//main函数 
int main(int argc,char *argv[]) {
    fd = fopen(argv[1],"r");
    //初始化优先关系矩阵
	init_priority();
    while(!feof(fd)){
        getopg();
    }
    fclose(fd);
    return 0;
}

//int main() {
//    fd = fopen("test.txt","r");
//    //初始化优先关系矩阵
//	init_priority();
//    while(!feof(fd)){
//        getopg();
//    }
//    fclose(fd);
//    return 0;
//}
