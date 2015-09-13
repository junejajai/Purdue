
#include <stdio.h>
#include "stack.h"
#include <stdlib.h>

int top=0;
double stack[MAXSTACK];

void stack_clear() 
{
  top = 0;
}

double stack_pop()
{       
        top --; 
//	if(top< 0)
//	printf("Stack:\nStack is Empty ");
        
	double x = stack[top];
	// Add implementation here`
	return x;
}

void stack_push(double val)
{
       stack[top] = val;
       top++;
       // Add implementation here
}

void stack_print()
{
int i = 0;
printf("Stack:\n");
if(top<=0)
{
printf("Stack is empty");
}
for(i = 0; i<top;i++)
{
printf("%d: %lf\n",i, stack[i]);
}
}

int stack_top()
{
  return top;
}

int stack_max()
{
  return MAXSTACK;
}

int stack_is_empty()
{
  return top == 0;
}


