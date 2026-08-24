#include "apihandler.h"
#include "parsehandler.h"
#include "time.h"


#define URL_LENGTH 64
#define URL_LENGTH_MID 95


extern curlticket ticket;
extern char  listurl[URL_LENGTH];
extern char  questionurl[URL_LENGTH_MID];
extern char categoryid[URL_LENGTH];
extern char authheader[URL_LENGTH_MID];



void initAPP();
void refillmenu();
void refillquestions();
void mainmenu();
void defineuser_category();
void askquiz();
void definerandomcat(char cat[URL_LENGTH]);


void gamecleanup();

