#include <iostream>
#include <fstream>

using namespace std;

#include "PriorityQueue.h"


long long int minWork(PriorityQueue<long long int, std::less<long long int>> list, const int& N)
{
	//Ponemos sol a 0 por si solo hay un valor en list
	long long int sol = 0;
	//Si list contiene mas de un valor
	if (N > 1)
	{
		//calculamos el numero de sumas que vamos a realizar (N-1)
		int numSumas = N - 1; 
		long long int a = 0, b = 0;
		vector<long long int> costes; //Aqui iran los costes de las sumas

		for (int i = 0; i < numSumas; i++)
		{
			//Sacamos los dos valores con mayor prioridad, es decir, los dos mas pequeños
			a = list.top();
			list.pop();
			b = list.top();
			list.pop();
			//Añadimos en el vector de costes el coste de sumar a y b
			//Añadimos ese coste a la lista de valores
			costes.push_back(a + b);
			list.push(a + b);
		}
		//Sumamos todos los costes del vector de costes y lo guardamos en "sol"
		int numCostes = costes.size();
		for (int i = 0; i < numCostes; i++)
		{
			sol += costes.back();
			costes.pop_back();
		}
	}
	//Devolvemos el coste de las sumas, si las hay
	return sol;
}

bool resuelveCaso() 
{
	int num;
	PriorityQueue<long long int,std::less<long long int>> list;

	cin >> num;

	if (num == 0)  // salida
		return false;

	//cargamos la lista
	for (int i = 1; i < num + 1; i++)
	{
		long long int a;
		cin >> a;
		list.push(a);
	}

	//calculamos la solucion
	cout << minWork(list, num) << "\n";

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
