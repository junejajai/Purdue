//
//  BinSearchDictionary.cpp
//  
//
//  Created by Jaideep Juneja on 7/15/15.
//
//

#include "BinSearchDictionary.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


BinSearchDictionary::BinSearchDictionary(int maxEntries)
{
    this->maxEntries = maxEntries;
    n = 0;
    table = new BinSearchEntry[maxEntries];
    sorted = true;
}

void BinSearchDictionary::insert(char * key, void * data)
{
    if(n>maxEntries)
    {
        maxEntries = 2 * maxEntries;
        BinSearchEntry * newtable = new BinSearchEntry[maxEntries];
        
        for(int i = 0;i<n;i++)
        {
            newtable[i].key = table[i].key;
            newtable[i].data = table[i].data;
        }
        delete [] table;
        table = newtable;
    }
    
    table[n].key = strdup(key);
    table[n].data = data;
    n++;
    sorted = false;
}

void * BinSearchDictionary:: find(char * key)
{
    if(!sorted)
    {
        sort();//define heapsort
        sorted = true;
    }
    int low = 0;
    int high= n-1;
    while(low<=high){
    int mid = (low+high)/2;
    if(!strcmp(table[mid].key,key))
    {
        return table[mid].data;
    }
        else if(strcmp(table[mid].key,key)<0)
        {
            high = mid -1;
        }
        else
        {
            low = mid+1;
        }
    }
    

}











