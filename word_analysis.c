#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//������ַ���
char token[50];

//��ǰ���ڴ�����ַ�
char charNow;

//�ļ�ָ��
FILE * fd;

//��ǰ�����������ֵ
int num;

//��ǰʶ��ĵ��ʵ�����
//ö���ͣ� 

//��ȡһ���ַ�
void get_charNow(FILE *fd){
	charNow=(char)fgetc(fd);
} 

//���token�ַ�����
void clearToken(){
	int i;
    for(i=0;i<50;i++){
        token[i]='\0';
    }
} 

//�жϵ�ǰ���ڴ�����ַ��Ƿ�Ϊ�ո�
bool isSpace(){
    if(charNow == ' '){
        return true;
    }
    return false;
}

//�жϵ�ǰ���ڴ�����ַ��Ƿ�Ϊ����
bool isNewline(){
    if(charNow == '\n' || charNow == '\r'){
        return true;
    }
    return false;
}

//�жϵ�ǰ���ڴ�����ַ��Ƿ�Ϊ�Ʊ��
bool isTab(){
	if(charNow == '\t'){
        return true;
    }
    return false;
}

//�жϵ�ǰ���ڴ�����ַ��Ƿ�Ϊ��ĸ
bool isLetter(){
    if(isalpha(charNow)){
        return true;
    }
    return false;
}

//�жϵ�ǰ���ڴ�����ַ��Ƿ�Ϊ����
bool isDigit(){
    if(isdigit(charNow)){
        return true;
    }
    return false;
}

//�жϵ�ǰ���ڴ�����ַ��Ƿ�Ϊð��
bool isColon(){
    if(charNow==':'){
        return true;
    }
    return false;
} 

//�жϵ�ǰ���ڴ�����ַ��Ƿ�Ϊ�Ӻ� 
bool isPlus(){
    if(charNow=='+'){
        return true;
    }
    return false;
} 

//�жϵ�ǰ���ڴ�����ַ��Ƿ�Ϊ�˺�
bool isStar(){
    if(charNow=='*'){
        return true;
    }
    return false;
} 

//�жϵ�ǰ���ڴ�����ַ��Ƿ�Ϊ����
bool isComma(){
    if(charNow==','){
        return true;
    }
    return false;
} 

//�жϵ�ǰ���ڴ�����ַ��Ƿ�Ϊ������
bool isLParenthesis(){
    if(charNow=='('){
        return true;
    }
    return false;
} 

//�жϵ�ǰ���ڴ�����ַ��Ƿ�Ϊ������
bool isRParenthesis(){
    if(charNow==')'){
        return true;
    }
    return false;
} 

//�жϵ�ǰ���ڴ�����ַ��Ƿ�Ϊ�Ⱥ�
bool isEqual(){
    if(charNow=='='){
        return true;
    }
    return false;
} 

//����ǰ�ַ���token�ַ������е��ַ������� 
void catToken(){
    strcat(token,&charNow);
}

//�����ַ�ָ�����һ���ַ�
void retract(){
    ungetc(charNow,fd);
} 

//���ұ����ֲ���� 
bool reserver(){
    if(strcmp(token,"BEGIN")==0){
        printf("Begin\n");
        return true;
    }
    else if(strcmp(token,"END")==0){
        printf("End\n");
        return true;
    }
    else if(strcmp(token,"FOR")==0){
        printf("For\n");
        return true;
    }
    else if(strcmp(token,"IF")==0){
        printf("If\n");
        return true;
    }
    else if(strcmp(token,"THEN")==0){
        printf("Then\n");
        return true;
    }
    else if(strcmp(token,"ELSE")==0){
        printf("Else\n");
        return true;
    }
    else{
        return false;
    }
}
 
//��token�е��ַ���ת����������ֵ 
void transNum(){
    num=atoi(token); 
}

//������
void error(){
	printf("Unknown\n");
	exit(0);
}

//�ʷ����������㷨
void getsym(){
    clearToken();
    get_charNow(fd);
    while(isSpace() || isNewline() || isTab()){
        get_charNow(fd);
    }
    if(isLetter()){
        while(isLetter()||isDigit()){
            catToken();
            get_charNow(fd);
        }
        retract();
        if(!reserver()){
            printf("Ident(%s)\n", token);
        }
    }
    else if(isDigit()){
        while(isDigit()){
            catToken();
            get_charNow(fd);
        }
        retract();
        transNum();
        printf("Int(%d)\n", num);
    }
    else if(isColon()){
        get_charNow(fd);
        if(isEqual()){
            printf("Assign\n");
        }
        else{
            retract();
            printf("Colon\n");
        }
    }
    else if(isPlus()){
        printf("Plus\n");
    }
    else if(isStar()){
        printf("Star\n");
    }
    else if(isComma()){
        printf("Comma\n");
    }
    else if(isLParenthesis()){
        printf("LParenthesis\n");
    }
    else if(isRParenthesis()){
        printf("RParenthesis\n");
    }
    else{
        if(feof(fd)){
            return;
        }
        error();
    }
}

//main���� 
int main(int argc,char *argv[]) {
    fd = fopen(argv[1],"r");
    while(!feof(fd)){
        getsym();
    }
    fclose(fd);
    return 0;
}

//int main() {
//    fd = fopen("test.txt","r");
//    while(!feof(fd)){
//        getsym();
//    }
//    fclose(fd);
//    return 0;
//}
