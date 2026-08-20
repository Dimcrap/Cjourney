#include "quizgame.h"
#include <stdio.h>
#include <string.h>

curlticket ticket;
char  listurl[URL_LENGTH];
char  questionurl[URL_LENGTH_MID];
char authheader[URL_LENGTH_MID];


void initAPP(){
    initcurl(&ticket);
    strcpy(listurl, "https://quizapi.io/api/v1/quizzes?limit=5");
    strcpy(questionurl, "https://quizapi.io/api/v1/questions?quiz_id"
        "=QUIZ_ID&include_answers=true");
    strcpy(authheader,
         "Authorization: Bearer qa_sk_f1307e26ecf484d0deb665f71e9345746ac73e43");
    
};


void refillmenu(){
    fetchurl(&ticket, listurl);
		fetchheader(&ticket , authheader);
		writeoutput("menu.json", &ticket);
    printf("menu refilled completly!\n");
};



void refillquestions(){
    fetchurl(&ticket, questionurl);
		fetchheader(&ticket , authheader);
		writeoutput("quiz.json", &ticket);
        printf("questions refreshed!\n");
};



void listcategories(){
    /*==================================================================================================*/
    
    

};



void mainmenu(){
    int pickup;
    printf("\t\t==================Quiz game==================\n\n\nchoose by number:\n"
    "1-define category for game\n2-Unknow\n\t:");
    scanf("%d",&pickup);

    while(pickup>1 || pickup<1){
        printf("unvalid input!\n1-define category for game\n2-Unknow\n  :");
        scanf("%d",&pickup);
    };

    switch (pickup) {
        case 1:
            listcategories();
            break;

    
    }

};



void gamecleanup(){
    cleanups(&ticket);
};

