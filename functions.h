#ifndef FUNCTIONS_H
#define FUNCTIONS_H

inline double transformDegreeToRadian (const int degreeNumber) {
    return (degreeNumber * M_PI / 180);
}

inline double truncateNumber(const double value, const int decimalPlaces) {
    const double factor = pow(10.0, (double) decimalPlaces);

    return trunc(value * factor) / factor;
}

inline int getDecimalPlaces(double accuracy) {
    int decimalPlaces = 0;

    while (accuracy < 1.0 && decimalPlaces < 15) {
        accuracy *= 10;
        decimalPlaces++;
    }

    return decimalPlaces;
}

inline double getAndValidateAccuracy() {
    double accuracy;
    bool validInput = false;

    do {
        printf("Enter the accuracy (e.g., 0.0001): ");
        if (scanf("%lf", &accuracy) != 1 || accuracy <= 0) {
            printf("Invalid input for accuracy. Please enter a positive number and not zero.\n");
            fflush(stdin);
            continue;
        }
        fflush(stdin);

        if (accuracy < MIN_ACCURACY || accuracy > MAX_ACCURACY) {
            printf("Accuracy value is out of range. Please enter a value between %.1e and %.1e.\n", MIN_ACCURACY, MAX_ACCURACY);
            continue;
        }

        const double logarithmValue = log10(accuracy);
        const double roundedLogarithm = round(logarithmValue);

        if (fabs(logarithmValue - roundedLogarithm) > MIN_ACCURACY) {
            printf("Accuracy should be a power of 10 (e.g., 1, 0.1, 0.01, etc.)\n");
            continue;
        }

        validInput = true;

    } while (!validInput);

    return accuracy;
}

inline int getAndValidateFunctionChar() {
    int sinOrCosInt;

    do {
        printf("Type You want to calculate sin - s, cos - c\n");
        sinOrCosInt = getchar();
        fflush(stdin);

        if (sinOrCosInt != S_LOWERCASE_LETTER && sinOrCosInt != C_LOWERCASE_LETTER) {
            printf("Invalid input. Please enter 's' for sin or 'c' for cos.\n");
        }
    } while (sinOrCosInt != S_LOWERCASE_LETTER && sinOrCosInt != C_LOWERCASE_LETTER);

    return sinOrCosInt;
}

inline double getAndValidateFirstNumber() {
    double degreesNumber = 0;

    do {
        printf("Type X1 value (degrees, between %d and %d, less than X2): ", MIN_DEGREES, MAX_DEGREES);
        if (scanf("%lf", &degreesNumber) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            fflush(stdin);

            continue;
        }
        fflush(stdin);

        if (degreesNumber < MIN_DEGREES || degreesNumber > MAX_DEGREES) {
            printf("The value must be between %d and %d degrees.\n", MIN_DEGREES, MAX_DEGREES);
        }
    } while (degreesNumber < MIN_DEGREES || degreesNumber > MAX_DEGREES);

    return transformDegreeToRadian(degreesNumber);
}

inline double getAndValidateSecondNumber(const double firstNumber) {
    double degreesNumber = 0;

    do {
        printf("Type X2 value (degrees, between %d and %d): ", MIN_DEGREES, MAX_DEGREES);
        if (scanf("%lf", &degreesNumber) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            fflush(stdin);

            continue;
        }
        fflush(stdin);

        if (degreesNumber < MIN_DEGREES || degreesNumber > MAX_DEGREES || degreesNumber <= firstNumber * 180.0 / M_PI) {
            printf("The value must be between %d and %d degrees and greater than X1.\n", MIN_DEGREES, MAX_DEGREES);
        }
    } while (degreesNumber < MIN_DEGREES || degreesNumber > MAX_DEGREES || degreesNumber <= firstNumber * 180.0 / M_PI);

    return transformDegreeToRadian(degreesNumber);
}

inline double getAndValidateStepNumber() {
    double step = 0;

    do {
        printf("Type dx value (step size in degrees, between %d and %d): ", MIN_STEP, MAX_DEGREES);
        if (scanf("%lf", &step) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            fflush(stdin);

            continue;
        }
        fflush(stdin);

        if (step < MIN_STEP || step > MAX_DEGREES) {
            printf("The step size must be greater or equal to %d and less than or equal to %d.\n", MIN_STEP, MAX_DEGREES);
        }
    } while (step < MIN_STEP || step > MAX_DEGREES);

    return step;
}

inline void printResults(
        const int iterationNumber,
        const double firstNumber,
        const double stepNumber,
        const int decimalPlaces,
        const double* resultArr,
        const double* mathResultArr
    ) {
    printf("\nResults:\n");
    printf("%-8s %-10s %-18s %-18s %-18s\n", "x", "sinX", "sinX (not trunc)", "sinX (math)", "delta (absolute)");

    for (int i = 0; i < iterationNumber; i++) {
        const double degree = (firstNumber * 180.0 / M_PI) + (double)i * stepNumber;

        printf("%-8d %-10.*lf %-18.12lf %-18.12lf %-18.12lf\n",
               (int)degree,
               decimalPlaces,
               truncateNumber(resultArr[i], decimalPlaces),
               truncateNumber(resultArr[i], 12),
               truncateNumber(mathResultArr[i], 12),
               truncateNumber(fabs(resultArr[i] - mathResultArr[i]), 12)
        );
    }
}

inline void calculateFunction(
        const double firstNumber,
        const double secondNumber,
        const double stepNumber,
        const double accuracy,
        const short int sinOrCosInt,
        int* iterationNumberPointer,
        double* resultArr,
        double* mathResultArr
        ) {
    for (double x = firstNumber; x < secondNumber; x += transformDegreeToRadian(stepNumber)) {
        double start;
        double delta;
        int n;

        if (sinOrCosInt == S_LOWERCASE_LETTER) {
            start = x;
            delta = x;
            n = 1;

            while (fabs(delta) >= accuracy) {
                delta = -delta * x * x / (double) ((n + 1) * (n + 2));
                start += delta;
                n += 2;
            }

        } else {
            start = 1.0;
            delta = 1.0;
            n = 2;

            while (fabs(delta) >= accuracy) {
                delta = -delta * x * x / (double) ((n - 1) * n);
                start += delta;
                n += 2;
            }
        }

        resultArr[*iterationNumberPointer] = start;
        mathResultArr[*iterationNumberPointer] = sinOrCosInt == S_LOWERCASE_LETTER ? sin(x) : cos(x);
        (*iterationNumberPointer)++;
    }
}

inline int getResultArraySize(const double secondNumber, const double firstNumber, const double stepNumber) {
    return (int)((secondNumber - firstNumber) / transformDegreeToRadian(stepNumber) + 1.0);
}

#endif // FUNCTIONS_H
