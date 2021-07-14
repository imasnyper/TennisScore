#include <iostream>
#include <iomanip>

#include "Utils.h"
#include "GameState.h"

using namespace std;

int main() {
	printWelcome();

	pair<Athlete, Athlete> athletes;
	athletes = getAthletes();
	GameState state{athletes.first, athletes.second};

	char pointWinner;
	while (!state.matchWon()) {
		system("CLS");		
		state.printScore();


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

		if(state.getTiebreak())
		{
			cout << "Tiebreak";
		}

		cout << endl;
		
		cout << "L if " << state.getAthleteLeft().name << " scored point, R if " << state.getAthleteRight().name << " scored point" << endl;
		
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

	system("CLS");

	state.printScore();
	
	if (state.getAthleteLeft().getMatch())
		cout << "Game, set and match, " << state.getAthleteLeft().name << endl;
	else
		cout << "Game, set and match, " << state.getAthleteLeft().name << endl;
}