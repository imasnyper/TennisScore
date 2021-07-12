#pragma once
#include <vector>

using namespace std;

static struct Scoring {
	vector<pair<size_t, size_t>> points{ 
		pair(0, 0), pair(1, 15), pair(2, 30), pair(3, 40) };
};