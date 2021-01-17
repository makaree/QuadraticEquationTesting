#include<stdio.h>
#include<Windows.h>

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

void main()
{
	int i = 1;
	int enumvalue = 0;
	double a = 0, b = 0, c = 0;
	printf(" This program accesses dynamic link library file quadratic.dll and return the solution of \n quadratic equation based on it. It is solely designed for manual testing of the quadratic.dll file");
	while (i == 1)
	{
		HINSTANCE hInst = LoadLibrary(TEXT("quadratic.dll"));
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

