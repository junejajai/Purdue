//
//  hashtable.cpp
//  
//
//  Created by Jaideep Juneja on 7/15/15.
//
//

#include "hashtable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

HashTableVoid()
{
    _n = TableSize;
    buckets = (HashTableVoidEntry **) malloc(_n * sizeof(HashTableVoidEntry *));
    for (int i = 0; i<_n; i++) {
        buckets[i] = NULL;
    }
}

int HashTableVoid::hash(const char * key)
{
    int s = 0;
    
    for(int i = 0;i<strlen(key);i++)
    {
        s+=key[i] * (i+1);
    }
    return s%_n;
}

bool HashTableVoid::find(const char * key, void ** data)
{
    int h = hash(key);
    HashTableVoidEntry * e = buckets[h];
    
    while (e!=NULL) {
        if(!strcmp(e->key,key))
        {
            *data = e->data;
            return true;
        }
        e = e->next;
    }
}


bool HashTableVoid::insertItem(const char * key, void * data)
{
    int h = hash(key);
    HashTableVoidEntry * e = buckets[h];
    
    while (e!=NULL) {
        if(!strcmp(e->key,key))
        {
            e->data = data;
            return true;
        }
        e=e->next;
    }
    e = new HashTableVoidEntry;
    e->key = strdup(key);
    e->data = data;
    e->next = buckets[h];
    buckets[h]=e;
    return false;
}

bool removeItem(const char * key){
    int h = hash(key);
    HashTableVoidEntry * e = buckets[h];
    HashTableVoidEntry * prev = NULL;
    
    while (e!=NULL) {
        if(!strcmp(e->key,key))
        {
            if(prev == NULL)
            {
                buckets[h] = e->next;
            }
            else{
                prev->next = e->next;
            }
            return true;
        }
        prev = e;
        e=e->next;
    }
    return false;
}

rehash()
{
    int old = _n;
    _n = 2*_n;
    
    HashTableVoidEntry ** newBuckets =
    (HashTableVoidEntry **) malloc(_n* sizeof(HashTableVoidEntry*));
    
    for ( int i = 0; i < _n; i++) {
        newBuckets[i] = NULL;
    }
    
    for ( int i = 0; i < old; i++) {
        HashTableVoidEntry * e = _buckets[i];
        while ( e != NULL) {
            HashTableVoidEntry * next = e->next;
            int h = hash(e->key);
            e->next = newBuckets[h];
            newBuckets[h] = e;
            e = next;
            
        }
    }

    
}















