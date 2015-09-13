
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct WordInfo {
	char * word;
	int count;
};

typedef struct WordInfo WordInfo;

int maxWords;
int nWords;
WordInfo*  wordArray;

#define MAXWORD 100
int wordLength;
char word[MAXWORD];
FILE * fd;
int charCount;
int wordPos;
int isaletter(char ch)
{
	if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
	{
		return 1;
	}
	return 0;
}
int isUpper(char ch)
{
	if(ch>='A'&&ch<='Z')
	{
		//ch = ch - 'A'+ 'a';
		return 1;
	}
	return 0;
}
void toLower(char *s) {
        char * t = s;
	while(*t!='\0')
	{
		if(isaletter(*t)== 1 && isUpper(*t)==1)
		{
			*t = *t -'A'+'a';
		}
		t++;
	}
}

// It returns the next word from stdin.
// If there are no more more words it returns NULL. 
static char * nextword() {
	wordLength = 0;
	char ch;
	while((ch = fgetc(fd))!= EOF)
	{
		if(isaletter(ch))
		{
	//	        printf("%c",ch);
			word[wordLength] = ch;
			wordLength++;
		}
		else
		{
			word[wordLength] = '\0';
	//		printf("\n %s\n",word);
			toLower(word);
	//		printf("\n %s\n",word);
			if(wordLength>0)
			{
			        wordLength = 0;
				return word;
			}
			wordLength = 0;
		}
	}

	return NULL;
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: countwords filename\n");
		exit(1);
	}

	char * filename = argv[1];
	fd = fopen(filename, "r");
	if(fd == NULL)
	{
		exit(0);
	}
	int t = 0;
	nWords = 0;
	int i = 0;
	int flag = 0;
	maxWords = 10; 
	wordArray = (WordInfo *)malloc(maxWords * sizeof(WordInfo));
	//char w[50];
	char * w = (char *)malloc(30*sizeof(char)); 
	while((w = nextword())!=NULL)
	{
//	printf("\n1\n");
	//	if(nWords < maxWords)
	//	{
			for(i=0;i<nWords;i++)
			{
				if(strcmp(wordArray[i].word,w)==0)
				{
					wordArray[i].count++;
					flag = 1;
					break;

				}
			}
			if(flag == 0)
			{
				wordArray[nWords].word = strdup(w);
				wordArray[nWords].count++;
				nWords++;
			}
			flag = 0;
	//		printf("%s",wordArray[0].word);
	//	}
		if(nWords >= maxWords)
		{
			maxWords = 2 * maxWords;
			wordArray = (WordInfo *)realloc(wordArray,maxWords * sizeof(WordInfo));

		}
	}
	int j = 0;
	for(i=0;i<nWords;i++)
	{

		for(j=0;j<nWords-1-i;j++)
		{
			if(strcmp(wordArray[j].word,wordArray[j+1].word) > 0)
			{
				WordInfo  temp = wordArray[j];
				wordArray[j]=wordArray[j+1];
				wordArray[j+1] = temp;
			}
		}
	}

	for(i=0;i<nWords;i++)
	{
		printf("%s %d\n",wordArray[i].word,wordArray[i].count);
	}
	fclose(fd);
}


