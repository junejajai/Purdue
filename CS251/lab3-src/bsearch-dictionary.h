
// Implementation of a dictionary using an array and binary search
// The class inherits from ArrayDictionary

#include "array-dictionary.h"

class BinarySearchDictionary : public ArrayDictionary {
  // Add any member variables you need
  bool sorted;
public:
  // Constructor
  BinarySearchDictionary();
  
  bool addRecord( KeyType key, DataType record);
  
  // Find a key in the dictionary and return corresponding record or NULL
  // Use binary search
  DataType findRecord( KeyType key);

  // Sort array using heap sort.
  void sort();
	void siftDown(int root, int bottom);
    // Removes one element from the table
  //bool removeElement(KeyType key);

  // Returns all the elements in the table as an array of strings.
  // *n is the size of the table and it is returned by reference
  //KeyType * keys(int * n);

  // Add other methods you may need
};

