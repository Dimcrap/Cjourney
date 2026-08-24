#include <cjson/cJSON.h>
#include <stdio.h>
#include <string.h>

#define LENGTH 12

extern char menupath[16];
extern char quizespath[16];
extern int lastquiz;



typedef struct{
char explenatin[512];
char question[256];
char difficulity[16];
char answers[4][32];
int trueindex;
}quiz;



void initparserpaths();
void extract_categories( char  catgeoryId[10][75] );
int countkeyword( cJSON * dataarray , char key[] );
void pickaquiz( quiz * qz );
void extractanswers( cJSON * answersarray , quiz * quizinfo );
char * extractrandom_catid();


void extract_quiz();

