/*A simple program that uses dynamic link library quadratic.dll, where user
can manually input the value of Coefficient of quadratic equation a,b
and c, in quadratic equation a*x*x + b*x + c=0 and get the solution of 
the given equation from the dynamic link library.
*/

#include<stdio.h>
#include<Windows.h>

/* Accesses the dynamic link library quadratic.dll and sets the 
coefficient “a” of the equation  a*x*x + b*x + c = 0.
*/
void (*setA)(const double);

/* Accesses the dynamic link library quadratic.dll and sets the 
coefficient “b” of the equation  a*x*x + b*x + c = 0.
*/
void (*setB)(const double);

/* Accesses the dynamic link library quadratic.dll and sets the 
coefficient “c” of the equation  a*x*x + b*x + c = 0.
*/
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

/*This is a main function which helps to manually test the dynamic link library quadratic.dll
and return the solution after calculation from the same dll. It can be run multiple times 
for calculating the solution by pressing 1 in the end of the calcuation and exit the code
by pressing any other character.
*/
void main()
{
	int i = 1;
	int enumvalue = 0;
	double a = 0, b = 0, c = 0;
	printf(" This program accesses dynamic link library file quadratic.dll and return the solution of \n quadratic equation based on it. It is solely designed for manual testing of the quadratic.dll file");
	while (i == 1)
	{	
		// Get a handle to the DLL module.
		HINSTANCE hInst = LoadLibrary(TEXT("quadratic.dll"));

		// If the handle is valid, try to get the function address.
		if (hInst != NULL)
		{
			printf("\n\n Please enter the values of a,b and c in numbers. Entering it in \n character may crash this application or might not function properly.");
			printf(" \n Enter the value of a: ");
			scanf_s("%lf", &a);
			printf(" Enter the value of b: ");
			scanf_s("%lf", &b);
			printf(" Enter the value of c: ");
			scanf_s("%lf", &c);
			printf("\n Value of a = %lf, b = %lf, c = %lf", a, b, c);
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
				printf("\n Solution is %d - %s  \n", enumvalue, returnEnumValue(enumvalue));
			}
		}

		// Free the DLL module.
		FreeLibrary(hInst);
		i++;
		printf("\n Press 1 to continue. Press any other characters to exit. Do you wish to continue: ");
		scanf_s("%d", &i);
		if (i != 1)
		{
			break;
		}
	}
	printf("Exit successful", i);
}

