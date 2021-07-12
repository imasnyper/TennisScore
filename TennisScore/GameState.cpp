#include "GameState.h"
#include "Athlete.h"

GameState::GameState() {
	athleteLeft = Athlete("Left");
	athleteRight = Athlete("Right");
	deuce = false;
	setGames = SetGamesList_T();
}

GameState::GameState(Athlete left, Athlete right) {
	athleteLeft = left;
	athleteRight = right;
	deuce = false;
	setGames = SetGamesList_T();
}

void GameState::_point(Athlete& pointWinner, Athlete& pointLoser) {
	if (!deuce && pointWinner.getPoints() == 3) {
		_winGame(pointWinner, pointLoser);
	}
	else if (deuce && pointWinner.getAdvantage()) {
		_winGame(pointWinner, pointLoser);
	}
	else if (deuce && !pointWinner.getAdvantage() && !pointLoser.getAdvantage()) {
		pointWinner.flipAdvantage();
	}
	else if (deuce && pointLoser.getAdvantage()) {
		pointLoser.flipAdvantage();
	}
	else if (!deuce) {
		pointWinner.increasePoints();
	}
}

void GameState::_winGame(Athlete& gameWinner, Athlete& gameLoser) {
	gameWinner.newGame();
	gameLoser.newGame();
	if (gameWinner.getGames() == 5 && gameLoser.getGames() <= 4) {
		_winSet(gameWinner, gameLoser);
	}
	else if (gameWinner.getGames() == 5 && gameLoser.getGames() == 5) {
		tieBreak = true;
	}
	else if (gameWinner.getGames() <= 4)
		gameWinner.increaseGames();
}

void GameState::_winSet(Athlete& setWinner, Athlete& setLoser) {
	addSetGame(
		SetGames_T{ 
			AthleteSetGames{{athleteLeft, athleteLeft.getGames()}},
			AthleteSetGames{{athleteRight, athleteRight.getGames()}}
		}
	);
	setWinner.newSet();
	setLoser.newSet();
	if (setWinner.getSets() == 2)
		setWinner.winMatch();
	else
		setWinner.increaseSets();
}

void GameState::leftPoint() {
	_point(athleteLeft, athleteRight);
}

void GameState::rightPoint() {
	_point(athleteRight, athleteLeft);
}

void GameState::printScore() {
	athleteLeft.printScore();
	athleteRight.printScore();
}

SetGamesList_T GameState::getSetGames(){
	return setGames;
}

void GameState::setSetGames(SetGamesList_T setGames) {
	this->setGames = setGames;
}

void GameState::addSetGame(SetGames_T setGame) {
	this->setGames.push_back(setGame);
}

void GameState::printSetGames() {
	for (size_t i = 0; i < setGames.size(); i++) {

	}
}