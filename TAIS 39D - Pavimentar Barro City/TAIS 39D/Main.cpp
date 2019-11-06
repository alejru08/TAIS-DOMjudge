#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

class Pavimento
{
public:
	Pavimento(GrafoValorado<int> const& g, PriorityQueue<Arista<int>> pq) :coste(0), tam(1)
	{
		//Usamos conjuntos disjuntos para comprobar que no generan ciclos
		ConjuntosDisjuntos c(g.V());
		//Mietras la cola no este vacia
		while (!pq.empty())
		{
			//Sacamos la arista de menor coste
			Arista<int> e = pq.top();
			pq.pop();
			//Cargamos los vertices que une
			int v = e.uno();
			int w = e.otro(v);
			//Si no hemos cargado esos vertices en los conjuntos como unidos, los unimos 
			if (!c.unidos(v, w))
			{
				c.unir(v, w);
				//se va actualizando el coste que suma los costes de los caminos
				coste += e.valor();
			}
			//tam es igual al numero de vertices que estan conectados
			tam = c.tam(v);
		}
		
	}

	//Devuelve el coste del camino minimo
	int sol(){ return coste; } 
	//Si el tamaño de vertices conectados es igual al numero de vertices del grafo
	//Significa que es conexo y hay solucion
	int esSolucion(int N){ return tam == N; } 

private:
	int coste;
	int tam;
};

void cargarGrafo(GrafoValorado<int> &g, PriorityQueue<Arista<int>> &pq, const int &C)
{
	for (int i = 0; i < C; i++)
	{
		int i1, i2, coste;
		cin >> i1 >> i2 >> coste;
		Arista<int> a = Arista<int>(i1 - 1, i2 - 1, coste);
		pq.push(a);
	}
}

bool resuelveCaso()
{
	int N, C;
	//Creamos una cola de prioridad que guardará las aristas ordenadas por menor coste
	PriorityQueue<Arista<int>> pq;

	cin >> N >> C;
	if (!cin)
	{
		return false;
	}

	//Creamos el grafo valorado y cargamos la cola
	GrafoValorado<int> g = GrafoValorado<int>(N);
	cargarGrafo(g, pq, C);
	//Creamos el Pavimento de menor coste
	Pavimento p(g, pq);
	//Si todos los puntos estan conectados, saca el minimo coste del camino posible
	if (p.esSolucion(g.V()))
	{
		cout << p.sol() << "\n";
	}
	else
	{
		cout << "Imposible\n";
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