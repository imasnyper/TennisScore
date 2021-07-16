#include "GameState.h"
#include "Athlete.h"

bool Athlete::matchWon;

GameState::GameState()
{
	athleteLeft = Athlete("Left");
	athleteRight = Athlete("Right");
	deuce = false;
	matchScore = MatchScore_T{};
}

GameState::GameState(Athlete& left, Athlete& right)
{
	athleteLeft = left;
	athleteRight = right;
	deuce = false;
	matchScore = MatchScore_T{};
}

void GameState::_point(Athlete& pointWinner, Athlete& pointLoser)
{
	if (tieBreak)
	{
		pointWinner.increaseTiebreakPoints();

		int tiebreakDifference = static_cast<int>(pointWinner.getTiebreakPoints()) - static_cast<int>(pointLoser.getTiebreakPoints());
		if (pointWinner.getTiebreakPoints() >= 7 && tiebreakDifference > 1)
		{
			athleteLeft.setTiebreakSetPoints(setNumber, athleteLeft.getTiebreakPoints());
			athleteRight.setTiebreakSetPoints(setNumber, athleteRight.getTiebreakPoints());
			_winGame(pointWinner, pointLoser);			
		}

		Athlete* setPoint = calculateTiebreakSetPoint();
		if (setPoint)
			setSetPoint(setPoint);
	}
	else if (!deuce && pointWinner.getPoints() == 3)
	{
		_winGame(pointWinner, pointLoser);
	}
	else if (deuce && pointWinner.getAdvantage())
	{
		_winGame(pointWinner, pointLoser);
		updateDeuce();
	}
	else if (deuce && !pointWinner.getAdvantage() && !pointLoser.getAdvantage())
	{
		pointWinner.flipAdvantage();
		setGamePoint(&pointWinner);
	}
	else if (deuce && !pointWinner.getAdvantage() && pointLoser.getAdvantage())
	{
		pointLoser.flipAdvantage();
	}
	else if (!deuce)
	{
		pointWinner.increasePoints();
		updateDeuce();

		calculateGameSetMatchPoint();
	}
}

void GameState::_winGame(Athlete& gameWinner, Athlete& gameLoser)
{
	this->gameWinner = &gameWinner;
	this->gamePoint = nullptr;

	gameWinner.newGame();
	gameLoser.newGame();
	

	if (tieBreak)
	{
		gameWinner.increaseGames();
		_winSet(gameWinner, gameLoser);
	}
	else if (gameWinner.getGames() == 5 && gameLoser.getGames() == 6)
	{
		gameWinner.increaseGames();
		tieBreak = true;
	}
	else if (gameWinner.getGames() >= 5 && gameWinner.getGames() - gameLoser.getGames() > 0)
	{
		if (gameWinner.getGames() <= 5)
			gameWinner.increaseGames();
		_winSet(gameWinner, gameLoser);
	}

	else if (gameWinner.getGames() <= 6)
	{
		gameWinner.increaseGames();
	}
}

void GameState::_winSet(Athlete& setWinner, Athlete& setLoser)
{
	this->setPoint = nullptr;
	this->setWinner = &setWinner;
	incrementSetNumber();

	tieBreak = false;
	addSetToMatch(CurrentSetScore_T{athleteLeft.getGames(), athleteRight.getGames()});

	setWinner.newSet();
	setLoser.newSet();

	if (setWinner.getSets() == 2)
	{
		setWinner.increaseSets();
		Athlete::matchWon = true;
		setWinner.winMatch();
	}
	else
	{
		setWinner.increaseSets();
	}
}

void GameState::leftPoint()
{
	_point(athleteLeft, athleteRight);
}

void GameState::rightPoint()
{
	_point(athleteRight, athleteLeft);
}

void GameState::printScore()
{
	vector<size_t> leftSetGames, rightSetGames;
	for (size_t i = 0; i < matchScore.size(); i++)
	{
		leftSetGames.push_back(matchScore.at(i).first);
		rightSetGames.push_back(matchScore.at(i).second);
	}

	athleteLeft.printMatchScore(leftSetGames, tieBreak);
	athleteRight.printMatchScore(rightSetGames, tieBreak);
}

Athlete GameState::getAthleteLeft()
{
	return athleteLeft;
}

Athlete GameState::getAthleteRight()
{
	return athleteRight;
}

void GameState::updateDeuce()
{
	deuce = athleteLeft.getPoints() == 3 && athleteRight.getPoints() == 3;
}

void GameState::addSetToMatch(CurrentSetScore_T currentSet)
{
	matchScore.push_back(currentSet);
}

