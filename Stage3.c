#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define MAXLENZEILE 150

FILE * geradeZeilen;
FILE * ungeradeZeilen;
FILE * ergebnis;

pid_t evenProzess;
pid_t oddProzess;

pietroff = 1;

void signalhandlereven(int sig){
    printf("test");
    char geradeZeile[MAXLENZEILE];
    fseek(ergebnis, 0L, SEEK_END);
    fgets(geradeZeile, MAXLENZEILE, geradeZeilen);
    fprintf(ergebnis,"%s", geradeZeile);

}

void evenProzzess(){
    signal(SIGUSR1,signalhandlereven);
    start:
        sleep(30);
        if (pietroff){
            goto start;
        }
                

    exit(0);
}

void oddProzzess(){
    char ungeradeZeile[MAXLENZEILE];
    sleep(1);
    while (feof(ungeradeZeilen)!=1) {
        fseek(ergebnis, 0L, SEEK_END);
        fgets(ungeradeZeile, MAXLENZEILE, ungeradeZeilen);
        fprintf(ergebnis,"%s", ungeradeZeile);
        if (kill(evenProzess, SIGUSR1)!=0){
            printf("could not find buddy");
            exit(123);
        }
        sleep(2);
    }
    kill(evenProzess, SIGTERM);
}

int main() {


    geradeZeilen = fopen("gedicht_even.txt","r"); // a für append w für write
    ungeradeZeilen = fopen("gedicht_odd.txt", "r");
    ergebnis = fopen("gedischt_alles.txt", "w");

    if (geradeZeilen == NULL || ungeradeZeilen == NULL){
        exit(EXIT_FAILURE);
    }

    switch (evenProzess = fork()) {
        case -1:
            printf("Fehler");
            break;
        case 0:
            evenProzzess();
            exit(0);
        default:
            switch (oddProzess = fork()) {
                case -1:
                    printf("Fehler");
                    break;
                case 0:
                    oddProzzess();
                    exit(0);
                default:
                    ;
            }
            wait(NULL);
            wait(NULL);

    }
    fclose(geradeZeilen);
    fclose(ungeradeZeilen);
    fclose(ergebnis);
    return 0;
}
