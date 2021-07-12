#include "Utils.h"

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

	return pair<Athlete, Athlete>{a, b};
}