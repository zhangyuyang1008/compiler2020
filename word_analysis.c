#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//输入的字符串
char token[50];

//当前正在处理的字符
char charNow;

//文件指针
FILE * fd;

//当前读入的整型数值
int num;

//当前识别的单词的类型
//枚举型？ 

//读取一个字符
void get_charNow(FILE *fd){
	charNow=(char)fgetc(fd);
} 

//清空token字符数组
void clearToken(){
	int i;
    for(i=0;i<50;i++){
        token[i]='\0';
    }
} 

//判断当前正在处理的字符是否为空格
bool isSpace(){
    if(charNow == ' '){
        return true;
    }
    return false;
}

//判断当前正在处理的字符是否为换行
bool isNewline(){
    if(charNow == '\n' || charNow == '\r'){
        return true;
    }
    return false;
}

//判断当前正在处理的字符是否为制表符
bool isTab(){
	if(charNow == '\t'){
        return true;
    }
    return false;
}

//判断当前正在处理的字符是否为字母
bool isLetter(){
    if(isalpha(charNow)){
        return true;
    }
    return false;
}

//判断当前正在处理的字符是否为数字
bool isDigit(){
    if(isdigit(charNow)){
        return true;
    }
    return false;
}

//判断当前正在处理的字符是否为冒号
bool isColon(){
    if(charNow==':'){
        return true;
    }
    return false;
} 

//判断当前正在处理的字符是否为加号 
bool isPlus(){
    if(charNow=='+'){
        return true;
    }
    return false;
} 

//判断当前正在处理的字符是否为乘号
bool isStar(){
    if(charNow=='*'){
        return true;
    }
    return false;
} 

//判断当前正在处理的字符是否为逗号
bool isComma(){
    if(charNow==','){
        return true;
    }
    return false;
} 

//判断当前正在处理的字符是否为左括号
bool isLParenthesis(){
    if(charNow=='('){
        return true;
    }
    return false;
} 

//判断当前正在处理的字符是否为右括号
bool isRParenthesis(){
    if(charNow==')'){
        return true;
    }
    return false;
} 

//判断当前正在处理的字符是否为等号
bool isEqual(){
    if(charNow=='='){
        return true;
    }
    return false;
} 

//将当前字符与token字符数组中的字符串连接 
void catToken(){
    strcat(token,&charNow);
}

//将读字符指针后退一个字符
void retract(){
    ungetc(charNow,fd);
} 

//查找保留字并输出 
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
 
//将token中的字符串转换成整型数值 
void transNum(){
    num=atoi(token); 
}

//错误处理
void error(){
	printf("Unknown\n");
	exit(0);
}

//词法分析程序算法
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

//main函数 
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
