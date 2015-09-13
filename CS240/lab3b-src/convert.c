#include <stdio.h>
#include<stdlib.h>
#include<string.h>
//int pow(int x , int y)
//{
  //  int i = 0;
   // int po = 1;
    //for(i = 0;i<y;i++)
    //{
     //   po = po*x;
    //}
    //return po;
//}

int main(int argc,char ** argv)
{
    if(argc<4)
    {
        printf("Usage:  convert <basefrom> <baseto> <number>\n");
        exit(0);
    }
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    char * number = argv[3];
    printf("Number read in base %d: %s\n",x,number);
    int num[38];
    int i = 0;
    char anum[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q'};
    //store string in int array	
int k = 0;
    for(i = 0;i<strlen(number);i++)
     {
           while(k<27)
        {
             if(number[i]==anum[k])
             {
               num[i]=k; 
               break;
             }
          k++;
        }
       k = 0; 
       if(num[i]>x)
        {
          //printf("num[%d] %d x %d \n",i,num[i],x );
            printf("Wrong digit in number.\n");
            exit(0);
         } 
     }
    // int p = i;
    // printf("%d \n",i);
    /* for(p = i-1; p>=0; p--)
     {
      printf("p[%d] =  %d \n",p,num[p] );
     }*/
    //Convert to base 10
    int numt = 0;
    int j = 0;
    int base = 0; 
    for(j=i-1;j>=0;j--)
     {
        numt += num[j] * pow(x,base);
        base++;
        //printf("num[j]: %d ,numt: %d,j %d \n",num[j],numt,j);
      }
      printf("Converted to base 10: %d\n",numt);
      //printf("change to specified base\n");
      int ans = 0;//Specified base conversion
      int l = 0;
      int m = 0;
      
      char store[100];
      while(numt!=0)
       {
           m = numt%y;
           store[l] = anum[m];
           l++;
           numt = numt/y;  
       }
    char store1[38];
    int u = 0;
    int r = 0;
  //  printf("%d",l-1);
    for(u = l-1 ;u>=0 ;u--)
    {
        store1[r] = store[u];

//        printf("%s",store1);
//	printf("r %d store1[%d] %c  store[%d] %c \n",r,r,store1[r],u,store[u] );
    r++;
    }
    
    // char * h;
   // int e = 0;
   // for(i = 0;i<r-1;i++)
   //{
   // h[i] = store1[i];  
   // e++;
   // }
  printf("Converted to base %d: %s\n",y,store1);


}
     

