#include <AL/al.h>
#include <AL/alc.h>
#include <stdio.h>
#include "beep/beep.h"

static void keypushed();
static void takeKeyboard();


int main(){
    beep(640,50);
    beep(550,50);

    return 0;

}


static void takeKeyboard(){

	printf("================== Enter Word ===================\n");
	while(1){
		
		

	}

};



static void keypushed(){

}
