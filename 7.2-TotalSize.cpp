#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

const long int spaceNeeded = 30000000;
const long int spaceAvailable = 70000000;

class Directorio {

public:
	string name; //nombre directorio
	int superior; //posicion del directorio superior en el vector "directories"
	Directorio(string n, int s) {
		this->name = n;
		this->superior = s;
	}
	vector<string> directories; //lista de los directorios que este contiene
	long int nfiles = 0; //lo que ocupa en total

};

void organizar(vector<Directorio>& directories) {
	ifstream archivo("data.txt");
	string line;
	int current = -1;
	string data[6];
	int i = 0, sup_aux = -1;
	Directorio* A = new Directorio("", -1);

	while (getline(archivo, line)) {

		stringstream aux(line);
		i = 0;
		while (getline(aux, data[i], (' '))) i++; //dividimos el comando por palabras
		//data[0] puede ser $ para los comandos, "dir", o el tamaño de un archivo


		if (data[0] == "$") { //comandos
			if (data[1] == "cd") { //nos movemos a otro directorio, que puede ser el superior ".." o uno inferior
				if (data[2] == "..") { //si es el superior, hacemos que la variable "current" señale a la posición de ese directorio y que "A" apunte a dicho objeto
					current = A->superior;
					*A = directories.at(current);
				}
				else { //si entramos en uno inferior, tenemos que crear un objeto nuevo y añadirlo a la lista
					A = new Directorio(data[2], current);
					directories.push_back(*A);
					current = directories.size() - 1;
				}
			}
			//ls solo indica que a continuación aparecerá el contenido del directorio actual, asi que no es necesario tener en cuenta dicho comando
		}
		else if (data[0] == "dir") { //si nos indican la existencia de un nuevo directorio, lo añadimos al vector de directorios contenidos en el actual
			directories.at(current).directories.push_back(data[1]);
		}
		else { //si es un archivo, sumamos lo que ocupa al peso total del directorio (nfiles) así como a los directorios superiores
			directories.at(current).nfiles += stoi(data[0]);
			sup_aux = A->superior;
			while (sup_aux != -1) { //con esto sumamos este archivo a lo que ocupan los directorios superiores
				directories.at(sup_aux).nfiles += stoi(data[0]);
				sup_aux = directories.at(sup_aux).superior;
			}
		}
	}

}

int resolver(const vector<Directorio>& directories) {
	long int currentFree, minNeeded;
	long int smallestToFree = spaceAvailable;
	//calculamos el espacio libre actual y cuánto más necesitaríamos liberar
	currentFree = spaceAvailable - directories.at(0).nfiles; //directorio "/" que contiene todos los demas y representa todo el espacio ocupado
	minNeeded = spaceNeeded - currentFree; //espacio que necesitamos liberar como mínimo

	for (auto dir : directories) { 
		if (dir.nfiles >= minNeeded && dir.nfiles < smallestToFree) smallestToFree = dir.nfiles; //si supera el mínimo necesario y es más pequeño que la actual mejor opción, nos quedamos con ese
	}
	return smallestToFree;
}

int main() {

	vector<Directorio> directories;

	organizar(directories);
	cout << resolver(directories) << endl;

	return 0;
}