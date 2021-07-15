#pragma once
#include "Athlete.h"
#include "GameState.h"

void printWelcome();

void printGameInformation(GameState& state);

void getPointWinner(GameState& state);

void printMatchEnd(GameState& state);

pair<Athlete, Athlete> getAthletes();

