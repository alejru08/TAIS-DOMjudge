#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#include "Grafo.h"

class NodosLejanos
{
public:
	NodosLejanos(Grafo const& g, int origen, int TTL) :marked(g.V(), false), distTo(g.V())
	{
		//calulamos las distancias entre nodos desde el origen
		bfs(g, origen);
		//inicializamos los nodos que se encunetran en el rango TTL al numero de nodos del grafo
		_inicializables = g.V();
		for (int i = 0; i < g.V(); i++)
		{
			//Si un nodo esta marcado y su distancia se encunetra en el rango de TTL, se resta uno
			if (marked[i] && distTo[i] <= TTL)
			{
				--_inicializables;
			}
		}
	}

	//Devuelve el numero de nodos que no estan en el rango de la TTL
	int sol(){ return _inicializables; }

private:
	vector<bool> marked;
	vector<int> distTo;
	int _inicializables;

	void bfs(Grafo const&g, int s)
	{
		//creamos la cola e inicializamos el nodo de origen a 0 de distancia y lo marcamos y metemos en la cola
		queue<int> q;
		distTo[s] = 0;
		marked[s] = true;
		q.push(s);

		//mientras la cola no este vacia
		while (!q.empty())
		{
			//extraemos el primer nodo de la cola
			int v = q.front();
			q.pop();
			//recorremos sus adyacentes
			for (int w : g.ady(v))
			{
				//si no estan marcados
				if (!marked[w])
				{
					//se marcan y se pone su distancia a la de su padre mas uno y se añade a la cola para recorrer los adyacentes de este
					distTo[w] = distTo[v] + 1;
					marked[w] = true;
					q.push(w);
				}
			}
		}
	}
	
};

void cargarGrafo(Grafo &g, int E)
{
	int n1, n2;
	for (int i = 0; i < E; i++)
	{
		cin >> n1 >> n2;
		g.ponArista(n1 - 1, n2 - 1);
	}
}

bool resuelveCaso()
{
	int N, E;
	cin >> N >> E;

	if (!cin)
	{
		return false;
	}

	Grafo g = Grafo(N);
	cargarGrafo(g, E);

	int K;
	cin >> K;

	for (int i = 0; i < K; i++)
	{
		int O, TTL;
		cin >> O >> TTL;
		NodosLejanos nl = NodosLejanos(g, O - 1, TTL);
		cout << nl.sol() << "\n";
	}
	cout << "---\n";
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