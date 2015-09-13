//
//  DLList.h
//  
//
//  Created by Jaideep Juneja on 7/15/15.
//
//

#include <stdio.h>


struct DLNode{
    int data;
    DLNode * _next;
    DLNode * _prev;
};

class DLList{
    DLNode * _head;
public:
    DLList();
    void addFront(int data);
    void addEnd(int data);
    bool removeFront(int &data);
    //bool removeEnd(int &data);
    bool isEmpty();
   // void print();
};