#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main() {
	ifstream archivo("data.txt");
	string linea;
	int totalCalories = 0, maxCalories = 0;

	while (!archivo.eof()) {
		getline(archivo, linea);
		if (linea != "") {
			totalCalories += stoi(linea);
		}
		else {
			if (totalCalories > maxCalories) maxCalories = totalCalories;
			totalCalories = 0;
		}
	}
	if (totalCalories > maxCalories) maxCalories = totalCalories;
	
	cout << "Max calories: " << maxCalories;
	archivo.close();
	return 0;
}