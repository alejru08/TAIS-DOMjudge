#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

int resolver(vector<int> menor,vector<int> mayor, int pesoMax, int N)
{
	int cont = 0, viajes = 0;
	//Mientras que el numero de personas que viajan sea menor a N
	while (cont < N)
	{
		//Miramos el mayor y el menor peso
		int M = menor.back(), m = mayor.back();
		//Si la suma de el mayor peso y el menor peso es mayor al peso maximo permitido
		if (M + m > pesoMax)
		{
			//El de mayor peso ira solo, por lo que le sacamos del vector e incrementamos el numero de personas en viaje
			menor.pop_back();
			cont++;
		}
		else
		{
			//Si no, emparejamos a esas dos personas, las sacamos del vector e incrementamos en dos las personas que viajan
			menor.pop_back();
			mayor.pop_back();
			cont += 2;
		}
		//incrementamos el numero de viajes
		viajes++;
	}

	return viajes;
}

bool resuelveCaso()
{
	int pesoMax, N;
	vector<int> mayor;
	vector<int> menor;

	cin >> pesoMax >> N;

	if (!cin)
	{
		return false;
	}
	//Cargamos los vectores y los ordenamos
	for (int i = 0; i < N; i++)
	{
		int peso;
		cin >> peso;
		mayor.push_back(peso);
	}

	menor = mayor;
	sort(menor.begin(), menor.end(), less<int>()); //menor: ordenado de menor a mayor, sacaremos del final el peso mayor
	sort(mayor.begin(), mayor.end(), greater<int>()); //mayor: ordenado de mayor a menor, sacaremos del final el menor peso
	//Calculamos el resultado y lo sacamos por pantalla
	cout << resolver(menor, mayor, pesoMax, N) << "\n";

	return true;
}

int main()
{
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