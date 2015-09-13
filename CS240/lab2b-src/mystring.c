
#include <stdlib.h>
#include "mystring.h"

// Type "man string" to see what every function expects.

int mystrlen(char * s) {
int c = 0;
int i; 
for(i = 0; s[i]!='\0';i++)
{
c++;
}
return c;
}

char * mystrcpy(char * dest, char * src) {

int i;
if(mystrlen(src)==1){return src;}
for( i = 0; src[i]!='\0';i++ )
{
dest[i] = src[i];

}
dest[i]= '\0';
return dest;
}

char * mystrcat(char * dest, char * src) {
int count = 0,count2 = 0;
int i = mystrlen(dest);
int j;
     // dest[i] = "";
      for ( j =0;src[j] !='\0'; j++ )
      {
      dest[i+j] = src[j];
      }
      dest[i+j]='\0';
      return dest;
}
int mystrcmp(char * s1, char * s2) {
	int l1 = 0;
	int l2 = 0;
	int i , j;
	   for(i = 0; s1[i]!='\0';i++)
	    {
	     l1++;
	    }
	    for(i = 0; s2[i]!='\0';i++)
	        {
                 l2++;  
		}
        if(l1>l2)
	{
	return 1;
	}

	if(l1==l2)
	{
	return 0;
	}
	if(l1<l2)
	{
         return -1;
	}
	
}


char * mystrstr(char * hay, char * needle) {
/*
int i,j;
 int posn = 0;
	  // int k;
	        for (i = 0; i < mystrlen(hay); i++) {
		int k;
	                if (hay[i] == needle[0] && k != mystrlen(needle)) {
	                        k = 0;
	                        for (j = 0; j < mystrlen(needle); j++) {
	                                if (hay[i+j] == needle[j]) {
	                                        k++;
	                                        if (k == mystrlen(needle)) {
	                                               break;
	                                        }
	                                }
	                        }
	                }
	                if (k == mystrlen(needle)) {
	                      posn = i;
			      return hay + posn;
	                }
	        } 
	            return NULL;
	       }    
	       
*/
int i=0;
int j=0;
int inc;
while(i < mystrlen(hay)){
	if(hay[i]==needle[0] && inc != mystrlen(needle)){
	inc = 0;
		for(j=0;j<mystrlen(needle);j++){
		  if(hay[i+j]==needle[j]){
		  inc++;
	            if(inc == mystrlen(needle)){
			break;
		    }
		  }


		}
	}
	if(inc==mystrlen(needle)){
	return hay+i;
	}
	i++;
}
	return NULL;
}
char * mystrdup(char * s) {
	char* a = malloc(sizeof(s)+1);
	if(a!=NULL)
	{
	mystrcpy(a,s);
	}
	return a;
}

char * mymemcpy(char * dest, char * src, int n)
{
char* holder;
	if(n>mystrlen(src))
	{
	mystrcpy(dest,src);
	}
else	
	{
	int i;
	for(i=0;i<n;i++)
	{
          holder[i]=src[i];
	}
	mystrcpy(dest,holder);
}
	return dest;
}

