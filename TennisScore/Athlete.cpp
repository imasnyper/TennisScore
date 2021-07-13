#include "Athlete.h"
#include "Scoring.h"
#include <iomanip>

Athlete::Athlete() {
	name = "Athlete";
	points = 0, games = 0, sets = 0;
	tiebreakPoints = 0;
	advantage = false;
	match = false;
}

Athlete::Athlete(string name) {
	this->name = name;
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

void Athlete::setSets(size_t sets) {
	this->sets = sets;
}

void Athlete::newGame() {
	setPoints(0);
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

void Athlete::printScore() {
	Scoring sco;
	cout << setw(10) << name << ": ";
	cout << setw(4) << sco.points.at(points).second << "\t" << endl;
	// cout << setw(4) << games << "\t";
	// cout << setw(4) << sets << endl;
}