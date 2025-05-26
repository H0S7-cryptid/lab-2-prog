#include "Btree_struct_int.h"

void ShowSortTreeIncInt(nodeI* seeker)
{
	if (seeker == NULL) return;
	ShowSortTreeIncInt(seeker->left);
	printf("%d ", seeker->data);
	ShowSortTreeIncInt(seeker->right);
}

void ShowSortTreeDecInt(nodeI* seeker)
{
	if (seeker == NULL) return;
	ShowSortTreeDecInt(seeker->right);
	printf("%d ", seeker->data);
	ShowSortTreeDecInt(seeker->left);
}

void InsertIntoTreeInt(nodeI** search, int value, int* ins_c)
{
	if (*search == NULL)
	{
		*search = (nodeI*)malloc(sizeof(nodeI));
		if (!*search) return;
		(*search)->right = NULL;
		(*search)->left = NULL;
		(*search)->data = value;
		(*ins_c)++;
		return;
	}

	if ((*search)->data == value) return;

	if ((*search)->data > value)
		InsertIntoTreeInt(&(*search)->left, value, ins_c);
	else
		InsertIntoTreeInt(&(*search)->right, value, ins_c);
}

nodeI* ExtractFromTreeInt(nodeI** search, int key, process* state, nodeI** prev) 
{
	if (*search == NULL) { printf("Нет такого значения!\n"); *state = FAILURE; return NULL;	}

	if ((*search)->data == key) 
	{
		nodeI* temp = *search;

		if ((*search)->left == NULL) 
		{
			*search = (*search)->right;
			*state = PROCESS_SUCСESS;
			return temp;
		}
		if ((*search)->right == NULL) 
		{
			*search = (*search)->left;
			*state = PROCESS_SUCСESS;
			return temp;
		}

		nodeI** pred_ptr = &((*search)->left);

		while ((*pred_ptr)->right != NULL) 
			pred_ptr = &((*pred_ptr)->right);

		(*search)->data = (*pred_ptr)->data;

		nodeI* removed = *pred_ptr;
		*pred_ptr = (*pred_ptr)->left;

		*state = PROCESS_SUCСESS;
		return removed;
	}

	if (key < (*search)->data)
		return ExtractFromTreeInt(&((*search)->left), key, state, search);
	else
		return ExtractFromTreeInt(&((*search)->right), key, state, search);
}

int DeleteTreeInt(nodeI** root)
{
	process state = FAILURE;

	if (*root == NULL) return state;

	while (*root != NULL)
	{
		process state_ = FAILURE;
		nodeI* tmp = ExtractFromTreeInt(root, (*root)->data, &state_, root);
		if (state_) free(tmp);
		else continue;
	}

	state = PROCESS_SUCСESS;

	return state;
}

int CreateTreeInt(nodeI** root, int num_of_nodes)
{
	srand(time(NULL));

	int idx = 0;

	int* actuall_idx = (int*)malloc(sizeof(int));
	if (!actuall_idx) return FAILURE;
	*actuall_idx = 0;

	int fact_idx = 0;

	if (num_of_nodes < 0) return FAILURE;

	while (idx < num_of_nodes)
	{
		fact_idx = *actuall_idx;
		int rand_num = rand() % 101;
		InsertIntoTreeInt(root, rand_num, actuall_idx);

		if (fact_idx == *actuall_idx) continue;

		idx++;
	}

	return PROCESS_SUCСESS;
}
