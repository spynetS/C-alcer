#include <stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "posfix.c"

void checkFlags(int argc, char *argv[]){
    if(argc>1){
        for(int i = 1; i< argc ; i++){
            char * arg = argv[i];
            printf("%s\n",arg);
            if(strcmp(arg,"-d")==0){
                debug = 1;
            }
        }
    }
}


int main(int argc, char *argv[]){
    operators[0] = getNewOperator("+", 0);
    operators[1] = getNewOperator("-", 0);
    operators[2] = getNewOperator("*", 1);
    operators[3] = getNewOperator("/", 1);
    
    checkFlags(argc,argv);

    /* char* expressionStr = "10+10/2*6"; */

    char expressionStr[128];
    fgets(expressionStr,128,stdin);
    expressionStr[strlen(expressionStr)-1] = '\0';
    /* printf("%s\n",expressionStr); */

    struct node* expression = getExpression(expressionStr);

    printStack(infixToPosfix(expression)," ");

    return 0;
}
