#pragma once
#include <iostream>

template<typename T>
class Node{
public:
	T data{};
	Node *head {nullptr};
	Node *tail {nullptr};

	//Constructors
	Node(T v) : data(v), head(nullptr), tail(nullptr){};
	Node(T v, Node *t, Node *h) : data(v), head(h), tail(t){};

	void push_front(Node &other)
	{
		Node *curr = this;
		while(curr->head != nullptr)
			curr = curr->head;
		curr->head = &other;
		other.tail = curr;
	}
	void push_back(Node &other)
	{
		Node *curr = this;
		while(curr->tail != nullptr)
			curr = curr->tail;
		curr->tail = &other;
		other.head = curr;
	}
	void pop_front()
	{
		Node *curr = this;
		while(curr->head != nullptr)
			curr = curr->head;
		if(curr->tail != nullptr)
			curr->tail->head = nullptr;
		curr->tail = nullptr;
	}
	void pop_back()
	{
		Node *curr = this;
		while(curr->tail != nullptr)
			curr = curr->tail;
		curr->head->tail = nullptr;
		curr->head = nullptr;
	}
	Node *front()
	{
		Node *curr = this;
		while(curr->head != nullptr)
			curr = curr->head;
		return curr;
	}
	Node *back()
	{
		Node *curr = this;
		while(curr->tail != nullptr)
			curr = curr->tail;
		return curr;
	}
	bool empty()
	{
		return head == nullptr && tail == nullptr;
	}
	long long size()
	{
		long long count = 0;
		Node *curr = this->back();
		while(curr != nullptr){
			curr = curr->head;
			count ++;
		}
		return count ;
	}
	void reverse()
	{
		Node *curr = this->front();
		while(curr != nullptr){
			std::cout << curr->data << ", ";
			curr = curr->tail;
		}
	}
	int insert_after(int newVal, int refVal)
	{
		Node *curr = this;
		while(curr != nullptr && curr->data != refVal){
			curr = curr->head;
		}
		if(curr == nullptr) return -1;

		Node *oldNext = curr->head;
		Node *node = new Node(newVal, curr, oldNext);  // tail=curr, head=oldNext
		curr->head = node;
		if (oldNext != nullptr) oldNext->tail = node;
		return 0;
	}
};
