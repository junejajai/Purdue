
#include "SimpleHTMLParser.h"
#include "openhttp.h"
#include <string.h>
#include <stdlib.h>
SimpleHTMLParser::SimpleHTMLParser()
{
}

bool
SimpleHTMLParser::match(char **b, const char *m) {
	int len = strlen(m);
	if ( !strncasecmp(*b, m, len)) {
		(*b)+=len;
		return true;
	}
	return false;
}

bool
SimpleHTMLParser::parse(char * buffer, int n)
{
	enum { START, TAG, SCRIPT, ANCHOR, HREF,
	       COMMENT, FRAME, SRC, TITLE, METAK, METAD, METAN } state;//added case TITLE

	state = START;
	
	char * temp = (char*)malloc(1000*sizeof(char));//added
	char * in = temp;
	int flag = 0;	
	int ent = 0;	
	char * bufferEnd = buffer + n;
	char * b = buffer;
	bool lastCharSpace = false;
	while (b < bufferEnd) {
		//printf("<%c,%d,%d>", *b, *b,state);
		switch (state) {
		case START: {
			if (match(&b,"<SCRIPT")) {
				state = SCRIPT;
			}
			else if (match(&b,"<TITLE>"))//added this elif
			{
				state = TITLE;
			}
			else if(match(&b,"<META NAME=\"KEYWORDS\" CONTENT=\""))//added METAK
				{
					state = METAK;
				}
			else if(match(&b,"<META NAME=\"DESCRIPTION\" CONTENT=\""))//added METAD
				{
					state = METAD;
				}
			else if(match(&b,"<META CONTENT=\""))//added METAN
				{
					state = METAN;
				}				
			else if (match(&b,"<!--")) {
				state = COMMENT;
			}
			else if (match(&b,"<A ")) {
				state = ANCHOR;
			}
			else if (match(&b,"<FRAME ")) {
				state = FRAME;
			}
			else if	(match(&b,"<")) {
				state = TAG;
			}
			
			else {
				char c = *b;
				//Substitute one or more blank chars with a single space
				/*if (c=='\n'||c=='\r'||c=='\t'||c==' ') {
					if (!lastCharSpace) {
						onContentFound(' ');
					}
					lastCharSpace = true;
				}
				else {
					onContentFound(c);
					lastCharSpace = false;
				}*/
				
				b++;
			}
			break;
		}
		case ANCHOR: {
			if (match(&b,"href=\"")) {
				state = HREF;
				urlAnchorLength=0;
				//printf("href=");
			}
			else if (match(&b,">")) {
				// End script
				state = START;
			}
			else {
				b++;
			}
			break;
				
		}
		case HREF: {
			if (match(&b,"\"")) {
				// Found ending "
				state = ANCHOR;
				urlAnchor[urlAnchorLength] = '\0';
				onAnchorFound(urlAnchor);
				//printf("\n");
			}
			else {
				if ( urlAnchorLength < MaxURLLength-1) {
					urlAnchor[urlAnchorLength] = *b;
					urlAnchorLength++;
				}
				//printf("%c", *b, *b);
				b++;
			}
			break;
		}
		case TITLE://addded this case
		{
		if(ent == 0)
		{
			onContentFound(']');
			ent ++;
		}
			
		if(match(&b,"</title>"))
			{
			onContentFound('\n');
			onContentFound('[');
			ent = 0;
			state = START;
			}
			else 
			{
			onContentFound(*b);	
			b++;
			}
			break;
		}
		case FRAME: {
			if (match(&b,"src=\"")) {
				state = SRC;
				urlAnchorLength=0;
				//printf("href=");
			}
			else if (match(&b,">")) {
				// End script
				state = START;
			}
			else {
				b++;
			}
			break;
				
		}
		case METAK://adding
			{
			if(ent == 0)
		{
			onContentFound('/');
			ent ++;
		}
			if(match(&b,"\" />"))
			{
				onContentFound('[');
				ent = 0;
				state = START;
				break;
			}
			//printf("ninet\n");
			//if(match(&b,))
			onContentFound(*b);	
			b++;
			break;	
			}
		case METAD://adding
			{
			if(ent == 0)
		{
			onContentFound(':');
			ent ++;
		}
			if(match(&b,"\" />")||match(&b,">"))
			{
				onContentFound('[');
				ent = 0;
				state = START;
				break;
			}
			//printf("ninet\n");
			//if(match(&b,))
			onContentFound(*b);	
			b++;
			break;	
			}
		case METAN://added
			{
				//if(match(&b,"NAME=\"DESCRIPTION\"/>") || match(&b,"NAME=\"KEYWORDS\"/>"))
				/*if(match(&b,"/>"))
				{
					onContentFound('[');
					printf("END\n");
					state = START;
					break;	
				}*/	
				//if(ent ==0)
				//{
				//	ent = 1;
				//	onContentFound(';');
				//}
				flag  = 0;
				for(int i = 0;i<strlen(temp);i++)
					{
						*temp ='\0';
						temp ++;						
						}
				temp = in;
				while(!match(&b,"/>"))//&&(!match(&b,">")))
				{ 
			/*	if(match(&b,">"))//kind of added
					{
						flag = 1;
					ent = 2;	
					state = START;
					break;
						//break;
					}*/
				//printf("y0u\n");
				*temp = *b;	
				//onContentFound(*temp);
				//printf("%c\n",*temp);
				//onContentFound(*b);
				//b++;
				//temp++;
				if(match(&b,"NAME=\"DESCRIPTION\"/>"))// || match(&b,"NAME=\"KEYWORDS\"/>"))
				{
					//onContentFound(':');
					//temp = in;
					//printf("entry\n");
					flag = 1;
					ent = 1;
					state = START;
					break;
				}
				else if(match(&b,"NAME=\"KEYWORDS\"/>"))
				{
					//onContentFound('/');
					//temp = in;
					//printf("entry\n");
					flag = 1;
					ent = 2;	
					state = START;
					break;	
				}
				else if(match(&b,"\">"))
					{
						temp = in;
						state = START;
						flag = 0;
						ent = 0;
						break;		
					}
			b++;
			temp++;
			}
	//printf("jk: %s\n", in);
			*temp = '\0';
			temp = in;
			
			int l = 0;
//printf("%ld\n",strlen(in));
                if(flag == 0)
				{
					state = START;
					temp = in;
					ent = 0;	
					break;
				}
			
			else
 				{
				if(ent == 1)
				{
					onContentFound(':');
					while(l<(strlen(in)))
				{
					//onContentFound(*(temp+l));
					//printf("w1 %c\n",*(temp+l));	
					onContentFound(*temp);			
					l++;
					temp++;
				}		
				//do something
				}	
				else
					{
						onContentFound('/');
						//do somefink else
						while((l<(strlen(in)) && (*temp!='\"')))
				{
					//onContentFound(*(temp+l));
					//printf("w1 %c\n",*(temp+l));	
					onContentFound(*temp);
					//printf("*temp is %c",*temp);			
					l++;
					temp++;
				}	
						}	
				/*while(l<(strlen(in)))
				{
					//onContentFound(*(temp+l));
					//printf("w1 %c\n",*(temp+l));	
					onContentFound(*temp);			
					l++;
					temp++;
				}*/	
				}
			temp = in;
			/*for(int i = 0; i<strlen(temp);i++)
			{
			*(temp+i) = '\0';	
			}*/
			onContentFound('[');
			state = START;	
			break;
		}	
		case SRC: {
			if (match(&b,"\"")) {
				// Found ending "
				state = FRAME;
				urlAnchor[urlAnchorLength] = '\0';
				onAnchorFound(urlAnchor);
				//printf("\n");
			}
			else {
				if ( urlAnchorLength < MaxURLLength-1) {
					urlAnchor[urlAnchorLength] = *b;
					urlAnchorLength++;
				}
				//printf("%c", *b, *b);
				b++;
			}
			break;
		}
		case SCRIPT: {
			if (match(&b,"/SCRIPT>")) {
				// End script
				state = START;
			}
			else {
				b++;
			}
			break;
		}
		case COMMENT: {
			if (match(&b,"-->")) {
				// End comments
				state = START;
			}
			else {
				b++;
			}
			break;
		}
		case TAG: {
			if (match(&b, ">")) {
				state = START;
			}
			else {
				b++;
			}
			break;
		}
		default:;
		}
		
	}
}

void
SimpleHTMLParser::onContentFound(char c) {
}

void
SimpleHTMLParser::onAnchorFound(char * url) {
}
