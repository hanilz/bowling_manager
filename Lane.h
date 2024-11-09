#pragma once
#include "Game.h"

typedef struct {
	char	laneCode[1];
	Game**	games;
	int		numOfGames;
	int		bestScore;
} Lane;

int		initLane(Lane* pLane);
int		getLaneCode(Lane* pLane);
void	printLane(const Lane* pLane);
void	freeLane(Lane*);
void	freeLaneV(void* ppLane);
int		compareLanesByCode(char c1, char c2);
int		compareLanesByBestScore(int score1, int score2);
int		addGame(Lane*);
void	clearGameList(Lane*);
int		saveLaneToFile(Lane* pLane, FILE* fp);
int		loadLaneFromFile(Lane* pLane, FILE* fp);
void	printLaneV(void* val);
