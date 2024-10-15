#include <stdio.h>
#include <math.h>

#define DEGREE_STEPS 10

double degreeToRadian (const int degreeNumber) {
    return (degreeNumber * M_PI / 180);
}

int main() {
    double x1, x2, dx, epsilon;
    int iterationNumber = 0;

    printf("Type X1 value (degrees): ");
    scanf("%lf", &x1);
    x1 = degreeToRadian(x1);

    printf("Type X2 value (degrees): ");
    scanf("%lf", &x2);
    x2 = degreeToRadian(x2);

    printf("Type dx value (step size in degrees): ");
    scanf("%lf", &dx);

    printf("Type epsilon value (precision): ");
    scanf("%lf", &epsilon);

    int arraySize = (int)((x2 - x1) / degreeToRadian(dx)) + 1;
    double sinResults[arraySize];
    double mathSinResults[arraySize];

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
        mathSinResults[iterationNumber] = sin(x);
        iterationNumber++;
    }

    printf("\nResults:\n");
    for (int i = 0; i < iterationNumber; i++) {
        double degree = (x1 * 180 / M_PI) + i * dx;
        printf("Degrees: %.2lf, Taylor Series: %.6lf, Math sin: %.6lf\n",
               degree, sinResults[i], mathSinResults[i]);
    }

    return 0;
}
