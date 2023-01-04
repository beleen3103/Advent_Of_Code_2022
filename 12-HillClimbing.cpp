#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

bool valido(const vector<vector<char>>& map, const pair<int, int>& pos, const pair<int, int>& next_pos, const pair<int,int>& dst, const vector<pair<int, int>>& path, const int& fewest) {
	if (path.size() >= fewest) return false; //poda
	if (pos == next_pos) return false;
	if (abs(next_pos.first - dst.first) > fewest || abs(next_pos.second - dst.second) > fewest) return false; //queda demasiado camino como para que sea la solucion que buscamos
	if (map[pos.first][pos.second] == 'S') {
		if (map[next_pos.first][next_pos.second] != 'a' && map[next_pos.first][next_pos.second] != 'b') return false;
	}
	else if (map[next_pos.first][next_pos.second] == 'E') {
		if (map[pos.first][pos.second] != 'z' && map[pos.first][pos.second] != 'y') return false;
	}
	else if (map[next_pos.first][next_pos.second] - map[pos.first][pos.second] > 1 || map[next_pos.first][next_pos.second] - map[pos.first][pos.second] < 0) { // si la diferencia de altura no es 1 o 0 o si la siguiente es mas bajita
		return false;
	}
	if (find(path.begin(), path.end(), next_pos) != path.end()) { //si es una posicion en la que ya hemos estado
		return false;
	}
	return true;
}

void esSolucion(const vector<pair<int, int>>& path, vector<pair<int, int>>& bpath, int& sol) {
	if (path.size() < sol) {
		sol = path.size();
		bpath = path;
	}
}

void resolver(const vector<vector<char>>& map, int& fewest, const pair<int,int>& dst, vector<pair<int, int>>& best_path, vector<pair<int,int>>& path, const int& origin_x, const int& origin_y) {
	pair<int, int> past_pos = { origin_x,origin_y };
	int check[4] = { -1, 1, -1, 1 }; // posiciones que comprobar
	pair<int, int> pos; //siguiente posible paso

		//seleccionamos siguiente posicion entre las 4 posibles
	for (int i = 0; i < 4; i++ ) {			
		if (i < 2) { //eje X
			if (past_pos.first + check[i] < 0 || past_pos.first + check[i] >= map.size()) continue;
			pos = { past_pos.first + check[i],past_pos.second };
		}
		else { //eje Y
			if (past_pos.second + check[i] < 0 || past_pos.second + check[i] >= map[0].size()) continue;
			pos = { past_pos.first,past_pos.second + check[i] };
		}
		if (valido(map, past_pos, pos, dst,path, fewest)) { //comprobamos si el siguiente paso es valido
			path.push_back(pos); //añadimos la siguiente pos al path
				
			if (map[pos.first][pos.second] == 'E') esSolucion(path, best_path, fewest); //Si es la posicion 'E', comprobamos los pasos tomados hasta alli
			else resolver(map, fewest,dst,best_path, path, pos.first, pos.second);
				
			path.pop_back();
		}

	}
}


int main() {
	ifstream archivo("data.txt");
	vector<vector<char>> map;
	vector<char> aux;
	vector<pair<int, int>> path, best_path;
	string line;
	pair<int, int> dst;
	int origin_x, origin_y;
	while (getline(archivo, line)) {
		for(int i = 0; i < line.length(); i++) {
			aux.push_back(line[i]);
			if (line[i] == 'S') {
				origin_x = i;
				origin_y = map.size();
			}
			else if (line[i] == 'E') {
				dst.first = i;
				dst.second = map.size();
			}
		}
		map.push_back(aux);
		aux.clear();
	}
	//path.push_back({ origin_x,origin_y });
	int fewest = map.size() * map[0].size();
	resolver(map,fewest,dst,best_path,path, origin_x, origin_y);

	//for (int i = 0; i < best_path.size(); i++) cout << best_path[i].first << " " << best_path[i].second << endl;
	cout << fewest << endl;
	archivo.close();
	return 0;
}