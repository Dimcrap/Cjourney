#include <cjson/cJSON.h>
#include <stdio.h>
#include <string.h>

#define LENGTH 12

extern char menupath[16];
extern char quizespath[16];


void initparserpaths();
void extract_categories(char  catgeoryId[10][75]);
void extract_quiz(char cateoryId[10][75]);

