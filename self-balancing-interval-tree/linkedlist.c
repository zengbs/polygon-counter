#include<stdio.h>
#include<stdlib.h>
#include"macro.h"
#include"intervaltree.h"
#include "prototypes.h"


ListNode *searchNodeList( ListNode *head, int key )
{
   ListNode *current = head;

   while( current != NULL ){
      if ( current->key  == key ) return current;
      current = current->next;
   }

   REPORT_ERROR;

   return NULL;
}



void addNodeList( ListNode *head, int key )
{
   ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));

   if ( newNode == NULL ) REPORT_ERROR;

   newNode->key = key;

   ListNode *current = head;
   ListNode *prev = NULL;

   while( (current != NULL) && (current->key > key ) ){
      prev = current;
      current = current->next;
   }

   newNode->next = current;
   newNode->prev = prev;

   if (   prev != NULL )  prev->next    = newNode;
   if (current != NULL )  current->prev = newNode;
}



void deleteNodeList( ListNode *deleteNode )
{

   if ( deleteNode->prev != NULL )
      deleteNode->prev->next = deleteNode->next;

   if ( deleteNode->next != NULL )
      deleteNode->next->prev = deleteNode->prev;

}


void freeList( ListNode *head )
{
   ListNode *current = head;
   ListNode *prev = NULL;

   while( current != NULL ){
      prev = current;
      current = current->next;
      free(prev);
   }
}
