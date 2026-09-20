#include <AL/al.h>
#include <AL/alc.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "beep/beep.h"
#include <poll.h>



double octave =50 ;//latency
double scale = 1 ;


static void keypushed(char key);
static void takeKeyboard();


static struct termios orig;

static void reset_terminal( void){
    tcsetattr(STDIN_FILENO ,TCSANOW , &orig);
};

static void modscale(int add);
static void modoctave(int add);
static void play(char c);


int main(void){

    if (!isatty(STDIN_FILENO)) {
        fprintf(stderr, "stdin is not a terminal\n");
        return 1;
    }
    if (tcgetattr(STDIN_FILENO, &orig) != 0) {
        perror("tcsetattr");
        return 1;
    }
    atexit(reset_terminal);


    struct termios raw = orig ;

    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 1 ;
    raw.c_cc[VTIME] = 0 ;


    if(tcsetattr(STDIN_FILENO,TCSANOW ,&raw)!= 0){
        perror("tcsetattr");
        return 1;
    };

    struct termios check;
    tcgetattr(STDIN_FILENO, &check);
    fprintf(stderr, "ICANON=%d ECHO=%d VMIN=%d VTIME=%d\n",
            !!(check.c_lflag & ICANON),
            !!(check.c_lflag & ECHO),
            check.c_cc[VMIN],
            check.c_cc[VTIME]);



        takeKeyboard();


    return 0;

}


static void takeKeyboard(){

    char c;
	printf("\t\t\t================== Enter Word ===================\n\n"
           "\t\t\t    ~ = quit   < > = scale    ↑↓ = octave         \n\n "
    );
    while(1){
	if(read(STDIN_FILENO , &c , 1 ) == 1 ){

		printf("Got : %c\n ",c );
        //fflush( stdout );
        if(c=='~')break;
        keypushed(c);
        //c='\0';
	}

    }

};


static void keypushed(char key){
    if ( key=='>' || key=='<' ) modscale( (key='>')? 1 : 0 );
    if ( key=='A' || key=='B' ) modoctave( (key=='A')? 1 : 0 );
    else if ( isalpha(key)) play( key );

}



static void modscale(int add){
    if( add ) scale++;
    else if(add<1 && scale>=1 ) scale--;
};


static void modoctave(int add){
    if( add ) octave+=5;
    else if( add < 1 && octave>=55 ) octave-=5;
};


static void play(char c){
    //printf("play is called");
    beep( scale * (c-'0') , octave );
     //beep(50,50)
};
