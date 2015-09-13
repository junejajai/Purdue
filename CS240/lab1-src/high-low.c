#include <stdio.h>

int main(int argc, char **argv) 
{
	printf("Welcome to the High Low game...\n");
	int high = 100;
	int low = 1;

	while (1)
	{
		int mid;
		printf("Think of a number between 1 and 100 and press press <enter>");
		getchar();
		while(high >= low)
		{ 
			mid = (high + low)/2;
			printf("Is it higher than %d? (y/n)\n",mid);
			char a = getchar();
			getchar();
			if(a == 'y')
			{
				low = mid + 1;
			}
			else if(a == 'n')
			{
				high = mid - 1;
			} 
			else
			{
				printf("Type y or n\n");

			}  
		}
		printf("\n>>>>>> The number is %d\n",high + 1);
		printf("\nDo you want to continue playing (y/n)?"); 
		char c = getchar();
		getchar();
		if(c == 'n')
		{ 
			break;
		}
		else if(c=='y')
		{
			high = 100;
			low = 1;
		}

	}
	printf("Thanks for playing!!!\n");

}

