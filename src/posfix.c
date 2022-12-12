#include <stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stack.c"

int debug = 0; // 1 will log what its doing

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

struct Operator operators[5];

int isOperator(char* operator){
    for(int i = 0;i < sizeof(operators)/sizeof(operators[0]); i++){
        if(*operator == *operators[i].symbol){
            return 0;
        }
    }
    return 1;
}

int getLevel(char* operator){
    if(*operator == '^') return 2;
    if(*operator == '*') return 1;
    if(*operator == '/') return 1;
    if(*operator == '+') return 0;
    if(*operator == '-') return 0;

    return 0;
}

void addOperator(struct node* stack,struct node* output,char* operator){
    /* printf("operators %s\n",operator); */
    if(stackLen(stack)>0){
        // get preoriti
        int myLevel = getLevel(operator);


        if(strcmp(peek(stack)->value,"(")==0){
            push(stack,operator);
        }
        //is operator
        else{
            
            while(stackLen(stack)>0 && 
                myLevel <= getLevel(peek(stack)->value)){

                if(debug == 1){
                    printf("top %i\n",getLevel(peek(stack)->value));
                    printf("new %i\n",myLevel);
                }
                push(output,pop(stack)->value);
            }
            push(stack,operator);
        }
    }else{
        push(stack,operator);
    }

}
//Returns a string in posfixform from a linkedlist of infix
struct node* infixToPosfix(struct node *expression){
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
            char* poped = pop(stack)->value; 
            while(0==0){
                push(output,poped);

                if(strcmp(peek(stack)->value,"(")==0) break;

                poped = pop(stack)->value;
            }
            //remove the last (
            pop(stack);
        }
        // if operator we do some magic (add in a special way)
        else if(isOperator(term)==0){
            addOperator(stack, output,term);
        }else{
            push(output,term);
        }
        
        if(debug==1){
            printf("r %s\nstack ",term);
            printStack(stack," ");
            printf("output ");
            printStack(output," ");
        }
    }
    // add the remaining operat operators to the output 
    int slen = stackLen(stack);
    for(int i = 0; i < slen;i++){
       push(output,pop(stack)->value);
    }
    
    /* printStack(stack," "); */
    return output;
}

char* parseNegativeNumbers(char* expressionStr,size_t size){

    int isOp = 0;
    char ex[256];
    int count = 0;
    int isNeg = 0;
    for (char character = *expressionStr; character != '\0'; character = *++expressionStr){
        if(isOperator(&character)==0 ){
            if(isOp == 1 && character == '-'){
                ex[count] = '(';
                count++;
                ex[count] = '0';
                isNeg = 1;
                count++;
            }
            else if(isNeg == 1){
                ex[count] = ')';
                isNeg = 0;
                count++;
                continue;
            }
            isOp = 1; 
        }
        else{
            isOp=0;
        }
        ex[count] = character;

        count++;
    }
    if(isNeg == 1){
        ex[count] = ')';
        count++;
    }
    if(debug==1){
        printf("t %p\n",expressionStr);
    }
    ex[count] = '\0';
    return strdup(ex);     
}

 /*
 *Infix string addded all operands and operators to a linkded list
 **/
struct node* getExpression(char* expressionS){
    
    char* expressionStr = parseNegativeNumbers(expressionS, sizeof(expressionS)); 

    if(debug==1){
        printf("after negative check %s\n",expressionStr);
    }

    struct node* expression = init_stack();

    char word[256];
    memset(word,0,256);

    int count = 0;
    int isOp = 0;
    for (char character = *expressionStr; character != '\0'; character = *++expressionStr){
        // if the char is a operator add the prev word to the list
        if(isOperator(&character)==0 ){
            if(strlen(word)>0){
                push(expression,word);
                /* printStack(expression,":"); */
            }
            push(expression,&character);
            memset(word,0,sizeof(word));
            count=0;
            isOp = 1;
            continue;
        }
        else if(character=='('){

            if(strlen(word)>0){
                push(expression,word);
            }

            push(expression,"(");
            memset(word,0,sizeof(word));
            count=0;
            continue;
        }
        else if(character==')'){
            if(strlen(word)>0){
                push(expression,word);
            }

            push(expression,")");
            memset(word,0,sizeof(word));
            count=0;
            continue;
        }
        else{
            word[count] = character;
        }

        count++;
    }
    push(expression,word);
    if(debug==1){
        printStack(expression," ");
    }

    return expression;
}
