#include "posfix.c"
#include <stdio.h>
#include <string.h>


void replaceVar(struct node* posfix, struct node* variables){
    
    int len = stackLen(posfix);
    int varableslen = stackLen(variables);

    for(int i = 0; i < len;i++){
        char* term = get(posfix,i)->value;
        for(int iv = 0; iv < varableslen;iv++){
            struct map* variable = (struct map*)get(variables,iv)->value;
            //printf("term %s=",term);
            //printf("%s\n",variable->key);
            if(strcmp(term, variable->key)==0){

                char* value = malloc(sizeof(char));
                gcvt(*(float*)variable->value, 9, value);
                strcpy(term,value);
            }
        }
    }
}

void replaceFunctions(struct node* posfix, struct node* functions){

    int len = stackLen(posfix);
    int funLen = stackLen(functions);

    for(int i = 0; i < len;i++){
        char* term = get(posfix,i)->value;
        for(int iv = 0; iv < funLen;iv++){
            struct function* function = (struct function*)get(functions,iv)->value;
            if(strcmp(term,function->name)==0){
                printf("posfgix ");
                printStack(function->posfix," ");
            }
        }
    }
}

float calculate(struct node* posfix,struct node* variables, struct node* functions){
    if(debug == 1){
        printf("posfix: ");
        printStack(posfix, " ");
    }
    replaceVar(posfix, variables);
    //replaceFunctions(posfix, functions);
    
    if(debug==1){
        printStack(posfix, " ");
    }

    struct node* operands = init_stack(); 
    int len = stackLen(posfix);

    for(int i = 0; i < len;i++){
        char* term = get(posfix,i)->value;     
        if(isOperator(term)==0){

            float f2 = *(float*)pop(operands)->value;
            float f1 = *(float*)pop(operands)->value;

            if(*term=='+'){
                float new = (f1 + f2);
                push(operands,&new);
            }
            else if(*term=='-'){
                //printf("%f",*(float*)peek(operands)->value); 
                float new = f1 - f2;
                push(operands,&new);
            }
            else if(*term=='*'){
                float new = f1 * f2;
                push(operands,&new);
            }
            else if(*term=='/'){
                float new = f1 / f2;
                push(operands,&new);
            }
            else if(*term=='^'){
                // add readl computation
                float new = f1 + f2;
                push(operands,&new);
            }
            if(debug == 1){
                printf("%f",f1);
                printf(" %s ",term);
                printf("%f = ",f2);
                printf("%f\n",*(float*)peek(operands)->value);
            }
            
        }else if (*term!='\0'){
            float f = strtof(term,NULL);
            free(term);

            // make copy to add to stack
            float *newFloat = (float*)malloc(sizeof(float));
            *newFloat = f; 

            push(operands,newFloat);
        }
    }
    /* printStackF(operands," "); */

   return *(float*)get(operands,0)->value; 
}

