#include "redblack.h"

RBNode Nil; // NULL값으로 다 포인팅 해줄거

RBNode* Create(int NewData,int ox)
{
	RBNode* NewNode = (RBNode*) malloc(sizeof(RBNode));
	NewNode->Parent = NULL;
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Data = NewData;
	NewNode->Color = Black;
	NewNode->ox = ox; //자리에 사람이 있는지 없는지 여부를 저장합니다.
	return NewNode;
}

void Destroy(RBNode* Node)
{
	free(Node);
}

void TreeDestroy(RBNode* Tree)
{
	if(Tree->Right != &Nil)
		TreeDestroy(Tree->Right);

	if(Tree->Left != &Nil)
		TreeDestroy(Tree->Left);

	Tree->Left = &Nil;
	Tree->Right = &Nil;

	Destroy(Tree);
}

void RotateRight(RBNode** Root, RBNode* Parent)
{
	RBNode* LeftChild = Parent->Left;
	Parent->Left = LeftChild->Right;
	
	if(LeftChild->Right != &Nil)
		LeftChild->Right->Parent = Parent;

	LeftChild->Parent = Parent->Parent;

	if(Parent -> Parent == NULL)
		(*Root) = LeftChild;
	else
	{
		if (Parent == Parent->Parent->Left)
			Parent->Parent->Left = LeftChild;
		else
			Parent->Parent->Right = LeftChild;
	}

	LeftChild->Right = Parent;
	Parent->Parent = LeftChild;
}

void RotateLeft(RBNode** Root, RBNode* Parent)
{
	RBNode* RightChild = Parent->Right;
	Parent->Right = RightChild->Left;

	if(RightChild->Left != &Nil)
		RightChild->Left->Parent = Parent;

	RightChild->Parent = Parent ->Parent;

	if(Parent->Parent == NULL)
		(*Root) = RightChild;
	else
	{
		if(Parent == Parent->Parent->Left)
			Parent->Parent->Left = RightChild;
		else
			Parent->Parent->Right = RightChild;
	}

	RightChild->Left = Parent;
	Parent->Parent = RightChild;
}

RBNode* SearchMin(RBNode* Tree)
{
	if(Tree == &Nil)
		return &Nil;

	if(Tree->Left == &Nil)
		return Tree;
	else
		return SearchMin(Tree->Left);
}
void Insert(RBNode** Tree, RBNode* NewNode)
{
	InsertHelp(Tree, NewNode);

	NewNode->Color = Red;
	NewNode->Left = &Nil;
	NewNode->Right = &Nil;

	InsertAfter(Tree, NewNode);
}

void InsertHelp(RBNode** Tree, RBNode* NewNode)
{
	if( (*Tree) == NULL)
		(*Tree) = NewNode;

	if( (*Tree)->Data < NewNode->Data)
	{
		if( (*Tree) ->Right == &Nil)
		{
			(*Tree) ->Right = NewNode;
			NewNode->Parent = (*Tree);
		}
		else
			InsertHelp(&(*Tree)->Right, NewNode);
	}

	else if((*Tree) ->Data > NewNode->Data)
	{
		if( (*Tree)->Left == &Nil)
		{
			(*Tree)->Left = NewNode;
			NewNode->Parent = (*Tree);
		}
		else
			InsertHelp(&(*Tree)->Left, NewNode);
	}
}

void InsertAfter(RBNode** Root, RBNode* Node)
{
	while (Node!=(*Root) && Node->Parent->Color == Red)
	{
		
		if(Node->Parent == Node->Parent->Parent->Left)
		{
			RBNode* Uncle = Node->Parent->Parent->Right;
			if(Uncle->Color == Red)
			{
				Node->Parent->Color = Black;
				Uncle->Color = Black;
				Node->Parent->Parent->Color = Red;

				Node= Node->Parent->Parent;
			}
			else
			{
				if(Node == Node->Parent ->Right)
				{
					Node= Node->Parent;
					RotateLeft(Root,Node);
				}

				Node->Parent->Color = Black;
				Node->Parent->Parent->Color = Red;

				RotateRight(Root, Node->Parent->Parent);
			}
		}
		else
		{
			RBNode* Uncle = Node->Parent->Parent->Left;
			if(Uncle->Color == Red)
			{
				Node->Parent->Color = Black;
				Uncle->Color = Black;
				Node->Parent->Parent->Color = Red;
				Node = Node->Parent->Parent;
			}
			else
			{
				if(Node == Node->Parent->Left)
				{
					Node = Node->Parent;
					RotateRight(Root, Node);
				}

				Node->Parent->Color = Black;
				Node->Parent->Parent->Color = Red;
				RotateLeft(Root, Node->Parent->Parent);
			}
		}
	}
	(*Root) ->Color = Black;
}

