#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

#include "Matriz.h"

typedef struct
{
	int prof;
	int oro;

}tCofre;

void resolver(const int &N, const int& T, const vector<tCofre> &cofres)
{
	Matriz<int> posible(N + 1, T + 1, 0);

	//Caso base
	//j = 0 -> resolver (i,0) = 0;
	//i = 0 -> resolver (0,j) = 0;
	for (int j = 0; j < T + 1; j++)
	{
		posible[0][j] = 0;
	}
	for (int i = 0; i < N + 1; i++)
	{
		posible[i][0] = 0;
	}

	//resolver (i-1, j) si Pi + 2*Pi > j
	//max (resolver (i-1, j-(Pi + 2*Pi) + Oi, resolver(i-1, j)) si Pi + 2Pi <= j
	int tiempoRecorrido;
	for (int i = 1; i <= N; ++i)
	{
		tiempoRecorrido = cofres[i].prof + 2 * cofres[i].prof;
		for (int j = 1; j <= T; ++j)
		{
			if (tiempoRecorrido > j)
			{
				posible[i][j] = posible[i - 1][j];
			}
			else
			{
				posible[i][j] = max(posible[i - 1][j], posible[i - 1][j - tiempoRecorrido] + cofres[i].oro);
			}
		}
	}

	int prof = T;
	vector<bool> cofresBuscados(N+1);
	int contCofres = 0;
	for (int i = N; i >= 1; --i) {
		if (posible[i][prof] == posible[i - 1][prof]) 
		{
			// no cogemos cofre i
			cofresBuscados[i] = false;
		}
		else 
		{ 
			// sí cogemos cofre i
			cofresBuscados[i] = true;
			prof = prof - cofres[i].prof - 2 * cofres[i].prof;
			contCofres++;
		}
	}
	
	cout << posible[N][T] << "\n";
	cout << contCofres << "\n";
	for (int i = 1; i <= N; i++)
	{
		if (cofresBuscados[i] == true)
		{
			cout << cofres[i].prof << " " << cofres[i].oro << "\n";
		}
	}
}


bool resuelveCaso()
{
	int T, N;

	cin >> T;

	if (!cin)
	{
		return false;
	}
	cin >> N;
	//Cargamos cofres
	vector<tCofre> cofres(N + 1); //n+1

	for (int i = 0; i < N; i++)
	{
		int prof, oro;
		tCofre cofre;
		cin >> prof >> oro;
		cofre.prof = prof;
		cofre.oro = oro;
		cofres[i + 1] = cofre;
	}

	//calculamos el numero de compañeros que necesitamos y lo sacamos por pantalla
	resolver(N, T, cofres);

	cout << "---\n";

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