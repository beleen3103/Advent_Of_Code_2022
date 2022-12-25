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

int resolver(const string& rucksack1, const string& rucksack2, const string& rucksack3) {

	int i = 0, j = 0, k = 0, priority = 0;
	bool found = false;

	while (i < rucksack1.length() && !found) { //buscamos la letra que coincida
		while (j < rucksack2.length() && !found) {
			if (rucksack1[i] == rucksack2[j]) { //cuando encontremos una que coincida en los dos primeros, miramos si también lo hace en el tercero
				while (k < rucksack3.length() && !found) {
					if (rucksack1[i] == rucksack3[k]) found = true;
					k++;
				}
				k = 0;
			}
			j++;
		}
		j = 0;
		if (!found) i++;
	}

	//asignamos la prioridad
	if ((int)rucksack1[i] > 91) priority = (int)rucksack1[i] - 96; //lower case
	else priority = (int)rucksack1[i] - 38; //upper case

	return priority;
}


int main() {
	ifstream archivo("data.txt");
	string rucksack1, rucksack2, rucksack3;
	int res = 0;
	while (archivo >> rucksack1>> rucksack2 >> rucksack3) {

		res += resolver(rucksack1, rucksack2, rucksack3);
	}

	cout << res;
	archivo.close();
	return 0;
}