RBNode* Delete(RBNode** Root, int Data)
{
	RBNode* Deleted = NULL;
	RBNode* Successor = NULL;
	RBNode* Target = Search((*Root), Data);

	if(Target == NULL)
		return NULL;

	if(Target->Left == &Nil || Target->Right == &Nil)
		Deleted = Target;
	else
	{
		Deleted = SearchMin(Target->Right);
		Target->Data = Deleted->Data;
	}

	if(Deleted->Left != &Nil)
		Successor = Deleted->Left;
	else

		Successor = Deleted->Right;

	Successor->Parent = Deleted->Parent;

	if(Deleted->Parent ==NULL)
		(*Root) = Successor;
	else
	{
		if(Deleted == Deleted->Parent->Left)
			Deleted->Parent->Left = Successor;
		else
			Deleted->Parent->Right = Successor;
	}

	if(Deleted->Color == Black)
		DeleteAfter(Root,Successor);

	return Deleted;
}

void DeleteAfter(RBNode** Root, RBNode* Successor)
{
	RBNode* Sibling = NULL;

	while (Successor->Parent != NULL && Successor->Color == Black)
	{
		if(Successor == Successor->Parent->Left)
		{
			Sibling = Successor ->Parent ->Right;

			if(Sibling->Color == Red)
			{
				Sibling->Color = Black;
				Successor->Parent->Color = Red;
				RotateLeft(Root, Successor->Parent);
			}
			else
			{
				if(Sibling->Left->Color == Black && Sibling->Right->Color == Black)
				{
					Sibling->Color = Red;
					Successor = Successor ->Parent;
				}

				else
				{
					if(Sibling ->Left ->Color = Red)
					{
						Sibling->Left->Color = Black;
						Sibling->Color = Red;
						RotateRight(Root,Sibling);
						Sibling = Successor->Parent->Right;
					}

					Sibling->Color = Successor->Parent->Color;
					Sibling->Right->Color = Black;
					RotateLeft(Root, Successor->Parent);
					Successor = (*Root);
				}
			}
		}
		else
		{
			Sibling = Successor->Parent->Left;

			if(Sibling->Color == Red)
			{
				Sibling->Color = Black;
				Successor->Parent->Color = Red;
				RotateRight(Root, Successor->Parent);
			}
			else
			{
				if(Sibling->Right->Color == Black && Sibling->Left->Color == Black)
				{
					Sibling ->Color = Red;
					Successor = Successor->Parent;
				}
				else
				{
					if(Sibling->Right->Color == Red)
					{
						Sibling->Right->Color = Black;
						Sibling->Color = Red;

						RotateLeft(Root,Sibling);
						Sibling = Successor->Parent->Left;
					}
					Sibling->Color = Successor->Parent->Color;
					Successor->Parent->Color = Black;
					Sibling->Left->Color = Black;
					RotateRight(Root,Successor->Parent);
					Successor = (*Root);
				}
			}
		}
	}
	Successor->Color = Black;
}

RBNode* Search(RBNode* Tree, int target)
{
	if (Tree == &Nil)
		return NULL;
	
	if(Tree->Data > target)
		return Search(Tree->Left, target);
	else if (Tree->Data < target)
		return Search(Tree->Right, target);
	else
		return Tree;
}
void Print(RBNode* Node, int depth, int black)
{
	int i = 0;
	char c = 'a';
	int v = -1;
	char cnt[1000];

	if (Node == NULL || Node == &Nil)
		return;

	if (Node->Color == Black)
		black++;

	if (Node->Parent != NULL)
	{
		v = Node->Parent->Data;

		if (Node->Parent->Left == Node)
			c = 'l'; // LEFTCHILD
		else
			c = 'r'; //RIGHTCHILD
	}

	if (Node->Left == &Nil && Node->Right == &Nil)
		sprintf(cnt, "..%d", black);
	else
		sprintf(cnt, " ");

	printf("%d %s [%c, %d] %s\n", Node->Data, (Node->Color == Red) ? "Red" : "Black", c, v, cnt);

	Print(Node->Left, depth + 1, black);
	Print(Node->Right, depth + 1, black);
}