#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Grafo.h"

class Bipartito
{
public:
	Bipartito(Grafo const &g) :marked(g.V(), false), color(g.V()), bipartito(true)
	{
		for (int i = 0; i < g.V() && bipartito; i++)
		{
			//vamos a los vertices que no estan marcados
			if (!marked[i])
			{
				color[i] = true;
				bipartito = dfs(g, i);
			}
		}
	}

	bool esBipartito(){ return bipartito; }

private:
	vector<bool> marked;
	vector<bool> color;
	bool bipartito;

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
				//Sera del color opuesto al vertice padre
				color[w] = !color[v];
				//comprobar adyacentes del hijo
				if (!dfs(g, w))
				{
					return false;
				}
			}
			//Si esta mercado y su color es el mismo que el del padre hay un error
			else if (color[w] == color[v])
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
		g.ponArista(v1, v2);
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

	Bipartito bip = Bipartito(grafo);

	if (bip.esBipartito())
	{
		cout << "SI\n";
	}
	else
	{
		cout << "NO\n";
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