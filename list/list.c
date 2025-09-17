// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  list_t* mylist = (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
  return mylist;  // Missing return statement!
}
void list_free(list_t *l) {
  if (l == NULL) return;
  
  node_t *current = l->head;
  while (current != NULL) {
    node_t *temp = current;
    current = current->next;
    free(temp);
  }
  free(l);
}

void list_print(list_t *l) {
  if (l == NULL || l->head == NULL) {
    printf("NULL\n");
    return;
  }
  
  node_t *current = l->head;
  while (current != NULL) {
    printf("%d", current->value);
    if (current->next != NULL) {
      printf("->");
    }
    current = current->next;
  }
  printf("->NULL\n");
}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 10024);
  char tbuf[20];
  
  // Initialize buffer to empty string
  buf[0] = '\0';

  if (l == NULL || l->head == NULL) {
    strcat(buf, "NULL");
    return buf;
  }

  node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) { 
  if (l == NULL || l->head == NULL) return 0;
  
  int count = 0;
  node_t *current = l->head;
  while (current != NULL) {
    count++;
    current = current->next;
  }
  return count;
}
void list_add_to_back(list_t *l, elem value) {
  if (l == NULL) return;
  
  node_t *new_node = getNode(value);
  
  if (l->head == NULL) {
    l->head = new_node;
    return;
  }
  
  node_t *current = l->head;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = new_node;
}
void list_add_to_front(list_t *l, elem value) {
  if (l == NULL) return;
  
  node_t *cur_node = (node_t *) getNode(value);

  /* Insert to front */
  node_t *head = l->head;  // get head of list

  cur_node->next = head;
  l->head = cur_node;
}

node_t * getNode(elem value) {
  node_t *mynode;

  mynode = (node_t *) malloc(sizeof(node_t));
  mynode->value = value;
  mynode->next = NULL;

  return mynode;
}
