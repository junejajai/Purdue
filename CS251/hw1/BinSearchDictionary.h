//
//  BinSearchDictionary.h
//  
//
//  Created by Jaideep Juneja on 7/15/15.
//
//

struct BinSearchEntry{
    char * key;
    void * item;
};

class BinSearchDictionary{
    int maxEntries; // Max entries
    int n; // Current size of table
    BinSearchEntry *table;
    bool sorted; // Is table sorted
    
public:
    BinSearchDictionary(int maxEntries);
    void insert(char * key, void * item);
    void * find(char * key); // Given a key, return item.
};