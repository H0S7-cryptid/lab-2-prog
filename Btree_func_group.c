#include "Btree_struct_group.h"

void ShowSortTreeIncGr(nodeG* seeker)
{
	if (seeker == NULL) return;
	ShowSortTreeIncGr(seeker->left);
	printGroup(&seeker->data);
	ShowSortTreeIncGr(seeker->right);
}

void ShowSortTreeDecGr(nodeG* seeker)
{
	if (seeker == NULL) return;
	ShowSortTreeDecGr(seeker->right); 
	printGroup(&seeker->data); 
	ShowSortTreeDecGr(seeker->left); 
}

void InsertIntoTreeGr(nodeG** search, group *value, int* ins_c)
{
	if (*search == NULL)
	{
		*search = (nodeG*)malloc(sizeof(nodeG));
		if (!*search) return;
		(*search)->right = NULL;
		(*search)->left = NULL;
		(*search)->data = *value;
		(*ins_c)++;
		return;
	}

	if (isEqualGroup(&(*search)->data, value) == GROUPS_ARE_EQUAL) return;

	if (WhichGroupIsSmaller(&(*search)->data, value) == GROUP2_IS_SMALLER)
		InsertIntoTreeGr(&(*search)->left, value, ins_c);
	else
		InsertIntoTreeGr(&(*search)->right, value, ins_c);
}

nodeG* ExtractFromTreeGr(nodeG** search, group* key, process_* state, nodeG** prev)
{
	if (*search == NULL) {
		printf("Нет такого значения!\n");
		*state = FAILURE_;
		return NULL;
	}

	if (isEqualGroup(&(*search)->data, key) == GROUPS_ARE_EQUAL)
	{
		nodeG* temp = *search;

		if ((*search)->left == NULL)
		{
			*search = (*search)->right;
			*state = PROCESS_SUCСESS_;
			return temp;
		}
		if ((*search)->right == NULL)
		{
			*search = (*search)->left;
			*state = PROCESS_SUCСESS_;
			return temp;
		}

		nodeG** pred_ptr = &((*search)->left);
		while ((*pred_ptr)->right != NULL)
			pred_ptr = &((*pred_ptr)->right);

		(*search)->data = (*pred_ptr)->data;
		nodeG* removed = *pred_ptr;
		*pred_ptr = (*pred_ptr)->left;

		*state = PROCESS_SUCСESS_;
		return removed;
	}

	// Здесь исправляем порядок аргументов, как в функции вставки.
	if (WhichGroupIsSmaller(&((*search)->data), key) == GROUP2_IS_SMALLER)
		return ExtractFromTreeGr(&((*search)->left), key, state, search);
	else
		return ExtractFromTreeGr(&((*search)->right), key, state, search);
}

int DeleteTreeGr(nodeG** root)
{
	process_ state = FAILURE_;

	if (*root == NULL) return state;

	while (*root != NULL)
	{
		process_ state_ = FAILURE_;
		nodeG* tmp = ExtractFromTreeGr(root, &(*root)->data, &state_, root);
		if (state_) free(tmp);
		else continue;
	}

	state = PROCESS_SUCСESS_;

	return state;
}

void InsertGroupsFromUser(nodeG** root)
{
	int ins_c = 0;
	group temp;
	char choice[10];  
	char buffer[20];
	char name[MAX_GROUP_NAME_LEN];
	char dir[MAX_STUDY_DIRECTION_LEN];
	char lvl;
	int year;

	while (1)
	{
		// Чтение данных группы от пользователя.
		int i = 0;
		printf("\nВведите имя группы: ");
		fgets(name, MAX_GROUP_NAME_LEN, stdin);
		while (name[i] != '\n') i++;
		if (name[i] == '\n') name[i] = '\0';
		i = 0;

		printf("Введите направление обучения: ");
		fgets(dir, MAX_STUDY_DIRECTION_LEN, stdin);
		while (dir[i] != '\n') i++;
		if (dir[i] == '\n') dir[i] = '\0';

		printf("Введите год поступления (целое число): ");
		fgets(buffer, 20, stdin);
		if (IsTrueNumber(buffer) == NUM_IS_GOOD) year = atoi(buffer);
		else return;
		
		printf("Введите уровень подготовки (целое число: 0 - Бакалавриат, 1 - Магистратура): ");
		fgets(buffer, 20, stdin);
		if (IsTrueNumber(buffer) == NUM_IS_GOOD && (atoi(buffer) >= 0 && atoi(buffer) <= 1))
			lvl = atoi(buffer);
		else return;
		
		initGroup(&temp, name, dir, year, lvl);

		InsertIntoTreeGr(root, &temp, &ins_c); 
		printf("Количество элементов: %d\n", ins_c);
		printf("Добавить еще группу? (y/n): ");
		fgets(choice, 10, stdin);
		if (choice[0] == 'n' || choice[0] == 'N')
			break;
	}
}

nodeG* ExtractGroupFromTree(nodeG** root) 
{
	int i = 0;
	char buffer[10];
	char name[MAX_GROUP_NAME_LEN];
	char dir[MAX_STUDY_DIRECTION_LEN];
	char lvl;
	int year;

	printf("Введите имя группы для удаления: ");
	fgets(name, MAX_GROUP_NAME_LEN, stdin);
	while (name[i] != '\n') i++;
	if (name[i] == '\n') name[i] = '\0';
	i = 0;

	printf("Введите направление обучения для удаления: ");
	fgets(dir, MAX_STUDY_DIRECTION_LEN, stdin); 
	while (dir[i] != '\n') i++; 
	if (dir[i] == '\n') dir[i] = '\0'; 
	
	printf("Введите год поступления группы для удаления: ");
	fgets(buffer, 10, stdin);
	if (IsTrueNumber(buffer) == NUM_IS_GOOD) year = atoi(buffer);
	else return;

	printf("Введите уровень подготовки (целое число: 0 - Бакалавриат, 1 - Магистратура): ");
	fgets(buffer, 10, stdin); 
	if (IsTrueNumber(buffer) == NUM_IS_GOOD && (atoi(buffer) >= 0 && atoi(buffer) <= 1)) 
		lvl = atoi(buffer); 
	else return; 

	group temp;
	initGroup(&temp, name, dir, year, lvl);

	process_ state = FAILURE_;
	nodeG* deleted = ExtractFromTreeGr(root, &temp, &state, root);
	return deleted;
}
