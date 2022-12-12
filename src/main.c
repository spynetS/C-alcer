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

void checkFlags(int argc, char *argv[]){
    if(argc>1){
        for(int i = 1; i< argc ; i++){
            char * arg = argv[i];
            if(strcmp(arg,"-d")==0){
                debug = 1;
            }
            else if(strcmp(arg,"-ni")==0){
                strcpy(input,argv[i+1]);
            }
            else{
                strcpy(input,arg);
            }
        }
    }
}

void calc(char* expressionStr){

    //parsed string to linkedlist
    struct node* expression = getExpression(expressionStr);
    // translate infix linkedlist to posfix linkedlist
    printf("\n> %f",calculate(infixToPosfix(expression)));
}

void checkPreDefined(char* string){
    if(strcmp(string, "exit")==0){
        loop = 0;
    }
    else if(strcmp(string, "help")==0){
        printf("This is a advanced calculator");
        printf("write example 90-90/2-(3-5)");        
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
        while(loop){
            printf("< ");
            fgets(expressionStr,128,stdin);
            expressionStr[strlen(expressionStr)-1] = '\0';
            checkPreDefined(expressionStr);
            calc(expressionStr);
            printf("\n");
        }
    }else{
        calc(input);
    }

    return 0;
}
