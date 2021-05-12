#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define MAXLENZEILE 150
#define true 1
#define false 0
int ReadLine(char *,int ,FILE *);
void even_(FILE *even,FILE *ergebnis) {
    sleep(3);
    char line1[MAXLENZEILE];
    while (!feof(even)){
        ReadLine(line1,MAXLENZEILE,even);
        fseek(ergebnis,0L,SEEK_END);
        //ReadLine(line1,MAXLENZEILE,even);
        fprintf(ergebnis,"%s\n" ,line1);
        sleep(2);
    }
}
void odd_(FILE *odd,FILE *ergebnis){
    char line2[MAXLENZEILE];
    while (!feof(odd)){
        ReadLine(line2,MAXLENZEILE,odd);
        sleep(2);
        fseek(ergebnis,0L,SEEK_END);
        fprintf(ergebnis,"%s\n" ,line2);
    }
}
int main() {
    FILE * even;
    FILE * odd;
    FILE * ergebnis;
    even = fopen("gedicht_even.txt","r");
    odd = fopen("gedicht_odd.txt", "r");
    ergebnis = fopen("gedicht_alles.txt", "w+");
    if (even == NULL || odd == NULL){
        printf("file couldn'nt be read");
        exit(-1);
    }
    switch (fork()) {
        case -1:
            printf("Error: process could not start");
            break;
        case 0:
            printf("even process started\n");
            even_(even,ergebnis);
            exit(0);
        default:
            switch (fork()) {
                case -1:
                    printf("Error: process could not start");
                    break;
                case 0:
                    printf("odd process started\n");
                    odd_(odd, ergebnis);
                    exit(0);
                default:
                    ;
            }
            wait(NULL);
            wait(NULL);
    }
    fseek(ergebnis,0L,SEEK_SET);
    while(!feof(ergebnis)){
        char ch = fgetc(ergebnis);
        putchar(ch);
    }
    fclose(odd);
    fclose(even);
    fclose(ergebnis);
    return 0;
}
int ReadLine(char *buff, int size, FILE *fp) {
    buff[0] = '\0';
    buff[size - 1] = '\0';
    char *tmp;
    if (fgets(buff, size, fp) == NULL) {
        *buff = '\0';
        return false;
    }
    else {

        if ((tmp = strrchr(buff, '\n')) != NULL) {
            *tmp = '\0';
        }
    }
    return true;
}
