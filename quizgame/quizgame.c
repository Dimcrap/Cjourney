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
    strcpy(questionurl, "https://quizapi.io/api/v1/questions?cmmdjge2800bqutgrh5shuktc"
        "=QUIZ_ID&include_answers=true");
    strcpy(authheader,
         "Authorization: Bearer qa_sk_f1307e26ecf484d0deb665f71e9345746ac73e43");
    initparserpaths();
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
    lastquiz=0;
};


void defineuser_category(){
    char catIDs[10][75];
    int pickup;

    extract_categories(catIDs);

    printf("\nchoose category: ");
    scanf("%d",&pickup);
    while(strcmp(catIDs[pickup],NULL)){
        printf("\nunvalid input\nchoose category:");
        scanf("%d",&pickup);
    };
    
};


void askquiz(){

    quiz thequiz;
    pickaquiz(&thequiz);
    int pickup=0;

    printf("\n%s\ndifficulity:%s\t1-%s\n2-%s\t3-%s\t4-%s\n",
        thequiz.question,thequiz.difficulity,thequiz.answers[0],thequiz.answers[1],
    thequiz.answers[2],thequiz.answers[3]);
    scanf("%d",&pickup);
    
    if(pickup-1==thequiz.trueindex){
        printf("\nwell done it is correct!\n\n%s\n\n",thequiz.explenatin);
        mainmenu();
        
    }else{
        printf(" \n\n\nahh :( nice try\n\n\n ");
        mainmenu();

    };
    
    
};


void mainmenu(){
    int pickup;
    printf("\t\t==================Quiz game==================\n\n\nchoose by number:\n"
    "1-define category for game\n2-answer quiz\n3-refresh quizes\n\t:");
    scanf("%d",&pickup);

    while(pickup>3 || pickup<1){
        printf("unvalid input!\n1-define category for game\n2-ask quiz\n3-refresh quizes\n  :");
        scanf("%d",&pickup);
    };


    switch (pickup) {
        case 1:
            defineuser_category();
            break;
        case 2:
            askquiz();
            break;
        case 3:
            refillquestions();
            break;
    }


};



void gamecleanup(){
    cleanups(&ticket);
};

