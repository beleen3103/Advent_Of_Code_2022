#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int resolver(const vector<vector<int>>& trees) {
	int res = 0;

	bool visible;
	int row = 0, column = 0;
	int maxHeight = -1;
	for (int i = 1; i < trees.size()-1; i++) {//fila del arbol que estamos comprobando
		for (int j = 1; j < trees[i].size()-1; j++) { //columna del arbol que estamos comprobando
			visible = false;
			while (!visible && row < trees[i].size()) {// comprobamos en horizontal
				if (row < j) /*estamos a la izq*/ {
					if (trees[i][row] > maxHeight) maxHeight = trees[i][row];
				}
				else if (row == j /*hemos llegado al arbol que estamos comprobando*/) {
					if (maxHeight < trees[i][j]) {
						visible = true;
						res++;
					}
					else maxHeight = trees[i][j]; //si no se ve por la izquierda, tenemos que probar por la derecha
				}
				else {//estamos a la derecha
					if (trees[i][row] >= maxHeight) break; //hemos encontrado un arbol mas alto y por lo tanto no se ve
					else if (row == trees[i].size() - 1 && trees[i][row] < maxHeight) {
						visible = true;
						res++;
					}
				}
				row++;
			}
			maxHeight = -1;
			while (!visible && column < trees.size()) {
				if (column < i /*estamos encima*/) {
					if ( trees[column][j] > maxHeight) maxHeight =  trees[column][j];
				}
				else if (column == i /*hemos llegado al arbol que estamos comprobando*/) {
					if (maxHeight <  trees[i][j]) {
						visible = true;
						res++;
					}
					else maxHeight =  trees[i][j]; //si no se ve por la arriba, tenemos que probar por debajo
				}
				else {//estamos debajo
					if ( trees[column][j] >= maxHeight) break; //hemos encontrado un arbol mas alto y por lo tanto no se ve
					else if (column == trees.size() - 1 &&  trees[column][j] < maxHeight) {
						visible = true;
						res++;
					}
				}
				column++;
			}
			row = 0;
			column = 0;
			maxHeight = -1;
		}
	}

	return res;
}

int main() {
	ifstream archivo("data.txt");
	vector<vector<int>> trees;
	vector<int> aux;
	string line;
	int visibleTrees = 0;

	while (getline(archivo, line)) {
		for (int i = 0; i < line.length(); i++) {
			aux.push_back(line[i]-48);
		}
		trees.push_back(aux);
		aux.clear();
	}

	//numero de arboles es un extremo
	visibleTrees = (trees.size()-1) * 2 + (trees[0].size() - 1) *2;

	cout << visibleTrees << endl;

	if (trees.size() > 2 && trees[0].size() > 2) cout << visibleTrees + resolver(trees) << endl;
	else cout << visibleTrees << endl;
	archivo.close();
	return 0;
}