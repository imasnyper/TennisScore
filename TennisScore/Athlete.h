#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Athlete {	
	bool serving;
	size_t points, games, sets;
	size_t tiebreakPoints;
	bool advantage;
	bool match;
	

public:
	string name;
	static bool matchWon;

	Athlete();

	Athlete(string name);

	bool operator <(const Athlete& rhs) const;

	bool operator ==(const Athlete& rhs) const;

	bool operator !=(const Athlete& rhs) const;

	bool getServing();

	void setServing(bool serving);

	size_t getPoints();

	size_t getGames();

	size_t getSets();

	size_t getTiebreakPoints();

	bool getAdvantage();

	bool getMatch();

	void setPoints(size_t points);

	void setGames(size_t games);

	void newGame();

	void newSet();

	void increasePoints();

	void increaseGames();

	void increaseSets();

	void increaseTiebreakPoints();

	void flipAdvantage();

	void winMatch();

	void printMatchScore(vector<size_t> matchScores, bool tieBreak);
};