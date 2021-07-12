#pragma once
#include <map>
#include <vector>
#include "Athlete.h"
#include "Utils.h"

typedef map<Athlete, size_t> AthleteSetGames;
typedef pair<AthleteSetGames, AthleteSetGames> SetGames_T;
typedef vector<SetGames_T> SetGamesList_T;

class GameState {
private:
	Athlete athleteLeft, athleteRight;
	bool deuce, tieBreak;
	SetGamesList_T setGames;

	void _point(Athlete& pointWinner, Athlete& pointLoser);

	void _winGame(Athlete& gameWinner, Athlete& gameLoser);

	void _winSet(Athlete& setWinner, Athlete& setLoser);

public:
	GameState();

	GameState(Athlete left, Athlete right);

	void leftPoint();
	
	void rightPoint();

	void printScore();

	SetGamesList_T getSetGames();

	void setSetGames(SetGamesList_T setGames);

	void addSetGame(SetGames_T setGame);

	void printSetGames();
};