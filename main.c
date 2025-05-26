#include "Btree_struct_int.h"
#include "Btree_struct_group.h"

static void WorkWithInt()
{
	printf("\t\t\tСоздание бинарного дерева целых чисел, значения которых в диапазоне от 0 до 100\n\n");

	nodeI* to_delete = NULL;
	nodeI* root = NULL;
	process state = FAILURE;

	char buffer[MAX_BUFF_SIZE];
	int num_of_leaves;
	int key;

	printf("Введите количество узлов дерева: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	if (IsTrueNumber(buffer) == NUM_IS_GOOD) num_of_leaves = atoi(buffer);
	else return;
	
	if (CreateTreeInt(&root, num_of_leaves)) printf("Создание списка успешно!\n");

	ShowSortTreeIncInt(root);
	printf("\n");

	/*ShowSortTreeDec(root);
	printf("\n");*/

	printf("Какой элемент хотите удалить? Введите значение: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	if (IsTrueNumber(buffer) == NUM_IS_GOOD) key = atoi(buffer);
	else return;

	to_delete = ExtractFromTreeInt(&root, key, &state, &root); 
	if (to_delete)
	{
		printf("Удаление числа %d прошло успешно!\n", key);
		free(to_delete);
	}
	ShowSortTreeIncInt(root);
	printf("\n");

	if (DeleteTreeInt(&root)) printf("Дерево удалено!\n");
}

static void WordWithGroup()
{
	printf("\t\t\tСоздание бинарного дерева структур, хранящих данные о группе студентов\n");
	nodeG* root = NULL;
	
	InsertGroupsFromUser(&root);
	printf("\n");

	printf("\t\tВведённое дерево элементов: \n");
	ShowSortTreeIncGr(root);
	printf("\n");

	nodeG* to_delete = NULL;
	to_delete = ExtractGroupFromTree(&root); 
	free(to_delete);
	printf("\n");

	printf("\t\tОтредактированный список: \n");
	ShowSortTreeIncGr(root);
	printf("\n");

	DeleteTreeGr(&root);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	WorkWithInt();

	//WordWithGroup();

	return 0;
}
