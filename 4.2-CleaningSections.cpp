#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool resolver(const int& ini1, const int& ini2, const int& fin1, const int& fin2) {
	if ((ini1 < fin2 && ini2 <= fin1) || (ini2 < fin1 && ini1 <= fin2)) return true;
	else return false;
}

int main() {
	ifstream archivo("data.txt");
	char trash;
	int res = 0;
	int n1, n2, n3, n4;

	while (archivo >> n1 >> trash >> n2 >> trash >> n3 >> trash >> n4) if (resolver(n1, n3, n2, n4)) res++;

	cout << res;

	archivo.close();
	return 0;
}