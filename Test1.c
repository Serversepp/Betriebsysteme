#include <stdio.h>
#include <stdlib.h>

#define MAXLENZEILE 150

int main() {
    char geradeZeile[MAXLENZEILE];
    char ungeradeZeile[MAXLENZEILE];

    FILE * geradeZeilen;
    FILE * ungeradeZeilen;
    FILE * ergebnis;
    geradeZeilen = fopen("gedicht_even.txt","r"); // a für append w für write
    ungeradeZeilen = fopen("gedicht_odd.txt", "r");
    ergebnis = fopen("gedischt_alles.txt", "w");
    if (geradeZeilen == NULL || ungeradeZeilen == NULL){
        exit(EXIT_FAILURE);
    }
    while (!feof(ungeradeZeilen) || !feof(geradeZeilen) ){
        fgets(ungeradeZeile, MAXLENZEILE, ungeradeZeilen);
        fgets(geradeZeile, MAXLENZEILE, geradeZeilen);
        fprintf(ergebnis,"%s%s" , (feof(ungeradeZeilen)) ? "\0" : ungeradeZeile, (feof(geradeZeilen)) ? "\0" : geradeZeile);
    }

    fclose(ungeradeZeilen);
    fclose(geradeZeilen);
    fclose(ergebnis);

    return 0;
}
