#include "linked_list.h"
#include <stdlib.h>

Node *newNode(generic data, Node *t, Node *h)
{
	Node *root = (Node *) calloc(1, sizeof(Node));
	root->data = data;
	root->tail = t;
	root->head = h;
	return root;
}

void dNode(Node *n, dataDeleteFunc f)
{
	f(n->data);
	free(n);
}

void dNodeList(Node *root, dataDeleteFunc f)
{
	root = back(root);
	while(root->head != nullptr)
		pop_front(root, f);
	dNode(root, f);
}

void push_front(Node *root, Node *other)
{
	Node *curr = root;
	while(curr->head != nullptr)
		curr = curr->head;
	curr->head = other;
	other->tail = curr;
}

void push_back(Node *root, Node *other)
{
	Node *curr = root;
	while(curr->tail != nullptr)
		curr = curr->tail;
	curr->tail = other;
	other->head = curr;
}

void pop_front(Node *root, dataDeleteFunc f)
{
	Node *curr = root;
	while(curr->head != nullptr)
		curr = curr->head;
	if(curr->tail != nullptr)
		curr->tail->head = nullptr;
	dNode(curr, f);
}

void pop_back(Node *root, dataDeleteFunc f)
{
	Node *curr = root;
	while(curr->tail != nullptr)
		curr = curr->tail;
	if(curr->head != nullptr)
		curr->head->tail = nullptr;
	dNode(curr, f);
}

Node *front(Node *root)
{
	Node *curr = root;
	while(curr->head != nullptr)
		curr = curr->head;
	return curr;
}

Node *back(Node *root)
{
	Node *curr = root;
	while(curr->tail != nullptr)
		curr = curr->tail;
	return curr;
}

bool empty(Node *root)
{
	return root->head == nullptr && root->tail == nullptr;
}

long long size(Node *root)
{
	long long count = 0;
	Node *curr = back(root);
	while(curr != nullptr){
		curr = curr->head;
		count ++;
	}
	return count ;
}

int insert_after(Node *root, generic newVal, generic refVal,
		int (*dataCompare)(generic v1, generic v2))
{
	Node *curr = root;
	while(curr != nullptr && dataCompare(curr->data, refVal)){
		curr = curr->head;

	}
	if(curr == nullptr) return -1;

	Node *oldNext = curr->head;
	Node *node = newNode(newVal, curr, oldNext);  // tail=curr, head=oldNext
	curr->head = node;
	if (oldNext != nullptr) oldNext->tail = node;
	return 0;
}

void printLinkedList(Node *root, void (*dataPrint)(generic d, int opt), int opt)
{
	Node *curr = back(root);
	while(curr != nullptr){
		dataPrint(curr->data, opt);
		curr = curr->head;
	}
}
