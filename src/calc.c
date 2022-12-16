#include "posfix.c"

float calculate(struct node* posfix){
    printf("posfix: ");
    printStack(posfix, " ");
    struct node* operands = init_stack(); 
    int len = stackLen(posfix);

    for(int i = 0; i < len;i++){
        char* term = get(posfix,i)->value;     
        if(isOperator(term)==0){
            float* f2 = (float*)pop(operands)->value;
            float* f1 = (float*)pop(operands)->value;

            if(*term=='+'){
                printf("it is plus");
                float new = *f1+*f2;
                pushf(operands,&new);
            }
            else if(*term=='-'){
                float new = *f1-*f2;
                pushf(operands,&new);
            }
            else if(*term=='*'){
                float new = *f1 * *f2;
                pushf(operands,&new);
            }
            else if(*term=='/'){
                float new = *f1 / *f2;
                pushf(operands,&new);
            }
            else if(*term=='^'){
                // add readl computation
                float new = *f1+*f2;
                pushf(operands,&new);
            }
            if(debug == 1){
                printf("%f",*f1);
                printf(" %s ",term);
                printf("%f = ",*f2);
                printf("%f\n",*(float*)peek(operands)->value);
            }

        }else if (*term!='\0'){
            float f = strtof(term,NULL);
            pushf(operands,&f);
        }
    }
    /* printStackF(operands," "); */

   return *(float*)get(operands,0)->value; 
}

