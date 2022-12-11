#include <stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "posfix.c"

char input[128];

void checkFlags(int argc, char *argv[]){
    if(argc>1){
        for(int i = 1; i< argc ; i++){
            char * arg = argv[i];
            if(strcmp(arg,"-d")==0){
                debug = 1;
            }
            if(strcmp(arg,"-ni")==0){
                strcpy(input,argv[i+1]);
            }
        }
    }
}


int main(int argc, char *argv[]){
    operators[0] = getNewOperator("+", 0);
    operators[1] = getNewOperator("-", 0);
    operators[2] = getNewOperator("*", 1);
    operators[3] = getNewOperator("/", 1);
    operators[4] = getNewOperator("^", 2);
    
    checkFlags(argc,argv);

    // this is the string that will get parsed to infix
    char expressionStr[128];
    //if inputflag contains a str set the expressionStr to that
    if(strlen(input)<=0){
        fgets(expressionStr,128,stdin);
        expressionStr[strlen(expressionStr)-1] = '\0';
    }else{
        strcpy(expressionStr,input);
    }

    //parsed string to linkedlist
    struct node* expression = getExpression(expressionStr);
    // translate infix linkedlist to posfix linkedlist
    printStack(infixToPosfix(expression)," ");

    return 0;
}
