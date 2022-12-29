#include "stack.c"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int debug = 0; // 1 will log what its doing
struct node* variables;

int isOperator(char *operator) {
  if (*operator== '^')
    return 0;
  if (*operator== '*')
    return 0;
  if (*operator== '/')
    return 0;
  if (*operator== '+')
    return 0;
  if (*operator== '-')
    return 0;
  return 1;
}

int getLevel(char *operator) {
  if (*operator== '^')
    return 3;
  if (*operator== '*')
    return 2;
  if (*operator== '/')
    return 2;
  if (*operator== '+')
    return 1;
  if (*operator== '-')
    return 1;

  return -1;
}

void addOperator(struct node *stack, struct node *output, char *operator) {

  if (stackLen(stack) > 0) {
    int myLevel = getLevel(operator);
    
    // is operator
    while (stackLen(stack) > 0 && myLevel <= getLevel(peek(stack)->value)) {
      if (*(char *)peek(stack)->value == '(' ) {
          printf("NO NOT HERE\n");
          pop(stack);
          return;
      }
      if (debug == 1) {
        printf("top %i\n", getLevel(peek(stack)->value));
        printf("new %i\n", myLevel);
      }
      pushstr(output, pop(stack)->value);
    }
    pushstr(stack, operator);

  } else {
    pushstr(stack, operator);
  }
}

void replaceVar(struct node* expression){
    int exLen = stackLen(expression);
    int varLen = stackLen(variables);
    for(int i = 0; i < exLen;i++){
        char* term = (char*)get(expression,i)->value;
        for(int j = 0; j < varLen; j++){
            struct map* var = (struct map*)get(variables,j)->value;
            if(strcmp(term, (char * )var->key) == 0){
                insert(expression, "(",i);
                insert(expression, "0",i+1);
                insert(expression, "-",i+2);
                insert(expression, var->value,i+3);
                insert(expression, ")",i+4);
                removeNode(expression, i+5);
            }
        }
    }
}

// Returns a string in posfixform from a linkedlist of infix
struct node *infixToPosfix(struct node *expression) {
  // holds the operators
  struct node *stack = init_stack();
  // holds the operands
  struct node *output = init_stack();

  int len = stackLen(expression);

  printf("before var \n");
  printStack(expression," ");
  replaceVar(expression);
  printStack(expression," ");
  printf("after var \n");

  for (int i = 0; i < len; i++) {
    char *term = (char *)get(expression, i)->value;
    if (strcmp(term,"(") == 0) {
        pushstr(stack, term);
    }
    // pop all operators untill the next ( and pushstr top output
    else if (strcmp(term,")") == 0 || *term == ')' ) {

         char* poped = pop(stack)->value;
         while(strcmp(poped,"(")!=0){
            pushstr(output,poped);
            if(strcmp(poped,"(")==0 || *term == '(') {
                break;
            }
            poped = pop(stack)->value;
        }
    }
    // if operator we do some magic (add in a special way)
    else if (isOperator(term) == 0) {
      addOperator(stack, output, term);
    } else {
      pushstr(output, term);
    }

    if (debug == 1) {
      printf("r %s\nstack ", term);
      printStack(stack, " ");
      printf("output ");
      printStack(output, " ");
    }
  }
  // add the remaining operat operators to the output
  int slen = stackLen(stack);
  for (int i = 0; i < slen; i++) {
    pushstr(output, pop(stack)->value);
  }

  /* printStack(stack," "); */
  return output;
}
// checks for a operator followed by a negative sign and replaces it
// with(0-[next operand])
char *parseNegativeNumbers(char *expressionStr, size_t size) {
  int isOp = 1; // keeps track if previus char was a op (1 in begining to check first term)
  char ex[256]; // new string
  memset(ex,0,256);
  int count = 0;// keep track where to add chars to new string
  int levels = 0; // how many pernthesis we are in
  int iPlace = 0;
  struct node* negs = init_stack();
  for (char character = *expressionStr; character != '\0'; character = *++expressionStr) {
    if(debug == 1){
      printf("before %s\n", ex);
    }
    if (isOperator(&character) == 0) {
      if (isOp == 1 && character == '-') {
        if(debug == 1){
          printf("is negative %c\n", character);
        }
        ex[count] = '(';
        count++;
        ex[count] = '0';
        printf("pushed )\n");
        pushstr(negs,")"); 
        count++;
      } 
      else if (stackLen(negs) > 0 && levels == 0) {
        printf(")))%c\n",character);
        char* neg = (char*)pop(negs)->value;
        printf("poped %s\n",neg);
        ex[count] = *neg;
        free(neg);
        count++;
      }
      isOp = 1;
    } 
    else if(character == '('){
        levels++;
        isOp = 1;
    }
    else if(character == ')'){
        if(stackLen(negs)>0){
            char* neg = (char*)pop(negs)->value;
            printf("poped %s\n",neg);
            ex[count] = *neg;
            free(neg);
            count++;
            levels--;
        }
    }
    else {
      isOp = 0;
    }
    if(debug == 1){
      printf("added %c\n", character);
      printStack(negs, " ");
    }
    ex[count] = character;

    count++;
  }
  if (stackLen(negs)>0) {
      char* neg = (char*)pop(negs)->value;
      printf("poped %s\n",neg);
      ex[count] = *neg;
      free(neg);
      count++;
  }
  if (debug == 1) {
    printf("t %p\n", expressionStr);
  }
  ex[count] = '\0';
  return strdup(ex);
}

/* void replaceVar2(char* expression){ */

/*     char word[256]; */
/*     int count = 0; */

/*     int varlen = stackLen(variables); */
/*     char ex[256]; */
/*     for (char character = *expression; character != '\0'; character = *++expression) { */
        
/*         for(int i = 0; i < varlen; i++){ */
/*             struct map* variable = (struct map*)get(variables,i)->value; */
/*             if(strcmp(word, variable->key)==0){ */
/*                 if(strchr(variable->key,"-")!=NULL){ */

/*                 } */
/*             } */
/*         } */
/*         word[count] = character; */
/*         count++; */
/*     } */
/* } */

/*
 *Infix string addded all operands and operators to a linkded list
 **/
struct node *getExpression(char *expressionS) {

  char *expressionStr = parseNegativeNumbers(expressionS, sizeof(expressionS));

  if (debug == 1) {
    printf("after negative check %s\n", expressionStr);
  }

  struct node *expression = init_stack();

  char word[256];
  memset(word, 0, 256);

  int count = 0;
  for (char character = *expressionStr; character != '\0';
       character = *++expressionStr) {
    // if the char is a operator add the prev word to the list
    if (isOperator(&character) == 0 || character == '(' || character == ')') {
      if (strlen(word) > 0) {
        pushstr(expression, word);
        /* printStack(expression,":"); */
      }
      pushstr(expression, &character);
      memset(word, 0, sizeof(word));
      count = 0;
      continue;
    } else {
      word[count] = character;
    }

    count++;
  }
  pushstr(expression, word);
  if (debug == 1) {
    printStack(expression, " ");
  }

  return expression;
}
