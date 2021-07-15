#include "Utils.h"
#include <iomanip>

using namespace std;

void printWelcome() {
	cout << "Tennis Score" << endl;
}

pair<Athlete, Athlete> getAthletes() {
	string name;
	cout << "Enter the name of the athlete on the left." << endl;
	cin >> name;	
	Athlete a{ name };

	cout << "Enter the name of the athlete on the right." << endl;
	cin >> name;
	Athlete b{ name };

	int servingSide;
	cout << "(L)eft or (R)ight side serving?" << endl;
	cin >> servingSide;
	
	servingSide = tolower(servingSide);
	
	switch (servingSide)
	{
	case 'r':
		b.setServing(true);
		break;
	default:
		a.setServing(true);
	}

	return pair{a, b};
}

void printGameInformation(GameState& state)
{
	system("CLS");
	state.printScore();


	Athlete gamePoint, setPoint, matchPoint;
	state.getGamePoint(gamePoint);
	state.getSetPoint(setPoint);
	state.getMatchPoint(matchPoint);

	if(matchPoint != Athlete{})
	{
		if (!gamePoint.getServing())
			cout << "Break point" << endl;
		cout << "Match point " << matchPoint.name << endl;
	}
	else if (setPoint != Athlete{})
	{
		if (!setPoint.getServing())
			cout << "Break point" << endl;
		cout << "Set point " << setPoint.name << endl;
	}
	else if(gamePoint != Athlete{})
	{
		if (gamePoint.getServing())
			cout << "Game point " << gamePoint.name << endl;
		else
			cout << "Break point " << gamePoint.name << endl;
	}
	
	Athlete gameWinner, setWinner;
	state.getGameWinner(gameWinner);
	state.getSetWinner(setWinner);

	if (gameWinner != Athlete{} && setWinner != Athlete{})
		cout << "Game, set, " << gameWinner.name << endl;
	else if (gameWinner != Athlete{})
		cout << "Game, " << gameWinner.name << endl;
	else if (setWinner != Athlete{})
		cout << "Set, " << setWinner.name << endl;

	if (state.getDeuce()) {
		Athlete* deuceAdvantage = state.getDeuceAdvantage();
		if (deuceAdvantage)
			cout << "Advantage, " << deuceAdvantage->name << endl;
		else
			cout << "Deuce" << endl;
	}

	if (state.getTiebreak())
	{
		cout << "Tiebreak";
	}

	cout << endl;

	cout << "L if " << state.getAthleteLeft().name << " scored point, R if " << state.getAthleteRight().name << " scored point" << endl;
}

void getPointWinner(GameState& state)
{
	char pointWinner;

	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	
	cin >> pointWinner;
	switch (pointWinner) {
	case 'l':
		state.leftPoint();
		break;
	case 'r':
		state.rightPoint();
		break;
	}
}

void printMatchEnd(GameState& state)
{
	system("CLS");
	state.printScore();

	if (state.getAthleteLeft().getMatch())
		cout << "Game, set and match, " << state.getAthleteLeft().name << endl;
	else
		cout << "Game, set and match, " << state.getAthleteLeft().name << endl;
}
