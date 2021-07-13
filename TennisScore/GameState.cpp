#include "GameState.h"
#include "Athlete.h"

GameState::GameState() {
	athleteLeft = Athlete("Left");
	athleteRight = Athlete("Right");
	deuce = false;
	matchScore = MatchScore_T{};
}

GameState::GameState(Athlete left, Athlete right) {
	athleteLeft = left;
	athleteRight = right;
	deuce = false;
	matchScore = MatchScore_T{};
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
	gameWinner == athleteLeft ? updateCurrentSetScore(1, 0) : updateCurrentSetScore(0, 1);
	
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
	// addSetGame(
	// 	SetGames_T{ 
	// 		AthleteSetGames{{athleteLeft, athleteLeft.getGames()}},
	// 		AthleteSetGames{{athleteRight, athleteRight.getGames()}}
	// 	}
	// );
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
	// for(size_t i = 0; i < setGames.size(); i++)
	// {
	// 	cout << setGames.at(i).first[athleteLeft] << endl;
	// 	cout << setGames.at(i).first[athleteRight] << endl;
	// }
	athleteLeft.printScore();
	athleteRight.printScore();
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

CurrentSetScore_T GameState::getCurrentSetScore()
{
	return currentSetScore;
}

void GameState::addSetToMatch(CurrentSetScore_T currentSet)
{
	matchScore.push_back(currentSet);
}

MatchScore_T GameState::getMatchScore()
{
	return matchScore;
}