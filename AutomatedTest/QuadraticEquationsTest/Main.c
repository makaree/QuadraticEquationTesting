/*A simple program that uses dynamic link library quadratic.dll, where user
automatically inputs the value of Coefficient of quadratic equation a,b
and c, in a*x*x + b*x + c and get the solution of the given equation from the
dynamic link library as an Automated Test solution. It also checks the result
from the dll if the obtained result is same with expected result or not.*/

#include<stdio.h>
#include <stdlib.h>
#include<Windows.h>

/*A structure is defined with two integers for calculating the total number
of executed test cases, total number of passed test cases
*/
struct testResult {
	int totalCount, passedCount;
};

/*defining a definition for Struct 
*/
typedef struct testResult Struct;

/* Accesses the dynamic link library quadratic.dll and sets the 
coefficient “a” of the equation  a*x*x + b*x + c = 0.*/
void (*setA)(const double);

/* Accesses the dynamic link library quadratic.dll and sets the 
coefficient “b” of the equation  a*x*x + b*x + c = 0.*/
void (*setB)(const double);

/* Accesses the dynamic link library quadratic.dll and sets the 
coefficient “c” of the equation  a*x*x + b*x + c = 0.*/
void (*setC)(const double);

/* Accesses the dynamic link library quadratic.dll and  return values of getSolution
of the equation  a*x*x + b*x + c = 0 in integer as follows:
0 for SOLUTION_OK,
1 for ERROR_A_IS_ZERO,
2 for ERROR_NO_REAL_ROOTS
*/
int (*getSolution)(double*, double*);

/* This function returns String value for the passed integer as follows:
SOLUTION_OK for 0,
ERROR_A_IS_ZERO for 1,
ERROR_NO_REAL_ROOTS for 2
*/
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

/*This function accesses the getSolution funtion from dynamic link library quadratic.dll
and returns the solution after calculation from the same dll after user provides a, b and
c which are coefficient of  equation  a*x*x + b*x + c = 0. A parameter message is also included
in this function which is used to display the message.
*/
int getSolutionQuadraticEquation(double a, double b, double c, char* message)
{
	int enumvalue = -1;
	
	// Get a handle to the DLL module.
	HINSTANCE hInst = LoadLibrary(TEXT("quadratic.dll"));
	
	// If the handle is valid, try to get the function address.
	if (hInst != NULL)
	{
		printf("\nTest Module: %s", message);
		printf("\nTest with value of a = %lf, b = %lf, c = %lf", a, b, c);
		setA = (void*)GetProcAddress(hInst, "setA");
		setB = (void*)GetProcAddress(hInst, "setB");
		setC = (void*)GetProcAddress(hInst, "setC");
		getSolution = (int*)GetProcAddress(hInst, "getSolution");

		// If the function address is valid, call the function.
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

	// Free the DLL module.
	FreeLibrary(hInst);
	Sleep(100);
	return enumvalue;
}

/* This function checks if the result has met the Expected outcome when compared with
the actual outcome and increases the count of passed Result if only passed and increases 
the count for total number of test cases executed.
*/
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

/*This is a main function which uses Data Driven Approach in calculating the soltion of 
quadratic equation  a*x*x + b*x + c = 0 by accessing dynamic link library quadratic.dll. 
It calculates the solution of equation initally and compares the Actual result with the 
expected result and displays if the test case has passed or failed.
*/
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