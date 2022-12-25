#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;


int main() {
	ifstream archivo("data.txt");
	string linea;
	bool added = false;
	int top[3], aux = 0;

	int totalCalories = 0, i = 3, maxCalories = 0;
	
	while (!archivo.eof()) {
		getline(archivo, linea);
		if (linea != "") {
			totalCalories += stoi(linea);
		}
		else {
			if (aux < 3) top[aux] = totalCalories; //primero llenamos el top 3
			else {
				if (added) {//ordenamos de mayor a menor solo si en la iteración anterior hemos cambiado el top 3	
					sort(top, top + 3, greater<int>()); 	
					added = false;
				}
				if (top[2] < totalCalories) {
					top[2] = totalCalories; //si el numero entrante es mas pequeño que el ultimo del top, se cambia			
					added = true;
				}
				totalCalories = 0;
			}			
		}
		if (aux < 3) aux++;
	}
	//Sumamos el top 3 de calorias
	for (int i = 0; i < 3; i++) {
		maxCalories += top[i];
	}
	cout << "Max calories: " << maxCalories;
	archivo.close();
	return 0;
}