#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
A = 65 p->27
Z = 90 p->52
a = 97 p->1
z = 122 p->26
*/

int resolver(const string& cmp1, const string& cmp2) {

	int i = 0, j = 0, priority = 0;
	bool found = false;

	while (i < cmp1.length() && !found) { //buscamos la letra que coincida
		while (j < cmp2.length() && !found) {
			if (cmp1[i] == cmp2[j]) found = true;
			j++;
		}
		j = 0;
		if (!found) i++;
	}

	//asignamos la prioridad
	if ((int)cmp1[i] > 91) priority = (int)cmp1[i] - 96; //lower case
	else priority = (int)cmp1[i] - 38; //upper case

	return priority;
}


int main() {
	ifstream archivo("data.txt");
	string rucksack, cmp1, cmp2;
	int res = 0;
	while (archivo >> rucksack) {
		cmp1 = rucksack.substr(0, rucksack.length() / 2);
		cmp2 = rucksack.substr(rucksack.length() / 2);

		res += resolver(cmp1, cmp2);
	}
	
	cout << res;
	return 0;
}