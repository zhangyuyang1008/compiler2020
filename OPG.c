#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
//�ļ�ָ��
FILE * fd;

//���봮 
char T[1010]; 

//�������
char charNow;

//����ջ
char S[1010];


//���ȹ�ϵ���� 
int priority[7][7]; 

//��ʼ�����ȹ�ϵ����  ���ڣ�2��С�ڣ�1�����ڣ�0��������=-1 
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

//����������ȹ�ϵ�����е��±� 
int index(char c){
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

//ջ����ջ����бȽϵķ���
char cmp; 


//ջ��Ԫ�ظ���
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
 
 
//��������
void getopg(){
	//��ʼ���õ��ı��� 
	s=0;
	int i=0;
	memset(S,0,sizeof(char)*1009);
	memset(T,0,sizeof(char)*1009);
	fgets(T,1009,fd);	//����뻻�з�
	push('#');
	T[strlen(T)]='#';
	//ȥ�����з� 
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
		if(index(charNow)==-1){
			//���ڲ���ʶ��ķ��� 
			printf("E\n");
			exit(0);
		}
		else if(priority[index(cmp)][index(charNow)]==-1){
			//�����޷��Ƚ����ȼ������ 
			printf("E\n");
			exit(0);
		}
		else{
			//�����������Լ�ض��� 
			if(priority[index(cmp)][index(charNow)]==1||priority[index(cmp)][index(charNow)]==0){
				//�����ȼ���ϵΪ<��= 
				push(charNow);
				printf("I%c\n",charNow);
			}
			else{
				//�����ȼ�Ϊ>�����й�Լ
				char y=charNow;
				while(true){
					char x=pop();
					if(x=='N') continue;
					if(priority[index(x)][index(y)]==2||priority[index(x)][index(y)]==0){
						y=x;
						continue;
					}
					if(priority[index(x)][index(y)]==1){
						push(x);
						//�ɹ���Լ 
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

//main���� 
//int main(int argc,char *argv[]) {
//    fd = fopen(argv[1],"r");
//    //��ʼ�����ȹ�ϵ����
//	init_priority();
//    while(!feof(fd)){
//        getopg();
//    }
//    fclose(fd);
//    return 0;
//}

int main() {
    fd = fopen("test.txt","r");
    //��ʼ�����ȹ�ϵ����
	init_priority();
    while(!feof(fd)){
        getopg();
    }
    fclose(fd);
    return 0;
}
