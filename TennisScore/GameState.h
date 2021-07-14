#pragma once
#include <map>
#include <vector>
#include "Athlete.h"
#include "Utils.h"

typedef pair<size_t, size_t> CurrentSetScore_T;
typedef vector<CurrentSetScore_T> MatchScore_T;

class GameState {
	Athlete athleteLeft, athleteRight;
	bool deuce, tieBreak;
	MatchScore_T matchScore;
	Athlete *gameWinner, *setWinner;

	void _point(Athlete& pointWinner, Athlete& pointLoser);

	void _winGame(Athlete& gameWinner, Athlete& gameLoser);

	void _winSet(Athlete& setWinner, Athlete& setLoser);

public:
	GameState();

	GameState(Athlete& left, Athlete& right);

	void leftPoint();
	
	void rightPoint();

	void printScore();

	Athlete getAthleteLeft();

	Athlete getAthleteRight();

	void updateDeuce();

	void addSetToMatch(CurrentSetScore_T currentSet);

	bool matchWon();

	Athlete* getDeuceAdvantage();

	bool getDeuce();

	bool getTiebreak();

	void *getGameWinner(Athlete& winner);

	void *getSetWinner(Athlete& winner);
};