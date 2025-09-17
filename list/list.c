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