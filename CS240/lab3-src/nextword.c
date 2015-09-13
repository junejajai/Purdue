
#include <stdio.h>
#include <stdlib.h>

//
// Separates the file into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;

// It returns the next word from fd.
// If there are no more more words it returns NULL. 
char * nextword(FILE * fd) {
  	int c;
	int i = 0;
	// While it is not EOF read char
		// While it is not EOF and it is a non-space char
		// store character in word.
		// if char is not in word return word so far.
		//
	// Return null if there are no more words
	
	
	int j = 0;
	for(j = 0;j<wordLength;j++)
	{
	word[j] = '\0';
        }
	wordLength = 0;
	while((c=fgetc(fd))!= -1)
	{
          if(c!=' '&&c!='\n'&&c!='\t'&&c!='\r') // if((c >= 65&& c<= 90)||(c>=97&&c<=122)||(c>=48&&c<=57) )
	  {
           word[wordLength] = (char)c;
	   wordLength++;
          }
          else
	  
	  {
	  if(wordLength>0)
	  return word;
	  }  
	}
if(wordLength > 0)
{
return word;
}


	return NULL;
}

