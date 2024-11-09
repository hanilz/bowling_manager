#pragma once

#include "Lane.h"
#include "Employee.h"

typedef struct
{
	char* branchName;
	char* branchAddress;
	int			branchSerialNum;
	Employee** employeeArr;
	int			numOfEmployees;
	Lane** lanesArr;
	int			numOfLanes;
} Branch;

int		initBranch(Branch* pBranch);
int		initOfficeBranch(Branch* pBranch);
int		getBranchSerialNum(Branch* pBranch);
int		getBranchNumOfEmployees(Branch* pBranch);
int		getBranchEmployees(Branch* pBranch);
int		getBranchNumOfLanes(Branch* pBranch);
int		getBranchLanes(Branch* pBranch);
int		addEmployee(Branch* pBranch);
int		addLane(Branch*);
int		removeLane(Branch*);
int		removeEmployee(Branch*);
int		addGameToLane(Branch*);
int 	compareBranchesBySNEmployeesLanes(int, int);
int		changeBranchName(Branch*);
int		changeBranchAddress(Branch*);
void	printBranch(const Branch* pBranch);
void	printBranchV(const void* val);
int		saveBranchToFile(const Branch* pBranch, FILE* fp);
int		loadBranchFromFile(Branch* pBranch, FILE* fp);
void	freeBranch(Branch* pBranch);
void	freeBranchV(void* val);
int		compareBranchBySerialNumber(const void* branch1, const void* branch2);
int		compareBranchByNumOfEmployees(const void* branch1, const void* branch2);
int		compareBranchByNumOfLanes(const void* branch1, const void* branch2);
void	printLanes(const Branch* pBranch);
void	printEmployees(const Branch* pBranch);