bool GameState::matchWon()
{
	return athleteLeft.getMatch() || athleteRight.getMatch();
}

Athlete* GameState::getDeuceAdvantage()
{
	if (deuce)
	{
		if (athleteRight.getAdvantage())
			return &athleteRight;
		if (athleteLeft.getAdvantage())
			return &athleteLeft;
	}
	return nullptr;
}

bool GameState::getDeuce()
{
	return deuce;
}

bool GameState::getTiebreak()
{
	return tieBreak;
}

void* GameState::getGameWinner(Athlete& winner)
{
	if (gameWinner)
	{
		winner = *gameWinner;
		gameWinner = nullptr;
		return &winner;
	}
	return nullptr;
}

void* GameState::getSetWinner(Athlete& winner)
{
	if (setWinner)
	{
		winner = *setWinner;
		setWinner = nullptr;
		return &winner;
	}
	return nullptr;
}

void* GameState::getGamePoint(Athlete& athlete)
{
	if (gamePoint)
	{
		athlete = *gamePoint;
		gamePoint = nullptr;
		return &athlete;
	}
	return nullptr;
}

void* GameState::getSetPoint(Athlete& athlete)
{
	if (setPoint)
	{
		athlete = *setPoint;
		return &athlete;
	}
	return nullptr;
}

void* GameState::getMatchPoint(Athlete& athlete)
{
	if (matchPoint)
	{
		athlete = *matchPoint;
		return &athlete;
	}
	return nullptr;
}

void GameState::setGamePoint(Athlete* athlete)
{
	gamePoint = athlete;
}

void GameState::setSetPoint(Athlete* athlete)
{
	setPoint = athlete;
}

void GameState::setMatchPoint(Athlete* athlete)
{
	matchPoint = athlete;
}

Athlete* GameState::calculateTiebreakSetPoint()
{
	if (athleteLeft.getTiebreakPoints() == athleteRight.getTiebreakPoints()) {
		setPoint = nullptr;
		return nullptr;

	}

	if (athleteLeft.getTiebreakPoints() > athleteRight.getTiebreakPoints()) {
		const int tiebreakDifference = static_cast<int>(athleteLeft.getTiebreakPoints()) - 
			static_cast<int>(athleteRight.getTiebreakPoints());
		if (athleteLeft.getTiebreakPoints() >= 6 && tiebreakDifference > 0)
			return &athleteLeft;
	}

	if (athleteRight.getTiebreakPoints() > athleteLeft.getTiebreakPoints()) {
		const int tiebreakDifference = static_cast<int>(athleteRight.getTiebreakPoints()) - 
			static_cast<int>(athleteLeft.getTiebreakPoints());
		if (athleteRight.getTiebreakPoints() >= 6 && tiebreakDifference > 0)
			return &athleteRight;
	}

	return nullptr;
}

void GameState::calculateGameSetMatchPoint()
{
	if (athleteLeft.getPoints() == athleteRight.getPoints())
		gamePoint = nullptr;
	
	
	if(athleteLeft.getGames() == athleteRight.getGames())
		setPoint = nullptr;

	if(!deuce)
	{
		if(athleteLeft.getPoints() > athleteRight.getPoints())
		{
			const int gameDifference = static_cast<int>(athleteLeft.getGames()) - static_cast<int>(athleteRight.getGames());
			if(athleteLeft.getPoints() == 3)
			{
				if (athleteLeft.getSets() == 2 && athleteLeft.getGames() >= 5 && gameDifference > 0)
					setMatchPoint(&athleteLeft);
				else if (athleteLeft.getGames() >= 5 && gameDifference > 0)
					setSetPoint(&athleteLeft);
				else
					setGamePoint(&athleteLeft);
			}
		}
		else if (athleteRight.getPoints() > athleteLeft.getPoints())
		{
			const int gameDifference = static_cast<int>(athleteRight.getGames()) - static_cast<int>(athleteLeft.getGames());
			if (athleteRight.getPoints() == 3)
			{
				if (athleteRight.getSets() == 2 && athleteRight.getGames() >= 5 && gameDifference > 0)
					setMatchPoint(&athleteRight);
				else if (athleteRight.getGames() >= 5 && gameDifference > 0)
					setSetPoint(&athleteRight);
				else
					setGamePoint(&athleteRight);
			}
		}
	}
	else
	{
		gamePoint = nullptr;
		setPoint = nullptr;
		matchPoint = nullptr;
	}
}

void GameState::incrementSetNumber()
{
	setNumber += 1;
}
