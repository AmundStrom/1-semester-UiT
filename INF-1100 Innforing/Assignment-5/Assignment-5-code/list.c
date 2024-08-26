#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct listnode listnode_t;

struct listnode {
    listnode_t  *next;
    void        *item;
};

struct list {
    listnode_t *head;
    int numitems;
};


/*
 * Returns a newly created, empty list.
 */
list_t *list_create(void)
{
    list_t *NewList = malloc(sizeof(list_t)); //create space for the list in the memory
        NewList->numitems = 0; //sets the number of items in the list to 0
        NewList->head = NULL; //sets the start of the list to NULL, this means the list is empty
    return NewList;
}


/*
 * Frees the list; list and nodes, but not the items it holds.
 */
void list_destroy(list_t *list)
{
    free(list);
}


/*
 * Adds an item first in the provided list.
 */
void list_addfirst(list_t *list, void *item)
{
    listnode_t *AddFirstNode = (listnode_t*)malloc(sizeof(listnode_t)); //creates space in the memory for this node
        AddFirstNode->item = item; //sets the item in the node equal to the item-argument
        AddFirstNode->next = list->head; //sets the previous start of the list to be this node's next
        list->head = AddFirstNode; //sets the start of the list to be this node
        list->numitems++; //increases the number of items in the list by 1, to keep track of how many items there are in the list
}

void test()
{

list_t *list = list_create();
void *var = 3;

list_addfirst(list, var);

}

/*
 * Adds an item last in the provided list.
 */
void list_addlast(list_t *list, void *item)
{
     listnode_t *AddNewLastNode = (listnode_t*)malloc(sizeof(listnode_t));
        AddNewLastNode->item = item;
        AddNewLastNode->next = NULL;

    listnode_t *CurrentLastNode = list->head;
        //if list is empty
        if(CurrentLastNode == NULL)
        {
           list->head = AddNewLastNode; //for some reason you must write list->head, and not use the variable CurrentLastNode
        }else
        {
            //if list contain 1 or more nodes, iterates through the list, searching for the last node
            while(CurrentLastNode->next != NULL)
            {
                CurrentLastNode = CurrentLastNode->next;
            }
            CurrentLastNode->next = AddNewLastNode;
        }
    list->numitems++;
}


/*
 * Removes an item from the provided list, only freeing the node.
 */
void list_remove(list_t *list, void *item)
{
    listnode_t *CurrentNode, *tmp;
        CurrentNode = list->head;
        //if item is at the start of the list
        if(CurrentNode->item == item)
        {
            tmp = CurrentNode; //saves the CurrentNode in tmp for later use
            list->head = CurrentNode->next; //for some reason you must write list->head, and not use the varaible CurrentNode
        }else
        {
            // iterates through the list, looking for the mathcing item
            while(CurrentNode->next->item != item)
            {
                CurrentNode = CurrentNode->next;
            }
            //if the matching item is at the end
            if(CurrentNode->next == NULL)
            {
                tmp = CurrentNode->next;
                CurrentNode->next = NULL;
            }else //if the matching item is not at the end
            {
                tmp = CurrentNode->next;
                CurrentNode->next = CurrentNode->next->next;
            }
        }
        free(tmp);
        list->numitems--;      
}


/*
 * Return the number of items in the list.
 */
int list_size(list_t *list)
{
    return list->numitems;
}


struct list_iterator {
    listnode_t *next;
    list_t *list;
};


/*
 * Return a newly created list iterator for the given list.
 */
list_iterator_t *list_createiterator(list_t *list)
{
    list_iterator_t *NewIterator = malloc(sizeof(list_iterator_t)); //create space in memory for this list
        NewIterator->list = list; //set the list for the iterator equal to the Original list, so they will have the same content
        NewIterator->next = list->head; //set the first node for the iterator equal to the head of the Original list
    return NewIterator;   
}


/*
 * Free the memory for the given list iterator.
 */
void list_destroyiterator(list_iterator_t *iter)
{
    free(iter);
}


/*
 * Move iterator to next item in list and return current.
 */
void *list_next(list_iterator_t *iter)
{
    void *item; //this is the same variable as the Original list->item
 
    //this will increase by 1 node every time this function is called until it reaches NULL
    if (iter->next != NULL) {
        item = iter->next->item;
        iter->next = iter->next->next;
    }
    return item;
}


/*
 * Let iterator point to first item in list again.
 */
void list_resetiterator(list_iterator_t *iter)
{
    iter->next = iter->list->head;
}
