#include <stdio.h>
#include <string.h>

struct nodeF{
    float value;
    struct nodeF* next;
};
/**
 * value null
 * return head of linked list
 * */
struct nodeF* init_stackF(){

    struct nodeF* head = (struct nodeF*)malloc(sizeof(struct nodeF));
    memset(head,0,sizeof(struct nodeF));
    head->next = NULL;

    return head;
}
/**
 * add a new nodeF to linked list with value value
 * */
void pushF(struct nodeF* nodeFs,float value){
    struct nodeF* pnodeF = nodeFs;
    /* printf("push %s\n",value); */
    while(pnodeF->next != NULL){
        pnodeF = pnodeF->next;
    }
    struct nodeF* newnodeF = (struct nodeF*)malloc(sizeof(struct nodeF));
    /* memset(newnodeF,0,sizeof(struct nodeF)); */
    newnodeF->next = NULL;
     
    newnodeF->value = value;

    pnodeF->next = newnodeF;
}
void printStackF(struct nodeF *head,const char* sep){

    struct nodeF* pnodeF = head;
    while(pnodeF->next != NULL){
        pnodeF = pnodeF->next;
        printf("%f",pnodeF->value);
        printf("%s",sep);
    }
    printf("\n");
}
int stackLenF(struct nodeF* head){
    int len = 0;
    struct nodeF* pnodeF = head;
    while(pnodeF->next != NULL){
        pnodeF = pnodeF->next;
        len ++;
    }
    return len;
}
struct nodeF* getF(struct nodeF* head, int i){
    int n = 0; 
    struct nodeF* pnodeF = head;
    while(pnodeF->next != NULL){
        pnodeF = pnodeF->next;
        if(n == i) return pnodeF;
        n++;
    }
    return NULL;
}
/**
 * return last element
 **/
struct nodeF* peekF(struct nodeF* head){
    struct nodeF* pnodeF = head;
    struct nodeF* prev = NULL;
    while(pnodeF->next != NULL){
        prev = pnodeF;
        pnodeF = pnodeF->next;
    }
    return pnodeF;
}
/**
 * return last element and removed is
 **/
struct nodeF* popF(struct nodeF* head){
    struct nodeF* pnodeF = head;
    struct nodeF* prev = NULL;
    while(pnodeF->next != NULL){
        prev = pnodeF;
        pnodeF = pnodeF->next;
    }
    if(prev != NULL){
        prev->next = NULL;
    }
    return pnodeF;
}
