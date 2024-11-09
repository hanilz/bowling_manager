#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Branch.h"
#include "General.h"
//#include "fileHelper.h"


#define SEP_CHAR '_'

int	initBranch(Branch* pBranch)
{
	pBranch->branchName = getStrExactName("Please enter the branch name:");
	pBranch->branchAddress = getStrExactName("Please enter the branch address:");
	getBranchSerialNum(pBranch);
	getBranchEmployees(pBranch);
	getBranchLanes(pBranch);

	return 1;
}

// offices have no lanes and employees
int	initOfficeBranch(Branch* pBranch)
{
	pBranch->branchName = getStrExactName("Please enter the office name:");
	pBranch->branchAddress = getStrExactName("Please enter the office address:");
	getBranchSerialNum(pBranch);

	return 1;
}

int getBranchSerialNum(Branch* pBranch)
{
	do {
		printf("Enter branch Serial Number(positive integer): ");
		if (scanf("%d", &(pBranch->branchSerialNum)) != 1) {
			// If scanf fails, clear the input buffer
			while (getchar() != '\n');
		}
		// Check if the input is within the specified range
		if (pBranch->branchSerialNum < 0)
			printf("Invalid input. Please enter a positive integer .\n");
	} while (pBranch->branchSerialNum < 0);

	return 1;
}

int	getBranchNumOfEmployees(Branch* pBranch)
{
	do {
		printf("Enter how many employees you want to hire for the Branch(positive integer, not including manager): ");
		if (scanf("%d", &(pBranch->numOfEmployees)) != 1) {
			// If scanf fails, clear the input buffer
			while (getchar() != '\n');
		}
		// Check if the input is within the specified range
		if (pBranch->numOfEmployees < 0)
			printf("Invalid input. Please enter a positive integer .\n");
	} while (pBranch->numOfEmployees < 0);
	pBranch->numOfEmployees++;
	return 1;
}

int	getBranchNumOfLanes(Branch* pBranch)
{
	do {
		printf("Enter how many lanes you want to build in the Branch(positive integer, greater than 0): ");
		if (scanf("%d", &(pBranch->numOfLanes)) != 1) {
			// If scanf fails, clear the input buffer
			while (getchar() != '\n');
		}
		if (pBranch->numOfLanes < 1)
			printf("Invalid input. Please enter a positive integer that is greater than 0.\n");
	} while (pBranch->numOfLanes < 1);
	return 1;
}

int	getBranchEmployees(Branch* pBranch)
{
	getBranchNumOfEmployees(pBranch);
	pBranch->employeeArr = (Employee**)malloc((pBranch->numOfEmployees) * sizeof(Employee*));

	if (!(pBranch->employeeArr)) {
		ALLOC_ERROR_RETURN()
	}

	// the first employee in a branch is a manager
	Employee* e = (Employee*)malloc(sizeof(Employee));
	if (!(e)) {
		ALLOC_ERROR_RETURN()
	}

	initManagerEmployee(e);
	pBranch->employeeArr[0] = e;

	for (int i = 1; i < pBranch->numOfEmployees; i++) {
		Employee* e = (Employee*)malloc(sizeof(Employee));
		if (!(e)) {
			ALLOC_ERROR_RETURN()
		}

		initEmployee(e);
		pBranch->employeeArr[i] = e;
	}

	return 1;
}

int	addEmployee(Branch* pBranch)
{
	Employee* e = (Employee*)malloc(sizeof(Employee));
	if (!(e)) {
		ALLOC_ERROR_RETURN()
	}

	if (!initEmployee(e)) {
		PRINT_ERROR_STR_RETURN_0("Employee initialization")

	}
	pBranch->employeeArr[pBranch->numOfEmployees] = e;
	pBranch->numOfEmployees++;

	return 1;
}

int	getBranchLanes(Branch* pBranch)
{
	getBranchNumOfLanes(pBranch);
	pBranch->lanesArr = (Lane**)malloc((pBranch->numOfLanes) * sizeof(Lane*));

	if (!(pBranch->lanesArr)) 
	{
		ALLOC_ERROR_RETURN()
	}

	for (int i = 0; i < pBranch->numOfLanes; i++) {
		Lane* l = (Lane*)malloc(sizeof(Lane));
		if (!(l)) 
		{
			ALLOC_ERROR_RETURN()
		}

		initLane(l);
		pBranch->lanesArr[i] = l;
	}

	return 1;
}

