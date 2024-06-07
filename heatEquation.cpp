#include <cstdio>
#include <cmath>

FILE *fp;
const double DELTAX = 0.1;
const double DELTAT = 0.01;
const double ENDTIME = 5.01;
const double ALPHA = 0.30;
const double R = (ALPHA * DELTAT) / (DELTAX * DELTAX);
const double STARTX = 0;
const double ENDX = 2;
const int POINTS = static_cast<int>((ENDX - STARTX) / DELTAX) + 1;
const bool PERIODIC_BOUNDARY_CONDITIONS = true;

double function(double x){
    return (x > 1.0) ? 1 : 0;
}

void euler(const double u[], double un[]){
    for (int x = 1; x <= POINTS; x++){
        un[x] = u[x] + R * (u[x + 1] - 2 * u[x] + u[x - 1]);
    }
}

void midPoint(const double u[], double un[]) {
    double k1, k2;
    for (int x = 1; x <= POINTS; x++){
        k1 = R * (u[x + 1] - 2 * u[x] + u[x - 1]);
        k2 = R * (u[x + 1] - 2 * (u[x] + 0.5 * DELTAT * k1) + u[x - 1]);

        un[x] = u[x] + k2;
    }
}

void rungeKutta(const double u[], double un[]) {
    double k1, k2, k3, k4;
    for (int x = 1; x <= POINTS; x++){
        k1 = R * (u[x + 1] - 2 * u[x] + u[x - 1]);
        k2 = R * (u[x + 1] - 2 * (u[x] + 0.5 * DELTAT * k1) + u[x - 1]);
        k3 = R * (u[x + 1] - 2 * (u[x] + 0.5 * DELTAT * k2) + u[x - 1]);
        k4 = R * (u[x + 1] - 2 * (u[x] + DELTAT * k3) + u[x - 1]);

        un[x] = u[x] + (k1 + 2*k2 + 2*k3 + k4)/6;
    }
}

void boundaryConditions(double u[], double un[]){
    if (!PERIODIC_BOUNDARY_CONDITIONS) {
        un[1] = u[1];
        un[POINTS] = u[POINTS];
        return;
    }
    u[0] = un[POINTS];
    u[POINTS + 1] = un[1];
}

void copy(double u[], double un[]){
    for (int i = 1; i <= POINTS; ++i) {
        printf("%.5f\t", u[i]);
        fprintf(fp, "%.5f\t", u[i]);
        u[i] = un[i];
    }
    if(PERIODIC_BOUNDARY_CONDITIONS) boundaryConditions(u, un);
}

void initialCondition(double u[]){
    double j = STARTX;
    for (int i = 1; i <= POINTS; ++i) {
        u[i] = function(j);
        printf("%.2f\t", j);
        fprintf(fp, "%.2f\t", j);
        j = j + DELTAX;
    }
    printf("\nt\n");
    fprintf(fp, "\nt\n");
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

void printInfo(){
    printf("Zaciatocna funkcia:\t \n");
    fprintf(fp, "Zaciatocna funkcia:\t \n");
    printf("Podmienka stability:\t %.5f <= %.5f\n", DELTAT, (DELTAX * DELTAX) / (2 * ALPHA));
    fprintf(fp, "Podmienka stability:\t %.5f <= %.5f\n", DELTAT, (DELTAX * DELTAX) / (2 * ALPHA));
    printf("N = %d\t dx = %.4f\t dt = %.4f\t r = %.4f\n", POINTS, DELTAX, DELTAT, R);
    fprintf(fp, "N = %d\t dx = %.4f\t dt = %.4f\t r = %.4f\n", POINTS, DELTAX, DELTAT, R);
    printf("x\t\t");
    fprintf(fp, "x\t\t");
}

int main(){
    double u[POINTS + 2], un[POINTS + 1];
    double t;
    int method;
    getMethodInput(&method);
    fp = fopen("../bak_vysledky/15.txt", "w");
    if (fp == nullptr) {
        perror("CHYBA otvorenia suboru");
        return EXIT_FAILURE;
    }
    printInfo();
    initialCondition(u);

    //okrajove podmienky
    boundaryConditions(u, u);

    for (t = 0; t < ENDTIME; t += DELTAT) {
        switch(method){
            case 1:
                euler(u, un);
                break;
            case 2:
                midPoint(u, un);
                break;
            case 3:
                rungeKutta(u, un);
                break;
            default:
                printf("CHYBA");
        }
        printf("%.4f\t\t", t);
        fprintf(fp, "%.4f\t\t", t);

        if(!PERIODIC_BOUNDARY_CONDITIONS) boundaryConditions(u, un);
        copy(u, un);

        printf("\n");
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;
}