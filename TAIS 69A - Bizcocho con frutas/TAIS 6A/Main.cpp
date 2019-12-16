//Alejandro Ruiz Martin

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;

#include "Matriz.h"

int resolver(const int &N, vector<int> trozos)
{
	Matriz<int> diasrep(N, N, 0);
	//Caso base
	//j = 0 -> diasrep (i,0) = 0  -> con 0 dias, hay cero trozos
	//i = 0 -> diasrep (0,j) = 0  -> con 0 trozos, no hay reparto

	//sub devuelve el mayor numero de días que se repite el repite sabor
	//valor = max(diasrep(i+2, j), diasrep(i, j-2), diasrep(i+1, j-1))
	//diasrep(i,j) = valor + 1 si trozos[i] == trozos[j] && (trozos[i] == 1 || trozos[i] == 2)
	//diasrep(i, i+1) = 0 son trozos consecutivos
	//i < j

	for (int d = 1; d <= N - 1; ++d)
	{
		for (int i = 0; i < N - d; ++i)
		{
			int j = i + d;
			if (j == i + 1) //no hay dos trozos iguales seguidos
			{
				diasrep[i][j] = 0;
			}
			else if (i < j)
			{
				int valor = max(diasrep[i + 2][j], diasrep[i][j - 2]);
				int suma;
				if ((trozos[i] == trozos[j]) && (trozos[i] == 2 || trozos[i] == 1))
				{
					suma = 1;
				}
				else
				{
					suma = 0;
				}
				valor = max(valor, diasrep[i + 1][j - 1] + suma);
				diasrep[i][j] = valor;
			}
		}
	}

	return diasrep[0][N-1];
}


bool resuelveCaso()
{
	int N;
	cin >> N;

	if (!cin)
	{
		return false;
	}
	//Cargamos los trozos
	vector<int> trozos(N,0);
	for (int i = 0; i < N; i++)
	{
		int sabor;
		cin >> sabor;
		trozos[i] = sabor;
	}
	//resolvemos
	cout << resolver(N, trozos) << "\n";

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