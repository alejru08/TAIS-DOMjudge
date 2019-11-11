#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int sol(vector<int> a, vector<int> l, const int &N)
{
	int sol = 0;
	for (int i = 0; i < N; i++)
	{
		//le sumamos a la solucion el absoluto de la resta entre la minima altura y la minima longitud de cada vector
		sol += abs(a.back() - l.back());
		//eliminamos del vecotor esos valores que hemos usado
		a.pop_back();
		l.pop_back();
	}
	return sol;
}
	
bool resuelveCaso()
{
	int N;
	vector<int> altura;
	vector<int> longitud;
	cin >> N;

	if (N == 0)  // salida
		return false;
	//cargamos los vectores de alturas y longitudes
	for (int i = 0; i < N; i++)
	{
		int alt;
		cin >> alt;
		altura.push_back(alt);
	}

	for (int i = 0; i < N; i++)
	{
		int lon;
		cin >> lon;
		longitud.push_back(lon);
	}
	//Los ordenamos de mayor a menor para ir sacando los elementos del final(los menores)
	sort(altura.begin(), altura.end(), greater<int>());
	sort(longitud.begin(), longitud.end(), greater<int>());

	//calculamos la solucion y la mostramos por pantalla
	cout << sol(altura, longitud, N) << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}