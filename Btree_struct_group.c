#ifndef BTREE_STRUCT_GROUP
#define BTREE_STRUCT_GROUP

#include"STRUCT.h"

typedef enum Process_ { PROCESS_SUCСESS_ = 1, FAILURE_ = 0 } process_;

struct Btree_node_group
{
	group data;
	struct Btree_node_group* left;
	struct Btree_node_group* right;
};

typedef struct Btree_node_group nodeG;

// Функция вставки элемента в дерево
void InsertIntoTreeGr(nodeG** search, group* value, int* ins_c);

// Функция исключения элемента из дерева и его дальнейшая обработка
nodeG* ExtractFromTreeGr(nodeG** search, group* key, process_* state, nodeG** prev);

// Функция удаления всего дерева
int DeleteTreeGr(nodeG** root);

// Функция, выводящая сведения о всём дереве в порядке возрастания
void ShowSortTreeIncGr(nodeG* seeker);

// Функция, выводящая сведения о всём дереве в порядке убывания
void ShowSortTreeDecGr(nodeG* seeker);

// Функция создания и вставки групп, заданных пользователем (любое количество)
void InsertGroupsFromUser(nodeG** root);

// Функция исключения найденого элемента
nodeG* ExtractGroupFromTree(nodeG** root);

#endif
