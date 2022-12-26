#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int resolver(const string& code) {

	int ini = 0, fin = 14, check = 0; //check = caracter a comprobar
	bool found = false;
	int i = ini + 1;
	while (fin < code.length() && !found) {
		if (code[check] != code[i] && i < fin) i++; //comprobamos de 4 en 4 que los caracteres no coincidan
		else if (i == fin && check < fin) { //si ya hemos comprobado un caracter con los restantes de la ventana, pasamos al siguiente 
			check++;
			i = check + 1;
		}
		else if (check == fin) found = true; //si comrpobamos todas las combinaciones y ninguna coincide, hemos encontrado el marker
		else { //si dos caracteres coinciden, desplazamos la ventana de 4 hasta quitar 1 de los caracteres repetidos
			check++;
			ini = check;
			fin = ini + 14;
			i = ini + 1;
		}
	}
	return fin;
}

int main() {
	ifstream archivo("data.txt");
	string code;

	archivo >> code;
	int res = resolver(code);

	cout << res << endl;

	archivo.close();
	return 0;
}