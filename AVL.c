#include "AVL.h"
#include <stdio.h>


Status InsertAVL(BiTree *T, int e, Status *taller)
{
	if (!*T)
	{
		(*T) = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller = TRUE;
	}

	else
	{
		if (e == (*T)->data)
		{
			*taller = FALSE;
			return FALSE;
		}

		else if (e < (*T)->data)
		{
			if (!InsertAVL(&(*T)->lchild, e, taller))
			{
				return FALSE;
			}

			if (*taller)
			{
				switch ((*T)->bf)
				{
					case LH:
						LeftBalance(T);
						*taller = FALSE;
						break;
					case EH:
						(*T)->bf = LH;
						*taller = TRUE;
						break;
					case RH:
						(*T)->bf = EH;
						*taller = FALSE;
						break;
				}
			}
		}

		else
		{

			if (!InsertAVL(&(*T)->rchild, e, taller))
			{
				return FALSE;
			}

			if (*taller)
			{
				switch ((*T)->bf)
				{
					case LH:
						(*T)->bf = EH;
						*taller = FALSE;
						break;
					case EH:
						(*T)->bf = RH;
						*taller = TRUE;
						break;
					case RH:
						RightBalance(T);
						*taller = FALSE;
						break;
				}
			}
		}
	}

	return TRUE;
}

void LeftBalance(BiTree *T)
{
	BiTree L, Lr;
	L = (*T)->lchild;

	switch (L->bf)
	{
		case LH:
			L->bf = (*T)->bf = EH;
			R_Rotate(T);
			break;
		case RH:
			Lr = L->rchild;
			switch (Lr->bf)
			{
				case LH:
					L->bf = EH;
					(*T)->bf = RH;
					break;
				case EH:
					L->bf = (*T)->bf = EH;
					break;
				case RH:
					L->bf = LH;
					(*T)->bf = EH;
					break;
			}
			Lr->bf = EH;
			L_Rotate(&(*T)->lchild);
			R_Rotate(T);
	}
}

void RightBalance(BiTree *T)
{
	BiTree R, Rl;
	R = (*T)->rchild;

	switch (R->bf)
	{
	case RH:
		R->bf = (*T)->bf = EH;
		L_Rotate(T);
		break;
	case LH:
		Rl = R->lchild;
		switch (Rl->bf)
		{
		case LH:
			(*T)->bf = EH;
			R->bf = RH;
			break;
		case EH:
			R->bf  = (*T)->bf = EH;
			break;
		case RH:
			(*T)->bf = LH;
			R->bf = EH;
			break;
		}
		Rl->bf = EH;
		R_Rotate(&(*T)->rchild);
		L_Rotate(T);
	}
}

void R_Rotate(BiTree *p)
{
	BiTree q;
	q = (*p)->lchild;
	(*p)->lchild = q->rchild;
	q->rchild = *p;
	*p = q;
}

void L_Rotate(BiTree *p)
{
	BiTree q;
	q = (*p)->rchild;
	(*p)->rchild = q->lchild;
	q->lchild = *p;
	*p = q;
}