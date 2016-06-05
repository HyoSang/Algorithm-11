#ifndef REDBLACK_H
#define REDBLACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct tagNode
{
	struct tagNode* Parent;
	struct tagNode* Left;
	struct tagNode* Right;

	enum {Red, Black} Color;

	int Data;
} RBNode;
// ������ �� ������ ���� ���������� int�� ����־����ϴ�

/*Tree ȸ��*/
void RotateLeft(RBNode** Root, RBNode* Parent);
void RotateRight(RBNode** Root, RBNode* Parent);

/* Tree ���� �� ���� */
RBNode* Create(int NewData);
void Destroy(RBNode* Node); // Node ����
void TreeDestroy(RBNode* Tree); // Tree ����

/*Insertion ���� */
void Insert(RBNode** Tree, RBNode* NewNode);
void InsertHelp(RBNode** Tree, RBNode* NewNode);
void InsertAfter(RBNode** Tree, RBNode* NewNode);

/*Deletion ���� */
RBNode* Delete(RBNode** Root, int target);
void DeleteAfter(RBNode** Root, RBNode* rbnode);

RBNode* SearchMin(RBNode* Tree);
RBNode* Search(RBNode* Tree, int target);

#endif