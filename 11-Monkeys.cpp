#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

class monkey {
public:
	vector<int> startingitems; //lista de items
	string op; // operacion a realizar
	int op_number, test; //operador de la operacion, numero por el que dividir al testear
	int t, f; // mono en caso true, mono en caso false

	int operation(int old) {
		int aux;
		if (this->op_number == -1) aux = old;
		else aux = this->op_number;

		if (op == "+") return old + aux;
		if (op == "*") return old * aux;
	};

	bool testing(int n) {
		return ((n % this->test) == 0);
	};
};


void inspection(vector<monkey>& monkeys, vector<int>& inspected_items) {
	int worry = 0, next_monkey = 0;
	for (int i = 0; i < 20; i++) {// 20 rondas
		for (int j = 0; j < monkeys.size(); j++) { //monos
			while (!monkeys[j].startingitems.empty()) { //items de cada mono
				worry = monkeys[j].operation(monkeys[j].startingitems[0]); //aumentamos la preocupacion
				if (monkeys[j].testing(worry / 3)) next_monkey = monkeys[j].t; //comprobamos si es divisible o no, y seleccionamos el mono al que tirarle el item
				else next_monkey = monkeys[j].f;
				monkeys[next_monkey].startingitems.push_back(worry / 3); //lanzamos el item
				monkeys[j].startingitems.erase(monkeys[j].startingitems.begin()); //lo borramos de la lista del mono actual
				inspected_items[j]++; //un item más inspeccionado
			}
		}
	}


}

int main() {
	ifstream archivo("data.txt");
	string line, item;
	int i = 0;
	string data[6];
	vector<monkey> monkeys;
	monkey* m = new monkey();
	getline(archivo, line);
	while (getline(archivo, line)) {	
		while (line[0] == ' ') line.erase(line.begin()); //quitamos los tabulados iniciales
		if (line[0] == 'm') {//nuevo mono
			monkeys.push_back(*m);
			m = new monkey();
		}
		else if (line[0] == 's') {//obtenemos la lista de items que tiene
			line = line.substr(line.find(": ") + 2, line.length() - 1); //nos quedamos solo con la lista de items
			stringstream aux(line);
			while (getline(aux, item, (','))) m->startingitems.push_back(stoi(item)); //dividimos el comando por palabras y añadimos cada item a la lista del mono
		}
		else { //dividimos el resto de lineas palabra por palabra
			stringstream aux(line);
			while (getline(aux, data[i], (' '))) i++;

			if (data[0] == "operation:") {//operation
				m->op = data[4];
				if (data[5] == "old") m->op_number = -1;
				else m->op_number = stoi(data[5]);
			}
			else if (data[0] == "test:") { //test
				m->test = stoi(data[3]);
			}
			else { //mono al que lanzar siguiente objeto en caso true o false
				if (data[1] == "true:") m->t = stoi(data[5]);
				else m->f = stoi(data[5]);
			}
			i = 0;
			data->clear();
		}

	}
	monkeys.push_back(*m);

	vector<int> inspected_items(monkeys.size(), 0);
	inspection(monkeys, inspected_items);

	sort(inspected_items.begin(), inspected_items.end(), greater<int>()); //ordenamos de mayor a menor

	cout << inspected_items[0] * inspected_items[1] << endl;

	return 0;
}