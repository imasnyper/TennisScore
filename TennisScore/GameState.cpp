#include "GameState.h"
#include "Athlete.h"

GameState::GameState() {
	athleteLeft = Athlete("Left");
	athleteRight = Athlete("Right");
	deuce = false;
	matchScore = MatchScore_T{};
}

GameState::GameState(Athlete& left, Athlete& right) {
	athleteLeft = left;
	athleteRight = right;
	deuce = false;
	matchScore = MatchScore_T{};
}

void GameState::_point(Athlete& pointWinner, Athlete& pointLoser) {
	if (tieBreak) {
		if (pointWinner.getTiebreakPoints() >= 6 and pointWinner.getTiebreakPoints() - pointLoser.getTiebreakPoints() > 1) {
			_winGame(pointWinner, pointLoser);
		}
		else
			pointWinner.increaseTiebreakPoints();
	}
	else if (!deuce && pointWinner.getPoints() == 3) {
		_winGame(pointWinner, pointLoser);
	}
	else if (deuce && pointWinner.getAdvantage()) {
		_winGame(pointWinner, pointLoser);
		updateDeuce();
	}
	else if (deuce && !pointWinner.getAdvantage() && !pointLoser.getAdvantage()) {
		cout << "Advantage " << pointWinner.name << endl;
		pointWinner.flipAdvantage();
	}
	else if (deuce && !pointWinner.getAdvantage() && pointLoser.getAdvantage()) {
		cout << "Deuce" << endl;
		pointLoser.flipAdvantage();
	}
	else if (!deuce) {
		pointWinner.increasePoints();
		updateDeuce();
	}
}

void GameState::_winGame(Athlete& gameWinner, Athlete& gameLoser) {
	gameWinner == athleteLeft ? updateCurrentSetScore(1, 0) : updateCurrentSetScore(0, 1);
	
	gameWinner.newGame();
	gameLoser.newGame();

	if (tieBreak) {
		gameWinner.increaseGames();
		_winSet(gameWinner, gameLoser);
	}
	else if (gameWinner.getGames() == 5 && gameLoser.getGames() == 6) {
		gameWinner.increaseGames();
		cout << "Tiebreak " << endl;
		tieBreak = true;
	}
	else if (gameWinner.getGames() >= 5 && gameWinner.getGames() - gameLoser.getGames() > 1) {
		if(gameWinner.getGames() <= 5)
			gameWinner.increaseGames();
		_winSet(gameWinner, gameLoser);
	}

	else if (gameWinner.getGames() <= 6) {
		cout << "Game, " << gameWinner.name << endl;
		gameWinner.increaseGames();
	}
	
}

void GameState::_winSet(Athlete& setWinner, Athlete& setLoser) {
	tieBreak = false;
	CurrentSetScore_T cs{ athleteLeft.getGames(), athleteRight.getGames() };
	matchScore.push_back(cs);
	resetCurrentSetScore();
	setWinner.newSet();
	setLoser.newSet();
	if (setWinner.getSets() == 2) {
		setWinner.increaseSets();
		setWinner.winMatch();
	}
	else {
		setWinner.increaseSets();
		cout << "Game, set, " << setWinner.name << endl;
	}
}

void GameState::leftPoint() {
	_point(athleteLeft, athleteRight);
}

void GameState::rightPoint() {
	_point(athleteRight, athleteLeft);
}

void GameState::printScore() {
	vector<size_t> leftSetGames, rightSetGames;
	for (size_t i = 0; i < matchScore.size(); i++) {
		leftSetGames.push_back(matchScore.at(i).first);
		rightSetGames.push_back(matchScore.at(i).second);
	}

	athleteLeft.printMatchScore(leftSetGames, currentSetScore.first, tieBreak);
	athleteRight.printMatchScore(rightSetGames, currentSetScore.second, tieBreak);
}

void GameState::updateCurrentSetScore(size_t leftScore, size_t rightScore)
{
	currentSetScore.first += leftScore;
	currentSetScore.second += rightScore;
}

void GameState::resetCurrentSetScore()
{
	currentSetScore.first = 0;
	currentSetScore.second = 0;
}

Athlete GameState::getAthleteLeft() {
	return athleteLeft;
}

Athlete GameState::getAthleteRight() {
	return athleteRight;
}

CurrentSetScore_T GameState::getCurrentSetScore()
{
	return currentSetScore;
}

void GameState::updateDeuce() {
	deuce = athleteLeft.getPoints() == 3 && athleteRight.getPoints() == 3;
	if (deuce)
		cout << "Deuce" << endl;
}

void GameState::addSetToMatch(CurrentSetScore_T currentSet)
{
	matchScore.push_back(currentSet);
}

bool GameState::matchWon() {
	return athleteLeft.getMatch() || athleteRight.getMatch();
}