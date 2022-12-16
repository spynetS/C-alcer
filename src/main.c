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
struct node* varables;

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

    printf("> %f",calculate(infixToPosfix(expression),varables));
}

int checkPreDefined(char* string){
    if(strcmp(string, "exit")==0){
        loop = 0;
        return 1;
    }
    else if(strstr(string,"=")){
        // get variable name
        char varname[256];
        memset(varname,0,256);
        int equal = 0;
        for(int i = 0;i<strlen(string);i++){
            if(string[i]=='='){
                break;
            }
            varname[i] = string[i];
            equal++;            
        }
        // get value
        char value[256];
        memset(value,0,256);
        for(int i = equal+1;i < strlen(string);i++){
            value[i-equal-1] = string[i];
        }

        struct node* expression = getExpression(value);

        // translate infix linkedlist to posfix linkedlist
        float calculated = calculate(infixToPosfix(expression),varables);

        int varLen = stackLen(varables);

        struct map* variable = init_map();
        //set varable struct to the one with the same name
        for(int i = 0;i < varLen; i++ ){
            if(debug==1){
                printf("remap variable name");
            }
            struct node* vNode = (struct node*)get(varables,i);
            if(strcmp(varname,((struct map*)vNode->value)->key)==0){
                variable = ((struct map*)vNode->value);
            }
        }


        variable->key = malloc(sizeof(char*));
        memset(variable->key,0,sizeof(*variable->key));
        strcpy(variable->key,varname);

        variable->value = malloc(sizeof(float));
        *variable->value = calculated;


        push(varables,variable);

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

    varables = init_stack();

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
