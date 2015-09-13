
#include "webcrawler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openhttp.h"
#include "SimpleHTMLParser.h"
#define MAXWORD 200
// Add your implementation here
//int urlinsert = 0;
//int descripinsert = 0;
int utoua = 0;

	
WebCrawler::WebCrawler(int maxUrls, int nurlRoots, const char ** urlRoots)
{
	_maxUrls = maxUrls;
	_headURL = 0;
	_tailURL = nurlRoots;
	_urlArray = new URLRecord[_maxUrls];
	_des = new descr[_maxUrls];	
	int c = 0;
	while(c < _tailURL)
	{
		_urlArray[c]._url = strdup (*(urlRoots + c)); //also -> operator does not work. CHECK OUT WHY LATER 
		//_urlArray[c]._description = strdup("initWord");//uncomment this to test
		c++;			
	}
	    _urlToUrlRecord = new HashTableTemplate<int>();
	    _wordToURLRecordList = new HashTableTemplate<URLRecordList*>();
}

void WebCrawler :: onAnchorFound(char * url) {
	//check if utoua(same as inserted) > maxUrlslater mbm
	if(_tailURL >= _maxUrls)
	{
		return;
	}
	char * baseURL = (char *)malloc((strlen(_urlArray[_headURL]._url)+2)*sizeof(char)); 
	strcpy(baseURL,_urlArray[_headURL]._url);

	char * fin = (char *)malloc(sizeof(char) * (strlen(url) + 1 + strlen(baseURL)));
	//abs url check
	//fin = strdup("");
	strcpy(fin,"");
//	_urlArray[_tailURL]._url = strdup(url);//find later
//	_tailURL++;
	if(!strncmp("http://",url,7))
	{
		//absolute url found
		//check for if page is same for two diff urls with same buffer
		int x = 0;
		while(x<_tailURL) //may be causing errors. 
		{
			int n;
			int n1;	
			char * b = strdup(url);//fetchHTML(url,&n);
			char * b1 =strdup(_urlArray[x]._url);//fetchHTML(_urlArray[x]._url,&n1);	
			if(!strcmp(b,b1))
			{
				//printf("similar url found");
				return;
			}
			x++;	

		}

		_urlArray[_tailURL]._url = strdup(url);//find later
			_urlToUrlRecord->insertItem(fin, _tailURL);	//headURL

		_tailURL++;
		return;
	}
	else
	{

		if(url[0]=='/' && url[1] == '/')
		{
		return;
		}
		if(!strncmp("https://",url,8))
		{
		return;
		}
		if(strlen(url) == 1)
			{
			
			return;	
			}
		//relative url found
		if(url[0]!='/')
		{
		if(baseURL[strlen(baseURL) - 1] != '/')
		{
			char * addendum = strdup("/");
			strcat(baseURL,addendum); //appends '/'
		}
		}
		//char * fin = (char *)malloc(strlen(url) + 1 + strlen(baseURL));
		strcat(fin,baseURL);
		strcat(fin,url);
	}
	int x = 0;
	while(x<_tailURL)
	{
		int n2;
		int n3;
		char * b3 = strdup(fin);//fetchHTML(fin,&n2);
		char * b2 = strdup(_urlArray[x]._url);//fetchHTML(_urlArray[x]._url,&n3);
		if(strcmp(b3,b2))
		{
			//printf("similar url found");	
			return;
		}
		x++;
	}
	//printf("%s\n",url);
	_urlArray[_tailURL]._url = strdup(fin);//find later
	/*
	   int check = 0;
	   while()

*/
		_urlToUrlRecord->insertItem(fin, _tailURL);	//headURL

	_tailURL++;//only problem exists with description being added, but if we add at head it should be fine
	//printf("%d\n",_tailURL);

	return;

//printf("%s\n",url);
}
char words[1000];
int wordLength;
void WebCrawler :: crawl()
{
	while(_headURL < _tailURL)// && _tailURL<=_maxUrls)
	{
		int n;
        
		char * buffer = fetchHTML(_urlArray[_headURL]._url,&n);
		if(buffer == NULL)
		{
			_headURL++;
			continue;
		}
		parse(buffer,n);
		_headURL++;
        
	}	
	//add title keyword description to _urlArray
	//wordLength = 0;
	int tr = 0;
	int dcount = 0;
	int kcount = 0;	
	//implementing nextword
	int tcount = 0;
	while(tcount<_headURL)
	{	
	int f = 0;
	//printf("1\n");
	//printf("%d is count %d is headURL ",count,_headURL);//,_urlArray[count]._title);	
	char * ti = _urlArray[tcount]._title;

	if(ti == NULL)
		{
			f = 1;
			tcount++;
			continue;
		}
	
	//printf("%s\n",ti);	

//char * key = _urlArray[count]._keywords;
	int j = 0;
	//char * descrip = _urlArray[count]._description;
	for(j=0;j<wordLength;j++)
		{
			words[j] = '\0';
		}	
	wordLength = 0;

	while(*ti!='\0')
	{		
			
          if(*ti!=' '&&*ti!='\n'&&*ti!='\t'&&*ti!='\r'&&*ti!='-'&&*ti!=','&&*ti!='\"'&&*ti!='.') // if((c >= 65&& c<= 90)||(c>=97&&c<=122)||(c>=48&&c<=57) )
	  {
           words[wordLength] = *ti;
	   		wordLength++;
          }
          else
	  
	  {
	  if(wordLength>0)
		{
			words[wordLength] = '\0';
			wordLength++;

			URLRecordList *tmp = NULL;        
        if (_wordToURLRecordList->find(words, &tmp) == false)
        {
            URLRecordList *data = new URLRecordList();
            data->_urlRecordIndex = tcount;
            data->_next = NULL;
            							printf("%s\n",words);	
            _wordToURLRecordList->insertItem(words, data);
        }
        else
        {
            URLRecordList *data = new URLRecordList();
            data->_urlRecordIndex = tcount;
            data->_next = tmp;
            							printf("%s\n",words);	
            _wordToURLRecordList->insertItem(words, data);
        }


			printf("%s\n",words);
			for(j=0;j<wordLength;j++)
		{
			words[j] = '\0';
		}
		wordLength = 0;		
		}
		else
			{
				wordLength = 0;
			}			
		}
		ti++;

		}
	tcount++;
	//printf("count is %d\n",count);
}


while(dcount<_headURL)
	{	
	int f = 0;
	//printf("1\n");
	//printf("%d is count %d is headURL ",count,_headURL);//,_urlArray[count]._title);	
	//char * ti = _urlArray[dcount]._title;
	char * descrip = _urlArray[dcount]._description;
	if(descrip == NULL)
		{
			f = 1;
			dcount++;
			continue;
		}
	//printf("%s\n",descrip);	

//char * key = _urlArray[count]._keywords;
	int j = 0;
	
	for(j=0;j<wordLength;j++)
		{
			words[j] = '\0';
		}	
	wordLength = 0;

	while(*descrip!='\0')
	{		
			
          if(*descrip!=' '&&*descrip!='\n'&&*descrip!='\t'&&*descrip!='\r'&&*descrip!='-'&&*descrip!=','&&*descrip!='.') // if((c >= 65&& c<= 90)||(c>=97&&c<=122)||(c>=48&&c<=57) )
	  {
           words[wordLength] = *descrip;
	   		wordLength++;
          }
          else
	  
	  {
	  if(wordLength>0)
		{
			words[wordLength] = '\0';
			wordLength++;
						//printf("%s\n",words);		
			URLRecordList *tmp = NULL;        
        if (_wordToURLRecordList->find(words, &tmp) == false)
        {
            URLRecordList *data = new URLRecordList();
            data->_urlRecordIndex = dcount;
            data->_next = NULL;
							printf("%s\n",words);	
            _wordToURLRecordList->insertItem(words, data);
        }
        else
        {
            URLRecordList *data = new URLRecordList();
            data->_urlRecordIndex = dcount;
            data->_next = tmp;
							printf("%s\n",words);	
            _wordToURLRecordList->insertItem(words, data);
        }


			printf("%s\n",words);
			for(j=0;j<wordLength;j++)
		{
			words[j] = '\0';
		}
		wordLength = 0;		
		}
		else
			{
				wordLength = 0;
			}			
		}
		descrip++;

		}
	dcount++;
	//printf("count is %d\n",count);
}



while(kcount<_headURL)
	{	
	int f = 0;
	//printf("1\n");
	//printf("%d is count %d is headURL ",count,_headURL);//,_urlArray[count]._title);	
	//char * ti = _urlArray[kcount]._title;
char * key = _urlArray[kcount]._keywords;	
	if(key == NULL)
		{
			f = 1;
			kcount++;
			continue;
		}
	//printf("%s\n",key);	


	int j = 0;
	//char * descrip = _urlArray[count]._description;
	for(j=0;j<wordLength;j++)
		{
			words[j] = '\0';
		}	
	wordLength = 0;

	while(*key!='\0')
	{		
			
          if(*key!=' '&&*key!='\n'&&*key!='\t'&&*key!='\r'&&*key!='-'&&*key!=','&&*key!='.') // if((c >= 65&& c<= 90)||(c>=97&&c<=122)||(c>=48&&c<=57) )
	  {
           words[wordLength] = *key;
	   		wordLength++;
          }
          else
	  
	  {
	  if(wordLength>0)
		{
			words[wordLength] = '\0';
			wordLength++;
			//printf("%s\n",words);	
			URLRecordList *tmp = NULL;        
        if (_wordToURLRecordList->find(words, &tmp) == false)
        {
            URLRecordList *data = new URLRecordList();
            data->_urlRecordIndex = kcount;
            data->_next = NULL;
            							printf("%s\n",words);	
            _wordToURLRecordList->insertItem(words, data);
        }
        else
        {
            URLRecordList *data = new URLRecordList();
            data->_urlRecordIndex = kcount;
            data->_next = tmp;
            							printf("%s\n",words);	
            _wordToURLRecordList->insertItem(words, data);
        }


			printf("%s\n",words);
			for(j=0;j<wordLength;j++)
		{
			words[j] = '\0';
		}
		wordLength = 0;		
		}
		else
			{
				wordLength = 0;
			}			
		}
		key++;

		}
	kcount++;
	//printf("count is %d\n",count);
}




 tr = 0;
	while(tr<_tailURL)
	{
		printf("url:%s\nkeyword:%s\ntitle:%s\ndescription:%s\n",_urlArray[tr]._url,_urlArray[tr]._keywords,_urlArray[tr]._title,_urlArray[tr]._description);//added description
		tr++;
	}
}
char * word = (char *)malloc(1000);//[MAXWORD];
char * t = word;

