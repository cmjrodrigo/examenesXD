#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node{
	void *data;
	struct Node *head;
	struct Node *tail;
}Node;

Node *newNode(void *data, Node *t, Node *h);

void push_front(Node *root, Node *other);
void push_back(Node *root, Node *other);
void pop_front(Node *root);
void pop_back(Node *root);

Node *front(Node *root);
Node *back(Node *root);

bool empty(Node *root);
long long size(Node *root);

int insert_after(Node *root, void *newVal, void *refVal);

#endif
