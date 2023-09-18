#include <stdio.h>
#include <stdlib.h>

//typedef is uesd to rename the type from struct node to node
typedef struct node{
	void* value;
	struct node *to;
} node;

node* createN(void* value){
	//use malloc to allocate storage on runtime, otherwise it would be static. Malloc returns a pointer
	node* new = (struct node*)malloc(sizeof(node));
	if(new == NULL){
		printf("Oh no it failed");
	}
	new->value = value;
	new->to = NULL;
	return new;
}

void add(struct node** start, void* value){
	node* new = createN(value);
	if(*start == NULL){
		*start = new;
		return;
	}

	node* current = *start;
	while(current->to != NULL){
		//current->to is a pointer
		current = current->to;
	}
	current->to = new;
}

void printList(node* head) {
    node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->to;
    }
    printf("NULL\n");
}

void kill(node* start){
	node* current = start;
	while(start != NULL){
		node* toKill = current;
		current = current->to;
		free(toKill);
	}
}

