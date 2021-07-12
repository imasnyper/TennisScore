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

	getchar();
	while (!athletes.first.getMatch() && !athletes.second.getMatch()) {
		state.printScore();
		cout << "L if left scored point, R if right scored point" << endl;
		char pointWinner = getchar();
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