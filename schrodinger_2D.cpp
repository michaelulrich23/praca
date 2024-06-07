#include <cstdio>
#include <cmath>

const double DELTAT = 0.001;
const double ENDTIME = 1.001;
const double STARTX = 0;
const int NX = 51;
const int NY = 51;
const double DELTAX = 0.1;
const double R = DELTAT / (2 * DELTAX * DELTAX);
const double U = 0;


double function(double x, double y){
    return 1;
}

double function2(double x, double y){
    return 0.5;
}

long double euler(long double u[][NY + 2], int x, int y){
    return R * (u[x+1][y] + u[x-1][y] + u[x][y+1] + u[x][y-1] - 4 * u[x][y]) + U;
}

void boundaryConditions(long double u[][NY + 2], const long double un[][NY + 2]){
    for (int i = 1; i <= NX; ++i) {
        u[0][i] = un[NX][i];
        u[NX + 1][i] = un[1][i];
    }
    for (int i = 1; i <= NY ; ++i) {
        u[i][0] = un[i][NY];
        u[i][NY + 1] = un[i][1];
    }
}

void normalize(long double sqrtSquare, long double u[][NY + 2]){
    for (int i = 1; i <= NX; ++i) {
        for (int j = 1; j <= NY; ++j) {
            u[i][j] /= sqrtSquare;
        }
    }
}

void copy(long double u[][NY + 2], long double un[][NY + 2]) {
    for (int i = 1; i <= NX; ++i) {
        for (int j = 1; j <= NY; ++j) {
            u[i][j] = un[i][j];
        }
    }
    boundaryConditions(u, un);
}

void printArray(long double u[][NY + 2], long double u2[][NY + 2], double t, FILE* fp, FILE* fp2){
    double xCoord = STARTX;
    for (int i = 1; i <= NX; ++i) {
        fprintf(fp, "%.4f\t%.2f\t", t, xCoord);
        fprintf(fp2, "%.4f\t%.2f\t", t, xCoord);
        for (int j = 1; j <= NY; ++j) {
            fprintf(fp, "%.5Lf\t", u[i][j]);
            fprintf(fp2, "%.5Lf\t", u2[i][j]);
        }
        fprintf(fp, "\n");
        fprintf(fp2, "\n");
        xCoord += DELTAX;
    }
}

long double computeSums(long double real[][NY + 2], long double imag[][NY + 2], FILE* file, bool normalizedPrint){
    long double sumReal=0, sumComplex=0, sumSquare=0;
    for (int i = 1; i <= NX; ++i) {
        for (int j = 1; j <= NY; ++j) {
            sumReal += std::abs(real[i][j]) * DELTAX;
            sumComplex += std::abs(imag[i][j]) * DELTAX;
            sumSquare += (real[i][j] * real[i][j] + imag[i][j] * imag[i][j]) * DELTAX;
        }
    }
    if(normalizedPrint){
        fprintf(file, "%.4Lf\t%.4Lf\t\t%.4Lf\t\t%.4Lf\n", sumReal, sumComplex, sumReal + sumComplex, sumSquare);
        return sqrtl(sumSquare);
    }
    fprintf(file, "%.4Lf\t%.4Lf\t%.4Lf\t\t%.4Lf\n", sumReal, sumComplex, sumReal + sumComplex, sumSquare);
    return sqrtl(sumSquare);
}

void initialCondition(long double real[][NY + 2], long double imag[][NY + 2]){
    double x = STARTX;
    for (int i = 1; i <= NX ; ++i) {
        double y = STARTX;
        for (int k = 1; k <= NY; ++k) {
            if(x >= 1 && x <= 4 && y >= 1 && y <= 4){
                real[i][k] = function(x,y);
                imag[i][k] = function2(x,y);
            }
            y = y + DELTAX;
        }
        x = x + DELTAX;
    }
}

void printXCoord(FILE* fp, FILE* fp2){
    double x = STARTX;
    for (int i = 1; i <= NX ; ++i) {
        fprintf(fp, "%.2f\t", x);
        fprintf(fp2, "%.2f\t", x);
        x = x + DELTAX;
    }
    fprintf(fp, "\n");
    fprintf(fp2, "\n");
}

void printInfo(FILE* fp, FILE* fp2, FILE* fp_data){
    fprintf(fp, "Zaciatocna funkcia:\t \n");
    fprintf(fp2, "Zaciatocna funkcia:\t \n");
    fprintf(fp, "NX = %d\t NY = %d\t dx = %.4f\t dt = %.4f\t R = %.4f\n", NX, NY, DELTAX, DELTAT, R);
    fprintf(fp2, "NX = %d\t NY = %d\t dx = %.4f\t dt = %.4f\t R = %.4f\n", NX, NY, DELTAX, DELTAT, R);
    fprintf(fp, "x\t\t");
    fprintf(fp2, "x\t\t");
    fprintf(fp_data, "t\t real\t complex\t sum\t sumNormalized\t kvadrat\t kvadratNormalized\n");
}

int main(){
    FILE *fp;
    FILE *fp2;
    FILE *fp_data;
    long double imagNew[NX + 2][NY + 2]{0}, imag[NX + 2][NY + 2]{0};
    long double realNew[NX + 2][NY + 2]{0}, real[NX + 2][NY + 2]{0};
    double t;
    fp = fopen("../bak_vysledky/17.txt", "w");
    if (fp == nullptr) {
        perror("CHYBA otvorenia suboru 1");
        return EXIT_FAILURE;
    }
    fp2 = fopen("../bak_vysledky/17_2.txt", "w");
    if (fp2 == nullptr) {
        perror("CHYBA otvorenia suboru 2");
        fclose(fp);
        return EXIT_FAILURE;
    }
    fp_data = fopen("../bak_vysledky/17_data.txt", "w");
    if (fp_data == nullptr) {
        perror("CHYBA otvorenia suboru 3");
        fclose(fp);
        fclose(fp2);
        return EXIT_FAILURE;
    }

    printInfo(fp, fp2, fp_data);
    initialCondition(real, imag);

    for (t = 0; t < ENDTIME; t += DELTAT) {
        fprintf(fp, "\nt\t\t");
        fprintf(fp2, "\nt\t\t");
        printXCoord(fp, fp2);
        fprintf(fp_data, "%.4f\t", t);
        printf("%.4f\n", t);

        long double sqrtSquare = computeSums(real, imag, fp_data, false);
        normalize(sqrtSquare, real);
        normalize(sqrtSquare, imag);
        fprintf(fp_data, "\t");
        computeSums(real, imag, fp_data, true);
        //periodicke okrajove podmienky
        boundaryConditions(real, real);
        boundaryConditions(imag, imag);
        printArray(real, imag, t, fp, fp2);

        for (int x = 1; x <= NX; x++) {
            for (int y = 1; y <= NY; ++y) {
                realNew[x][y] = euler(imag, x, y) + real[x][y];
                imagNew[x][y] = euler(real, x, y) + imag[x][y];
            }
        }

        copy(real, realNew);
        copy(imag, imagNew);

        fprintf(fp, "\n");
        fprintf(fp2, "\n");
    }

    fclose(fp);
    fclose(fp2);
    fclose(fp_data);
    return 0;
}