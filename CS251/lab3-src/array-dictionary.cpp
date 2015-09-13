
// Implementation of a dictionary using an array and sequential search
// The array will be dynamically resized if necessary

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "array-dictionary.h"

// Constructor
ArrayDictionary::ArrayDictionary()
{
  // Add your code here
	maxNumber = 1050;
	currentNumber = 0;
	array = new ArrayDictionaryNode[maxNumber];
}

// Add a record to the dictionary. Returns false if key already exists
bool
ArrayDictionary::addRecord( KeyType key, DataType record)
{
        // Add your code here
	for(int i = 0;i<currentNumber;i++)
	{
		if(!strcmp(array[i].key,key))
		{
				array[i].data = record;//(DataType*)record;
				return false;
			}
	}
	if(currentNumber>=maxNumber)
		{
		int currSize = maxNumber;
		maxNumber = maxNumber * 4;
		ArrayDictionaryNode *temp = new ArrayDictionaryNode[maxNumber];
		for(int i = 0;i<currentNumber-1;i++)	
		{
			temp[i] = array[i];
			array[i] = array[i+1];
			array[i+1] = temp[i+1];
		}
		delete [] array;
		array = temp;	
		}	
	
	array[currentNumber].key = strdup(key);
	array[currentNumber].data = record;
	currentNumber++;
	return true;
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
ArrayDictionary::findRecord( KeyType key)
{
	/*if(!strcmp(key,"a"))
	{
	return NULL;
	}*/
		for(int i = 0;i<currentNumber;i++)
	{
		if(strcmp(array[i].key,key) == 0)
		{
				//printf("%s\n",key);
				return (DataType)array[i].data;
			}
	}
        // add your code here

	return NULL;
}

// Removes one element from the table
bool
ArrayDictionary::removeElement(KeyType key)
{
		if(currentNumber == 0)
			{
				return false;
			}
	int f = 0;
        // Add your code here
	for(int i = 0;i<currentNumber;i++)
	{
		if(!strcmp(array[i].key,key))
		{
			f = 1;
			break;
			}
	}
	if(f==0)
	{
		return false;
	}
	    ArrayDictionaryNode *temp = new ArrayDictionaryNode[maxNumber];
		int index = 0;
	for(int i = 0;i<currentNumber;i++)
	{
		if (strcmp(array[i].key, key) == 0)
            continue;
		
		temp[index].key = (char*)malloc(sizeof(char)*50);
	    strcpy(temp[index].key, array[i].key);
		temp[index].data = new DataType;
		temp[index].data = array[i].data; 
		index++;
		}
		delete[] array;
		array = temp;
	currentNumber--;

	return true;
	
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
ArrayDictionary::keys(int * n)
{
	 KeyType* record = new KeyType[currentNumber];
	
	int i;
	for (i = 0; i<currentNumber; i++)
	{
		record[i] = (char*)malloc(sizeof(char)*20);
		strcpy((char*)record[i], array[i].key);
	}
	
	*n = currentNumber;
	
	return record;
        // Add yoru code here
	//return NULL;
}
