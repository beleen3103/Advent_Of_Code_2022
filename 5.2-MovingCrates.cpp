#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


void resolver(vector<vector<char> >& matrix, string& line) {
	stringstream aux(line);
	string data[6];
	int i = 0;
	while (getline(aux, data[i], (' '))) i++; //dividimos el comando por palabras
	//data[1] = number of craves
	//data[3] = origin
	//data[5] = destiny

	vector<char> group(stoi(data[1]));

	//movemos los elementos
	i = 0;
	while (i < stoi(data[1])) { //guardamos todos los elementos a mover en una variable auxiliar
		group.push_back(matrix[stoi(data[3]) - 1].back());
		//matrix[stoi(data[5]) - 1].push_back(matrix[stoi(data[3]) - 1].back()); //metemos el ultimo dato del origen en el destino
		matrix[stoi(data[3]) - 1].pop_back(); //quitamos el elemento del origen
		i++;
	}
	i = 0;
	while (i < stoi(data[1])) { //pasamos todos los elementos de la variable auxiliar al destino, asi quedan todos ordenados como en el origen
		matrix[stoi(data[5]) - 1].push_back(group.back());
		group.pop_back();
		i++;
	}

}

int main() {
	ifstream archivo("data.txt");
	//char aux[3];
	string line;
	getline(archivo, line);
	const int columns = line.length() / 4 + 1; //cada columna tiene 3 char + hay un espacio entre columnas excepto en la última, por eso +1
	int j = 1, col = 0; // j recorre los caracteres a tener en cuenta, es decir, las letras
	vector<vector<char> > matrix(columns);


	while (line[1] != '1') {
		while (j < line.length()) {
			if (line[j] != ' ') matrix[col].push_back(line[j]); //si hay un elemento, se añade a su columna correspondiente
			col++;
			j += 4; //+4 para coger la siguiente letra si es que hay
		}
		col = 0;
		j = 1;
		getline(archivo, line);
	}
	getline(archivo, line); //quitamos la linea vacía entre la matriz y los comandos

	int i = 0;
	while (i < columns) { //como trabajamos con vectores, revertimos el orden de todos para trabajar siempre con la "parte de atrás" (las letras superiores de cada columna)
		reverse(matrix[i].begin(), matrix[i].end());
		i++;
	}

	//resolvemos cada comando
	while (getline(archivo, line)) resolver(matrix, line);

	i = 0;
	while (i < columns) {
		cout << matrix[i].back();
		i++;
	}

	archivo.close();
	return 0;
}