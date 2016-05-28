#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int seatnum;
	int color;
	node_pointer parent;
	node_pointer left;
	node_pointer right;
}node;

typedef struct node* node_pointer;

node_pointer New_Node() {
	node_pointer y = (node_pointer)malloc(sizeof(node)); 
	y->color = 1;	y->seatnum = -1; y->right = -1; y->left = NULL; y->right = NULL; y->parent = NULL;
	return y;
}

void Left_Rotate(node_pointer root, node_pointer x) {
	node_pointer y = x->right;
	x->right = y->left;

	if (y->left != NULL) 	y->left->parent = x;

	y->parent = x->parent;

	if (x->parent == NULL)	root = y; 
	else if (x == x->parent->left)	x->parent->left = y;
	else x->parent->right = y;

	y->left = x;	x->parent = y;
}

void Right_Rotate(node_pointer root, node_pointer x) {
	node_pointer y = x->left;
	x->left = y->right;

	if (y->right != NULL) 	y->right->parent = x;

	y->parent = x->parent;

	if (x->parent == NULL)	root = y;
	else if (x == x->parent->right)	x->parent->right = y;
	else x->parent->left = y;

	y->right = x;	x->parent = y;
}

void Insert_Fixup(node_pointer root, node_pointer z) {
	node_pointer y = New_Node();
	while (z->parent->color == 0) {
		if (z->parent == z->parent->parent->left) {
			y = z->parent->parent->right;
			if (y->color == 0) {
				z->parent->color = 1;
				y->color = 1;
				z->parent->parent->color = 0;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;	Left_Rotate(root, z);
				}
				z->parent->color = 1;	z->parent->parent->color = 0; Right_Rotate(root, z->parent->parent);
			}
		}
		else {
			y = z->parent->parent->left;
			if (y->color == 0) {
				z->parent->color = 1;
				y->color = 1;
				z->parent->parent->color = 0;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;	Right_Rotate(root, z);
				}
				z->parent->color = 1;	z->parent->parent->color = 0; Left_Rotate(root, z->parent->parent);
			}
		}
	}
}

void Insert_Node(node_pointer root, node_pointer z) {
	node_pointer y = New_Node(), x = root;
	
	if (Find_Node(root, z->seatnum) != NULL) {
		printf("%d is already occupied \n", x->seatnum);
		return;
	}

	if (root->seatnum == -1) {	root = z;	return;	}

	while (x != NULL) {
		y = x;
		if (z->seatnum < x->seatnum)	x = x->left;
		else x = x->right;
	}
	z->parent = y;
	
	if (y == NULL) root = z;
	else if (z->seatnum < y->seatnum)	y->left = z;
	else y->right = z;
	
	z->left = NULL;	z->right = NULL; z->color = 0;

	Insert_Fixup(root, z);
}

node_pointer Find_Node(node_pointer root, int seat) {
	node_pointer x = root, y;
	if (x->seatnum == seat)	return root;
	
	while (x != NULL) {
		if (x->seatnum == seat)	return x;
		else if (x->seatnum > seat)	x = x->left;
		else x = x->right;
	}
	return x;
}

void Delete_Fixup(node_pointer root, node_pointer x) {
	node_pointer w = New_Node();

	while (x != root && x->color == 1) {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == 0) {
				w->color = 1;
				x->parent->color = 0;
				Left_Rotate(root, x->parent);
				w = x->parent->right;
			}
			if (w->left->color == 1 && w->right->color == 1) {
				w->color = 0;	x = x->parent;
			}
			else {
				if (w->right->color == 1) {
					w->left->color = 1;
					w->color = 0;
					Right_Rotate(root, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = 1;
				w->right->color = 1;
				Left_Rotate(root, x->parent);
				x = root;
			}
		}
		else {
			w = x->parent->left;
			if (w->color == 0) {
				w->color = 1;
				x->parent->color = 0;
				Right_Rotate(root, x->parent);
				w = x->parent->left;
			}
			if (w->right->color == 1 && w->left->color == 1) {
				w->color = 0;	x = x->parent;
			}
			else {
				if (w->left->color == 1) {
					w->right->color = 1;
					w->color = 0;
					Left_Rotate(root, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = 1;
				w->left->color = 1;
				Right_Rotate(root, x->parent);
				x = root;
			}
		}
	}
	x->color = 1;
}

void Delete_Node(node_pointer root, node_pointer z) {
	node_pointer y = New_Node(), x = New_Node();

	if (Find_Node(root, z->seatnum) == NULL) {
		printf("There is no %d\n", z->seatnum);
		return;
	}

	if (z->left == NULL || z->right == NULL)	y = z;
	else y = Tree_Successor(z);

	if (y->left != NULL)	x = y->left;
	else x = y->right;

	x->parent = y->parent;
	
	if (y->parent == NULL)	root = x;
	else if (y == y->parent->left)	y->parent->left = x;
	else	y->parent->right = x;

	if (y != z)	z->seatnum = y->seatnum;

	if (y->color == 1)	Delete_Fixup(root, x);

	return y;
}

node_pointer Tree_Successor(node* z) {
	node_pointer y = New_Node();

	if (z->right->seatnum != NULL) {
		y = z;
		while (y->left->seatnum != -1) {
			y = y->left;
		}
		return y;
	}
	else {
		y = z->parent;
		while (y != NULL && z->seatnum == y->right->seatnum) {
			z = y;
			y = y->parent;
		}
	}
	return y;
}