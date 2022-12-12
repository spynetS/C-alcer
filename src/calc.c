#include "linkedListFloat.c"
#include "posfix.c"

float calculate(struct node* posfix){
       
    printStack(posfix, "");
    struct nodeF* operands = init_stackF(); 
    int len = stackLen(posfix);

    for(int i = 0; i < len;i++){
        char* term = get(posfix,i)->value;     
        if(isOperator(term)==0){
            float f2 = popF(operands)->value;
            float f1 = popF(operands)->value;

            if(*term=='+'){
                pushF(operands,(f1+f2));
            }
            else if(*term=='-'){
                pushF(operands,(f1-f2));
            }
            else if(*term=='*'){
                pushF(operands,(f1*f2));
            }
            else if(*term=='/'){
                pushF(operands,(f1/f2));
            }
            else if(*term=='^'){
                // add readl computation
                pushF(operands,(f1*f2));
            }
            if(debug == 1){
                printf("%f",f1);
                printf(" %s ",term);
                printf("%f = ",f2);
                printf("%f\n",peekF(operands)->value);
            }

        }else if (*term!='\0'){
            float f = strtof(term,NULL);
            pushF(operands,f);
        }
    }
    /* printStackF(operands," "); */

   return getF(operands,0)->value; 
}