char * wordd = (char *)malloc(1000);//[MAXWORD];
char * td = wordd;

char * wordk = (char *)malloc(1000);//[MAXWORD];
char * tk = wordk;
char * ff = (char *)malloc(2000);//[MAXWORD]; 
//char * t1 = "";
//strcat(ff,t1);
int counter = 0;
//strcpy(word,"");
//int wordlength;
int co = 0;
int flaga = 0;
void WebCrawler :: onContentFound(char c)
{
	//printf("flaga is %d",flaga);
	//printf ("c is %c",c);	
	if(c>='A'&&c<='Z')
	{
		c = c+32;	
	}
	if(c == ':')	
	{
		flaga = 1;
		return;
	}	
	else if (c == '/')
		{
			flaga = 2;
			return;
		}
	else if(c == ']')
		{	
			flaga = 3;
			return;
		}
	if(c=='[')
	{
		if(flaga == 3)
		{
		*t = '\0';
		_urlArray[_headURL]._title = strdup(word);//-strdup for ftrcat
		//_des[_headURL]._title = strdup(word);	
		//printf("utit %s\n",_urlArray[_headURL]._title);
		//printf("%s\n",word);
		for(int i =0;i<strlen(word);i++)
		{
			word[i] = '\0';
		}
		t = word;
		}
		if(flaga == 1)
		{
		*td = '\0';
		_urlArray[_headURL]._description = strdup(wordd);
		//_des[_headURL]._description = strdup(wordd);	
		//printf("udec %s\n",_des[_headURL]._description);	
		//printf("udec %s\n",_urlArray[_headURL]._description);
		//printf("wordd is %s\n",wordd);
		for(int i =0;i<strlen(wordd);i++)
		{
			wordd[i] = '\0';
		}
		td = wordd;
		}		
		if(flaga == 2)
		{
		*tk = '\0';
		_urlArray[_headURL]._keywords = strdup(wordk);
		//_des[_headURL]._keywords = strdup(wordk);		
		//printf("udec %s\n",_des[_headURL]._keywords);//_urlArray[_headURL]._description);
		//printf("ukey %s\n",_urlArray[_headURL]._keywords);
		//printf("wordk is %s\n",wordk);
		for(int i =0;i<strlen(wordk);i++)
		{
			wordk[i] = '\0';
		}
		tk = wordk;
		}
		return;	
	}
	if(flaga == 1)
	{	
	*td = c;
	td++;	
   return;	
	}
	else if (flaga == 2)
		{
			if(c == '\"')
			{
				flaga = 4;
			}
			*tk = c;
			//printf("c is %c",c);	
			
			tk++;
			return;
		}
	else if (flaga == 3)
		{
			*t = c;
			t++;
			return;
		}
}

