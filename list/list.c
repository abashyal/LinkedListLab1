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
  node_t *head = l->head;  

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
void list_add_at_index(list_t *l, elem value, int index) {
  if (l == NULL || index < 1) return;  
  
  if (index == 1) {  
    list_add_to_front(l, value);
    return;
  }
  
  node_t *new_node = getNode(value);
  node_t *current = l->head;
  
  // Navigate to the position before where we want to insert
  for (int i = 1; i < index - 1 && current != NULL; i++) {  // Changed from i = 0 to i = 1
    current = current->next;
  }
  
  // If current is NULL, index is out of bounds
  if (current == NULL) {
    free(new_node);
    return;
  }
  
  new_node->next = current->next;
  current->next = new_node;
}
elem list_remove_from_back(list_t *l) { 
  if (l == NULL || l->head == NULL) return -1;
  
  // If only one element
  if (l->head->next == NULL) {
    elem value = l->head->value;
    free(l->head);
    l->head = NULL;
    return value;
  }
  
  // Find second to last node
  node_t *current = l->head;
  while (current->next->next != NULL) {
    current = current->next;
  }
  
  elem value = current->next->value;
  free(current->next);
  current->next = NULL;
  return value;
}

elem list_remove_from_front(list_t *l) { 
  if (l == NULL || l->head == NULL) return -1;
  
  node_t *temp = l->head;
  elem value = temp->value;
  l->head = l->head->next;
  free(temp);
  return value;
}
elem list_remove_at_index(list_t *l, int index) { 
  if (l == NULL || l->head == NULL || index < 1) return -1;  
  
  if (index == 1) {  
    return list_remove_from_front(l);
  }
  
  node_t *current = l->head;
  
  // Navigate to the position before the one we want to remove
  for (int i = 1; i < index - 1 && current != NULL; i++) {  
    current = current->next;
  }
  
  // If current is NULL or the next node doesn't exist, index is out of bounds
  if (current == NULL || current->next == NULL) {
    return -1;
  }
  
  node_t *node_to_remove = current->next;
  elem value = node_to_remove->value;
  current->next = node_to_remove->next;
  free(node_to_remove);
  return value;
}
elem list_get_elem_at(list_t *l, int index) { 
  if (l == NULL || l->head == NULL || index < 1) return -1;  // Changed from index < 0 to index < 1
  
  node_t *current = l->head;
  for (int i = 1; i < index && current != NULL; i++) {  // Changed from i = 0 to i = 1
    current = current->next;
  }
  
  if (current == NULL) return -1;
  return current->value;
}
int list_get_index_of(list_t *l, elem value) { 
  if (l == NULL || l->head == NULL) return -1;
  
  node_t *current = l->head;
  int index = 1;  // Changed from 0 to 1
  
  while (current != NULL) {
    if (current->value == value) {
      return index;
    }
    current = current->next;
    index++;
  }
  return -1;
}
bool list_is_in(list_t *l, elem value) { 
  if (l == NULL || l->head == NULL) return false;
  
  node_t *current = l->head;
  while (current != NULL) {
    if (current->value == value) {
      return true;
    }
    current = current->next;
  }
  return false;
}
