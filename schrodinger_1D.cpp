#include <cstdio>
#include <cmath>
#include <ctime>

const double DELTAX = 0.05;
const double DELTAT = 0.00001;
const double ENDTIME = 1.00001;
const double R = DELTAT / (2 * DELTAX * DELTAX);
const double STARTX = -10;
const int POINTS = 401;
long double U[POINTS+2]{0};

double function(double x){
    return exp(-x*x);
}

double function2(double x){
    return 0;
}

void boundaryConditions(long double u[], const long double un[]){
    u[0] = un[POINTS];
    u[POINTS + 1] = un[1];
}

long double Hamiltonian(const long double u[], int x){
    return R * (u[x + 1] - 2 * u[x] + u[x - 1]) - U[x]*u[x];
}

void rungeKutta(const long double imag[], const long double real[], long double imagNew[], long double realNew[]) {
    long double k_real1[POINTS + 1], k_real2[POINTS + 1], k_real3[POINTS + 1], k_real4[POINTS + 1];
    long double k_imag1[POINTS + 1], k_imag2[POINTS + 1], k_imag3[POINTS + 1], k_imag4[POINTS + 1];
    long double Utmp[POINTS+2];
    long double Utmp2[POINTS+2];
    long double Utmp3[POINTS+2];
    long double Utmp4[POINTS+2];

    for (int x = 1; x <= POINTS; ++x) {
        k_real1[x] = Hamiltonian(imag, x);
        k_imag1[x] = Hamiltonian(real, x);
        Utmp[x] = real[x] + 0.5 * DELTAT * k_real1[x];
        Utmp2[x] = imag[x] + 0.5 * DELTAT * k_imag1[x];
    }
    boundaryConditions(Utmp, Utmp);
    boundaryConditions(Utmp2, Utmp2);
    for (int x = 1; x <= POINTS; ++x) {
        k_real2[x] = Hamiltonian(Utmp2, x);
        k_imag2[x] = Hamiltonian(Utmp, x);
        Utmp3[x] = real[x] + 0.5 * DELTAT * k_real2[x];
        Utmp4[x] = imag[x] + 0.5 * DELTAT * k_imag2[x];
    }
    boundaryConditions(Utmp3, Utmp3);
    boundaryConditions(Utmp4, Utmp4);
    for (int x = 1; x <= POINTS; ++x) {
        k_real3[x] = Hamiltonian(Utmp4, x);
        k_imag3[x] = Hamiltonian(Utmp3, x);
        Utmp[x] = real[x] + DELTAT * k_real3[x];
        Utmp2[x] = imag[x] + DELTAT * k_imag3[x];
    }
    boundaryConditions(Utmp, Utmp);
    boundaryConditions(Utmp2, Utmp2);
    for (int x = 1; x <= POINTS; ++x) {
        k_real4[x] = Hamiltonian(Utmp2, x);
        k_imag4[x] = Hamiltonian(Utmp, x);
        realNew[x] = real[x] + (k_imag1[x] + 2 * k_imag2[x] + 2 * k_imag3[x] + k_imag4[x]) / 6;
        imagNew[x] = imag[x] + (k_real1[x] + 2 * k_real2[x] + 2 * k_real3[x] + k_real4[x]) / 6;
    }
}

void midPoint(const long double imag[], const long double real[], long double imagNew[], long double realNew[]) {
    long double k_real1[POINTS + 1], k_real2[POINTS + 1];
    long double k_imag1[POINTS + 1], k_imag2[POINTS + 1];
    long double Utmp[POINTS+2];
    long double Utmp2[POINTS+2];

    for (int x = 1; x <= POINTS; ++x) {
        k_real1[x] = Hamiltonian(imag, x);
        k_imag1[x] = Hamiltonian(real, x);
        Utmp[x] = real[x] + 0.5 * DELTAT * k_real1[x];
        Utmp2[x] = imag[x] + 0.5 * DELTAT * k_imag1[x];
    }
    boundaryConditions(Utmp, Utmp);
    boundaryConditions(Utmp2, Utmp2);
    for (int x = 1; x <= POINTS; ++x) {
        k_real2[x] = Hamiltonian(Utmp2, x);
        k_imag2[x] = Hamiltonian(Utmp, x);
        realNew[x] = real[x] + k_imag2[x];
        imagNew[x] = imag[x] + k_real2[x];
    }
}

void euler(const long double imag[], const long double real[], long double imagNew[], long double realNew[]) {
    for (int x = 1; x <= POINTS; ++x) {
        realNew[x] = real[x] + Hamiltonian(imag, x);
        imagNew[x] = imag[x] + Hamiltonian(real, x);
    }
}

long double computeSums(const long double real[], const long double imag[], FILE* file, bool normalizedPrint){
    long double sumReal=0, sumComplex=0, sumSquare=0;
    for (int i = 1; i <= POINTS; ++i) {
        sumReal += std::abs(real[i]) * DELTAX;
        sumComplex += std::abs(imag[i]) * DELTAX;
        sumSquare += (real[i] * real[i] + imag[i] * imag[i]) * DELTAX;
    }
    if(normalizedPrint){
        fprintf(file, "%.6Lf\t%.6Lf\t\t%.6Lf\t\t%.6Lf\n", sumReal, sumComplex, sumReal + sumComplex, sumSquare);
        return sqrtl(sumSquare);
    }
    fprintf(file, "%.6Lf\t%.6Lf\t%.6Lf\t\t%.6Lf\n", sumReal, sumComplex, sumReal + sumComplex, sumSquare);
    return sqrtl(sumSquare);
}