int	removeLane(Branch* pBranch)
{
	if (pBranch->numOfLanes == 1)
	{
		PRINT_ERROR_STR_RETURN_0("There must be at least one lane in branch!")
	}
	printf("Choose a number from the following %d lanes, or 0 to cancel:\n", pBranch->numOfLanes);
	for (int i = 0; i < pBranch->numOfLanes; i++) {
		printf("Lane No. %d: ", i + 1);
		printLane(pBranch->lanesArr[i]);
	}
	int selection = 0;
	printf("Enter your selection or 0 to cancel: ");
	scanf("%d", &selection);  //FREE BUFFER
	if (!selection) {
		PRINT_ERROR_STR_RETURN_0("remove lane from branch canceled!")
	}
	if (pBranch->numOfLanes < selection || 0 > selection)
	{
		PRINT_ERROR_STR_RETURN_0("Invalid input. Canceling operation.")
	}
	--selection;
	free(pBranch->lanesArr[selection]);

	// Shift the elements after the removed item to fill the gap
	for (int i = selection; i < pBranch->numOfLanes - 1; i++) {
		pBranch->lanesArr[i] = pBranch->lanesArr[i + 1];
	}

	pBranch->numOfLanes--;

	return 1;
}

int	removeEmployee(Branch* pBranch)
{
	if (!pBranch->numOfEmployees)
	{
		PRINT_ERROR_STR_RETURN_0("No employees to remove!")
	}
	printf("Choose a number from the following %d employees, or 0 to cancel:\n", pBranch->numOfEmployees);
	for (int i = 0; i < pBranch->numOfEmployees; i++) {
		printf("Employee No. %d: ", i + 1);
		printEmployee(pBranch->employeeArr[i]);
	}
	int selection = 0;
	printf("Enter your selection or 0 to cancel: ");
	scanf("%d", &selection);  //FREE BUFFER
	if (!selection) 
	{
		PRINT_ERROR_STR_RETURN_0("remove employee from branch canceled!")
	}
	if (pBranch->numOfEmployees < selection || 0 > selection)
	{
		PRINT_ERROR_STR_RETURN_0("Invalid input. Canceling operation.")
	}
	--selection;
	free(pBranch->employeeArr[selection]);

	// Shift the elements after the removed item to fill the gap
	for (int i = selection; i < pBranch->numOfEmployees - 1; i++) {
		pBranch->employeeArr[i] = pBranch->employeeArr[i + 1];
	}
	
	pBranch->numOfEmployees--;

	return 1;
}

int	addLane(Branch* pBranch)
{
	Lane* l = (Lane*)malloc(sizeof(Lane));
	if (!(l)) {
		ALLOC_ERROR_RETURN()

	}

	if (!initLane(l)) 
	{
		PRINT_ERROR_STR_RETURN_0("Lane initialization")
	}
	pBranch->lanesArr[pBranch->numOfLanes] = l;
	pBranch->numOfLanes++;

	return 1;
}

int	addGameToLane(Branch* pBranch) {
	printf("Which lane do you want to play on?\n");
	printf("Choose a number from the following %d lanes, or -1 to cancel:\n", pBranch->numOfLanes);
	for (int i = 0; i < pBranch->numOfLanes; i++) {
		printf("Lane No. %d: ", i + 1);
		printLane(pBranch->lanesArr[i]);
	}
	int selection = 0;
	do {
		printf("Enter your selection or -1 to cancel: ");
		if (scanf("%d", &selection) != 1) {
			// If scanf fails, clear the input buffer
			while (getchar() != '\n');
		}		
		if (selection == -1) {
			printf("Add game to lane cancelled.");
			return 0;
		}
		if (pBranch->numOfLanes < selection || -1 > selection || !selection)
			printf("Invalid input. Please enter a positive integer that is equal or less than %d or -1 to cancel.\n", pBranch->numOfLanes);
	} while (pBranch->numOfLanes < selection || -1 > selection || !selection);
	addGame(pBranch->lanesArr[selection - 1]);

	return 1;
}

