#include <stdio.h>
#include <stdlib.h>

#include "BowlingCompany.h"
#include "General.h"

static const char* sortOptStr[eNofSortOpt] = {
	"None","Serial Number", "Number of Employees", "Number of Lanes" };

void initBowlingCompany(BowlingCompany* pComp)
{
	printf("-----------  Init Bowling Company\n");
	pComp->name = getStrExactName("Enter bowling company name: ");
	pComp->founderName = getStrExactName("Enter bowling company founder name: ");
	Branch* pBranch = (Branch*)calloc(1, sizeof(Branch));
	if (!pBranch)
	{
		ALLOC_ERROR_RETURN()
	}
	initOfficeBranch(pBranch);
	pComp->officeBranch = pBranch;
	Employee ceo;
	initCEOEmployee(&ceo);
	pComp->ceo = ceo;
	pComp->branchArr = NULL;
	pComp->numOfBranches = 0;
	pComp->numOfGames = 0;
}

int	addBranch(BowlingCompany* pComp)
{
	Branch* pBranch = (Branch*)calloc(1, sizeof(Branch));
	if (!pBranch) 
	{
		ALLOC_ERROR_RETURN()
	}

	initBranch(pBranch);

	pComp->branchArr = (Branch**)realloc(pComp->branchArr, (pComp->numOfBranches + 1) * sizeof(Branch*));
	if (!pComp->branchArr)
	{
		free(pBranch);
		return 0;
	}
	pComp->branchArr[pComp->numOfBranches] = pBranch;
	pComp->numOfBranches++;
	pComp->branchSortOpt = eNone;
	return 1;
}

void sortBranches(BowlingCompany* pComp)
{
	pComp->branchSortOpt = showSortMenu();
	int(*compare)(const void* branch1, const void* branch2) = NULL;

	switch (pComp->branchSortOpt)
	{
	case eSN:
		compare = compareBranchBySerialNumber;
		break;
	case eEmp:
		compare = compareBranchByNumOfEmployees;
		break;
	case eLane:
		compare = compareBranchByNumOfLanes;
		break;
	}

	if (compare != NULL)
		qsort(pComp->branchArr, pComp->numOfBranches, sizeof(Branch*), compare);
	printBranches(pComp);
}

// remove later
int	addLaneToBranch(BowlingCompany* pComp)
{
	if (!pComp->numOfBranches) {
		PRINT_ERROR_STR_RETURN_0("No branches in company. add branch first.")
	}
	printf("Which branch do you want to add a lane to?\n");
	printf("Choose a number from the following %d branches, or 0 to cancel:\n", pComp->numOfBranches);
	for (int i = 0; i < pComp->numOfBranches; i++) {
		printf("Branch No. %d: ", i + 1);
		printBranch(pComp->branchArr[i]);
	}
	int selection = 0;
	do {
		printf("Enter your selection or 0 to cancel: ");
		scanf("%d", &selection);  //FREE BUFFER
		if (!selection) {
			PRINT_ERROR_STR_RETURN_0("add lane to branch canceled!")
		}
		if (pComp->numOfBranches < selection || 0 > selection)
			printf("Invalid input. Please enter a positive integer that is equal or less than %d or 0 to cancel.\n", pComp->numOfBranches);
	} while (pComp->numOfBranches < selection || 0 > selection);

	return addLane(pComp->branchArr[selection - 1]);
}

Branch* findBranch(const BowlingCompany* pComp)
{
	int(*compare)(const void* branch1, const void* branch2) = NULL;
	Branch b = { 0 };
	Branch* pBranch = &b;

	switch (pComp->branchSortOpt)
	{
	case eSN:
		printf("%s\t", "Serial Number:");
		getBranchSerialNum(pBranch);
		compare = compareBranchBySerialNumber;
		break;

	case eEmp:
		printf("%s\t", "Number of Employees:");
		getBranchNumOfEmployees(pBranch);
		compare = compareBranchByNumOfEmployees;
		break;

	case eLane:
		printf("%s\t", "Number of Lanes:");
		getBranchNumOfLanes(pBranch);
		compare = compareBranchByNumOfLanes;
		break;

	}

	if (compare != NULL)
	{
		Branch** pB = bsearch(&pBranch, pComp->branchArr, pComp->numOfBranches, sizeof(Branch*), compare);
		if (pB == NULL)
			printf("Branch was not found\n");
		else {
			printf("Branch found, ");
			printBranch(*pB);
			return *pB;
		}
	}
	else {
		printf("The search cannot be performed, array not sorted\n");
	}
	return NULL;
}

eSortOption showSortMenu()
{
	int opt;
	printf("Base on what field do you want to sort?\n");
	do {
		for (int i = 1; i < eNofSortOpt; i++)
			printf("Enter %d for %s\n", i, sortOptStr[i]);
		scanf("%d", &opt);
	} while (opt < 0 || opt >= eNofSortOpt);

	return (eSortOption)opt;
}

void printBowlingCompany(const BowlingCompany* pComp) 
{
	printf("Bowling company name:%-20s\t founder name:%-20s\t Number of branches: %d\n\n", pComp->name, pComp->founderName, pComp->numOfBranches);
	printf("CEO info:\n");
	printEmployee(&(pComp->ceo));
	printf("\nCompany office info:\n");
	printBranch(pComp->officeBranch);
	printf("\n");
}
void printBranches(const BowlingCompany* pComp) 
{
	if (!pComp->numOfBranches) 
		printf("No branches to display!\t Add branches via menu first.\n");
	else {
		for (int i = 0; i < pComp->numOfBranches; i++)
			printBranch(pComp->branchArr[i]);
	}
}

void freeBowlingCompany(BowlingCompany* pComp)
{
	generalArrayFunction(pComp->branchArr, pComp->numOfBranches, sizeof(Branch*), freeBranchV);
	free(pComp->branchArr);
	free(pComp->founderName);
	free(pComp->name);
	freeEmployee(&(pComp->ceo));
	freeBranch(pComp->officeBranch);
	free(pComp);
}

int	removeBranch(BowlingCompany* pComp)
{
	if (!pComp->numOfBranches)
	{
		PRINT_ERROR_STR_RETURN_0("No branches to remove!")
	}
	sortBranches(pComp);
	Branch* pBranch = findBranch(pComp);
	if (!pBranch)
		return 0;
	int i = 0;
	for (i = 0; i < pComp->numOfBranches; i++)  // find index of pBranch
		if (pBranch == pComp->branchArr[i])
			break;
	freeBranch(pBranch);
	for (int j = i; j < pComp->numOfBranches - 1; j++) {
		pComp->branchArr[j] = pComp->branchArr[j + 1];
	}
	pComp->numOfBranches--;

	
	return 1;
	/*pComp->branchArr[i] = pComp->branchArr[pComp->numOfBranches - 1];
	pComp->numOfBranches--;
	pComp->branchArr = (Branch**)realloc(pComp->branchArr, (pComp->numOfBranches) * sizeof(Branch*));
	if (!pComp->branchArr && pComp->numOfBranches)
		return 0;*/
}
