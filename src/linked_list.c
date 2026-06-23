#include "linked_list.h"
#include <stdlib.h>
#include <printf.h>

Node *newNode(void *data, Node *t, Node *h)
{
	Node *root = (Node *) calloc(1, sizeof(Node));
	return root;
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

void pop_front(Node *root)
{
	Node *curr = root;
	while(curr->head != nullptr)
		curr = curr->head;
	if(curr->tail != nullptr)
		curr->tail->head = nullptr;
	curr->tail = nullptr;
}

void pop_back(Node *root)
{
	Node *curr = root;
	while(curr->tail != nullptr)
		curr = curr->tail;
	curr->head->tail = nullptr;
	curr->head = nullptr;
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

int insert_after(Node *root, void *newVal, void *refVal)
{
	Node *curr = root;
	while(curr != nullptr && curr->data != refVal){
		curr = curr->head;
	}
	if(curr == nullptr) return -1;

	Node *oldNext = curr->head;
	Node *node = newNode(newVal, curr, oldNext);  // tail=curr, head=oldNext
	curr->head = node;
	if (oldNext != nullptr) oldNext->tail = node;
	return 0;
}
