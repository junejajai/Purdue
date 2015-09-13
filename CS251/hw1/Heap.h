//
//  Heap.h
//  
//
//  Created by Jaideep Juneja on 7/15/15.
//
//



#include <stdio.h>

class Heap{
    int maxSize;
    int *heap;
    int last;
public:
    Heap(int maxSize);
    bool insert(int key);
    bool removeMin(int &key);
    void heapSort(int * array, int n);
};
