#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "General.h"
#include "main.h"
#include "BowlingCompany.h"

//int main()
//{
//	LIST	playersList1;
//	L_init(&playersList1);
//	Player* p1 = (Player*)malloc(sizeof(Player));
//	initPlayer(p1);
//	L_insert(&playersList1.head, p1);
//
//	int fScore = ((Player*)playersList1.head.next->key)->finalScore;
//	char* name1 = ((Player*)playersList1.head.next->key)->playerName;
//	printf("f score: %d \n", fScore);
//	printf("name: %s \n", name1);
//
//	Game* pGame1 =(Game*)malloc(sizeof(Game));
//	if (!pGame1)
//	{
//		ALLOC_ERROR_RETURN();
//	}
//	initGame(pGame1);
//
//	NODE* pNode = &pGame1->playersList.head;
//
//	for (int i = 0; i < pGame1->numOfPlayers; i++) 
//	{
//		pNode = pNode->next;
//		Player* pPlayer1 = (Player*)(pNode->key);
//		char* name = pPlayer1->playerName;
//		int score = pPlayer1->finalScore;
//		printf("Player %d name: %s, score: %d\n", (i+1), name, score);
//	}
//	getWinner(pGame1);
//	printf("Winner: ");
//	printPlayer(pGame1->winner);
//
//	printf("\nprint game:\n");
//	printGame(pGame1);
//
//	freeGame(pGame1);
//	printf("\nfreed\n");
//}

int main()
{
 	srand(time(NULL));

	BowlingCompany	company;
	Branch* pBranch;

	if (!initCompany(&company))
	{
		printf("error init");
		return;
	}

	int option;
	int optionBranch;
	int stop = 0;
	int stopBranch = 0;

	do
	{
		option = menu();
		switch (option)
		{
		case eAddBranch:
			if (!addBranch(&company))
				printf("Error adding branch\n");
			break;

		case eRemoveBranch:
			if (!removeBranch(&company))
				printf("Error remove branch\n");
			break;

		case eSortBranches:
			sortBranches(&company);
			break;

		case eFindBranch:
			findBranch(&company);
			break;

		case ePrintCompany:
			printBowlingCompany(&company);
			printBranches(&company);
			break;

		case eChangeOfficeName:
			if (!changeBranchName(company.officeBranch))
				printf("Error changing office name\n");
			break;

		case eChangeOfficeAddress:
			if (!changeBranchAddress(company.officeBranch))
				printf("Error changing office address\n");
			break;

		case eBranchMenu:
			printBranches(&company);
			sortBranches(&company);
			pBranch = findBranch(&company);
			if (pBranch) {
				do {
					optionBranch= branchMenu();
					switch (optionBranch)
					{
					case ePlayGame:
						if (!addGameToLane(pBranch))
							printf("Error Playing Game\n");
						break;
					case eAddEmployee:
						if (!addEmployee(pBranch))
							printf("Error adding employee to branch\n");
						break;
					case eRemoveEmployee:
						if (!removeEmployee(pBranch))
							printf("Error removing employee from branch\n");
						break;
					case ePrintEmployees:
						printEmployees(pBranch);
						break;
					case eAddLane:
						if (!addLane(pBranch))
							printf("Error adding lane to branch\n");
						break;
					case eRemoveLane:
						if (!removeLane(pBranch))
							printf("Error removing lane from branch\n");
						break;
					case ePrintLanes:
						printLanes(pBranch);
						break;
					case eChangeBranchName:
						if (!changeBranchName(pBranch))
							printf("Error changing branch name\n");
						break;
					case eChangeBranchAddress:
						if (!changeBranchAddress(pBranch))
							printf("Error changing branch address\n");
						break;
					case ePrintBranch:
						printBranch(pBranch);
						break;

					case EXIT:
						printf("Going back to Bowling Company menu.\n");
						stopBranch = 1;
						break;

					default:
						printf("Wrong option\n");
						break;
					}
				} while (!stopBranch);
			}
			stopBranch = 0;
			break;
		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			//saveManagerToFile(&manager, MANAGER_FILE_NAME);
			//saveBowlingCompanyToFile(&company, AIRLINE_FILE_NAME);
			freeBowlingCompany(&company);
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);

	printf("before dump\n");
	_CrtDumpMemoryLeaks();  // from HW3 project
	return 1;
}

int initCompany(BowlingCompany* pComp)
{
//	if (res == FROM_FILE)
//		return initAirlineFromFile(pCompany, pManager, AIRLINE_FILE_NAME);
//	else
	initBowlingCompany(pComp);
	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofOptions; i++)
		printf("%d - %s\n", i, strCompanyMenu[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}


int branchMenu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofBranchOptions; i++)
		printf("%d - %s\n", i, strBranchMenu[i]);
	printf("%d - Quit Branch Menu\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}

//int main()
//{
//	srand(time(NULL));
//
//	LIST	playersList1;
//	L_init(&playersList1);
//	Player* p1 = (Player*)malloc(sizeof(Player));
//	initPlayer(p1);
//	L_insert(&playersList1.head, p1);
//
//	int fScore = ((Player*)playersList1.head.next->key)->finalScore;
//	char* name1 = ((Player*)playersList1.head.next->key)->playerName;
//	printf("f score: %d \n", fScore);
//	printf("name: %s \n", name1);
//
//	Game* pGame1 = (Game*)malloc(sizeof(Game));
//	if (!pGame1)
//	{
//		ALLOC_ERROR_RETURN();
//	}
//	initGame(pGame1);
//
//	NODE* pNode = &pGame1->playersList.head;
//
//	for (int i = 0; i < pGame1->numOfPlayers; i++)
//	{
//		pNode = pNode->next;
//		Player* pPlayer1 = (Player*)(pNode->key);
//		char* name = pPlayer1->playerName;
//		int score = pPlayer1->finalScore;
//		printf("Player %d name: %s, score: %d\n", (i + 1), name, score);
//	}
//	getWinner(pGame1);
//	printf("Winner: ");
//	printPlayer(pGame1->winner);
//
//	printf("\nprint game:\n");
//	printGame(pGame1);
//
//
//	freeGame(pGame1);
//	printf("\nfreed\n");
//}
