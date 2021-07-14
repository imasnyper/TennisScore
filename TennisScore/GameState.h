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
	CurrentSetScore_T currentSetScore;
	MatchScore_T matchScore;

	void _point(Athlete& pointWinner, Athlete& pointLoser);

	void _winGame(Athlete& gameWinner, Athlete& gameLoser);

	void _winSet(Athlete& setWinner, Athlete& setLoser);

public:
	GameState();

	GameState(Athlete& left, Athlete& right);

	void leftPoint();
	
	void rightPoint();

	void printScore();

	void updateCurrentSetScore(size_t leftScore, size_t rightScore);

	void resetCurrentSetScore();

	Athlete getAthleteLeft();

	Athlete getAthleteRight();

	CurrentSetScore_T getCurrentSetScore();

	void updateDeuce();

	void addSetToMatch(CurrentSetScore_T currentSet);

	bool matchWon();
};