#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#include "Grafo.h"

class Colocacion
{
public:
	Colocacion(Grafo const &g) :marked(g.V(), false), guardias(g.V()), posible(true), minGuardias(0), minGuarTemp1(0),
		minGuarTemp2(0)
	{
		for (int i = 0; i < g.V() && posible; i++)
		{
			//vamos a los vertices que no estan marcados
			if (!marked[i])
			{
				guardias[i] = true;
				minGuarTemp1++;
				posible = dfs(g, i);
				
				minGuardias += std::min(minGuarTemp1, minGuarTemp2);
				
				minGuarTemp1 = 0;
				minGuarTemp2 = 0;
			}
		}
	}

	bool esPosible(){ return posible; }

	int minGuard(){ return minGuardias; }

private:
	vector<bool> marked;
	vector<bool> guardias;
	bool posible;
	int minGuardias;
	int minGuarTemp1;
	int minGuarTemp2;

	//busqueda profunda
	bool dfs(Grafo const &g, int v)
	{
		//marcamos el vertice
		marked[v] = true;
		//miramos adyacentes
		for (int w : g.ady(v))
		{
			//Si no esta marcado
			if (!marked[w])
			{
				//Si el padre tenia guardia, este no debe tener
				guardias[w] = !guardias[v];
				if (guardias[w] == true)
				{
					minGuarTemp1++;
				}
				else
				{
					minGuarTemp2++;
				}
				//comprobar adyacentes del hijo
				if (!dfs(g, w))
				{
					return false;
				}
			}
			//Si esta mercado y los dos tienen guardia, no se cumple la postcondicion
			else if (guardias[w] == guardias[v])
			{
				return false;
			}
		}
		return true;
	}
};

void cargarGrafo(Grafo &g, const int E)
{
	for (int i = 0; i < E; i++)
	{
		int v1, v2;
		cin >> v1 >> v2;
		g.ponArista(v1 - 1, v2 - 1);
	}
}

bool resuelveCaso()
{
	int V, E;

	cin >> V;
	if (!std::cin)
		return false;

	Grafo grafo = Grafo(V);
	cin >> E;

	cargarGrafo(grafo, E);

	Colocacion colGuar = Colocacion(grafo);

	if (colGuar.esPosible())
	{
		cout << colGuar.minGuard() <<"\n";
	}
	else
	{
		cout << "IMPOSIBLE\n";
	}


	return true;
}


int main() {

	// ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// restablecimiento de cin
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("pause");
#endif
	return 0;
}