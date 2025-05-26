#ifndef BTREE_STRUCT_INT
#define BTREE_STRUCT_INT

#include"STRUCT.h"

// Перечислимый тип итогового результата процесса
typedef enum Process { PROCESS_SUCСESS = 1, FAILURE = 0 } process;

// Структура, представляющая собой узел (элемент) дерева
struct Btree_node_int
{
	int data;
	struct Btree_node_int* right;
	struct Btree_node_int* left;
};

typedef struct Btree_node_int nodeI;

// Функция вставки элемента в дерево
void InsertIntoTreeInt(nodeI** search, int value, int* ins_c);

// Функция исключения элемента из дерева и его дальнейшая обработка
nodeI* ExtractFromTreeInt(nodeI** search, int key, process* state, nodeI** prev);

// Функция удаления всего дерева
int DeleteTreeInt(nodeI** root);

// Функция создания дерева с заданным количеством узлов (листьев)
int CreateTreeInt(nodeI** root, int num_of_nodes);

// Функция, выводящая сведения о всём дереве в порядке возрастания
void ShowSortTreeIncInt(nodeI* seeker);

// Функция, выводящая сведения о всём дереве в порядке убывания
void ShowSortTreeDecInt(nodeI* seeker);

#endif
