#include <iostream>
#include <fstream>
#include <string>
using namespace std;


/*A, X = Rock
B, Y = Paper
C, Z = Scissors

Round = Shape selected (1 = rock, 2 = paper, 3 = scissors) + outcome (0 = lost, 3 = draw, 6 = win)

'A' = 65, 'B' = 66, 'C' = 67
'X' = 88, 'Y' = 89, 'Z' = 90
*/

int resolver(const char& opponent, const char& me) {
	int res = 0;

	if ((int)me - (int)opponent == 23) res += 3; //draw
	//else if ((int)me - (int)opponent == (21 || 24)) res += 6; //win
	//if ((me == 'X' && opponent == 'A') || (me == 'Y' && opponent == 'B') || (me == 'Z' && opponent == 'C')) res += 3; //draw
	else if ((me == 'X' && opponent == 'C') || (me == 'Y' && opponent == 'A') || (me == 'Z' && opponent == 'B')) res += 6; //win

	res += ((int)me - 87);

	return res;
}


int main() {
	ifstream archivo("data.txt");
	char opponent, me;
	int res = 0;

	while (archivo >> opponent >> me) res += resolver(opponent, me);

	cout << res;


	return 0;
}