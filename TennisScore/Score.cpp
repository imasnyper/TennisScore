#include "Utils.h"

using namespace std;

int main() {
	printWelcome();

	pair<Athlete, Athlete> athletes = getAthletes();
	GameState state{athletes.first, athletes.second};

	while (!state.matchWon()) {
		printGameInformation(state);
		
		getPointWinner(state);
	}

	printMatchEnd(state);
}