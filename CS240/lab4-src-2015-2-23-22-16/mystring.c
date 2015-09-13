
#include <stdlib.h>
#include "mystring.h"

int mystrlen(char * s) {
int x = 0;
char * p = s;
while(*p!='\0')
{
x++;
p++;
}
return x;
}

char * mystrcpy(char * dest, char * src) {
char * p = dest;
char * q = src;
while(*q != '\0')
{
*p = *q;
p++;
q++;
}
*p = '\0';
return dest;
}

char * mystrcat(char * dest, char * src) {
char * p = dest;
char * q = src;
while(*p != '\0')
{
p++;
}
while(*q != '\0' )
{
*p = *q;
p++;
q++;
}
*p = '\0';
return dest;
}

int mystrcmp(char * s1, char * s2) {
	int a = mystrlen(s1);
	int b = mystrlen(s2);
	if(a==b)
	{
	return 0;
	}
        else if(a>b)
	{
	return 1;
	}
        else
	return -1;
}

char * mystrstr(char * hay, char * needle) {
	
int i=0;
int j=0;
int inc;
while(i < mystrlen(hay)){
	if(*(hay + i)== *needle && inc != mystrlen(needle)){
	inc = 0;
		for(j=0;j< mystrlen(needle);j++){
		  if(*(hay+(i+j))== *(needle+j)){
		  inc++;
	            if(inc == mystrlen(needle)){
			break;
		    }
		  }


		}
	}
	if(inc== mystrlen(needle)){
	return hay+i;
	}
	i++;
}
	return NULL;
}

char * mystrdup(char * s) {
//	char * p = s;
        char * s1 = malloc(sizeof(s)+1);
	if(s1 != NULL)
	{
	mystrcpy(s1,s);	
	}
	return s1;
}

char * mymemcpy(char * dest, char * src, int n)
{
char* holder;
        if(n> mystrlen(src))
         {
         mystrcpy(dest,src);
         }
 else    
         {
         int i;
         for(i=0;i<n;i++) 
         { 
          *(holder+i)=*(src+i);
         }
         mystrcpy(dest,holder);
 }
         return dest;

	
}

