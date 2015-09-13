//
//  Heap.cpp
//  
//
//  Created by Jaideep Juneja on 7/15/15.
//
//

#include "Heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Heap::Heap(int maxSize)
{
    this->maxSize = maxSize;
    last = 0;
    heap = new int[maxSize];
}

int left(int i)
{
    return 2*i + 1;
}

int right(int i)
{
    return 2*i + 2;
}

int hparent(int i)
{
    return (i-1)/2;
}

bool Heap::insert(int key)
{
    if(last == maxSize)
    {
        return false;
    }
    
    heap[last] = key;
    last ++;
    
    int child = last - 1;
    int parent = hparent(child);
    
    while (child > 0) {
        if(heap[child]<heap[parent])
        {
            int tmp = heap[child];
            heap[child] = heap[parent];
            heap[parent] = tmp;
            child = parent;
            parent = hparent(child);
        }
        else
        {
            break;
        }
    }
    return true;
}

bool Heap::removeMin(int &key)
{
    if(last == 0)
    {
        return false;
    }
    
    key = heap[0];
    heap[0] = heap[last];//remember
    last--;
    int parent = 0;
    int l = left(parent);
    int r = right(parent);
    int minch = l;
    while(l<last)
    {
        if(r<last&&heap[r]<heap[l])
        {
            minch = r;
        }
        if(heap[minch]<heap[parent])
        {
            int tmp = heap[minch];
            heap[minch]=heap[parent];
            heap[parent]=tmp;
            parent = minch;
            l = left(parent);
            r = right(parent);
        }
        else
        {
            break;
        }
    }
    return true;
    
}



void Heap::heapSort(int * array, int n)
{
    Heap heaps(n);
    for(int i = 0; i<n;i++)
    {
        heaps.insert(heap[i]);
    }
    for(int i = 0; i<n;i++)
    {
        heaps.removeMin(heap[i]);
    }
}


int main()
{
    return 0;
}









