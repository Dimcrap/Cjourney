#include "apihandler.h"
#include "parsehandler.h"


#define URL_LENGTH 64
#define URL_LENGTH_MID 85

extern curlticket ticket;
extern char  listurl[URL_LENGTH];
extern char  questionurl[URL_LENGTH_MID];
extern char authheader[URL_LENGTH_MID];


void initAPP();
void refillmenu();
void refillquestions();
void mainmenu();
void defineuser_category();
void randomquiz();


void gamecleanup();

