#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

class Puentes
{
public:
	Puentes(GrafoValorado<int> const& g, PriorityQueue<Arista<int>> pq) :coste(0), tam(1)
	{
		// Usamos conjuntos disjuntos para comprobar que no generan ciclos
		ConjuntosDisjuntos c(g.V());

		//mientras la cola no este vacia
		while (!pq.empty())
		{
			//extraemos el primer puente con menor coste
			Arista<int> e = pq.top();
			pq.pop();
			//Cargamos las islas que uniria
			int v = e.uno();
			int w = e.otro(v);
			//Si no hemos cargado esas islas en los conjuntos como unidos, los unimos
			//Si ya estan unidos por algun camino, no los unimos ya que gormarían un ciclo
			if (!c.unidos(v, w))
			{
				c.unir(v, w);
				//Al coste de la construccion de puentes se le suma el valor de este puente
				coste += e.valor();
			}
			//tam guarda el numero de islas unidas
			tam = c.tam(v);
		}
	}

	
	bool esSolucion(const int& N){ return tam == N; } //Devuelve si las islas unidas son iguales al numero total de islas(conexo)
	int sol(){ return coste; } //Devuelve el coste de la construccion

private:
	int coste;
	int tam;
};

void cargarPuentes(PriorityQueue<Arista<int>> &pq, const int &P)
{
	for (int i = 0; i < P; i++)
	{
		int i1, i2, coste;
		cin >> i1 >> i2 >> coste;
		Arista<int> a = Arista<int>(i1 - 1, i2 - 1, coste);
		pq.push(a);
	}
}

bool resuelveCaso()
{
	int I, P;
	PriorityQueue<Arista<int>> pq;
	cin >> I >> P;

	if (!cin)
	{
		return false;
	}
	//Creamos el grafo valorado y lo cargamos
	GrafoValorado<int> g = GrafoValorado<int>(I);
	cargarPuentes(pq, P);
	
	Puentes puentes(g, pq);

	if (puentes.esSolucion(g.V()))
	{
		cout << puentes.sol() << "\n";
	}
	else
	{
		cout << "No hay puentes suficientes\n";
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