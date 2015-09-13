
#include <stdio.h>
#include <stdlib.h>

#include "slist.h"

void sllist_init(SLList * list)
{
	list->head = NULL;
}

// Add int value to the end of list. The values may be repeated.
void sllist_add_end( SLList *list, int value )  {
	SLEntry * e = list->head;
	SLEntry *n = (SLEntry*)malloc(sizeof(SLEntry));
	SLEntry * prev = NULL;
	while(e!=NULL)
	{
		prev = e;
		e = e->next;
	}
	n->value = value;
	n->next = NULL;

	if(prev == NULL)
	{
		//  n->next = list->head; 
		//		list->head = n->next;
		list->head = n;
	}
	else 
	{
		prev->next = n;
		//prev->value = n->value;
		//        n->next = NULL;
		//	n->value=value;
	}

}


// Remove first occurrence of value in the list. It returns 1 if value is found or 0 otherwise.
int sllist_remove(SLList *list, int value) {
	SLEntry * e = list->head;
	SLEntry * t = NULL;
	while(e!=NULL)
	{
		if(e->value == value)
		{
			if(t==NULL)
			{
				list->head = e->next;
			}
			else
			{
				t->next = e->next;
			}
			return 1;
		}

		t = e;
		e = e->next;
	}
	return 0;
}


// Removes from the list and frees the nodes of all the items that are min <= value <= max
void sllist_remove_interval(SLList *list, int min, int max) {
	SLEntry * e = list->head;
	while(e!=NULL)
	{
		if(e->value >= min && e->value<=max)
		{
			sllist_remove(list,e->value);

		}
		e=e->next;
	}
}

void sllist_add(SLList * list, int value) {

	SLEntry * n = (SLEntry *) malloc(sizeof(SLEntry));
	n->value = value;

	n->next = list->head;
	list->head = n;
}













// It allocates and returns a new list with the intersection of the two lists, that is the 
// list of all the items that are common to the two lists. The items in the intersection are
// unique. 
SLList * sllist_intersection(SLList *a, SLList *b) {

	SLEntry * e = a->head;
	SLEntry * t = b->head;
	SLList * l1 = (SLList *)malloc(sizeof(SLList));
	int flag = 0;
	while(e!=NULL)// || t!=NULL)
	{
		while(t!=NULL)
		{
			if(e->value==t->value)
			{
				SLEntry * temp = l1->head;
				while(temp!=NULL)
				{
					if(e->value==temp->value)
					{
						flag=1;
						break;
					}
					temp=temp->next;
				}
				if(flag==0)
				{
					sllist_add(l1,e->value);
				}
				else
				{
					t=t->next;
					flag = 0;
					continue;
				}

			}
			t=t->next;
		}
		e=e->next;
		t=b->head;

	}
	return l1;
}

void sllist_print(SLList *list)
{
	// Move to the end
	SLEntry * e = list->head;

	printf("--- List ---\n");
	while (e!= NULL) {
		printf("val=%d\n", e->value);
		e = e->next;
	}
}

