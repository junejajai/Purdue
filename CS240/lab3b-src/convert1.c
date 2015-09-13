//#include<Math.h>
#include<stdio.h>
#include<stdlib.h>

int pow(int x,int y)
{
int i = 0;
int po = 1;
for(i = 0;i<y;i++)
{
po = po * x;
}
return po; 
}

int main(int argc,char ** argv)
{
if(argc<4)
{
printf("Usage:  convert <basefrom> <baseto> <number>\n");
exit(0);
}

int x = atoi(argv[1]);
int y = atoi(argv[2]);
unsigned long int t = atoi(argv[3]);
char * hello = argv[3];
printf("Number read in base %d: %d\n",x,t);
if(x<0||y<0)
{
printf("Error");
exit(0);
}
int t1 = t;
while(t1 > 0)
{
if((t1%10)>x)
{
printf("Wrong digit in number.\n");
exit(0);
}
t1 = t1/10;
}
int base = 0;
int numt = 0;
while(t > 0)
{
int temp = t%10; 

numt+=temp * pow(x,base);

t = t/10;
//printf("temp: %d ,numt: %d,t %d",temp,numt,t);
base++;
}

printf("Converted to base 10: %d\n",numt);
int store[100];
int ans = 0;
int l = 0;
while(numt>0)
{
//int temp = numt/;
store[l] = numt%y;
//int temp = numt%y;
//ans = ans *10 + temp;
numt = numt/y;
//printf("store[%d] %d numt %d y %d \n",l,store[l],numt,y);
l++;
}
int store1[100];
int i = 0;
for(i = l-1;i>=0;i--)
{
ans = ans*10+store[i];
}
printf("Converted to base %d: %d\n",y,ans );
}
																																														