int	compareBranchesBySNEmployeesLanes(int n1, int n2)
{
	if (n1 == n2)
		return 0;
	else if (n1 > n2)
		return 1;
	return -1;
}

void printBranch(const Branch* pBranch)
{
	printf("\nBranch name:%-20s\t", pBranch->branchName);
	printf("Address: %-20s\t Serial Number:%d\n", pBranch->branchAddress, pBranch->branchSerialNum);
	printEmployees(pBranch);
	printLanes(pBranch);
	printf("\n");
}

void printEmployees(const Branch* pBranch) 
{
	printf("Employees(%d):\n", pBranch->numOfEmployees);
	generalArrayFunction(pBranch->employeeArr, pBranch->numOfEmployees, sizeof(Employee*), printEmployeeV);
}

void printLanes(const Branch* pBranch)
{
	printf("Lanes(%d):\n", pBranch->numOfLanes);
	generalArrayFunction(pBranch->lanesArr, pBranch->numOfLanes, sizeof(Lane*), printLaneV);
}

void printBranchV(const void* val)
{
	const Branch* pBranch = (const Branch*)val;
	printBranch(pBranch);
}

int	saveBranchToFile(const Branch* pBranch, FILE* fp)
{
/*	if (!pBranch)
		return 0;
	fprintf(fp, "%s\n", pBranch->branchName);
	fprintf(fp, "%s\n", pBranch->branchAddress);
	fprintf(fp, "%d\n", pBranch->branchSerialNum);*/
	return 1;
}

int	loadBranchFromFile(Branch* pBranch, FILE* fp)
{
/*	if (!pBranch)
		return 0;

	pBranch->branchName = readDynStringFromTextFile(fp);

	pBranch->branchAddress = readDynStringFromTextFile(fp);

	readIntFromFile(&(pBranch->branchSerialNum), fp, "unable to read branch SN\n");*/
	return 1;
}

void freeBranch(Branch* pBranch)
{
	generalArrayFunction(pBranch->lanesArr, pBranch->numOfLanes, sizeof(Lane*), freeLaneV);
	free(pBranch->lanesArr);
	generalArrayFunction(pBranch->employeeArr, pBranch->numOfEmployees, sizeof(Employee*), freeEmployeeV);
	free(pBranch->employeeArr);
	free(pBranch->branchName);
	free(pBranch->branchAddress);
	free(pBranch);
}

void freeBranchV(void* ppBranch)
{
	freeBranch(*((Branch**)ppBranch));
}

int	changeBranchName(Branch* pBranch)
{
	free(pBranch->branchName);

	printf(" ");
	pBranch->branchName = getStrExactName("Please enter new branch name:");

	return 1;
}

int	changeBranchAddress(Branch* pBranch)
{
	free(pBranch->branchAddress);
	printf("Enter new branch address: ");

	pBranch->branchAddress = getStrExactName("Please enter new branch address:");
	return 1;
}

int	compareBranchBySerialNumber(const void* branch1, const void* branch2)
{
	const Branch* pBranch1 = *(const Branch**)branch1;
	const Branch* pBranch2 = *(const Branch**)branch2;
	return compareBranchesBySNEmployeesLanes(pBranch1->branchSerialNum, pBranch2->branchSerialNum);
}

int	compareBranchByNumOfEmployees(const void* branch1, const void* branch2)
{
	const Branch* pBranch1 = *(const Branch**)branch1;
	const Branch* pBranch2 = *(const Branch**)branch2;
	return compareBranchesBySNEmployeesLanes(pBranch1->numOfEmployees, pBranch2->numOfEmployees);
}

int	compareBranchByNumOfLanes(const void* branch1, const void* branch2)
{
	const Branch* pBranch1 = *(const Branch**)branch1;
	const Branch* pBranch2 = *(const Branch**)branch2;
	return compareBranchesBySNEmployeesLanes(pBranch1->numOfLanes, pBranch2->numOfLanes);
}
