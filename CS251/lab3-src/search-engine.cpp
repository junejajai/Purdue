
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "search-engine.h"


DictionaryType dictType;

//hrtime_t average;
int search = 0;
//char word[1000];
//int wordLength;
int nyot = 0;
SearchEngine::SearchEngine( int port, DictionaryType dictionaryType):
  MiniHTTPD(port)
{
  // Create dictionary of the indicated type
	if(dictionaryType == ArrayDictionaryType) //|| nyot==1)
	{
		_wordToURLList = new ArrayDictionary();
		//printf("1\n");
	}

	else if(dictionaryType == HashDictionaryType)//||nyot==2)
	{
		_wordToURLList = new HashDictionary();
		//printf("2\n");
	}

	else if(dictionaryType == AVLDictionaryType)//||nyot==3)
	{
		_wordToURLList = new AVLDictionary();
		//printf("3\n");
	}

	else if(dictionaryType == BinarySearchDictionaryType)
	{
		_wordToURLList = new BinarySearchDictionary();
		//printf("4\n");
	}
	else
	{
		_wordToURLList = NULL;
	}
	 dictType = dictionaryType;
     
	FILE * file = fopen("url.txt","r");
	char * l = (char *)malloc(500*sizeof(char));
	URLRecord **record = new URLRecord*[1011];
	
	for(int i =0;i<1011;i++)
	{
		record[i] = new URLRecord();
	}	
	
	int c;

	//while(f)//fgets(file,500,file))
	while(fgets(l,500,file))
	{
		if (strcmp(l, "\n") != 0)
		{
		char * hold = l;//new char[512];
		//hold = strtok(l," ");
		
		//char * t = hold;
		char * s = new char[20];
		char * no = s;		
		while(*hold!=' ')
		{
			*no=*hold;
			no++;
			hold++;
		}
		*no='\0';
		int index = atoi(s);//atoi(hold);
		char * ne = new char[600];
		char * t=ne;		
		//hold = strtok(NULL," \n");	
		while(*hold!='\n')
		{
			*t=*hold;
			hold++;
			t++;
		}	
		*t='\0';	
		char* url = strdup(ne);//strdup(hold);
			
		fgets(l,500,file);
		hold = l;//strtok(l,"\n");
		char * ui = new char[700];
		char * de = ui;
		while(*hold!='\n')
		{
		*de=*hold;
		de++;
		hold++;
		}	
		*de='\0';
		char * desc = strdup(ui);//(hold);
			printf("%d\n %s\n %s\n",index,url,desc);
			record[index]->_url = url;
			record[index]->_description = desc;		
			//printf("%d, %s, %s\n",index,record[index]->_url,record[index]->_description);		
		}
	}					
		
	delete l;
	fclose(file);	

	file = fopen("word.txt","r");
	l = new char[530];

	while(fgets(l,530,file))
	{
		if(strcmp(l,"\n")!=0)
		{
			char* tok = new char[512];
			tok = strtok(l," \n");
			char * wo = new char[512];
			strcpy(wo,tok); 
			//printf("%s\n",wo);
			
			URLRecordList * e = NULL;
			URLRecordList * prev = NULL;
			
			tok = strtok(NULL," \n");	
			while(tok!=NULL)
			{
				int position = atoi(tok);
				//printf("%d\n",position);	
				if (record[position]->_url == NULL)
					continue;
				URLRecordList * ent = new URLRecordList();
				if(e==NULL)
				{
					e = ent;
					}
					ent->_urlRecord = record[position];
					ent->_next = NULL;

					if(prev != NULL)
						prev->_next = ent;
					
					prev = ent;

				tok = strtok(NULL," \n");	
			}
				_wordToURLList->addRecord(wo, (URLRecordList*)e);
				delete wo;
				delete tok;

		}
	}
		delete l;
		fclose(file);		
	
	
  // Populate dictionary and sort it if necessary
}