void WebCrawler:: writeURLFile(const char * urlFileName)
{
	FILE * f;
	f = fopen(urlFileName,"w");
	
	for(int i = 0; i<_tailURL;i++)
	{
		 fprintf(f, "%d %s\n", i, _urlArray[i]._url);
        if (_urlArray[i]._description != NULL)
            fprintf(f, "%s\n", _urlArray[i]._description);
        else
            fprintf(f, "%s\n", "");
		        if (_urlArray[i]._title != NULL)
            fprintf(f, "%s\n", _urlArray[i]._title);
        else
            fprintf(f, "%s\n", "");
		        if (_urlArray[i]._keywords != NULL)
            fprintf(f, "%s\n", _urlArray[i]._keywords);
        else
            fprintf(f, "%s\n", "");
		
        fprintf(f, "\n");
    }
    
    fclose(f);
}


  
void
WebCrawler::writeWordFile(const char *wordFileName)
{


     FILE *file;
    file = fopen(wordFileName, "w");
    
    int *printed;
    
    int i;
    for (i = 0; i < 2039; i++)
    {
        if (_wordToURLRecordList->_buckets[i] == NULL)
            continue;
        
        fprintf(file, "%s", _wordToURLRecordList->_buckets[i]->_key);
        
        URLRecordList *curr = _wordToURLRecordList->_buckets[i]->_data;
        
        printed = new int[2039];
        
        int j;
        for (j = 0; j < 2039; j++)
        {
            printed[j] = -1;
        }
        
        while (curr != NULL)
        {
            if (curr->_urlRecordIndex < 0 ||
                curr->_urlRecordIndex > 20390)
            {
                break;
            }
            
            int found = 0;
            for (j = 0; j < 2039; j++)
            {
                if (printed[j] < 0) break;
                
                if (printed[j] == curr->_urlRecordIndex)
                {
                    found = 1;
                    break;
                }
            }
            
            if (found == 0)
            {
                fprintf(file, " %d", curr->_urlRecordIndex);
                
                for (j = 0; j < 2039; j++)
                {
                    if (printed[j] < 0)
                    {
                        printed[j] = curr->_urlRecordIndex;
                        break;
                    }
                }
            }
            
            curr = curr->_next;
        }
        
        fprintf(file, "\n");
    }
    
    fclose(file);/*	FILE *f;
	f = fopen(wordFileName,"w");
	int * hate;

	for(int i = 0;i<2039;i++)
		{
			if(_wordToURLRecordList->_buckets[i] == NULL)
            {
				continue;
			}
			 fprintf(file, "%s", _wordToURLRecordList->_buckets[i]->_key);
		     URLRecordList *current = _wordToURLRecordList->_buckets[i]->_data;		
					
		}	*/
}



int main(int argc, char ** argv)
{
	int n = 1;//change for moss
	

	if(argc < 2)
		{
			printf("ERROR\n");
			return 0;
		}
	int max = 1000;

	if(!strcmp(argv[1],"-u"))
	{
		max = atoi(argv[2]);
		n = 3;	
	}

	const char **initialUrls = new const char*[(argc - n)];//now for 1 later for all
	int i;
	for (i = n; i < argc; i++)
	{
		initialUrls[i - n] = argv[i];
	}
		

	    WebCrawler *crawler = new WebCrawler(max, (argc - n), initialUrls);
	    crawler->crawl();
		crawler->writeURLFile("url.txt");
		crawler->writeWordFile("word.txt");	
		
	return 0;
}



