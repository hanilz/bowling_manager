#pragma once

#define ATTEMPTS 3
#define MAX_SCORE 10

typedef struct {
	int	attempts[ATTEMPTS];
	int finalTurnScore;
	int	isStrike;
	int	isSpare;
	int	isLastTurn;
} Turn;

void	initTurn(Turn* pTurn, int turnNum);
void	freeTurn(Turn*);
void	takeSingleTurn(Turn*);
void	takeLastTurn(Turn*, int);
void	takeNormalTurn(Turn*, int);
int		getRandomScore(int lastAttempt);
int		calculateFinalTurnScore(Turn* pTurn1, Turn* pTurn2, Turn* pTurn3);
void	printTurnAttempts(const Turn* pTurn);
int		saveTurnToFile(Turn* pTurn, FILE* fp);  // check
int		loadTurnFromFile(Turn* pTurn, FILE* fp);  // check
