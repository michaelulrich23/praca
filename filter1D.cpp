#include <iostream>

void printData(FILE *fp, FILE *fp2, int numRows) {
    char line[500000];
    for (int i = 0; i < numRows; ++i) {
        fgets(line, sizeof(line), fp);
        fputs(line, fp2);
    }
}

void skipData(FILE *fp, int SKIPNDATA){
    char buffer[500000];
    int line_count = 0;

    while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
        if (++line_count % SKIPNDATA == 0) {
            return;
        }
    }
}

int main() {
    FILE *fp;
    FILE *fp2;
    int SKIPNDATA = 198;
    int STARTINIT = 6;
    int NUMROWS = 2;
    fp = fopen("../bak_vysledky/1D_midpoint.txt", "r");
    if (fp == nullptr) {
        perror("CHYBA otvorenia suboru 1");
        return EXIT_FAILURE;
    }
    fp2 = fopen("../bak_vysledky/1D_midpoint_filtered.txt", "w");
    if (fp2 == nullptr) {
        perror("CHYBA otvorenia suboru 2");
        fclose(fp);
        return EXIT_FAILURE;
    }

    printData(fp, fp2, STARTINIT);
    while(!feof(fp)) {
        skipData(fp, SKIPNDATA);
        printData(fp, fp2, NUMROWS);
    }

    fclose(fp);
    fclose(fp2);
    return 0;
}