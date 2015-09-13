
#include <stdio.h>
#include <stdlib.h>

#define MAXSTACK 50
char stack[MAXSTACK];
int top = 0;
void push(char x)
{
	stack[top] = x;
	top++;
}
char pop()
{
	top--;
	char x = stack[top];
	return x;
}

int check(char *s)
{
	int t = 0;
	while(*s!='\0')
	{
		switch(*s)
		{
			case '(':
			case '{':
			case '[':
				push(*s);
				break;

			case ')':
				if( stack[top-1] == '(')
				{
					pop();
					//return 1;
				}
				else
				{
					return 0;
				}
				break;

			case '}':
				if(stack[top-1] == '{')
				{
					pop();
					//	return 1;
				}
				else
					return 0;

				break;

			case ']':
				if(stack[top-1]=='[')
				{
					pop();
					//return 1;
				}
				else
					return 0;
				break;
		}
		s++;
	}
	if(top==0)
	{
		return 1;
	}
	else
		return 0;

}
int main(int argc,  char **argv)
{
	if(argc!=2)
	{
		printf("Wrong number of input");

	}

	if(check(argv[1])==1)
	{
		printf("string is balanced\n");

	}
	else
	{
		printf("string is not balanced\n");
	}
}

