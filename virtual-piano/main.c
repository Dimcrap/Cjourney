#include <AL/al.h>
#include <AL/alc.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "beep/beep.h"


static void keypushed(char key);
static void takeKeyboard();


static struct termios orig;

static void reset_terminal( void){
    tcsetattr(STDIN_FILENO ,TCSANOW , &orig);
};


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
    tcsetattr(STDIN_FILENO,TCSANOW ,&raw );

    if(tcsetattr(STDIN_FILENO,TCSANOW ,&raw)!= 0){
        perror("tcsetattr");
        return 1;
    };



    printf("prress key (q for quit)\n");
    fflush(stdout);

    char c;
    while( read(STDIN_FILENO , &c ,  1  ) == 1 ){
        printf("Got : %c (0x%02X)\n",c,(unsigned char)c);
        fflush(stdout);
        if(c=='q')break;
    }



    return 0;

}


static void takeKeyboard(){

	printf("================== Enter Word ===================\n");
	while(1){
		
		

	}

};



static void keypushed(char key){

}
