#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "General.h"
#include "Employee.h"

static const char* EmpTypeStr[eNofEmpTypes]
= { "CEO", "Manager", "Cashier", "Kitchen", "Maintenance" };

int initEmployee(Employee* pEmployee)
{
	pEmployee->empName = getStrExactName("Please enter the employee's name:");
	pEmployee->empID = getEmployeeID();
	pEmployee->salary = getEmployeeSalary();
	pEmployee->empType = getEmpType();

	return 1;
}

void initCEOEmployee(Employee* pEmployee)
{
	pEmployee->empName = getStrExactName("Please enter the CEO's name:");
	pEmployee->empID = getEmployeeID();
	pEmployee->salary = getEmployeeSalary();
	pEmployee->empType = (eEmpType)0;
}

void initManagerEmployee(Employee* pEmployee)
{
	pEmployee->empName = getStrExactName("Please enter the Manager's name:");
	pEmployee->empID = getEmployeeID();
	pEmployee->salary = getEmployeeSalary();
	pEmployee->empType = (eEmpType)1;
}

eEmpType getEmpType()
{
	int option;
	printf("\n\n");
	do {
		printf("Please enter one of the following types\n");
		for (int i = 2; i < eNofEmpTypes; i++)
			printf("%d for %s\n", i, EmpTypeStr[i]);
		if (scanf("%d", &option) != 1) {
			// If scanf fails, clear the input buffer
			while (getchar() != '\n');
		}
	} while (option < 2 || option >= eNofEmpTypes);
	getchar();
	return (eEmpType)option;
}

const char* getEmpTypeStr(int type)
{
	if (type < 0 || type >= eNofEmpTypes)
		return NULL;
	return EmpTypeStr[type];
}

int getEmployeeID()
{
	int num;
	//int unique = 0;
	do {
		printf("Enter employee ID number - between %d to %d:\n", MIN_ID, MAX_ID);
		if (scanf("%d", &num) != 1) {
			// If scanf fails, clear the input buffer
			while (getchar() != '\n');
		}
		//if (num >= MIN_ID && num <= MAX_ID)
		//	unique = isSerialNumUnique(planeArr, planeCount, num);
	} while (num < MIN_ID || num > MAX_ID);
	return num;
}

double getEmployeeSalary()
{
	double num;
	do {
		printf("Enter employee salary:\n");
		if (scanf("%lf", &num) != 1) {
			// If scanf fails, clear the input buffer
			while (getchar() != '\n');
		}
	} while (num < 0);
	return num;
}


void printEmployee(const Employee* pEmployee)
{
	printf("Employee: Name:%s, ID:%d, Type %s, Salary: %f\n", pEmployee->empName, pEmployee->empID, EmpTypeStr[pEmployee->empType], pEmployee->salary);
}

void printEmployeeV(void* ppEmp)
{
	Employee** ppE = (Employee**)ppEmp;
	Employee* pE = *ppE;
	printEmployee(pE);
}

int	saveEmployeeToFile(const Employee* pEmployee, FILE* fp)
{
	if (fwrite(pEmployee, sizeof(Employee), 1, fp) != 1)
	{
		PRINT_ERROR_STR_RETURN_0("write employee")
	}
	return 1;
}

int	loadEmployeeFromFile(Employee* pEmployee, FILE* fp)
{
	if (fread(pEmployee, sizeof(Employee), 1, fp) != 1)
	{
		PRINT_ERROR_STR_RETURN_0("read employee")
	}
	return 1;
}

void freeEmployee(Employee* pEmployee)
{
	if (pEmployee != NULL) {
		free(pEmployee->empName);
		free(pEmployee);
	}
}

void freeEmployeeV(void* ppEmp)
{
	freeEmployee(*((Employee**)ppEmp));
}

int	compareEmployeesByID(int id1, int id2)
{
	if (id1 == id2)
		return 0;
	else if (id1 > id2)
		return 1;
	return -1;
}


int	compareEmployeesBySalary(double salary1, double salary2)
{
	if (salary1 == salary2)
		return 0;
	else if (salary1 > salary2)
		return 1;
	return -1;
}

int	compareEmployeesByEmpType(int type1, int type2)
{
	if (type1 == type2)
		return 0;
	else if (type1 > type2)
		return 1;
	return -1;
}

int	changeSalary(Employee* pEmployee)
{
	if (!pEmployee)
		return 0;
	pEmployee->salary = getEmployeeSalary();
	return 1;
}

int	changeEmpType(Employee* pEmployee)
{
	if (!pEmployee)
		return 0;
	pEmployee->empType = getEmpType();
	return 1;
}