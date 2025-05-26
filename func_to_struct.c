#include "STRUCT.h"

int IsTrueNumber(char* number)
{
	const char* special_symbols = "\\|~`!@#$%^&*()_+=?:%;№";
	if (strpbrk(number, special_symbols) != NULL) return NUM_IS_BAD;

	if (number[0] == '\0' || number[0] == '\n' || number[0] == '/') return NUM_IS_BAD;
	
	int is_negative = (number[0] == '-') ? 1 : 0;
	size_t start_idx = is_negative ? 1 : 0, len = strlen(number);
	
	if (number[len] == '\n') { number[len - 1] = '\0'; len--; }
	
	if (len == 0 && is_negative == 1) return NUM_IS_BAD;
	
	for (size_t i = start_idx; i < len; i++) if (isalpha(number[i])) return NUM_IS_BAD;
	
	return NUM_IS_GOOD;
}

void printGroup(const group* g)
{
	const char* formatstr = "Study direction: %s\nGroup name: %s\nEnrollment year: %d\nLevel of preparation: %s\n";
	char* lvl_of_preporation_decoded = g->level_of_preparation == 1 ? "Magistracy" : "Baccalaureate";
	printf(formatstr, g->study_direction, g->group_name, g->enrollment_year, lvl_of_preporation_decoded);
	printf("\n");
}

int isCorrectGroup(const group* g)
{
	if (g->enrollment_year > 2024) return INCRCT_ENR_YEAR;
	if (g->level_of_preparation > 1) return INCRCT_LVL_OF_PREP;
	return INIT_DONE;
}

group* initGroup(group* g, const char* group_name, const char* study_direction, const int enrollment_year, const char level_of_preparation)
{
	if (g == NULL)
	{
		g = (group*)malloc(sizeof(group));
		if (!g) return NULL;
	}
	strncpy_s(g->group_name, MAX_GROUP_NAME_LEN, group_name, MAX_GROUP_NAME_LEN);
	strncpy_s(g->study_direction, MAX_STUDY_DIRECTION_LEN, study_direction, MAX_STUDY_DIRECTION_LEN);
	g->level_of_preparation = level_of_preparation;
	g->enrollment_year = enrollment_year;
	if (isCorrectGroup(g) == INIT_DONE)
		return g;
	else return initGroup(g, "", "", 1950, 0);
}

int LvlOfPrepCheck(char lvl_of_prep_1, char lvl_of_prep_2)
{
	if (lvl_of_prep_1 == lvl_of_prep_2) return GROUPS_ARE_EQUAL;
	else if (lvl_of_prep_1 < lvl_of_prep_2) return GROUP1_IS_SMALLER;
	else return GROUP2_IS_SMALLER;
}

int EnrYearCheck(int year_1, int year_2)
{
	if (year_1 == year_2) return GROUPS_ARE_EQUAL;
	else if (year_1 < year_2) return GROUP1_IS_SMALLER;
	else return GROUP2_IS_SMALLER;
}

int StudDirCheck(char* stud_dir_1, char* stud_dir_2)
{
	int is_eq = strcmp(stud_dir_1, stud_dir_2);
	if (is_eq == 0) return GROUPS_ARE_EQUAL;
	else if (is_eq < 0) return GROUP1_IS_SMALLER;
	else return GROUP2_IS_SMALLER;
}

int GroupNameCheck(char* name_1, char* name_2)
{
	int is_eq = strcmp(name_1, name_2);
	if (is_eq == 0) return GROUPS_ARE_EQUAL;
	else if (is_eq < 0) return GROUP1_IS_SMALLER;
	else return GROUP2_IS_SMALLER;
}

int isEqualGroup(group* g1, group* g2)
{
	int is_eq_E = EnrYearCheck(g1->enrollment_year, g2->enrollment_year) == GROUPS_ARE_EQUAL;
	int is_eq_Y = LvlOfPrepCheck(g1->level_of_preparation, g2->level_of_preparation) == GROUPS_ARE_EQUAL;
	int is_eq_N = GroupNameCheck(g1->group_name, g2->group_name) == GROUPS_ARE_EQUAL;
	int is_eq_SD = StudDirCheck(g1->study_direction, g2->study_direction) == GROUPS_ARE_EQUAL;

	if (is_eq_E && is_eq_Y && is_eq_N && is_eq_SD) return GROUPS_ARE_EQUAL;
	else return GROUPS_ARE_NOT_EQUAL;
}

int WhichGroupIsSmaller(const group* g1, const group* g2)
{
	if (EnrYearCheck(g1->enrollment_year, g2->enrollment_year) != GROUPS_ARE_EQUAL) 
		return EnrYearCheck(g1->enrollment_year, g2->enrollment_year);
	if (LvlOfPrepCheck(g1->level_of_preparation, g2->level_of_preparation) != GROUPS_ARE_EQUAL)
		return LvlOfPrepCheck(g1->level_of_preparation, g2->level_of_preparation);
	if (GroupNameCheck(g1->group_name, g2->group_name) != GROUPS_ARE_EQUAL)
		return GroupNameCheck(g1->group_name, g2->group_name);
	if (StudDirCheck(g1->study_direction, g2->study_direction) != GROUPS_ARE_EQUAL)
		return StudDirCheck(g1->study_direction, g2->study_direction);

	return GROUPS_ARE_EQUAL;
}
