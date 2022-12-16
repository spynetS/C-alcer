#include <stdio.h>
#include <string.h>


struct map {
    char* key;
    float* value; 
};

struct node{
    void* value;
    struct node* next;
};

struct map* init_map(){
        struct map* variable = (struct map*)malloc(sizeof(struct map));
        memset(variable,0,sizeof(*variable));
        return variable;
}

/**
 * value null
 * return head of linked list
 * */
struct node* init_stack(){

    struct node* head = (struct node*)malloc(sizeof(struct node));
    memset(head,0,sizeof(struct node));
    head->next = NULL;

    return head;
}
/**
 * adds a new node to linked list with value value
 * */
void pushstr(struct node* nodes,void* value){
    struct node* pNode = nodes;
    /* printf("push %s\n",value); */
    while(pNode->next != NULL){
        pNode = pNode->next;
    }
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    /* memset(newNode,0,sizeof(struct node)); */
    newNode->next = NULL;
    
    newNode->value = malloc(sizeof(value)+1);
    
    strcpy(newNode->value,value);

    pNode->next = newNode;
}
void push(struct node* nodes,void* value){
    struct node* pNode = nodes;
    /* printf("push %s\n",value); */
    while(pNode->next != NULL){
        pNode = pNode->next;
    }
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    /* memset(newNode,0,sizeof(struct node)); */
    newNode->next = NULL;
    
    /* newNode->value = malloc(sizeof(value)+1); */

    newNode->value = value;

    pNode->next = newNode;
}
void printStack(struct node *head,const char* sep){

    struct node* pNode = head;
    while(pNode->next != NULL){
        pNode = pNode->next;
        printf("%s",pNode->value);
        printf("%s",sep);
    }
    printf("\n");
}
void printStackf(struct node *head,const char* sep){

    struct node* pNode = head;
    while(pNode->next != NULL){
        pNode = pNode->next;
        printf("%f",*(float*)pNode->value);
        printf("%s",sep);
    }
    printf("\n");
}
int stackLen(struct node* head){
    int len = 0;
    struct node* pNode = head;
    while(pNode->next != NULL){
        pNode = pNode->next;
        len ++;
    }
    return len;
}
struct node* get(struct node* head, int i){
    int n = 0; 
    struct node* pNode = head;
    while(pNode->next != NULL){
        pNode = pNode->next;
        if(n == i) return pNode;
        n++;
    }
    return NULL;
}
/**
 * return last element
 **/
struct node* peek(struct node* head){
    struct node* pNode = head;
    struct node* prev = NULL;
    while(pNode->next != NULL){
        prev = pNode;
        pNode = pNode->next;
    }
    return pNode;
}
/**
 * return last element and removed is
 **/
struct node* pop(struct node* head){
    struct node* pNode = head;
    struct node* prev = NULL;
    while(pNode->next != NULL){
        prev = pNode;
        pNode = pNode->next;
    }
    if(prev != NULL){
        //free(prev->next);
        prev->next = NULL;
    }
    return pNode;

}
