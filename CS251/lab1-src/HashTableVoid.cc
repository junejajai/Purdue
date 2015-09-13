
//
// CS251
// Implementation of a HashTable that stores void *
//
#include "HashTableVoid.h"

// Obtain the hash code of a key
int HashTableVoid::hash(const char * key)
{
	// Add implementation here
	int n = 0;
	while(*key != '\0')
	{
		n = n + *key;
		key++;
	}
	return n%TableSize;
}

// Constructor for hash table. Initializes hash table
HashTableVoid::HashTableVoid()
{
	_buckets = /*new HashTableVoidEntry *[TableSize];*/(HashTableVoidEntry**)malloc(TableSize*sizeof(HashTableVoidEntry*));
	for(int i = 0; i <TableSize;i++)
	{
		_buckets[i] = NULL;
	}	 
	// Add implementation here

}

// Add a record to the hash table. Returns true if key already exists.
// Substitute content if key already exists.
bool HashTableVoid::insertItem( const char * key, void * data)
{
	// Add implementation here
	int posn = hash(key);
	HashTableVoidEntry * e = _buckets[posn];
	while(e!=NULL)
	{
		if(!strcmp(e->_key,key))
		{
			e->_key = key;
			e->_data = data;
			return true;
		}		
		e = e->_next;
	}    
	e = new HashTableVoidEntry;
	e->_key = strdup(key);
	e->_data = data;
	e->_next = _buckets[posn];
	_buckets[posn]=e;
	return false;
}

// Find a key in the dictionary and place in "data" the corresponding record
// Returns false if key is does not exist
bool HashTableVoid::find( const char * key, void ** data)
{
	// Add implementation here
	int h = hash(key);
	HashTableVoidEntry * e = _buckets[h];

	while(e!=NULL)
	{
		if(!strcmp(e->_key,key))
		{
			*data = e->_data;
			return true;
		}
		e = e->_next;
	}
	return false;
}

// Removes an element in the hash table. Return false if key does not exist.
bool HashTableVoid::removeElement(const char * key)
{
	int h = hash(key);
	HashTableVoidEntry * e = _buckets[h];
	HashTableVoidEntry * prev = NULL;
	while(e!=NULL)
	{
		if(strcmp(e->_key,key)==0)
		{
			if(prev == NULL)
			{
				_buckets[h] = e->_next;
			}
			else
			{
				prev->_next = e->_next;
			}
			free((char*)e->_key);
			delete e;
			return true;
		}

		prev = e;
		e = e->_next;
	}	
	// Add implementation here
	return false;
}

// Creates an iterator object for this hash table
HashTableVoidIterator::HashTableVoidIterator(HashTableVoid * hashTable)
{
	// Add implementation here
	_currentBucket = 0;
	_hashTable = hashTable;
	_currentEntry = _hashTable->_buckets[_currentBucket];
}

// Returns true if there is a next element. Stores data value in data.
bool HashTableVoidIterator::next(const char * & key, void * & data)
{
	// Add implementation here
	if(_currentEntry == NULL)
	{ 
		_currentBucket++;
		while(_hashTable->_buckets[_currentBucket]==NULL)
		{
			//		printf("1\n");
			_currentBucket++;
		}	_currentEntry = _hashTable->_buckets[_currentBucket];
		//	}
		if(_currentBucket < 2039)
		{
			key = _currentEntry->_key;
			data = _currentEntry->_data;
			_currentEntry = _currentEntry->_next;
			return true;
		}
		else
			return false;
}
else
{
	key = _currentEntry->_key;
	data = _currentEntry->_data;
	_currentEntry = _currentEntry->_next;
	return true;
}
return false;
}


