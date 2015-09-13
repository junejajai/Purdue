//
//  hashtable.h
//  
//
//  Created by Jaideep Juneja on 7/15/15.
//
//

struct HashTableVoidEntry{
    const char * key;
    void * data;
    HashTableVoidEntry * next;
};

class HashTableVoid
{
    enum
    {
        TableSize = 2000;
    }
    
    HashTableVoidEntry ** buckets;
    int hash(const char * key);
    int _n;
    
public:
    HashTableVoid();
    bool insertItem(const char * key, void * data);
    bool find(const char * key, void ** data);
    bool removeItem(const char * key);
};