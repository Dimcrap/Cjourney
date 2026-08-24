#include "quizgame.h"
#include <stdio.h>
#include <string.h>




curlticket ticket;
char  listurl[URL_LENGTH];
char  questionurl[URL_LENGTH_MID];
char id[URL_LENGTH];
char authheader[URL_LENGTH_MID];
char categoryid[URL_LENGTH];




void initAPP(){
    srand(time(NULL));
    initcurl(&ticket);
    initparserpaths();

    strcpy(listurl, "https://quizapi.io/api/v1/quizzes?limit=5");

    strcpy(categoryid, extractrandom_catid());
    printf("\ncatgoryid defined as :%s\n\n",categoryid);
    snprintf(questionurl,sizeof(questionurl) ,"https://quizapi.io/api/v1/questions?"
    "quiz_id=%s&include_answers=true",categoryid);

    strcpy(authheader,
         "Authorization: Bearer qa_sk_f1307e26ecf484d0deb665f71e9345746ac73e43");

};



void refillmenu(){
    fetchurl(&ticket, listurl);
	fetchheader(&ticket , authheader);
	writeoutput("menu.json", &ticket);
    printf("menu refilled and wroted!\n");
    mainmenu();     
};



void refillquestions(){
    fetchurl(&ticket, questionurl);
	fetchheader(&ticket , authheader);
	writeoutput("quiz.json", &ticket);
    printf("questions refreshed wroted\n");
    lastquiz=0;
    mainmenu();
};



void defineuser_category(){
    char catIDs[10][75];
    int pickup;

    extract_categories(catIDs);

    printf("\nchoose category: ");
    scanf("%d",&pickup);
    while(strcmp(catIDs[pickup-1],"")==0){
        printf("\nunvalid input\nchoose category:");
        scanf("%d",&pickup);
    };
    
    strcpy(categoryid,catIDs[pickup-1]);
    printf("category changed\n");
    snprintf(questionurl,sizeof(questionurl) , "https://quizapi.io/api/v1/questions?"
        "quiz_id=%s&include_answers=true",categoryid);
    refillquestions();
    mainmenu();

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
    "1-define category for game\n2-answer quiz\n3-refresh quizes\n4-refresh menu\n\t:");
    scanf("%d",&pickup);

    while(pickup>4 || pickup<1){
        printf("unvalid input!\n1-define category for game\n2-ask quiz\n3-refresh quizes\n"
            "4-refresh menu\n  :");
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
        case 4:
            refillmenu();
            break;
        default:
            mainmenu();
    }


};



void gamecleanup(){
    cleanups(&ticket);
};

