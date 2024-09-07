/*
    Basic executable to show how to use the gpioset tool
    Not the recommended way to generate PWM, Should directly use libgpiod (backend for gpioset)

    Will Toggle the PIN level on PIN 3 (LIBRE COMPUTER LAYOUT) with a 2 second period
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>

#define DELAY_S 1

int main(){

    /* BASIC PWM */
    for(;;){
        /* TURN SIGNAL HIGH */
        int pid = fork();
        if(pid == 0){
            /* CHILD PROCEESS */
            execvp("gpioset", (char * const[]) {"gpioset", "0", "5=1", NULL});
            /* SHOULD NEVER REACH */
            printf("ERROR, COULD NOT TRANSFORM PROCESS\n");
            exit(0);
        }
        waitpid(pid, NULL, 0);

        /* WAIT FOR A CERTAIN TIME */
        sleep(DELAY_S);

        /* TURN SIGNAL LOW */
        pid = fork();
        if(pid == 0){
            /* CHILD PROCEESS */
            execvp("gpioset", (char * const[]) {"gpioset", "0", "5=0", NULL});
            /* SHOULD NEVER REACH */
            printf("ERROR, COULD NOT TRANSFORM PROCESS\n");
            exit(0);
        }
        waitpid(pid, NULL, 0);

        /* WAIT FOR A CERTAIN TIME */
        sleep(DELAY_S);
    }

    return 0;
}