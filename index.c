#include "./includes.h"

double transformDegreeToRadian (int degreeNumber);
int getDecimalPlaces(double accuracy);
double getAndValidateAccuracy();
double getAndValidateFirstNumber();
double getAndValidateSecondNumber(double firstNumber);
double getAndValidateStepNumber();
double truncateNumber(double value, int decimalPlaces);
int getAndValidateFunctionChar();
void printResults(
    int iterationNumber,
    double firstNumber,
    double stepNumber,
    int decimalPlaces,
    const double* resultArr,
    const double* mathResultArr);
void calculateFunction(
    double firstNumber,
    double secondNumber,
    double stepNumber,
    double accuracy,
    short int sinOrCosInt,
    int* iterationNumberPointer,
    double* resultArr,
    double* mathResultArr);
int getResultArraySize(double secondNumber, double firstNumber, double stepNumber);

int main() {
    int iterationNumber = 0;
    int* iterationNumberPointer = &iterationNumber;

    const int sinOrCosInt = getAndValidateFunctionChar();
    const double firstNumber = getAndValidateFirstNumber();
    const double secondNumber = getAndValidateSecondNumber(firstNumber);
    const double stepNumber = getAndValidateStepNumber();
    const double accuracy = getAndValidateAccuracy();

    int arraySize = getResultArraySize(secondNumber, firstNumber, stepNumber);

    double resultArr[arraySize];
    double mathResultArr[arraySize];

    calculateFunction(
         firstNumber,
         secondNumber,
         stepNumber,
         accuracy,
         sinOrCosInt,
         iterationNumberPointer,
         resultArr,
         mathResultArr
         );

    const int decimalPlaces = getDecimalPlaces(accuracy);

    printResults(
        *iterationNumberPointer,
        firstNumber,
        stepNumber,
        decimalPlaces,
        resultArr,
        mathResultArr
        );

    return 0;
}
