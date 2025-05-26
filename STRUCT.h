#ifndef STRUCT
#define STRUCT

#define MAX_GROUP_NAME_LEN 20
#define MAX_STUDY_DIRECTION_LEN 50
#define MAX_BUFF_SIZE 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum check_number { NUM_IS_GOOD = 0, NUM_IS_BAD = -1 };

enum which_part_is_wrong { INIT_DONE = 0, INCRCT_ENR_YEAR = -1, INCRCT_LVL_OF_PREP = -2 };

enum group_comparison_eq {GROUPS_ARE_EQUAL = 0, GROUPS_ARE_NOT_EQUAL = - 1 };

enum group_comparison_sm_bg { GROUP1_IS_SMALLER = -1, GROUP2_IS_SMALLER = 1};

// Объект: Учебная группа.
//Характеристики объекта : Название группы, направление обучения, год набора, уровень подготовки(бакалавр / магистр).

struct study_group
{
	char group_name[MAX_GROUP_NAME_LEN];
	char study_direction[MAX_STUDY_DIRECTION_LEN];
	unsigned short enrollment_year;
	unsigned char level_of_preparation;
};

typedef struct study_group group;

int IsTrueNumber(char* number);

void printGroup(const group* g);

int isCorrectGroup(const group* g);

group* initGroup(group* g, const char* group_name, const char* study_direction, const int enrollment_year, const char level_of_preparation);

int LvlOfPrepCheck(char lvl_of_prep_1, char lvl_of_prep_2);

int EnrYearCheck(int year_1, int year_2);

int StudDirCheck(char* stud_dir_1, char* stud_dir_2);

int GroupNameCheck(char* name_1, char* name_2);

int WhichGroupIsSmaller(group* g1, group* g2);

int isEqualGroup(group* g1, group* g2);

#endif
