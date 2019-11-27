#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

#include "Matriz.h"

const int INFINITO = 1000000000;

typedef struct
{
	int lon;
	int coste;

}tVarilla;

//devuelve si se puede hacer una varilla J con las varillas de 1 a i
bool sePuede(int N, int L, const vector<tVarilla> &varillas) //i = varillas de la 1 a la i; j = tam 
{
	Matriz<bool> posible(N + 1, L + 1, 0);
	//a.
	//Caso base
	//j = 0 -> sePuede(i,0) = true
	//i = 0 -> sePuede(0,j) = false
	for (int j = 0; j < L + 1; j++)
	{
		posible[0][j] = false;
	}
	for (int i = 0; i < N + 1; i++)
	{
		posible[i][0] = true;
	}
	//no usamos varilla i si Li > j  -> sePuede(i-1,j)
	//usamos varilla i si Li <= j    -> sePuede(i-1,j-Li) || sePuede(i-1,j) ==
	//== Se puede forar varilla de con Li o Si llega justo al J
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= L; ++j)
		{
			if (varillas[i].lon > j)
			{
				posible[i][j] = posible[i - 1][j];
			}
			else
			{
				posible[i][j] = (posible[i - 1][j] || posible[i - 1][j - varillas[i].lon]);
			}
		}
	}

	

	return posible[N][L];
}

int formas(int N, int L, const vector<tVarilla> &varillas)
{
	Matriz<int> posible(N + 1, L + 1, 0);
	//b.
	//Caso Base
	//j = 0 -> formas(i,0) = 1;
	//i = 0 -> formas(0,j) = 0;
	for (int j = 0; j < L + 1; j++)
	{
		posible[0][j] = 0;
	}
	for (int i = 0; i < N + 1; i++)
	{
		posible[i][0] = 1;
	}

	//formas(i,j) numero de formas de hacer barra de tam J usando varillas de la 1 a la i
	//formas(i-1, j) si Li > j
	//formas(i-1, j-Li) + formas(i-1, j) si Li <= j
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= L; ++j)
		{
			if (varillas[i].lon > j)
			{
				posible[i][j] = posible[i - 1][j];
			}
			else
			{
				posible[i][j] = posible[i - 1][j] + posible[i - 1][j - varillas[i].lon];
			}
		}
	}

	return posible[N][L];
}

int minVar(int N, int L, const vector<tVarilla> &varillas)
{
	//c.
	Matriz<int> posible(N + 1, L + 1, 0);
	//Caso base
	//j = 0 -> minVar (i,0) = 0;
	//i = 0 -> minVar (0,j) = INFINITO j>0
	for (int j = 0; j < L + 1; j++)
	{
		posible[0][j] = INFINITO;
	}
	for (int i = 0; i < N + 1; i++)
	{
		posible[i][0] = 0;
	}

	//minVar (i-1, j) si Li > j
	//min (minVar (i-1, j-Li) + 1, minVar(i-1, j)) si Li <= j
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= L; ++j)
		{
			if (varillas[i].lon > j)
			{
				posible[i][j] = posible[i - 1][j];
			}
			else
			{
				posible[i][j] = min(posible[i - 1][j], (1 + posible[i - 1][j - varillas[i].lon] ));
			}
		}
	}

	return posible[N][L];
}

int minCoste(int N, int L, const vector<tVarilla> &varillas)
{
	//d. 
	Matriz<int> posible(N + 1, L + 1, 0);

	//Caso base
	//j = 0 -> minCoste (i,0) = 0;
	//i = 0 -> minCoste (0,j) = INFINITO j>0
	for (int j = 0; j < L + 1; j++)
	{
		posible[0][j] = INFINITO;
	}
	for (int i = 0; i < N + 1; i++)
	{
		posible[i][0] = 0;
	}

	//minCoste (i-1, j) si Li > j
	//min (minCoste (i-1, j-Li) + Ci, minVar(i-1, j)) si Li <= j
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= L; ++j)
		{
			if (varillas[i].lon > j)
			{
				posible[i][j] = posible[i - 1][j];
			}
			else
			{
				posible[i][j] = min(posible[i - 1][j], posible[i - 1][j - varillas[i].lon] + varillas[i].coste);
			}
		}
	}

	return posible[N][L];
}


bool resuelveCaso()
{
	int N, L;

	cin >> N >> L;

	if (!cin)
	{
		return false;
	}
	//Cargamos varillas
	vector<tVarilla> varillas(N+1); //n+1

	for (int i = 0; i < N; i++)
	{
		int tipo, cost;
		tVarilla var;
		cin >> tipo >> cost;
		var.lon = tipo;
		var.coste = cost;
		varillas[i + 1] = var;
	}
	
	//calculamos el numero de compañeros que necesitamos y lo sacamos por pantalla
	if (sePuede(N, L, varillas))
	{
		cout << "SI " << formas(N, L, varillas) << " " << minVar(N, L, varillas) << " " << minCoste(N, L, varillas) << "\n";
	}
	else
	{
		cout << "NO\n";
	}

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