void initialCondition(long double real[], long double imag[], FILE* fp){
    double j = STARTX;
    for (int i = 1; i <= POINTS ; ++i) {
        real[i] = function(j);
        imag[i] = function2(j);

        fprintf(fp, "%.3f\t", j);
        j = j + DELTAX;
    }
}

void initializePotential(FILE* fp){
    double j = STARTX;
    for (int i = 1; i <= POINTS ; ++i) {
        if(j > -0.11 && j < 0.10){
            U[i] = 0.5;
        }

        fprintf(fp, "%.1Lf\t", U[i]);
        j = j + DELTAX;
    }
}

void normalize(long double sqrtSquare, long double u[], FILE* fp, int* counter, int skipSteps){
    if(*counter >= skipSteps) *counter = 0;
    for (int i = 1; i <= POINTS; ++i) {
        u[i] /= sqrtSquare;
        if(*counter >= skipSteps || *counter == 0){
            fprintf(fp, "%.20Lf\t", u[i]);
        }
    }
}

void copy(long double u[], const long double un[]) {
    for (int i = 1; i <= POINTS; ++i) {
        u[i] = un[i];
    }
}

void printInfo(FILE* fp, FILE* fp2){
    fprintf(fp, "Zaciatocna funkcia:\t \n");
    fprintf(fp, "N = %d\t dx = %.4f\t rozsah <%.1f, %.1f>\t dt = %.6f\t endTime = %.6f\t R = %.5f\n",
            POINTS, DELTAX, STARTX, STARTX+(POINTS-1)*DELTAX, DELTAT, ENDTIME, R);
    fprintf(fp, "U\t\t");
    fprintf(fp2, "t\t real\t complex\t sum\t sumNormalized\t kvadrat\t kvadratNormalized\n");
}

void getMethodInput(int *method){
    int min = 1;
    int max = 3;
    printf("Vyberte metodu pre pocitanie:\n1: Euler\n2: Runge-Kutta 2 radu\n3: Runge-Kutta 4 radu\n");
    while (true) {
        if (scanf("%1d", method) != 1) {
            printf("Zadajte cele cislo: ");
            while (getchar() != '\n');
        } else if (*method < min || *method > max) {
            printf("Cislo mimo rozsah, zadajte cislo medzi %d a %d: ", min, max);
            while (getchar() != '\n');
        } else {
            break;
        }
    }
}

int main(){
    clock_t begin = clock();
    FILE *fp;
    FILE *fp2;
    long double imagNew[POINTS + 2]{0}, imag[POINTS + 2]{0};
    long double realNew[POINTS + 2]{0}, real[POINTS + 2]{0};
    double t;
    int counter = 0, counter2 = 0;
    int skipSteps = 100;
    int method;
    fp = fopen("../bak_vysledky/1D_euler.txt", "w");
    if (fp == nullptr) {
        perror("CHYBA otvorenia suboru 1");
        return EXIT_FAILURE;
    }
    fp2 = fopen("../bak_vysledky/1D_euler_data.txt", "w");
    if (fp2 == nullptr) {
        perror("CHYBA otvorenia suboru 2");
        fclose(fp);
        return EXIT_FAILURE;
    }

    getMethodInput(&method);
    printInfo(fp, fp2);
    //initializePotential(fp);
    fprintf(fp, "\nx\t\t");
    initialCondition(real, imag, fp);
    fprintf(fp, "\nt\n");

    for (t = 0; t < ENDTIME; t += DELTAT) {
        if(counter >= skipSteps || counter == 0){
            fprintf(fp, "%.5f\t\t", t);
        }
        fprintf(fp2, "%.6f\t", t);

        long double sqrtSquare = computeSums(real, imag, fp2, false);
        normalize(sqrtSquare, real, fp, &counter, skipSteps);
        if(counter2 >= skipSteps || counter2 == 0){
            fprintf(fp, "\n%.5f\t\t", t);
        }
        fprintf(fp2, "normalized\t");
        normalize(sqrtSquare, imag, fp, &counter2, skipSteps);
        computeSums(real, imag, fp2, true);
        //periodicke okrajove podmienky
        boundaryConditions(real, real);
        boundaryConditions(imag, imag);

        switch(method){
            case 1:
                euler(imag, real, imagNew, realNew);
                break;
            case 2:
                midPoint(imag, real, imagNew, realNew);
                break;
            case 3:
                rungeKutta(imag, real, imagNew, realNew);
                break;
            default:
                printf("CHYBA");
        }

        copy(real, realNew);
        copy(imag, imagNew);
        if(counter == 0){
            fprintf(fp, "\n");
        }
        counter++;
        counter2++;
    }

    fclose(fp);
    fclose(fp2);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n%f", time_spent);
    return 0;
}