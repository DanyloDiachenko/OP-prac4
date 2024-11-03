#include <stdio.h>
#include <math.h>

#define MIN_DEGREES 0
#define MAX_DEGREES 360

double degreeToRadian (const int degreeNumber) {
    return (degreeNumber * M_PI / 180);
}

int main() {
    double x1, x2, dx, epsilon;
    int iterationNumber = 0;

    do {
        printf("Type X1 value (degrees, between %d and %d, less than X2): ", MIN_DEGREES, MAX_DEGREES);
        if (scanf("%lf", &x1) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            fflush(stdin);

            continue;
        }
        fflush(stdin);

        if (x1 < MIN_DEGREES || x1 > MAX_DEGREES) {
            printf("The value must be between %d and %d degrees.\n", MIN_DEGREES, MAX_DEGREES);
        }
    } while (x1 < MIN_DEGREES || x1 > MAX_DEGREES);
    x1 = degreeToRadian(x1);

    do {
        printf("Type X2 value (degrees, between %d and %d): ", MIN_DEGREES, MAX_DEGREES);
        if (scanf("%lf", &x2) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            fflush(stdin);

            continue;
        }
        fflush(stdin);

        if (x2 < MIN_DEGREES || x2 > MAX_DEGREES || x2 <= x1 * 180 / M_PI) {
            printf("The value must be between %d and %d degrees and greater than X1.\n", MIN_DEGREES, MAX_DEGREES);
        }
    } while (x2 < MIN_DEGREES || x2 > MAX_DEGREES || x2 <= x1 * 180 / M_PI);
    x2 = degreeToRadian(x2);

    do {
        printf("Type dx value (step size in degrees, between 0 and 360): ");
        if (scanf("%lf", &dx) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            fflush(stdin);

            continue;
        }
        fflush(stdin);

        if (dx <= 0 || dx > MAX_DEGREES) {
            printf("The step size must be greater than 0 and less than or equal to 360.\n");
        }
    } while (dx <= 0 || dx > MAX_DEGREES);

    printf("Type epsilon value (precision): ");
    scanf("%lf", &epsilon);
    fflush(stdin);

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
    printf("\t--x--\t\t--sinX--\t--sinX (math)--\t--delta (absolute)--\n");
    for (int i = 0; i < iterationNumber; i++) {
        const double degree = (x1 * 180 / M_PI) + i * dx;
        printf("\t%-8.3lf \t%-10.6lf \t%-14.6lf \t%-14.6lf\n",
               degree, sinResults[i], mathSinResults[i], fabs(sinResults[i] - mathSinResults[i]));
    }

    return 0;
}
