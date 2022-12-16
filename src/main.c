/*
    Alfred Roos 2022-12-12
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.c"

char input[128];
int loop = 1;


int checkFlags(int argc, char *argv[]){
    // 1 continue with prorgam 0 to stop
    if(argc>1){
        for(int i = 1; i< argc ; i++){
            char * arg = argv[i];
            if(strcmp(arg,"-d")==0){
                debug = 1;
            }
            else if(strcmp(arg,"-h")==0){
                printf("calcer is a advenced calculator for writing\n");
                printf("math expressions like '90-90/2-(2-3)'\n\n");
                printf("-d enables debug mode(prints the stages to calculate)\n");
                printf("[expression] calculates the expression\n");
                return 0;
            }
            else{
                strcpy(input,arg);
            }
        }
    }
    return 1;
}

void calc(char* expressionStr){

    //parsed string to linkedlist
    struct node* expression = getExpression(expressionStr);
    // translate infix linkedlist to posfix linkedlist
    printf("\n> %f",calculate(infixToPosfix(expression)));
}

int checkPreDefined(char* string){
    if(strcmp(string, "exit")==0){
        loop = 0;
        return 1;
    }
    else if(strcmp(string, "help")==0){
        printf("This is a advanced calculator\n");        
        printf("write example 90-90/2-(3-5)");        
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]){
    
    if(checkFlags(argc,argv)==0)return 0;

    // this is the string that will get parsed to infix
    char expressionStr[128];
    //if inputflag contains a s set the expressionStr to that
    if(strlen(input)<=0){
        printf("ctrl-c/exit to exit \nwrite help for help\n");
        while(loop){
            printf("< ");
            fgets(expressionStr,128,stdin);
            expressionStr[strlen(expressionStr)-1] = '\0';
            if(checkPreDefined(expressionStr)==0){
                calc(expressionStr);
            }
            printf("\n");
        }
    }else{
        calc(input);
    }

    return 0;
}
