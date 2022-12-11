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
    if(strcmp(operator,"(")==0) return -1;
    return 0;
}

void addOperator(struct node* stack,struct node* output,char* operator){
    /* printf("operators %s\n",operator); */
    if(stackLen(stack)>0){
        int topLevel = getLevel(peek(stack)->value);
        int myLevel = getLevel(operator);
        printf("top %d\n",topLevel);
        printf("my %d\n",myLevel);
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
//Returns a string in posfixform from a linkedlist of infix
char* infixToPosfix(struct node *expression){
    // holds the operators 
    struct node* stack = init_stack();
    // holds the operands
    struct node* output = init_stack();

    int len = stackLen(expression);
    /* printStack(expression, "-"); */

    for(int i = 0; i < len;i++){
        char* term = get(expression,i)->value;
        /* printf("%s :",get(expression,i)->value); */
        if(strcmp(term,"(")==0){
            push(stack,term);
        }
        else if(strcmp(term,")")==0){
            /* printf("found p \n"); */
            char* poped = pop(stack)->value; 
            printf("peek %s\n",poped);
            while(0==0){
                push(output,poped);

                printf("--%s\n",peek(stack)->value);
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
        
        printf("r %s\nstack ",term);
        printStack(stack," ");
        printf("output ");
        printStack(output," ");
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
 *Infix string addded all operands and operators to a linkded list
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
                push(expression,word);
                /* printStack(expression,":"); */
            }
            push(expression,&character);
            memset(word,0,sizeof(word));
            count=0;
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
    printf("next %s\n",expression->next->next->next->value);
    push(expression,word);

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
    /* struct node* expression = init_stack(); */
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
    printStack(expression, " ");
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
