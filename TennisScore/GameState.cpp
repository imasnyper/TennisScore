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

		int tiebreakDifference = (int)pointWinner.getTiebreakPoints() - (int)pointLoser.getTiebreakPoints();
		if (pointWinner.getTiebreakPoints() >= 7 && tiebreakDifference > 1)
		{
			_winGame(pointWinner, pointLoser);
		}
		else if (pointWinner.getTiebreakPoints() >= 6 && tiebreakDifference > 0)
			setSetPoint(&pointWinner);
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

		if (!deuce && pointWinner.getPoints() == 3)
		{
			const int gameDifference = static_cast<int>(pointWinner.getGames()) - static_cast<int>(pointLoser.getGames());
			if (pointWinner.getSets() == 2)
				setMatchPoint(&pointWinner);
			else if (pointWinner.getGames() >= 5 && gameDifference > 0)
				setSetPoint(&pointWinner);
			else
				setGamePoint(&pointWinner);
		}
	}
}

void GameState::_winGame(Athlete& gameWinner, Athlete& gameLoser)
{
	this->gameWinner = &gameWinner;

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
	this->setWinner = &setWinner;

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
		setPoint = nullptr;
		return &athlete;
	}
	return nullptr;
}

void* GameState::getMatchPoint(Athlete& athlete)
{
	if (matchPoint)
	{
		athlete = *matchPoint;
		matchPoint = nullptr;
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
