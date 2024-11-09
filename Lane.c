#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "General.h"
#include "Lane.h"


int	initLane(Lane* pLane)
{
	getLaneCode(pLane);
	pLane->numOfGames = 0;
	pLane->bestScore = 0;
	pLane->games = NULL;
	return 1;
}

int	getLaneCode(Lane* pLane)
{
	printf("Please enter lane code: ");
	scanf(" %c", &(pLane->laneCode[0]));

	while (getchar() != '\n');
	return 1;
}

int	addGame(Lane* pLane) {
	(pLane->numOfGames)++;
	if (pLane->numOfGames == 1)  // first game
		pLane->games = (Game*)malloc(1 * sizeof(Game));
	else
		pLane->games = (Game*)realloc(pLane->games, pLane->numOfGames * sizeof(Game));
	if (!(pLane->games))
	{
		ALLOC_ERROR_RETURN()
	}

	pLane->games[pLane->numOfGames - 1] = (Game*)malloc(sizeof(Game));
	if (!(pLane->games[pLane->numOfGames - 1]))
	{
		ALLOC_ERROR_RETURN()
	}
	printf("Initializing new Game.\n");
	initGame(pLane->games[pLane->numOfGames - 1]);
	printGameScoreboard(pLane->games[pLane->numOfGames - 1]);
	if (pLane->bestScore < pLane->games[pLane->numOfGames - 1]->winner->finalScore) {
		printf("New lane best score! old record: %d, new record: %d\n", pLane->bestScore, pLane->games[pLane->numOfGames - 1]->winner->finalScore);
		pLane->bestScore = pLane->games[pLane->numOfGames - 1]->winner->finalScore;
	}
	return 1;
}

void printLane(const Lane* pLane) {
	printf("Lane code: %c ", pLane->laneCode[0]);
	if (pLane->numOfGames) {
		printf("number of games: %d, best score: %d ", pLane->numOfGames, pLane->bestScore);
		for (int i = 0; i < pLane->numOfGames; i++) {
			printf("Game No. %d :\n", i + 1);
			printGameSummary(pLane->games[i]);
		}
	}
	else
		printf("no games played on this lane!");
	printf("\n");
}

void printLaneV(void* ppLane)
{
	Lane** ppL = (Lane**)ppLane;
	Lane* pL = *ppL;
	printLane(pL);
}

void freeLane(Lane* pLane)
{
	clearGameList(pLane);
	IF_NOT_NULL_FREE(pLane)
}

void freeLaneV(void* ppLane)
{
	freeLane(*((Lane**)ppLane));
}

void clearGameList(Lane* pLane) {

	generalArrayFunction(pLane->games, pLane->numOfGames, sizeof(Game*), freeGameV);

	free(pLane->games);
	pLane->bestScore = 0;
	pLane->numOfGames = 0;
}

int	compareLanesByBestScore(int score1, int score2)
{
	if (score1 == score2)
		return 0;
	else if (score1 > score2)
		return 1;
	return -1;
}

int	compareLanesByCode(char c1, char c2)
{
	if (c1 == c2)
		return 0;
	else if (c1 > c2)
		return 1;
	return -1;
}

int	saveLaneToFile(Lane* pLane, FILE* fp)
{
	if (fwrite(pLane, sizeof(Lane), 1, fp) != 1)
	{
		PRINT_ERROR_STR_RETURN_0("write lane")
	}
	return 1;
}

int	loadLaneFromFile(Lane* pLane, FILE* fp)
{
	if (fread(pLane, sizeof(Lane), 1, fp) != 1)
	{
		PRINT_ERROR_STR_RETURN_0("read lane")
	}
	return 1;
}