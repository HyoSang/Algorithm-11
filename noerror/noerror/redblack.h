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
// 데이터 뭐 넣을지 딱히 안정해져서 int로 집어넣었습니당

/*Tree 회전*/
void RotateLeft(RBNode** Root, RBNode* Parent);
void RotateRight(RBNode** Root, RBNode* Parent);

/* Tree 생성 및 제거 */
RBNode* Create(int NewData);
void Destroy(RBNode* Node); // Node 제거
void TreeDestroy(RBNode* Tree); // Tree 제거

/*Insertion 관련 */
void Insert(RBNode** Tree, RBNode* NewNode);
void InsertHelp(RBNode** Tree, RBNode* NewNode);
void InsertAfter(RBNode** Tree, RBNode* NewNode);

/*Deletion 관련 */
RBNode* Delete(RBNode** Root, int target);
void DeleteAfter(RBNode** Root, RBNode* rbnode);

RBNode* SearchMin(RBNode* Tree);
RBNode* Search(RBNode* Tree, int target);

#endif