#include <stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stack.c"

struct Operator{
    char* symbol;
    int level;
};

struct Operator getNewOperator(char* symbol, int level){
   struct Operator new_op;
   new_op.symbol = symbol; 
   new_op.level = level;

   return new_op;
}

struct Operator operators[4];

int isOperator(char* operator){
    for(int i = 0;i < sizeof(operators)/sizeof(operators[0]); i++){
        if(*operator == *operators[i].symbol){
            return 0;
        }
    }
    return 1;
}

int getLevel(char* operator){
    if(strcmp(operator,"*")==0) return 1;
    if(strcmp(operator,"/")==0) return 1;
    if(strcmp(operator,"+")==0) return 0;
    if(strcmp(operator,"-")==0) return 0;
    return -1;
}

void addOperator(struct node* stack,struct node* output,char* operator){
    if(stackLen(stack)>0){

        int topLevel = getLevel(peek(stack)->value);
        int myLevel = getLevel(operator);
        /* printf("top %d\n",topLevel); */
        /* printf("my %d\n",myLevel); */
        if(myLevel <= topLevel){
            push(output,pop(stack)->value);
            push(stack,operator);
        }else{
            push(stack,operator);
        }
    }else{
        push(stack,operator);
    }

}

char* infixToPosfix(struct node *expression){
    // holds the operators 
    struct node* stack = init_stack();
    // holds the operands
    struct node* output = init_stack();

    int len = stackLen(expression);

    for(int i = 0; i < len;i++){
        char* term = get(expression,i)->value;

        if(strcmp(term,"(")==0){
            push(stack,term);
        }
        else if(strcmp(term,")")==0){
            /* printf("found p \n"); */
            char* poped = pop(stack)->value; 

            /* while(strcmp(poped,"(")!=0){ */
            /*     /1* printf("--%s\n",poped); *1/ */
            /*     push(output,poped); */

            /*     if(strcmp(peek(stack)->value,"(")==0) break; */

            /*     poped = pop(stack)->value; */
            /* } */
            //remove the last (
            pop(stack);
        }
        // if operator we do some magic (add in a special way)
        else if(isOperator(term)==0){
            addOperator(stack, output,term);
        }else{
            push(output,term);
        }
        
        /* printf("%s\nstack",term); */
        /* printStack(stack," "); */
        /* printf("output "); */
        /* printStack(output," "); */
    }
    // add the remaining operat operators to the output 
    int slen = stackLen(stack);
    for(int i = 0; i < slen;i++){
        push(output,pop(stack)->value);
    }
    
    /* printStack(stack," "); */
    printStack(output," ");
    return "";
}
 /*
 *
 *  iterate through string
 *  if ( push current word 
 *  if ) push current word 
 *  if operar push to list clear word
 *
 **/
struct node* getExpression(char* expressionStr){
    struct node* expression = init_stack();

    char word[256];
    memset(word,0,256);

    int count = 1;
    int len = 0;
    for (char character = *expressionStr; character != '\0'; character = *++expressionStr){
        len++;
        if(isOperator(&character)==0){
            if(strlen(word)>0){
                char* pword = (char*)malloc(sizeof(char*)*sizeof(word)/sizeof(word[0]));
                strcpy(pword, word);
                printf("%c ",character);
                printf("%s\n",&word[0]);
                push(expression,pword);
                /* printStack(expression,":"); */
            }

            char* pc = (char*)malloc(sizeof(char*));
            strcpy(pc, &character);
            push(expression,pc);

            count=0;
            memset(word,0,256);
            continue;
        }
        else if(character=='('){

            if(strlen(word)>0){
                char* pword = (char*)malloc(sizeof(char*)*sizeof(word)/sizeof(word[0]));
                strcpy(pword, word);
                printf("%c ",character);
                printf("%s\n",&word[0]);
                push(expression,pword);
            }

            push(expression,"(");
            count=0;
            memset(word,0,256);
            continue;
        }
        else if(character==')'){
            if(strlen(word)>0){
                char* pword = (char*)malloc(sizeof(char*)*sizeof(word)/sizeof(word[0]));
                strcpy(pword, word);
                printf("%c ",character);
                printf("%s\n",&word[0]);
                push(expression,pword);
            }

            push(expression,")");
            count=0;
            memset(word,0,256);
            continue;
        }
        else{
            word[count] = character;
        }

        count++;
    }
    char* pword = (char*)malloc(sizeof(char*)*sizeof(word)/sizeof(word[0]));
    strcpy(pword, word);
    printf("%s\n",&word[0]);
    push(expression,pword);

    return expression;
}

int main(){
    operators[0] = getNewOperator("+", 0);
    operators[1] = getNewOperator("-", 0);
    operators[2] = getNewOperator("*", 1);
    operators[3] = getNewOperator("/", 1);
    

    char* expressionStr = "(10+10)/2*6";
    printf("%s\n",expressionStr);
    /* printStack(," "); */

    struct node* expression = getExpression(expressionStr);
    /* push(expression, "("); */
    /* push(expression, "10"); */
    /* push(expression, "+"); */
    /* push(expression, "10"); */
    /* push(expression, ")"); */
    /* push(expression, "/"); */
    /* push(expression, "2"); */
    /* push(expression, "*"); */
    /* push(expression, "6"); */

    /* push(expression, "10"); */
    /* push(expression, "+"); */
    /* push(expression, "10"); */
    /* push(expression, "-"); */
    /* push(expression, "10"); */
    printStack(expression, "");
    /* printf("%s\n",(expression)); */
    /* strcpy(addSpaces(expression),expression ); */
    /* printf("%s\n",(expression)); */

    
    infixToPosfix(expression);
    /* struct node* head = init_stack(); */
    /* push(head,"Test1"); */
    /* push(head,"Test2"); */
    /* printStack(head," "); */
    /* pop(head); */
    /* printf("\n"); */
    /* printStack(head,"\n"); */

    return 0;
}
