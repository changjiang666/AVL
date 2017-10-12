#pragma once
#define TRUE	1
#define FALSE	0

#define LH	1
#define EH  0
#define RH	-1

typedef int Status;
typedef struct BiTNode
{
	int data;
	int bf;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

Status InsertAVL(BiTree *T, int e, Status *taller);
void LeftBalance(BiTree *T);
void RightBalance(BiTree *T);
void L_Rotate(BiTree *p);
void R_Rotate(BiTree *p);