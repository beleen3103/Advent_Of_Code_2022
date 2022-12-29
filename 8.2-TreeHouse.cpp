#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int resolver(const vector<vector<int>>& trees) {
	int top = 0, down = 0, right = 0, left =0, idealSpot= 0, currentSpot = 0;
	int row = 0, column = 0;
	int maxHeight = -1;

	for (int i = 1; i < trees.size() - 1; i++) {//fila del arbol que estamos comprobando
		for (int j = 1; j < trees[i].size() - 1; j++) { //columna del arbol que estamos comprobando

			while (row < trees[i].size()) {// comprobamos en horizontal
				if (row < j) /*estamos a la izq*/ {
					if (trees[i][row] >= trees[i][j]) { //si es más alto que el que tomamos de referencia, no se puede ver más lejos
						maxHeight = trees[i][row];
						left = 0;
					}
					left++;
				}
				else if (row == j /*hemos llegado al arbol que estamos comprobando*/) {
					 maxHeight = trees[i][j]; //tenemos que probar por la derecha
				}
				else {//estamos a la derecha
					right++;
					if (trees[i][row] >= maxHeight) break; //hemos encontrado un arbol mas alto y por lo tanto no se ve más allá
				}
				row++;
			}
			maxHeight = -1;
			while (column < trees.size()) {
				if (column < i /*estamos encima*/) {
					if (trees[column][j] >= trees[i][j]) { //si es más alto que el que tomamos de referencia, no se puede ver más lejos
						maxHeight = trees[column][j];
						top = 0;
					}
					top++;
				}
				else if (column == i /*hemos llegado al arbol que estamos comprobando*/) {
					 maxHeight = trees[i][j]; //tenemos que probar por debajo
				}
				else {//estamos debajo
					down++;
					if (trees[column][j] >= maxHeight) break; //hemos encontrado un arbol mas alto y por lo tanto no se ve
				}
				column++;
			}
			row = 0;
			column = 0;
			maxHeight = -1;
			currentSpot = right * left * top * down;
			if (idealSpot < currentSpot) idealSpot = currentSpot;
			top = 0;
			down = 0;
			right = 0;
			left = 0;
		}
	}

	return idealSpot;
}

int main() {
	ifstream archivo("data.txt");
	vector<vector<int>> trees;
	vector<int> aux;
	string line;

	while (getline(archivo, line)) {
		for (int i = 0; i < line.length(); i++) {
			aux.push_back(line[i] - 48);
		}
		trees.push_back(aux);
		aux.clear();
	}

	cout << resolver(trees) << endl;
	archivo.close();
	return 0;
}