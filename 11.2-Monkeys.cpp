#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

class Monkey {
public:
	vector<unsigned long long int> startingItems; //lista de items
	string op; // operacion a realizar
	unsigned long long int op_number, test; //operador de la operacion, numero por el que dividir al testear
	int t, f; // mono en caso true, mono en caso false

	unsigned long long int operation(unsigned long long int old) {
		unsigned long long int aux;
		if (this->op_number == -1) aux = old;
		else aux = this->op_number;

		if (op == "+") return old + aux;
		if (op == "*") return old * aux;
	};

	bool testing(unsigned long long int n) {
		return ((n % this->test) == 0);
	};
};


void inspection(vector<Monkey>& monkeys, vector<unsigned long long int>& inspected_items, long long int common_divider) {
	unsigned long long int worry = 0;
	int next_monkey = 0;
	for (int i = 0; i < 10000; i++) {// 20 rondas
		for (int j = 0; j < monkeys.size(); j++) { //monos
			while (!monkeys[j].startingItems.empty()) { //items de cada mono
				worry = monkeys[j].operation(monkeys[j].startingItems[0]); //aumentamos la preocupacion
				if (monkeys[j].testing(worry)) next_monkey = monkeys[j].t; //comprobamos si es divisible o no, y seleccionamos el mono al que tirarle el item
				else next_monkey = monkeys[j].f;
				monkeys[next_monkey].startingItems.push_back(worry%common_divider); //lanzamos el item
				monkeys[j].startingItems.erase(monkeys[j].startingItems.begin()); //lo borramos de la lista del mono actual
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
	vector<Monkey> monkeys;
	Monkey* m = new Monkey();
	long long int common_divider = 1;
	getline(archivo, line);
	while (getline(archivo, line)) {	
		while (line[0] == ' ') line.erase(line.begin()); //quitamos los tabulados iniciales
		if (line[0] == 'M') {//nuevo mono
			monkeys.push_back(*m);
			m = new Monkey();
		}
		else if (line[0] == 'S') {//obtenemos la lista de items que tiene
			line = line.substr(line.find(": ") + 2, line.length() - 1); //nos quedamos solo con la lista de items
			stringstream aux(line);
			while (getline(aux, item, (','))) m->startingItems.push_back(stoi(item)); //dividimos el comando por palabras y añadimos cada item a la lista del mono
		}
		else { //dividimos el resto de lineas palabra por palabra
			stringstream aux(line);
			while (getline(aux, data[i], (' '))) i++;

			if (data[0] == "Operation:") {//operation
				m->op = data[4];
				if (data[5] == "old") m->op_number = -1;
				else m->op_number = stoi(data[5]);
			}
			else if (data[0] == "Test:") { //test
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

	for (int i = 0; i < monkeys.size(); i++) { //encontramos el divisor comun entre todos los numeros de test al ser primos
		common_divider *= monkeys[i].test;
	}
	vector<unsigned long long int> inspected_items(monkeys.size(), 0);
	inspection(monkeys, inspected_items, common_divider);

	sort(inspected_items.begin(), inspected_items.end(), greater<int>()); //ordenamos de mayor a menor

	cout << inspected_items[0] * inspected_items[1] << endl;

	return 0;
}