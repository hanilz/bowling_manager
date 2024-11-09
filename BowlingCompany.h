#pragma once
#include "Employee.h"
#include "Branch.h"

typedef enum {
	eNone, eSN, eEmp, eLane, eNofSortOpt
} eSortOption;

typedef struct
{
	char*		name;
	char*		founderName;
	Employee	ceo;
	Branch**	branchArr;
	int			numOfBranches;
	int			numOfGames;
	Branch*		officeBranch;
	eSortOption branchSortOpt;
} BowlingCompany;

Branch*		findBranch(const BowlingCompany* pComp);
void		initBowlingCompany(BowlingCompany* pComp);
void		initBowlingCompanyFromFile(BowlingCompany*, FILE*);
int			addBranch(BowlingCompany* pComp);
int			removeBranch(BowlingCompany*);
int			addLaneToBranch(BowlingCompany*);  // REMOVE
void		printBowlingCompany(const BowlingCompany*);
void		sortBranches(BowlingCompany* pComp);
void		freeBowlingCompany(BowlingCompany* pComp);
eSortOption	showSortMenu();
void		printBranches(const BowlingCompany* pComp);
