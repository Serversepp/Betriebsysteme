#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLENZEILE 150

void even(FILE *geradeZeilen,FILE *ergebnis) {
    sleep(1);
    char geradeZeile[MAXLENZEILE];
    while (!feof(geradeZeilen) ){
        fgets(geradeZeile, MAXLENZEILE, geradeZeilen);
        fseek(ergebnis,0L,SEEK_END);
        fprintf(ergebnis,"%s" , (feof(geradeZeilen)) ? "\0" : geradeZeile);
        sleep(1);
    }
}


void odd(FILE *ungeradeZeilen,FILE *ergebnis){
    char ungeradeZeile[MAXLENZEILE];
    while (!feof(ungeradeZeilen)){
        sleep(1);
        fgets(ungeradeZeile, MAXLENZEILE, ungeradeZeilen);
        fseek(ergebnis,0L,SEEK_END);
        fprintf(ergebnis,"%s" , (feof(ungeradeZeilen)) ? "\0" : ungeradeZeile);
    }
}

int main() {

    FILE * geradeZeilen;
    FILE * ungeradeZeilen;
    FILE * ergebnis;

    geradeZeilen = fopen("gedicht_even.txt","r"); // a für append w für write
    ungeradeZeilen = fopen("gedicht_odd.txt", "r");
    ergebnis = fopen("gedischt_alles.txt", "w");

    if (geradeZeilen == NULL || ungeradeZeilen == NULL){
        exit(EXIT_FAILURE);
    }


    switch (fork()) {
        case -1:
            printf("Fehler");
            break;
        case 0:
            even(geradeZeilen,ergebnis);
            break;
        default:
            switch (fork()) {
                case -1:
                    printf("Fehler");
                    break;
                case 0:
                    odd(ungeradeZeilen, ergebnis);
                    break;
                default:
                    ;
            }
            wait(NULL);
            wait(NULL);
    }
    return 0;
}
