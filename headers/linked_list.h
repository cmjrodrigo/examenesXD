#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef void * generic;

typedef struct Node{
	generic data;
	struct Node *head;
	struct Node *tail;
}Node;

typedef void(*dataDeleteFunc)(generic );

Node *newNode(generic data, Node *t, Node *h);
void dNode(Node *n, dataDeleteFunc f);
void dNodeList(Node *root, dataDeleteFunc f);

void push_front(Node *root, Node *other);
void push_back(Node *root, Node *other);
void pop_front(Node *root, dataDeleteFunc f);
void pop_back(Node *root, dataDeleteFunc f);

Node *front(Node *root);
Node *back(Node *root);

bool empty(Node *root);
long long size(Node *root);

int insert_after(Node *root, generic newVal, generic refVal,
		int (*dataCompare)(generic v1, generic v2));

void printLinkedList(Node *root, void (*dataPrint)(generic d));

#endif
