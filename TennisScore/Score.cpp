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
		state.printScore();
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
}