
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

//
// Initialize a linked list
//
void llist_init(LinkedList * list)
{
	list->head = NULL;
}

//
// It prints the elements in the list in the form:
// 4, 6, 2, 3, 8,7
//
void llist_print(LinkedList * list) {
	
	ListNode * e;

	if (list->head == NULL) {
		printf("{EMPTY}\n");
		return;
	}

	printf("{");

	e = list->head;
	while (e != NULL) {
		printf("%d", e->value);
		e = e->next;
		if (e!=NULL) {
			printf(", ");
		}
	}
	printf("}\n");
}

//
// Appends a new node with this value at the beginning of the list
//
void llist_add(LinkedList * list, int value) {
	// Create new node
	ListNode * n = (ListNode *) malloc(sizeof(ListNode));
	n->value = value;
	
	// Add at the beginning of the list
	n->next = list->head;
	list->head = n;
}

//
// Returns true if the value exists in the list.
//
int llist_exists(LinkedList * list, int value) {
        ListNode * e;
	e = list -> head;
	if(e==NULL)
		{
		printf("{EMPTY}\n");
		return;
	        }
        while(e!=NULL)
	{
	if(e->value == value)
	{
	return 1;
	}
	e = e->next;
	}
	return 0;
}

//
// It removes the entry with that value in the list.
//
int llist_remove(LinkedList * list, int value) {
	ListNode * e = list->head;
	ListNode * q = NULL;
	while(e!=NULL)
	{
	if(e->value == value)
		{
		break;
		}
	q = e;
	e = e->next;
	}
	if(e==NULL)
		{
		return 0;
		}
         if(q==NULL)
	 {
	 list->head = e->next;
	 }
	 else
	 	{
		q->next = e->next;
	 	}
		//free(e->value);
		free(e);
	return 1;
}

//
// It stores in *value the value that correspond to the ith entry.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_get_ith(LinkedList * list, int ith, int * value) {
	ListNode * e = list -> head;
        int i = 0;
	while(e!=NULL)
	{
         if(i==ith)
	 {
	 *value = e->value;
	 return 1;
	 }
	 i++;
	 e = e->next;
	}

	return 0;
}

//
// It removes the ith entry from the list.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_remove_ith(LinkedList * list, int ith) {
	ListNode * e = list->head;
	int i = 0;
	while(e!=NULL)
	{
	if(i==ith)
	{
         llist_remove(list,e->value);

	 return 1;
	}
 	i++;
         e = e->next;
	}
	return 0;
}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LinkedList * list) {
int i = 0;
ListNode * e = list -> head;
while(e!=NULL)
{
i++;
e = e->next;
}
return i;
}


//
// It saves the list in a file called file_name. The format of the
// file is as follows:
//
// value1\n
// value2\n
// ...
//
int llist_save(LinkedList * list, char * file_name) {
	ListNode * e = list->head;
	FILE * f = fopen(file_name,"w");
	if(f != NULL)
	{
	while(e!=NULL)
		{
		fprintf(f,"%d\n",e->value);
		e = e->next;
		}
	
	fclose(f);
	return 0;
	}
	else
	{
	return 0;
	}
}

//
// It reads the list from the file_name indicated. If the list already has entries, 
// it will clear the entries.
//
int llist_read(LinkedList * list, char * file_name) {
       // ListNode * e = list->head;	
        FILE * f = fopen(file_name,"r");
	llist_clear(list);
	int cool = 0;
	int a[13];
	if(f!=NULL) {
	char ch;
	int n;
        	while(fscanf(f,"%d",&n)>0) {
       	 // e->value = fscanf(f);
		//e = e->next;
	//	int y;
	//	fscanf(f,"%d",&y);
		llist_add(list,n);
		//a[cool] = y;
	//	if(y==cool)
	//	continue;
	  //      cool++;	
		}
	//	int t = 0;
	//	for(t=0;t<13;t++)
	//	{
	//	printf("%d\n",a[t]);
	//llist_add(list,a[t]);
	//	}
        fclose(f);
//	int i = 0;
//		for(i=12;i>=0;i--)
//		{
//		printf("%d ",a[i]);
//		llist_add(list,a[i]);
//		}
	return 1;
	}
	else
	{
	return 0;
	}
}

//
// It sorts the list. The parameter ascending determines if the
// order si ascending (1) or descending(0).
//
void llist_sort(LinkedList * list, int ascending) {
ListNode * e = list->head;
int t = llist_number_elements(list);
int a[t];
int ele = 0;
while(e!=NULL)
	{
	a[ele] = e->value;
	//e = e->next;
	ele++;
	e = e->next;
	}
llist_clear(list);
int i;
int j;
for(i=0;i<t;i++)
	{
	for(j=0;j<t-1-i;j++)
		{
		if(a[j]>a[j+1])
			{
			int temp = a[j];
			a[j] = a[j+1];
			a[j+1] = temp;
			}
		}
	}
if(ascending==0)
	{
	int w;
	for(w = 0;w<t;w++)
		{
		llist_add(list,a[w]);
		}
	}
	else
	{
	int w;
	for(w=t-1;w>=0;w--)
		{
		llist_add(list,a[w]);
		}

	}
}

//
// It removes the first entry in the list and puts value in *value.
// It also frees memory allocated for the node
//
int llist_remove_first(LinkedList * list, int * value) {
        ListNode * e = list->head;
	int n = llist_number_elements(list);
	int a[n];
	int i = 0;
	if(n == 0) return 0;
	while(e!=NULL)
	{
	a[i]=e->value;
	i++;
	e=e->next;
	}
	*value = a[0];
	llist_clear(list);
	for(i=n-1;i>=1;i--)
	{
         llist_add(list,a[i]);
	}
   //     free(e);	
	return 1;
}

//
// It removes the last entry in the list and puts value in *value/
// It also frees memory allocated for node.
//
int llist_remove_last(LinkedList * list, int *value) {
 ListNode * e = list->head;
 int i = 0;
 int t = llist_number_elements(list);
 int a[t];
 if(t == 0)return 0;
 while(e!=NULL)
 {
 a[i] = e->value;
 i++;
 e = e->next;
 }
 *value = a[t-1];
 llist_clear(list);
 int ele = 0;
 for(ele=t-2;ele>=0;ele--)
 {
 llist_add(list,a[ele]);
 }
 //llist_remove(list,e->value;);
 //free(e);
 return 1;
}

//
// Insert a value at the beginning of the list.
// There is no check if the value exists. The entry is added
// at the beginning of the list.
//
void llist_insert_first(LinkedList * list, int value) {
llist_add(list,value);
}

//
// Insert a value at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
//
void llist_insert_last(LinkedList * list, int value) {
int n = llist_number_elements(list);
int a[n+1];
a[n] = value;
ListNode * e = list->head;
int i = 0;
//if(n == 0)return 0;
while(e!=NULL)
{
a[i] = e->value;
i++;
e = e->next;
}
llist_clear(list);
for(i = n;i>=0;i--)
{
llist_add(list,a[i]);
}
}
//
// Clear all elements in the list and free the nodes
//
void llist_clear(LinkedList *list)
{
ListNode * e = list -> head;
while(e!=NULL)
{
ListNode * t = e -> next;

free(e);
e = t;
}
list -> head = NULL; 
}
