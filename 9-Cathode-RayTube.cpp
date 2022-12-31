#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


long int resolver() {
	
	ifstream archivo("data.txt");
	string line;	
	string data[3];
	int i, it = 1, X = 1, res = 0, finInst = 0, suma =0; //suma es la operación a realizar al terminar una ejecucion. finInst es las iteraciones que quedan hasta completar la ejecucion actual
	bool fin = false;

	while (finInst != 0 || getline(archivo, line)) { //primero comprobamos que la ejecucion anterior haya terminado, y despues si quedan instrucciones por meter
		if (finInst == 0) { //si la ejecucion anterior ha terminado, cogemos la siguiente
			stringstream aux(line);
			i = 0;
			while (getline(aux, data[i], (' '))) i++; //dividimos el comando por palabras

		}

		if ((it - 20) % 40 == 0) { //comprobamos y sumamos el valor de X en las iteraciones que nos piden
			res += it * X;
		}

		if (finInst == 0) {//cuando termine la anterior ejecucion, comprobamos el nuevo tipo de operacion
			if (data[0] == "addx") { //si la nueva es un addx, comenzamos a ejecutarla (2 iteraciones)
				finInst = 2;
				suma = stoi(data[1]);
			}
			else suma = 0; //si la operacion es un noop, no operamos nada (suma = 0) y pasamos a la siguiente
		}
		
		if(finInst > 0) finInst--;
		if(finInst == 0) X += suma; // cuando se completa una instrucción, se hace la operación que corresponda
		it++;
	}
	
	return res;
}

int main() {
	
	cout << resolver() << endl;

	return 0;
}