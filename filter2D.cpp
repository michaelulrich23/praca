#include <iostream>

void printData(FILE *fp, FILE *fp2, int numRows) {
    char line[10000];
    for (int i = 0; i < numRows; ++i) {
        fgets(line, sizeof(line), fp);
        fputs(line, stdout);
        fputs(line, fp2);
    }
}

void skipData(FILE *fp){
    int c;
    while((c = fgetc(fp)) != EOF){
        if(c == '\n'){
            c = fgetc(fp);
            if(c == '\n'){
                c = fgetc(fp);
                if(c == '\n'){
                    return;
                }
            }
        }
    }
}

void skipData2(FILE *fp) {
    int c;
    int newlineCount = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            newlineCount++;
            if (newlineCount == 3) break;
        } else newlineCount = 0;
    }
}

int main() {
    FILE *fp;
    FILE *fp2;
    int SKIPNDATA = 499;
    int STARTINIT = 57;
    int NUMROWS = 54;
    fp = fopen("../bak_vysledky/17.txt", "r");
    if (fp == nullptr) {
        perror("CHYBA otvorenia suboru 1");
        return EXIT_FAILURE;
    }
    fp2 = fopen("../bak_vysledky/17_filtered.txt", "w");
    if (fp2 == nullptr) {
        perror("CHYBA otvorenia suboru 2");
        fclose(fp);
        return EXIT_FAILURE;
    }

    printData(fp, fp2, STARTINIT);
    while(!feof(fp)) {
        for (int i = 0; i < SKIPNDATA; ++i) {
            skipData2(fp);
        }
        printData(fp, fp2, NUMROWS);
    }

    fclose(fp);
    fclose(fp2);
    return 0;
}