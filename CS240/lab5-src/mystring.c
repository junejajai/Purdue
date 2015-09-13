
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Adds src at the end of dest. Return the value of dest.
char *mystrcat(char * dest, char * src) {
	while(*dest!='\0')
	{
		dest++;
	}
	while(*src!='\0')
	{
		*dest=*src;
		dest++;
		src++;
	}
	*dest = '\0';


	return dest;
}


// Return a pointer to the first occurrence of the substring needle in
// the string haystack. 
// Return NULL if the string is not found.
char * mystrstr(char * haystack, char * needle) {
	char *p = haystack;
	char *q = needle;
	char *l; //= (char *)malloc(30 * sizeof(char));
	while(*p!='\0')
	{
		l=p;
		while(*p==*q)
		{
			if(*(q+1)=='\0')
			{
				return l;
			}
			q++;
			p++;
		}
		p=l;
		p++;
		q=needle;

	}
	return NULL;
}

int cp(char * src, char * dest)
{
	while(*src != '\0')
	{
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';
	return 1 ;
}
// Trims any spaces that are at the beginning or the end of s and returns s.
// Use the same memory passed in s. 
// Example:
// char s1[20];
// strcpy(s1,      hello    );
// strtrim(s1);
// printf(<s1=%s>\n, s1); // it will print <s1=hello>  without the spaces.
char * mystrtrim(char * s) {
	char * s1= (char *)malloc(30*sizeof(char));
	char *t1 = s1; 
	char * t = s;
	while(*t != '\0')
	{
		//	printf("%c\n",*s);
		if(*t != ' ')
		{
			//printf("%c\n",*s );
			*t1 = *t;
			//s++;
			//	printf("%c \n",*s1);
			t1++;
		}
		t++;
	}
	//*s1 = '\0';
	// printf("s %s\n",s);
	//	s = s1;
	//	printf("s1 %s\n",s1);
	cp(s1,s);
	return s;
}
int mystrlen(char * s)
{
	int c = 0;
	while(*s!='\0')
	{
		c++;
		s++;
	}
	return c;
}
int mystrcpy(char * dest, char * src)
{
char * d = dest;
char * s = src;
while(*s!='\0')
{
*d = *s;
d++;
s++;
}
*d='\0';
}
// Returns a new string that will substitute the first occurrence of the substring from
//  to the substring to in the string src
// This call will allocate memory for the new string and it will return the new string.
// Example:
// char a[6];
// strcpy(a, apple);
// char * b = strreplace(a, pp, orange);
// printf(<b=%s>\n, b); // It will print <b=aorangele>  
char * mystrreplace( char * src, char * from, char * to)  {
	//char replace[1000];
	char * t = (char *)malloc(strlen(to) + 1);
	char * replace = (char *)malloc(strlen(src) * 10);
	char * str = (char*) malloc(1000*sizeof(char));
	char * s = (char*) malloc(1000*sizeof(char));
	mystrcpy(replace,src);
	do{
		int c = 0;
		int i = 0;
		char * r = replace;
		str = mystrstr(replace,from);
		mystrcpy(s,str);
		int x = mystrlen(str);
		int l = mystrlen(replace);
		int diff = l - x;
		r += diff;
		*r = '\0';
		mystrcat(r,to);
		int lf = mystrlen(from);
		s += lf;
		mystrcat(r,s);
	} while(mystrstr(replace,from)!=NULL);	
	return replace;
}


