#include <stdio.h>
#include <stdlib.h>
#include "RBtree.h"

Node * newNode(int num,Node * parent)
{
	Node * nN = (Node *)malloc(sizeof(Node*) * 2 + sizeof(bool) * 2 + sizeof(int));
	nN->left = NULL;
	nN->right = NULL;
	nN->parent = parent;
	nN->seatNumber = num;
	nN->color = false;
	nN->use = false;
	return nN;
}
Node * getG_Parent(Node * node)
{
	if (node->parent != NULL)
	{
		return node->parent->parent;
	}
	else
	{
		return NULL;
	}
}
Node * getUncle(Node * node)
{
	Node * g = getG_Parent(node);
	if(g != NULL)
	{
		if (g->left == node->parent)
		{
			return g->right;
		}
		else
		{
			return g->left;
		}
	}
	else return NULL;
}
void rotate_left(Node * n)
{
	Node * c = n->right;
	Node * p = n->parent;

	if (c->left != NULL)
		c->left->parent = n;
	n->right = c->left;
	n->parent = c;
	c->left = n;
	c->parent = p;

	if (p != NULL)
	{
		if (p->left == n)
			p->left = c;
		else
			p->right = c;
	}
}
void rotate_right(Node * n)
{
	Node * c = n->left;
	Node * p = n->parent;

	if (c->right != NULL)
	{
		c->right->parent = n;
	}

	n->left = c->right;
	n->parent = c;
	c->right = n;
	c->parent = p;

	if (p != NULL)
	{
		if (p->right == n)
			p->right = c;
		else
			p->left = c;
	}

}
void insertCase5(Node * node)
{
	Node *g = getG_Parent(node);
	node->parent->color = false;
	g->color = true;
	if (node == node->parent->left)
		rotate_right(g);
	else
		rotate_left(g);
}
Node * getSibling(Node * n)
{
	if (n = n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}
void insertCase4(Node * node)
{
	Node *g = getG_Parent(node);
	if ((node == node->parent->right) && (node->parent = g->left))
	{
		rotate_left(node->parent);
		node = node->left;
	}
	else if ((node == node->parent->left) && (node->parent == g->right))
	{
		rotate_right(node->parent);
		node = node->right;
	}
	insertCase5(node);
}
void insertCase3(Node * node)
{
	Node * u = getUncle(node),*g;

	if ((u != NULL) && (u->color == true))
	{
		node->parent->color = false;
		u->color = false;
		g = getG_Parent(node);
		g->color = true;
		insertCase1(g);
	}
	else
	{
		
	}
}

void insertCase2(Node * node)
{
	if (node->parent->color = false)
	{
		return;
	}
	else
		insertCase3(node);

}

void insertCase1(Node * node)
{
	if (node->parent == NULL)
	{
		node->color = false;
	}
	else
		insertCase2(node);
}


void insert(RBtree * RB, int num)
{
	Node * cNode;
	if (RB->num == 0)
	{
		RB->root = newNode(num,NULL);
		RB->num++;
	}
	else
	{
		cNode = RB->root;
		while (1)
		{
			
			if (cNode->seatNumber < num)
			{
				if (cNode->left == NULL)
				{
					cNode->left = newNode(num,cNode);
					cNode->left->color = true;
					cNode = cNode->left;
					break;
				}
				else
				{
					cNode = cNode->left;
				}
			}
			else
			{
				if (cNode->right == NULL)
				{
					cNode->right = newNode(num,cNode);
					cNode->right->color = true;
					cNode = cNode->right;
					break;
				}
				else
				{
					cNode = cNode->right;
				}
			}
		}
		insertCase1(cNode);
	
	}
}
void deleteCase6(Node * n)
{
	Node * s = getSibling(n);

	s->color = n->parent->color;
	n->parent->color = false;

	if (n == n->parent->left)
	{
		s->right->color = false;
		rotate_left(n->parent);
	}
	else
	{
		s->left->color = false;
		rotate_right(n->parent);
	}
}
void deleteCase5(Node * n)
{
	Node * s = getSibling(n);

	if (s->color == false)
	{
		if ((n == n->parent->left) && (s->right->color == false) && (s->left->color == true))
		{
			s->color == true;
			s->left->color == false;
			rotate_right(s);
		}
		else if ((n == n->parent->right) && (s->left->color == false) && (s->right->color == true))
		{
			s->color == true;
			s->right->color == false;
			rotate_left(s);
		}
	}
	deleteCase6(n);
}
void deleteCase4(Node * n)
{
	Node * s = getSibling(n);

	if ((n->parent->color == true) && (s->color == false) && (s->left->color == false) && (s->right->color == false))
	{
		s->color == true;
		n->parent->color == false;
	}
	else
		deleteCase5(n);
}
void deleteCase3(Node * n)
{
	Node * s = getSibling(n);

	if ((n->parent->color == false) && (s->color == false) && (s->left == false) && (s->right == false))
	{
		s->color = true;
		deleteCase1(n->parent);
	}
	else
	{
		deleteCase4(n);
	}
}
void deleteCase2(Node * n)
{
	struct node *s = getSibling(n);
	if (s->color == true)
	{
		n->parent->color == true;
		s->color == false;
		if (n = n->parent->left)
			rotate_left(n->parent);
		else
			rotate_right(n->parent);
	}
	deleteCase3(n);
}
void deleteCase1(Node * n)
{
	if (n->parent != NULL)
		deleteCase2(n);
}
void deleteOneNode(Node * n)
{
	Node * child;
	Node * temp;
	if (n->left != NULL)
	{
		child = n->left;
	}
	else if (n->right != NULL)
	{
		child = n->right;
	}
	else
	{
		child = n;
	}
	if (n == n->parent->left)
	{
		n->parent->left = child;
		child->parent = n->parent;
	}
	else if (n == n->parent->right)
	{
		n->parent->right = child;
		child->parent = n->parent;
	}
	if (child->color == true)
	{
		child->color = false;
	}
	else
	{
		deleteCase1(child);
	}
	free(n);
	
}
Node * searchNode(RBtree * rb,int num)
{
	Node * cNode = rb->root;
	while (1)
	{
		if (cNode == NULL)
		{
			return NULL;
		}
		if (cNode->seatNumber > num)
		{
			cNode = cNode->left;
		}
		else if (cNode->seatNumber < num)
		{
			cNode = cNode->right;
		}
		else if (cNode->seatNumber == num)
		{
			return cNode;
		}
	}
}
void deleteNode(RBtree * rb, int num)
{
	Node * cNode = searchNode(rb, num);
	Node * tNode = cNode;
	if (cNode->seatNumber>num)
	{
		while (cNode->left != NULL)
		{
			cNode = cNode->right;
		}
		
	}
	else
	{
		while (cNode->right != NULL)
		{
			cNode = cNode->right;
		}
	}
	if (cNode != tNode)
	{
		tNode->seatNumber = cNode->seatNumber;
	}
	deleteOneNode(cNode);
}

