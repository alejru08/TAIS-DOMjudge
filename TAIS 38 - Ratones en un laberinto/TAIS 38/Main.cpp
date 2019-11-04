#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"

const int INF = 1000000000;

class Dijkstra
{
public:
	Dijkstra(GrafoDirigidoValorado<int> const& g, int s) : distTo(g.V(), INF), pq(g.V())
	{
		//inicializamos la distancia de la salida a distancia 0 y metemos en la cola
		distTo[s] = 0;
		pq.push(s, 0);
		//Mientras que la cola no este vacía
		while (!pq.empty())
		{
			//sacamos el elemento con mayor prioridad
			int v = pq.top().elem;
			pq.pop();
			for (auto e : g.ady(v))
			{
				relax(e);
			}
		}
	}

	bool hayCamino(int v) const //Devuelve si hay camino o si el camino va al infinito
	{
		return distTo[v] != INF;
	}

	int valor(int v) const //devuelve el valor del camino
	{
		return distTo[v];
	}

private:
	vector<int> distTo;
	IndexPQ<int> pq;

	void relax(AristaDirigida<int> e)
	{
		//v = vertice origen, w = vertice destino
		int v = e.from(), w = e.to();
		//Si la distancia al destino es mayor a la del origen + valor del camino
		if (distTo[w] > distTo[v] + e.valor())
		{
			//igualamos el destino al origen + valor del camino para que sea menor
			distTo[w] = distTo[v] + e.valor();
			//actualizamos la cola
			pq.update(w, distTo[w]);
		}
	}
};

void cargarGrafo(GrafoDirigidoValorado<int> &g, const int &P)
{
	for (int i = 0; i < P; i++)
	{
		int i1, i2, coste;
		cin >> i1 >> i2 >> coste;
		AristaDirigida<int> a = AristaDirigida<int>(i1 - 1, i2 - 1, coste);
		g.ponArista(a);
	}
}

bool resuelveCaso()
{
	int N,S,T, P;
	cin >> N >> S >> T >> P;

	if (!cin)
	{
		return false;
	}
	
	GrafoDirigidoValorado<int> g = GrafoDirigidoValorado<int>(N);
	cargarGrafo(g, P);
	//Creamos el grafo inverso para hacer Dijkstra
	Dijkstra dj(g.inverso(), S - 1);
	//calculamos los ratones que llegan a la salida 
	int ratones = 0;
	for (int i = 0; i < N; i++)
	{
		//Si hay camino en i, el valor del camino es menor a T y el camino es distinto de la salida
		if (dj.hayCamino(i) && dj.valor(i) <= T && i != S - 1)
		{
			//incrementamos ratones
			ratones++;
		}
	}
	//sacamos por pantalla los ratones que llegan
	cout << ratones << "\n";
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