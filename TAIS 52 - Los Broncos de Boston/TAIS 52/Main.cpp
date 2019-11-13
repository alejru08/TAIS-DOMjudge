#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int sol(vector<int> r, vector<int> b, const int &n)
{
	int sol = 0, cont = 0;
	//Cargamos los primeros valores y los sacamos de sus vectores
	int ri = r.back(), bi = b.back();
	r.pop_back();
	b.pop_back();

	//Mientas que los punos de los rivales sean menores a los de los Broncos
	//Y el contador sea menor al numero de puntos a comparar
	while (ri < bi && cont < n)
	{
		//Actualizamos la solucion con la resta entre la mayor puntuacion de los Broncos y la menor de los rivales
		sol += bi - ri;
		//Sacamos los siguientes puntos a comparar
		ri = r.back();
		bi = b.back();
		r.pop_back();
		b.pop_back();
		//incrementamos contador
		cont++;
	}
	//Devolvemos la maxima puntuacion posible
	return sol;
}

bool resuelveCaso()
{
	int n;
	vector<int> b;
	vector<int> r;
	cin >> n;

	if (n == 0)  // salida
		return false;
	//cargamos los vectores de rivales(r) y Broncos(b)
	for (int i = 0; i < n; i++)
	{
		int ri;
		cin >> ri;
		r.push_back(ri);
	}

	for (int i = 0; i < n; i++)
	{
		int bi;
		cin >> bi;
		b.push_back(bi);
	}
	//Ordenamos r de mayor a menor para ir sacando los elementos del final(los menores)
	sort(r.begin(), r.end(), greater<int>());
	//Ordenamos b de menor a mayor para ir sacando los elementos del final(los mayores)
	sort(b.begin(), b.end(), less<int>());

	//calculamos la maxima puntuacion posible y la mostramos por pantalla
	cout << sol(r, b, n) << "\n";

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