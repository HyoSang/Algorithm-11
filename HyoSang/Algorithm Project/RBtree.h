#pragma once
typedef struct rbtree
{
	int num;
	Node * root;
}RBtree;

typedef struct node
{
	Node * parent;
	Node * left;
	Node * right;
	int seatNumber;
	bool use;
	bool color;
}Node;


