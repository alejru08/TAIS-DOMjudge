// Alejandro Ruiz Martin

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;

#include "Matriz.h"

const int INF = 1000000000;

void resolver(const int &N, const int &PMax, const int &PMin, vector<int> potencia, vector<int> coste)
{
	Matriz<int> bombillas(N + 1,PMax + 1, INF); //todo a INF, primer caso base cargado
	//PMax = coste bombillas
	//PMin potencia bombillas

	//Caso base
	//j = 0 -> bombillas (i,0) = 0  i >= 0
	//i = 0 -> bombillas (0,p) = INF p > 0 
	for (int i = 0; i < N + 1; i++)
	{
		bombillas[i][0] = 0;
	}
	// bombilla(i-1, p) si P[i] > p
	// min( bombilla(i-1, p), bombilla(i, p-P[i] + C[i])) si P[i] <= p -> min( bombilla no usada, bombilla usada)
	//solucion = min(tabla[nBomb][k]) PMin <= k <= PMax
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= PMax; j++)
		{
			if (potencia[i] > j)
			{
				bombillas[i][j] = bombillas[i - 1][j];
			}
			else
			{
				bombillas[i][j] = min(bombillas[i - 1][j], bombillas[i][j - potencia[i]] + coste[i]);
			}
		}
	}

	int mini = bombillas[N][PMin];
	int miniTemp = mini;
	int pot = PMin;
	for (int i = PMin + 1; i <= PMax; i++)
	{
		mini = min(mini, bombillas[N][i]);
		if (mini != miniTemp)
		{
			pot = i;
			miniTemp = mini;
		}
	}

	//Sol

	if (mini == INF)
	{
		cout << "IMPOSIBLE\n";
	}
	else
	{
		cout << mini << " " << pot << "\n";
	}
}


bool resuelveCaso()
{
	int N, PMax, PMin;
	cin >> N >> PMax >> PMin;

	if (!cin)
	{
		return false;
	}
	//Cargamos los potencia
	vector<int> potencia(N + 1, 0);
	for (int i = 1; i <= N; i++)
	{
		int p;
		cin >> p;
		potencia[i] = p;
	}
	//Cargamos costes
	vector<int> coste(N + 1, 0);
	for (int i = 1; i <= N; i++)
	{
		int c;
		cin >> c;
		coste[i] = c;
	}
	//resolvemos
	resolver(N, PMax, PMin, potencia, coste);

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