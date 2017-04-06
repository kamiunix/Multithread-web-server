struct client {
	char *filename;
	int fd;
	FILE *fin;
	int rem;
	int pos;
};

struct node {
   struct client *client;
   struct node *next;
   struct node *prev;
};

struct linkedlist {
	struct node *head;
	struct node *tail;
	int size;
};

//initialize client
void initClient(struct client* client);

//initialize linkedlist
void initList(struct linkedlist* list);

//display client
void printClient(struct client* client);

//display the list
void printList(struct linkedlist* list);

//roate list puting header to tail. (for RR)
void rotate(struct linkedlist* list);

//insert link at the first location
void insertFirst(struct linkedlist* list, struct client* client);

//insert link at the last location
void insertLast(struct linkedlist* list, struct client* client);

//return first client in list
struct client* getFirst(struct linkedlist* list);

//delete first item
struct client* deleteFirst(struct linkedlist* list);

//is list empty
int isEmpty(struct linkedlist* list);

//size of list
int length(struct linkedlist* list);

//find a link with given client 
struct client* find(struct linkedlist* list, struct client* client);

//delete a link with given client 
struct client* delete(struct linkedlist* list, struct client* client);

//sort by size of file to download
void sort(struct linkedlist* list);
