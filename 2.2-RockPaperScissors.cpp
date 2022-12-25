#include <iostream>
#include <fstream>
#include <string>
using namespace std;


/*A = Rock
B = Paper
C = Scissors

X = LOSE
Y = DRAW
Z = WIN

Round = Shape selected (1 = rock, 2 = paper, 3 = scissors) + outcome (0 = lost, 3 = draw, 6 = win)

'A' = 65, 'B' = 66, 'C' = 67
*/

int resolver(const char& opponent, const char& end) {
	int res = 0;
	
	if (end == 'Y') {//draw
		res += 3;
		res += ((int)opponent - 64); //need equal
	}
	else if (end == 'X') { //lose
		if (opponent == 'A') res += 3; //need scissors
		else res+= (int)opponent - 65;
	}
	else { //win
		res += 6;
		if (opponent == 'C') res++; //need rock
		else res += (int)opponent - 63;
	}

	return res;
}


int main() {
	ifstream archivo("data.txt");
	char opponent, end;
	int res = 0;

	while (archivo >> opponent >> end) res += resolver(opponent, end);

	cout << res;


	return 0;
}