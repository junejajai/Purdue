
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "rpn.h"
#include "nextword.h"
#include "stack.h"

double rpn_eval(char * fileName, double x) {

//read from a file
//open file
//chk if file is valid
//while(!EOF)
//chk if c= + - log * / exp sin cos
//if yes chk if current top>=2.
//if no underflow
//if yes perform operation
//
double a,b,c;
FILE * fd = fopen(fileName,"r");
char * word;
while(word = nextword(fd))
{
if(strcmp(word,"x")==0)
{
stack_push(x);
}
else if(strcmp(word,"+")!=0&&strcmp(word,"-")!=0&&strcmp(word,"*")!=0&&strcmp(word,"/")!=0&&strcmp(word,"sin")!=0&&strcmp(word,"cos")!=0&&strcmp(word,"log")!=0&&strcmp(word,"pow")!=0&&strcmp(word,"exp")!=0)
{
stack_push(atof(word));
}
else if (strcmp(word,"+")==0)
{
a = stack_pop();
b = stack_pop();
c = a + b;
stack_push(c);
}
else if(strcmp(word,"-")==0)
{
a = stack_pop();
//printf("a %f\n",a);
b = stack_pop();
//printf("b %f",b);
//c = b - a;
stack_push(b-a);
}
else if(strcmp(word,"*")==0)
{
stack_push(stack_pop()*stack_pop());
}
else if(strcmp(word,"/")==0)
{
a = stack_pop();
b = stack_pop();
//c = b/a;
stack_push(b/a);
}
else if(strcmp(word,"sin")==0)
{
stack_push(sin(stack_pop()));
}
else if(strcmp(word,"cos")==0)
{
stack_push(cos(stack_pop()));
}
else if(strcmp(word,"log")==0)
{
stack_push(log(stack_pop()));
}
else if(strcmp(word,"pow")==0)
{
a = stack_pop();
b = stack_pop();
stack_push(pow(b,a));
}
else if(strcmp(word,"exp")==0)
{
stack_push(exp(stack_pop()));
}
//printf("%s", word);
//stack_print();
if(stack_top() == 0)
{
printf("Stack underflow\n" );
exit(0);
}

}
if(stack_top()>1)
{
printf("Elements remain in the stack\n");
exit(0);
}
double result = stack_pop();
  return result;

}
