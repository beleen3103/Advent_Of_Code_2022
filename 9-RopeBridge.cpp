#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <set>
#include <stdlib.h>
#include <sstream>
using namespace std;


void resolver(const string& line, pair<int, int>& head, pair<int, int>& tail, set<pair<int, int>>& historyTail) {
	bool found = false, newPos = true;
	int x = -1, y = -1;

	stringstream aux(line);
	string data[3];
	int i = 0;
	while (getline(aux, data[i], (' '))) i++; //dividimos el comando por palabras

	for (int i = 0; i < stoi(data[1]); i++) {
		if (line[0] == 'U') {
			head.second++;
		}
		else if (line[0] == 'D') {
			head.second--;
		}
		else if (line[0] == 'R') {
			head.first++;
		}
		else head.first--;
	
		//comprobamos si la cola esta cerca
		if (abs(head.first - tail.first) < 2 && abs(head.second - tail.second) < 2) found = true;

		if (!found) { //si no lo esta, hay que mover la cola
			if (data[0] == "U") {
				tail.first = head.first;
				tail.second = head.second - 1;
			}
			else if (data[0] == "D") {
				tail.first = head.first;
				tail.second = head.second + 1;
			}
			else if (data[0] == "R") {
				tail.second = head.second;
				tail.first = head.first - 1;
			}
			else {
				tail.second = head.second;
				tail.first = head.first + 1;
			}

			//si la posicion es nueva, se añade
			historyTail.insert(tail);
		}
		else found = false;	
	}
}


int main() {
	ifstream archivo("data.txt");
	string line;
	set<pair<int, int>> tailHistory;
	pair<int, int> head(0,0), tail(0,0);
	tailHistory.insert(tail); //inicial
	while (getline(archivo, line)) resolver(line, head, tail, tailHistory);

	cout << tailHistory.size() << endl;

	archivo.close();
	return 0;
}