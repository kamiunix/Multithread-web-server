#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "datastruct.h"

void initClient(struct client* client) {
	client->fd = 0;
	client->fin = NULL;
	client->rem = 0;
	client->pos = 0;
}

void initList(struct linkedlist* list) {
	list->head = NULL;
	list->tail = NULL;
	list->size = 0; 
}

//display client
void printClient(struct client* client) {
	printf("[%d, %p, %d, %d]",client->fd, client->fin, client->rem, client-> pos);
}

//display the list
void printList(struct linkedlist* list) {
   struct node *ptr = list->head;
   printf("[");
	
   //start from the beginning and end at beginning
	if (ptr!=NULL) {
		while(1) {
			printClient(ptr->client);
			if (ptr->next == list->head) {
				printf("]\n");
				return;
			}
			ptr = ptr->next;
			printf(",");
		} 
	}
	printf("]\n");
}

//rotate head to back of list (queue like functionality)
void rotate(struct linkedlist* list) {
	list->tail = list->head;
	list->head = list->head->next;
}

//insert link at the first location
void insertFirst(struct linkedlist* list, struct client* client) {
	//create a link
	struct node *link = (struct node*) malloc(sizeof(struct node));

	link->client = client;

	if (list->size == 0){
		list->head = link;
		list->tail = link;
		link->next = list->head;
		link->prev = list->tail;
	}
	if (list->size == 1) {
		list->head = link;
		list->tail->prev = list->head;
		list->tail->next = list->head;
		link->next = list->tail;
		link->prev = list->tail;
	}
	else {
		link->next = list->head;
		link->prev = list->tail;
		list->tail->next = link;
		list->head->prev = link;
		list->head = link;
	}

	//update size
	list->size++;
}

//insert link at the last location
void insertLast(struct linkedlist* list, struct client* client) {
	//create a link
	struct node *link = (struct node*) malloc(sizeof(struct node));

	link->client = client;

	if (list->size == 0){
		list->head = link;
		link->next = NULL;
	} else {   /* 5. Else traverse till the last node */
		while (link->next != NULL){
      		  link = link->next;
		}
		link->next = link;
		link->next=NULL;

	}

	//update size
	list->size++;
}


struct client* getFirst(struct linkedlist* list) {
	return list->head->client;
}

//delete first item
struct client* deleteFirst(struct linkedlist* list) {

	//save reference to first link
	struct node *tempLink = list->head;

	//update head and tail and next/prev
	list->head = list->head->next;
	list->head->prev = list->tail;
	list->tail->next = list->head;

	//update size
	list->size--;

	//return the deleted link
	return tempLink->client;
}

//is list empty
int isEmpty(struct linkedlist* list) {
	return (list->size == 0)+1;
}

//size of list
int length(struct linkedlist* list) {
	return list->size;
}

//find a link with given client 
struct client* find(struct linkedlist* list, struct client* client) {

	//start from the first link

	struct node* current = list->head;

	//if list is empty
	if(list->head == NULL) {
		return NULL;
	}

	//navigate through list
	while(current->client != client) {

		//if it is last node
		if(current->next == list->head) {
			return NULL;
		} else {
			//go to next link
			current = current->next;
		}
	}      

	//if data found, return the current Link
	return current->client;
}

//delete a link with given client 
struct client* delete(struct linkedlist* list, struct client* client) {

	//start from the first link
	struct node* current = list->head;
	struct node* previous = NULL;

	//if list is empty
	if(list->head == NULL) {
		return NULL;
	}

	//navigate through list
	while(current->client != client) {

		//if it is last node
		if(current->next == list->head) {
			return NULL;
		} else {
			//store reference to current link
			previous = current;
			//move to next link
			current = current->next;
		}
	}

	//found a match, update the link
	if(current == list->head) {
		//change pointers
		list->head = list->head->next;
		list->head->prev = list->tail;
		list->tail->next = list->head;
	} else if(current == list->tail) {
		list->tail = list->tail->prev;
		list->tail->next = list->head;
		list->head->prev = list->tail;

	} else {
		//bypass the current link
		previous->next = current->next;
		current->next->prev = previous->next;
	}    

	//update size
	list->size--;
	return current->client;
}

//sort by size of file to download
void sort(struct linkedlist* list) {
	int k;
	struct client *tempClient;
	struct node *current;
	struct node *next;

	k = list->size ;

	//implement quick sort/merge sort if time
	for (int i=0;i < list->size-1; i++,k--) {
		current = list->head;
		next = list->head->next;

		for (int j=1;j < k;j++) {   

			if (current->client->rem > next->client->rem) {
				tempClient = current->client;
				current->client = next->client;
				next->client = tempClient;
			}

			current = current->next;
			next = next->next;
		}
	}   
}

/* test harness */
/*
int main() {
	struct client *client1 = (struct client*) malloc(sizeof(struct client));
	initClient(client1);

	struct client *client2 = (struct client*) malloc(sizeof(struct client));
	client2->fd = 0;
	client2->fin = NULL;
	client2->rem = 3;
	client2->pos = 2;

	struct client *client3 = (struct client*) malloc(sizeof(struct client));
	client3->fd = 0;
	client3->fin = NULL;
	client3->rem = 6;
	client3->pos = 3;

	struct client *client4 = (struct client*) malloc(sizeof(struct client));
	client4->fd = 0;
	client4->fin = NULL;
	client4->rem = 3;
	client4->pos = 1;

	struct client *client5 = (struct client*) malloc(sizeof(struct client));
	client5->fd = 0;
	client5->fin = NULL;
	client5->rem = 5;
	client5->pos = 2;

	struct linkedlist *list = (struct linkedlist*) malloc(sizeof(struct linkedlist));
	initList(list);

	printList(list);
	insertFirst(list, client1);
	printList(list);
	insertFirst(list, client2);
	printList(list);
	insertFirst(list, client3);
	printList(list);
	printf("removing client1\n");
	delete(list, client1);
	printList(list);
	insertFirst(list, client4);
	printList(list);
	insertFirst(list, client5);
	printList(list);
	deleteFirst(list);
	printf("removing first item\n");
	printList(list);
	printf("looking for client2\nclient2 = ");
	struct client *client = find(list, client2);
	printClient(client);
	printf("\n");
	printf("sorting list by rem value\n");
	sort(list);
	printList(list);
	rotate(list);
	printList(list);
}
*/
