//
//  DLList.cpp
//  
//
//  Created by Jaideep Juneja on 7/15/15.
//
//

#include "DLList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DLList::DLList()
{
    _head =  new DLNode();
    _head->_next = _head;
    _head->_prev = _head;
}

bool DLList::isEmpty()
{
    return _head->_next == _head;
}

void DLList::addFront(int data)
{
    DLNode * e = new DLNode();
    e->_data = data;
    e->_next = _head->_next;
    e->_prev = _head;
    _head->_next = e;
    e->_next->_prev = e;
    }

void DLList::addEnd(int data)
{
    DLNode * e = new DLNode();
     e->_data = data;
    e->_next= _head;
    e->_prev= _head->_prev;
    _head->_prev->_next = e;
    _head->prev=e;
}

bool DLList::removeFront(int &data)
{
    if(isEmpty())
    {
        return false;
    }
    
    DLNode * e = _head->next;
    _head->_next = e->_next;
    e->_next->_prev = _head;//or e_._prev
    data = e->data;
    delete e;
    return true;
}

bool DLList::removeEnd(int &data)
{
    if(isEmpty())
    {
        return false;
    }
    DLNode * e = _head->_prev;
    e->_prev->_next = _head;
    _head->_prev = e->_prev;
    data = e->data;
    delete e;
    return true;

    
}


