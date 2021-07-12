#pragma once
#include <iostream>

using namespace std;

class Athlete {
private:
	size_t points, games, sets;
	size_t tiebreakPoints;
	bool advantage;
	bool match;

public:
	string name;

	Athlete();

	Athlete(string name);

	size_t getPoints();

	size_t getGames();

	size_t getSets();

	size_t getTiebreakPoints();

	bool getAdvantage();

	bool getMatch();

	void setPoints(size_t points);

	void setGames(size_t games);

	void setSets(size_t sets);

	void newGame();

	void newSet();

	void increasePoints();

	void increaseGames();

	void increaseSets();

	void increaseTiebreakPoints();

	void flipAdvantage();

	void winMatch();

	void printScore();
};