void
SearchEngine::dispatch( FILE * fout, const char * documentRequested)
{
  if (strcmp(documentRequested, "/")==0) {
    // Send initial form
    fprintf(fout, "<TITLE>CS251 Search Engine</TITLE>\r\n");
	fprintf(fout, "<body background=\"http://img2.goodfon.ru/original/2016x1080/e/62/art-ronald-reygan-avtomat.jpg\">");
    fprintf(fout, "<CENTER><H1><em><font face = \"verdana\" color = \"gray\">Boiler Search</font></em></H1>\n");
    fprintf(fout, "<H2>\n");
    fprintf(fout, "<FORM ACTION=\"search\">\n");
    fprintf(fout, "<font face = \"verdana\" color = \"blue\">Search:\n</font>");
    fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
    fprintf(fout, "</H2>\n");
    fprintf(fout, "</FORM></CENTER>\n");	
	fprintf(fout, "<CENTER><H3><font face = \"verdana\" color = \"purple\">By Jaideep S. Juneja\n</font></H3></CENTER>");	
	fprintf(fout, "</body>");
    return;
  }
	if(strlen(documentRequested)<13)
	{
		return;	
	}
	
	char * parameters = new char[strlen(documentRequested)+2];
	strcpy(parameters,documentRequested+13);
	
	char ** searchword = new char*[200];
	for(int i=0;i<200;i++)
		{
			searchword[i] = NULL;
		 }
	int n = 0;
	char * word = new char[150];
	word = strtok(parameters,"+");//may have to malloc
		
	while(word!=NULL)
		{		
			searchword[n]= new char[100];
			strcpy(searchword[n],word);
			n++;
			word = strtok(NULL,"+");
		}	
	
  // TODO: The words to search in "documentRequested" are in the form
  // /search?word=a+b+c
  //
  // You need to separate the words before search
  // Search the words in the dictionary and find the URLs that
  // are common for al the words. Then print the URLs and descriptions
  // in HTML. Make the output look nicer.

  // Here the URLs printed are hardwired
  
  //const int nurls=2;

  //const char * words = "data structures";

  //const char * urls[] = {
    //"http://www.cs.purdue.edu",
    //"http://www.cs.purdue.edu/homes/cs251"
  //};
  
  //const char * description[] = {
   // "Computer Science Department. Purdue University.",
    //"CS251 Data Structures"
  //};
char * q = new char[5020];
strcpy(q,"");
for(int i=0;i<n;i++)
	{
		strcat(q,searchword[i]);
		if(i!=n-1)
		strcat(q," ");//can also be for all i except last one
	}
	
	
  fprintf( stderr, "Search for words: \"%s\"\n", q);//words);

  fprintf( fout, "<TITLE>CS251 Search Results</TITLE>\r\n");
  fprintf( fout, "<body background=\"http://i.imgur.com/rPNFro2.jpg\" style=\"background-attachment:fixed\">");
  fprintf( fout, "<H1> <Center><em><font color = \"gray\">Boiler Search</font></em></H1>\n");
  fprintf( fout, "<H2> <font color = \"purple\">Search Results for \"%s\"</font></center></H2>\n", q);//words );

 // for ( int i = 0; i < nurls; i++ ) {
   // fprintf( fout, "<h3>%d. <a href=\"%s\">%s</a><h3>\n", i+1, urls[i], urls[i] );
    //fprintf( fout, "<blockquote>%s<p></blockquote>\n", description[i] );
  //}


	int c = 0;
	int lc = 0;
	
	URLRecord ** list = new URLRecord*[600];
	for(int i = 0;i<n;i++)
	{
		URLRecordList * data = (URLRecordList*)_wordToURLList->findRecord(searchword[i]);
		
		while(data!=NULL)
		{
			int flag = 1;
			for(int j = 0;j<lc;j++)
			{
				if(list[j] == data->_urlRecord)
				{
					flag = 0;
					break;	
				}
			}
			if(flag==1)
			{
					list[lc] = data->_urlRecord;
				lc++;
			}
		data=data->_next;	
		}	
	}

	//herte
	//printf("before\n");
	for(int i = 0;i<lc;i++)
		{
			for(int j =0;j<n;j++)
			{
			URLRecordList * data = (URLRecordList*)_wordToURLList->findRecord(searchword[j]);
		int flag = 1;
		while(data!=NULL)
		{
			
			
				if(list[i] == data->_urlRecord)
				{
					flag = 0;
					//data=data->_next;	
					//continue;	
				}
			//flag = 0;
			
		data=data->_next;	
		}	
		if(flag==1)
		{
			list[i]=NULL;
		}
		}	
		}
	//printf("after\n");
 //search++;
 for ( int i = 0; i < lc; i++ ) {	
	if(list[i]==NULL)	
	{
		continue;
		}	
   fprintf( fout, "<h3>%d. <a href=\"%s\">%s</a><h3>\n", c+1, list[i]->_url, list[i]->_url);
    fprintf( fout, "<blockquote>%s<p></blockquote>\n", list[i]->_description);
	c++;
  }
/*if(dictType==ArrayDictionaryType)
	{
		fprintf(fout,"<h3><font color = \"red\">Dictionary Used is ArrayDictionary</font></h3>\n");
	}	

else if(dictType==HashDictionaryType)
	{
		fprintf(fout,"<h3><font color = \"green\">Dictionary Used is HashDictionary</font></h3>\n");
	}	
else if(dictType==BinarySearchDictionaryType)
	{
		fprintf(fout,"<h3><font color = \"red\">Dictionary Used is BinSearchDictionaryDictionary</font></h3>\n");
	}	
else if(dictType==AVLDictionaryType)
	{
		fprintf(fout,"<h3><font color = \"purple\">Dictionary Used is AVLDictionary</font></h3>\n");
	}	

else
	{
		fprintf(fout,"<h3>Dictionary Used is UnknownDictionary</h3>\n");
	}
*/


	
	
  // Add search form at the end
  fprintf(fout, "<HR><H2>\n");
  fprintf(fout, "<FORM ACTION=\"search\">\n");
  fprintf(fout, "Search:\n");
  fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
  fprintf(fout, "</H2>\n");
  fprintf(fout, "</FORM>\n");
  fprintf(fout, "</body>");
}

void
printUsage()
{
  const char * usage =
    "Usage: search-engine port (array | hash | avl | bsearch)\n"
    "  It starts a search engine at this port using the\n"
    "  data structure indicated. Port has to be larger than 1024.\n";

  fprintf(stderr, "%s", usage);
}

int main(int argc, char ** argv)
{
  if (argc < 3) {
    printUsage();
    return 1;
  }
printf("%s\n",argv[2]);
  // Get port
  int port;
  sscanf( argv[1], "%d", &port);
	
  // Get DictionaryType
  const char * dictType = argv[2];
  DictionaryType dictionaryType;
  if (!strcmp(dictType, "array")) {
    dictionaryType = ArrayDictionaryType;
	nyot = 1;
	printf("1\n");
  }
  else if (!strcmp(dictType, "hash")) {
    dictionaryType = HashDictionaryType;
	nyot = 2;
	printf("2\n");
  }
  else if (!strcmp(dictType, "avl")) {
    dictionaryType = AVLDictionaryType;
	nyot =3;
	printf("3\n");  
	}
  else if (!strcmp(dictType, "bsearch")) {
    dictionaryType = BinarySearchDictionaryType;
	nyot =4;	
	printf("4\n");  
	}
  else {
    printUsage();
    return 0;
  }
  
  SearchEngine httpd(port, dictionaryType);
  
  httpd.run();

  return 0;
}








#define MAXWORD 1000
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





