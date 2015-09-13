#include<stdio.h>
#include<stdlib.h>

// It prints the bits in bitmap as 0s and 1s.
void printBits(unsigned int bitmap)
{
	// Add your code here
	int i = 0;
	for(i = 31;i >= 0;i--)
	{
		//print("");
		printf("%d",(bitmap>>i)&1);
	}
	printf("\n");
	//printf("10987654321098765432109876543210\n");
	for(i = 31;i>=0;i--)
	{
		printf("%d",i%10);
	}
	printf("\n");
}


// Sets the ith bit in *bitmap with the value in bitValue (0 or 1)
void setBitAt( unsigned int *bitmap, int i, int bitValue ) {
	// Add your code here
	unsigned int mask = 1 << i;
	unsigned int ma = ~(mask);
	*bitmap &= ma;
	*bitmap = *bitmap | (bitValue<<i);

}

// It returns the bit value (0 or 1) at bit i
int getBitAt( unsigned int bitmap, unsigned int i) {
	// Add your code here
	unsigned int mask = 1 << i;
	unsigned int n =  (bitmap & mask)>>i;
	return n;
}

// It returns the number of bits with a value "bitValue".
// if bitValue is 0, it returns the number of 0s. If bitValue is 1, it returns the number of 1s.
int countBits( unsigned int bitmap, unsigned int bitValue) {
	// Add your code here
	int count = 0;
	int i = 0;
	for(i=0;i<32;i++)
	{
		if(getBitAt(bitmap,i) == bitValue)
		{
			count++;
		}
	}

	return count;
}

// It returns the number of largest consecutive 1s in "bitmap".
// Set "*position" to the beginning bit index of the sequence.
// 00000000001111111100=pos=2;
int maxContinuousOnes(unsigned int bitmap, int * position) {
	// Add your code here
	int i = 0;
	int j;
	int pos;
	int count = 0;
	int maxcount = 0;
	for(i = 0; i<32;i++)
	{
		if(getBitAt(bitmap,i)==1)
		{
			count++;
			if(count == 1)
				pos = i;

			for(j = i+1;j<32;j++)
			{
				if(getBitAt(bitmap,j)==1)
				{
			          count++;
				}
				else
				{
					break;
				}
			}
			}
			if(maxcount<count)
			{
			maxcount = count;
			*position = pos;
			}
			count = 0;

		
	}
return maxcount;
}


