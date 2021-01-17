#include<stdio.h>
#include <stdlib.h>
#include<Windows.h>
struct testResult {
	int totalCount, passedCount;
};

typedef struct testResult Struct;

void (*setA)(const double);
void (*setB)(const double);
void (*setC)(const double);
int (*getSolution)(double*, double*);

const char* returnEnumValue(int enumValue)
{
	char* returnvalue = NULL;
	switch (enumValue)
	{
	case 0:
		returnvalue = "SOLUTION_OK";
		return returnvalue;
		break;
	case 1:
		returnvalue = "ERROR_A_IS_ZERO";
		return returnvalue;
		break;
	case 2:
		returnvalue = "ERROR_NO_REAL_ROOTS";
		return returnvalue;
		break;
	default:
		returnvalue = "NOT_IN_LIST";
		return returnvalue;
		break;
	}
}

int getSolutionQuadraticEquation(double a, double b, double c, char* message)
{
	int enumvalue = -1;
	HINSTANCE hInst = LoadLibrary(TEXT("quadratic.dll"));

	if (hInst != NULL)
	{
		printf("\nTest Module: %s", message);
		printf("\nTest with value of a = %lf, b = %lf, c = %lf", a, b, c);
		setA = (void*)GetProcAddress(hInst, "setA");
		setB = (void*)GetProcAddress(hInst, "setB");
		setC = (void*)GetProcAddress(hInst, "setC");
		getSolution = (int*)GetProcAddress(hInst, "getSolution");

		if (setA != NULL && setB != NULL && setC != NULL && getSolution != NULL) {
			setA(a);
			setB(b);
			setC(c);
			double valb = 0;
			double vala = 0;
			enumvalue = getSolution(&vala, &valb);
			printf("\nSolution is %d - %s  \n", enumvalue, returnEnumValue(enumvalue));
		}
	}
	FreeLibrary(hInst);
	Sleep(100);
	return enumvalue;
}

Struct testCase(int expectedResult, int actualResult, int totalCount, int passedCount)
{
	Struct s;
	if (expectedResult == actualResult)
	{
		printf("Test Case: PASSED");
		s.passedCount = passedCount + 1;
	}
	else
	{
		s.passedCount = passedCount;
		printf("Test Case: FAILED");
		printf("\nExpected Result is %s and Actual Results is %s", returnEnumValue(expectedResult), returnEnumValue(actualResult));
	}
	s.totalCount = totalCount + 1;
	printf("\n\n");
	return s;
}

