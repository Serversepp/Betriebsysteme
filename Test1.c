//
// Created by serversepp on 28.04.21.
//

#include <stdio.h>#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXLINE 150
#define true 1
#define false 0
#include<stdlib.h>


// Var sektion


int main(int argc, char **argv){
    char line[MAXLINE];
    int i=0;
    FILE *fp1, *fp2;
    bool ret=true;
    if(argc < 3) {  // Wenn mehr als zwei Argumente gegeben sind wir alles übersprungen
        printf("USAGE: %s filename\n", *argv);
        printf("list 2 file names on the command line to be read and printed\n");

        fp1 = fopen(argv[0],"r");
        fp2 = fopen(argv[1],"r")

}