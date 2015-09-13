#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//
// Sort an array of element of any type
// it uses "compFunc" to sort the elements.
// The elements are sorted such as:
//
// if ascending != 0
//   compFunc( array[ i ], array[ i+1 ] ) <= 0
// else
//   compFunc( array[ i ], array[ i+1 ] ) >= 0
//
// See test_sort to see how to use mysort.
//
void mysort( int n,                      // Number of elements
		int elementSize,            // Size of each element
		void * array,               // Pointer to an array
		int ascending,              // 0 -> descending; 1 -> ascending
		CompareFunction compFunc )  // Comparison function.
{
	char * p = (char*)array;	
	int i = 0;
	int j = 0;
	for(i=0;i < n;i++)
	{
		for(j=0;j<n-1-i;j++)

		{
			if(ascending!=0)
			{


				if(compFunc((p+(j*elementSize)),(p+(elementSize*(j+1)))) >= 0)
					//if(compFunc(array[j],array[j+1]) <= 0 )
				{
					int k;
					for(k=0;k<elementSize;k++)
					{
						//if(compFunc(*(p+j),*(p+(j+1))) <= 0)
						//printf("Looping in first loop\n");
						char temp = *(p+(elementSize*j)+k);
						*(p+(elementSize*j)+k) = *(p+(elementSize*(j+1))+k);
							*(p+(elementSize*(j+1)+k)) = temp;
					}

				}
			}
			else
			{
                         if(compFunc((p+(j*elementSize)),(p+(elementSize*(j+1))))<=0)
			 {
			 int k;
			 for(k=0;k<elementSize;k++)
			 {
			 char temp = *(p+(elementSize*j)+k);
			 *(p+(elementSize*j)+k) = *(p+(elementSize*(j+1))+k);
			 *(p+(elementSize*(j+1)+k)) = temp;
			 }
			 }
			}

		}


	}
	// Add your code here
}