void main()
{
	Struct result;
	result.totalCount = 0;
	result.passedCount = 0;
	double minvalue = 0;
	double minvalueplusone = minvalue + 1;
	double maxvalue = 1000;//1.79769313486231570E+308;
	double maxvalueminusone = maxvalue - 1;
	double midvalue = (minvalue + maxvalue) / 2;
	result = testCase(1, getSolutionQuadraticEquation(minvalue, midvalue, midvalue, "All Coefficient are positive values"), result.totalCount, result.passedCount);
	//result = testCase(0, getSolutionQuadraticEquation(minvalueplusone, midvalue, midvalue, "All Coefficient are positive values"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(maxvalueminusone, midvalue, midvalue, "All Coefficient are positive values"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(maxvalue, midvalue, midvalue, "All Coefficient are positive values"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(midvalue, minvalue, midvalue, "All Coefficient are positive values"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(midvalue, minvalueplusone, midvalue, "All Coefficient are positive values"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(midvalue, maxvalueminusone, midvalue, "All Coefficient are positive values"), result.totalCount, result.passedCount);
	//result = testCase(0, getSolutionQuadraticEquation(midvalue, maxvalue, midvalue, "All Coefficient are positive values"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, midvalue, minvalue, "All Coefficient are positive values"), result.totalCount, result.passedCount);
	//result = testCase(0, getSolutionQuadraticEquation(midvalue, midvalue, minvalueplusone, "All Coefficient are positive values"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(midvalue, midvalue, maxvalueminusone, "All Coefficient are positive values"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(midvalue, midvalue, maxvalue, "All Coefficient are positive values"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(midvalue, midvalue, midvalue, "All Coefficient are positive values"), result.totalCount, result.passedCount);

	result = testCase(1, getSolutionQuadraticEquation(-minvalue, -midvalue, -midvalue, "All Coefficient are negative values"), result.totalCount, result.passedCount);
	//result = testCase(0, getSolutionQuadraticEquation(-minvalueplusone,-midvalue, -midvalue, "All Coefficient are negative values"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(-maxvalueminusone, -midvalue, -midvalue, "All Coefficient are negative values"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(-maxvalue, -midvalue, -midvalue, "All Coefficient are negative values"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(-midvalue, -minvalue, -midvalue, "All Coefficient are negative values"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(-midvalue, -minvalueplusone, -midvalue, "All Coefficient are negative values"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(-midvalue, -maxvalueminusone, -midvalue, "All Coefficient are negative values"), result.totalCount, result.passedCount);
	//result = testCase(0, getSolutionQuadraticEquation(-midvalue, -maxvalue, -midvalue, "All Coefficient are negative values"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, -midvalue, -minvalue, "All Coefficient are negative values"), result.totalCount, result.passedCount);
	//result = testCase(0, getSolutionQuadraticEquation(-midvalue, -midvalue, -minvalueplusone, "All Coefficient are negative values"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(-midvalue, -midvalue, -maxvalueminusone, "All Coefficient are negative values"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(-midvalue, -midvalue, -maxvalue, "All Coefficient are negative values"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(-midvalue, -midvalue, -midvalue, "All Coefficient are negative values"), result.totalCount, result.passedCount);

	result = testCase(1, getSolutionQuadraticEquation(-minvalue, midvalue, midvalue, "Coefficient A is negative, B and C positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-minvalueplusone, midvalue, midvalue, "Coefficient A is negative, B and C positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-maxvalueminusone, midvalue, midvalue, "Coefficient A is negative, B and C positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-maxvalue, midvalue, midvalue, "Coefficient A is negative, B and C positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, minvalue, midvalue, "Coefficient A is negative, B and C positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, minvalueplusone, midvalue, "Coefficient A is negative, B and C positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, maxvalueminusone, midvalue, "Coefficient A is negative, B and C positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, maxvalue, midvalue, "Coefficient A is negative, B and C positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, midvalue, minvalue, "Coefficient A is negative, B and C positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, midvalue, minvalueplusone, "Coefficient A is negative, B and C positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, midvalue, maxvalueminusone, "Coefficient A is negative, B and C positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, midvalue, maxvalue, "Coefficient A is negative, B and C positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, midvalue, midvalue, "Coefficient A is negative, B and C positive"), result.totalCount, result.passedCount);

	result = testCase(1, getSolutionQuadraticEquation(minvalue, -midvalue, -midvalue, "Coefficient A is positive, B and C negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(minvalueplusone, -midvalue, -midvalue, "Coefficient A is positive, B and C negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(maxvalueminusone, -midvalue, -midvalue, "Coefficient A is positive, B and C negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(maxvalue, -midvalue, -midvalue, "Coefficient A is positive, B and C negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, -minvalue, -midvalue, "Coefficient A is positive, B and C negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, -minvalueplusone, -midvalue, "Coefficient A is positive, B and C negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, -maxvalueminusone, -midvalue, "Coefficient A is positive, B and C negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, -maxvalue, -midvalue, "Coefficient A is positive, B and C negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, -midvalue, -minvalue, "Coefficient A is positive, B and C negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, -midvalue, -minvalueplusone, "Coefficient A is positive, B and C negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, -midvalue, -maxvalueminusone, "Coefficient A is positive, B and C negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, -midvalue, -maxvalue, "Coefficient A is positive, B and C negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, -midvalue, -midvalue, "Coefficient A is positive, B and C negative"), result.totalCount, result.passedCount);

	result = testCase(1, getSolutionQuadraticEquation(minvalue, -midvalue, midvalue, "Coefficient B is negative, A and C positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(minvalueplusone, -midvalue, midvalue, "Coefficient B is negative, A and C positive"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(maxvalueminusone, -midvalue, midvalue, "Coefficient B is negative, A and C positive"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(maxvalue, -midvalue, midvalue, "Coefficient B is negative, A and C positive"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(midvalue, -minvalue, midvalue, "Coefficient B is negative, A and C positive"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(midvalue, -minvalueplusone, midvalue, "Coefficient B is negative, A and C positive"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(midvalue, -maxvalueminusone, midvalue, "Coefficient B is negative, A and C positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, -maxvalue, midvalue, "Coefficient B is negative, A and C positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, -midvalue, minvalue, "Coefficient B is negative, A and C positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, -midvalue, minvalueplusone, "Coefficient B is negative, A and C positive"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(midvalue, -midvalue, maxvalueminusone, "Coefficient B is negative, A and C positive"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(midvalue, -midvalue, maxvalue, "Coefficient B is negative, A and C positive"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(midvalue, -midvalue, midvalue, "Coefficient B is negative, A and C positive"), result.totalCount, result.passedCount);

	result = testCase(1, getSolutionQuadraticEquation(-minvalue, midvalue, -midvalue, "Coefficient B is positive, A and C negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-minvalueplusone, midvalue, -midvalue, "Coefficient B is positive, A and C negative"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(-maxvalueminusone, midvalue, -midvalue, "Coefficient B is positive, A and C negative"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(-maxvalue, midvalue, -midvalue, "Coefficient B is positive, A and C negative"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(-midvalue, minvalue, -midvalue, "Coefficient B is positive, A and C negative"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(-midvalue, minvalueplusone, -midvalue, "Coefficient B is positive, A and C negative"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(-midvalue, maxvalueminusone, -midvalue, "Coefficient B is positive, A and C negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, maxvalue, -midvalue, "Coefficient B is positive, A and C negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, midvalue, -minvalue, "Coefficient B is positive, A and C negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, midvalue, -minvalueplusone, "Coefficient B is positive, A and C negative"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(-midvalue, midvalue, -maxvalueminusone, "Coefficient B is positive, A and C negative"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(-midvalue, midvalue, -maxvalue, "Coefficient B is positive, A and C negative"), result.totalCount, result.passedCount);
	result = testCase(2, getSolutionQuadraticEquation(-midvalue, midvalue, -midvalue, "Coefficient B is positive, A and C negative"), result.totalCount, result.passedCount);

	result = testCase(1, getSolutionQuadraticEquation(minvalue, midvalue, -midvalue, "Coefficient C is negative, A and B positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(minvalueplusone, midvalue, -midvalue, "Coefficient C is negative, A and B positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(maxvalueminusone, midvalue, -midvalue, "Coefficient C is negative, A and B positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(maxvalue, midvalue, -midvalue, "Coefficient C is negative, A and B positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, minvalue, -midvalue, "Coefficient C is negative, A and B positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, minvalueplusone, -midvalue, "Coefficient C is negative, A and B positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, maxvalueminusone, -midvalue, "Coefficient C is negative, A and B positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, maxvalue, -midvalue, "Coefficient C is negative, A and B positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, midvalue, -minvalue, "Coefficient C is negative, A and B positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, midvalue, -minvalueplusone, "Coefficient C is negative, A and B positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, midvalue, -maxvalueminusone, "Coefficient C is negative, A and B positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, midvalue, -maxvalue, "Coefficient C is negative, A and B positive"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(midvalue, midvalue, -midvalue, "Coefficient C is negative, A and B positive"), result.totalCount, result.passedCount);

	result = testCase(1, getSolutionQuadraticEquation(-minvalue, -midvalue, midvalue, "Coefficient C is positive, A and B negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-minvalueplusone, -midvalue, midvalue, "Coefficient C is positive, A and B negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-maxvalueminusone, -midvalue, midvalue, "Coefficient C is positive, A and B negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-maxvalue, -midvalue, midvalue, "Coefficient C is positive, A and B negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, -minvalue, midvalue, "Coefficient C is positive, A and B negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, -minvalueplusone, midvalue, "Coefficient C is positive, A and B negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, -maxvalueminusone, midvalue, "Coefficient C is positive, A and B negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, -maxvalue, midvalue, "Coefficient C is positive, A and B negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, -midvalue, minvalue, "Coefficient C is positive, A and B negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, -midvalue, minvalueplusone, "Coefficient C is positive, A and B negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, -midvalue, maxvalueminusone, "Coefficient C is positive, A and B negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, -midvalue, maxvalue, "Coefficient C is positive, A and B negative"), result.totalCount, result.passedCount);
	result = testCase(0, getSolutionQuadraticEquation(-midvalue, -midvalue, midvalue, "Coefficient C is positive, A and B negative"), result.totalCount, result.passedCount);
	printf("Summary: \nTotal Tests = %d \nPassed Tests = %d \nFailed Tests = %d", result.totalCount, result.passedCount, result.totalCount - result.passedCount);
}