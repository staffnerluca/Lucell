#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node {
    void* value;
    struct node* to;
} node;

node* createN(void* value);
void add(struct node** start, void* value);
void printList(node* head);
void kill(node* start);

#endif

