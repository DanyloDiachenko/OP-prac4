#include <stdio.h>
#include <math.h>

#define DEGREE_STEPS 10

double degreeToRadian (const int degreeNumber) {
    return (degreeNumber * M_PI / 180);
}

int main() {
    double x1, x2, dx, epsilon;
    const int arraySize = (100 / DEGREE_STEPS) + 1;
    double sinResults[arraySize];
    int iterationNumber = 0;

    printf("Type X1 value: ");
    scanf("%lf", &x1);
    x1 = degreeToRadian(x1);
    fflush(stdin);

    printf("Type X2 value: ");
    scanf("%lf", &x2);
    x2 = degreeToRadian(x2);
    fflush(stdin);

    printf("Type dx value: ");
    scanf("%lf", &dx);
    fflush(stdin);

    printf("Type epsilon value: ");
    scanf("%lf", &epsilon);
    fflush(stdin);

    for (double x = x1; x < x2; x += degreeToRadian(dx)) {
        double sinX = x;
        double delta = sinX;
        int n = 1;

        while (fabs(delta) >= epsilon) {
            delta = delta * - (x * x) / ((n + 1.0) * (n + 2.0));
            sinX = sinX + delta;
            n = n + 2;
        }

        sinResults[iterationNumber] = sinX;
        iterationNumber++;
    }

    for (int i = 0; i < iterationNumber; i++) {
        printf("sin(%d degrees) = %.6lf\n", i * DEGREE_STEPS, sinResults[i]);
    }

    return 0;
}
