//Alejandro Ruiz Martin

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;

#include "Matriz.h"

void resolver(const int &N, const int& T, const string &X, const string &Y)
{
	Matriz<int> sub(N + 1, T + 1, 0);
	//Caso base
	//j = 0 -> resolver (i,0) = 0  -> palabra j sin caracteres
	//i = 0 -> resolver (0,j) = 0  -> palabra i sin caracteres
	for (int j = 0; j < T + 1; j++)
	{
		sub[0][j] = 0;
	}
	for (int i = 0; i < N + 1; i++)
	{
		sub[i][0] = 0;
	}

	//sub devuelve el tamaño maximo de la cadena
	//sub(i-1, j-1)+1 si x[i-1] == y[j-1]
	//max(sub(i-1,j), sub(i, j-1)) si X[i-1] != Y[j-1]

	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= T; ++j)
		{
			if (X[i-1] == Y[j-1])
			{
				sub[i][j] = sub[i - 1][j-1] + 1;
			}
			else
			{
				sub[i][j] = max(sub[i - 1][j], sub[i][j - 1]);
			}
		}
	}

	//Recorremos la matriz y las palabras para ver cuales hemos elegido(basandonos en la funcion recursiva)
	int recY = T, recX = N, cont = 0;
	int letras = sub[N][T];
	string subconjunto(letras, ' ');
	//mientras no hayamos encontrado todas las letras (valor que nos devuelve sub(N, T)
	while (cont < letras) 
	{
		//Si la letra Xi es igual a Yj
		if (X[recX - 1] == Y[recY - 1])
		{
			// usamos esa letra
			subconjunto[letras - cont - 1] = X[recX-1];
			//como ese valor en la matriz viene de la diagonal, restamos uno a cada componente
			recX--;
			recY--;
			cont++;
		}
		//Si son distintas
		else
		{
			//no usamos letra
			//Si el maximo estaba en la fila i
			if (sub[recX][recY] == sub[recX - 1][recY])
			{
				recX--;
			}
			//Si el maximo estaba en la columna j
			else if (sub[recX][recY] == sub[recX][recY - 1])
			{
				recY--;
			}
		}
	}

	for (int i = 0; i < letras; i++)
	{
		cout << subconjunto[i];
	}
	cout << "\n";
}


bool resuelveCaso()
{
	string X, Y;
	//cargamos las dos palabras
	cin >> X >> Y;

	if (!cin)
	{
		return false;
	}
	//Buscamos una subsecuencia presente en ambas palabras
	resolver(X.size(), Y.size(), X, Y);

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