#include "Athlete.h"
#include <iomanip>

#include "TerminalColors.h"

Athlete::Athlete() {
	name = "Athlete";
	serving = false;
	points = 0, games = 0, sets = 0;
	tiebreakPoints = 0;
	advantage = false;
	match = false;
}

Athlete::Athlete(string name) {
	this->name = name;
	serving = false;
	points = 0, games = 0, sets = 0;
	tiebreakPoints = 0;
	advantage = false;
	match = false;
}

bool Athlete::operator <(const Athlete& rhs) const
{
	return name < rhs.name;
}

bool Athlete::operator ==(const Athlete& rhs) const
{
	return name == rhs.name;
}

bool Athlete::operator !=(const Athlete& rhs) const
{
	return name != rhs.name;
}

bool Athlete::getServing()
{
	return serving;
}

void Athlete::setServing(bool serving)
{
	this->serving = serving;
}


size_t Athlete::getPoints() {
	return points;
}

size_t Athlete::getGames() {
	return games;
}

size_t Athlete::getSets() {
	return sets;
}

size_t Athlete::getTiebreakPoints() {
	return tiebreakPoints;
}

bool Athlete::getAdvantage() {
	return advantage;
}

bool Athlete::getMatch() {
	return match;
}

void Athlete::setPoints(size_t points) {
	this->points = points;
}

void Athlete::setGames(size_t games) {
	this->games = games;
}

void Athlete::newGame() {
	setPoints(0);
	advantage = false;
	tiebreakPoints = 0;
	serving = !serving;
}

void Athlete::newSet() {
	newGame();
	setGames(0);
}

void Athlete::increasePoints() {
	points += 1;
}

void Athlete::increaseGames() {
	games += 1;
}

void Athlete::increaseSets() {
	sets += 1;
}

void Athlete::increaseTiebreakPoints() {
	tiebreakPoints += 1;
}

void Athlete::flipAdvantage() {
	advantage = !advantage;
}

void Athlete::winMatch() {
	match = true;
}

void Athlete::printMatchScore(vector<size_t> matchScores, bool tieBreak) {
	vector<pair<size_t, size_t>> pointConversion{
		pair(0, 0), pair(1, 15), pair(2, 30), pair(3, 40) };

	Color::Modifier fg_black(Color::FG_BLACK);
	Color::Modifier bg_white(Color::BG_WHITE);
	Color::Modifier bg_default(Color::BG_DEFAULT);
	Color::Modifier fg_default(Color::FG_DEFAULT);
	Color::Modifier bg_blue(Color::BG_BLUE);
	Color::Modifier fg_white(Color::FG_WHITE);
	Color::Modifier bg_bblack(Color::BG_BBLACK);
	Color::Modifier bg_bmagenta(Color::BG_BMAGENTA);
	Color::Modifier fg_lmagenta(Color::FG_LIGHT_MAGENTA);

	if (serving)
		cout << ">";
	else
		cout << " ";
	
	// Athlete Name:
	cout << setw(10) << name << ": ";
	
	// Athlete games won in each set:
	for (size_t i = 0; i < matchScores.size(); i++) {
		cout << fg_black;
		if (i % 2 == 0)
			cout << bg_white;
		else
			cout << bg_bblack;
		cout << setw(4) << matchScores.at(i);

		if(checkTiebreakSetPoints(i) != 0)
		{
			size_t setTiebreakPoints = getTiebreakSetPoints(i);
			cout << fg_lmagenta;
			cout << setw(2) << setTiebreakPoints;
		}
	}

	// normal colors
	cout << fg_default << bg_default;

	if (!matchWon) {

		// Athlete current set games won:
		cout << setw(4) << getGames();

		// current set points color
		cout << fg_white;

		// Current set points. If set is in tiebreak, tiebreak points instead.
		if (tieBreak) {
			cout << bg_bmagenta;
			cout << setw(4) << tiebreakPoints;
		}
		else {
			cout << bg_blue;
			cout << setw(4) << pointConversion.at(points).second << "\t";
		}

		// normal colors
		cout << fg_default << bg_default;
	}
		
	// end the line
	cout << endl;
}

void Athlete::setTiebreakSetPoints(size_t setNumber, size_t tiebreakSetPointsWon)
{
	this->tiebreakSetPoints[setNumber] = tiebreakSetPointsWon;
}

size_t Athlete::checkTiebreakSetPoints(size_t set)
{
	return tiebreakSetPoints.count(set);
}


size_t Athlete::getTiebreakSetPoints(size_t set)
{
	return tiebreakSetPoints.at(set);
}
