#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#include "GrafoValorado.h"

class Ruta
{
public:
	Ruta(GrafoValorado<int> const& g, int origen, int ancho) :marked(g.V(), false), distTo(g.V(), false)
	{
		queue<int> q;
		//Marcamos el origen y ponemos a true en el vector de si es posible llegar "distTo"
		distTo[origen] = true;
		marked[origen] = true;
		q.push(origen);

		//mientras la cola no este vacia
		while (!q.empty())
		{
			//extraemos el primer vertive de la cola
			int v = q.front();
			q.pop();
			//recorremos sus adyacentes
			for (Arista<int> a : g.ady(v))
			{
				int w = a.otro(v); //el otro vertice del camino a
				int val = a.valor(); //el valor del camino a (el ancho del camino a)
				//si no esta marcado
				if (!marked[w])
				{
					//si su valor es mayor o igual al ancho minimo necesario 
					if (val >= ancho)
					{
						//se marca
						marked[w] = true;
						//es posible camino y se añade a la cola para seguir trazando la ruta
						distTo[w] = true;
						q.push(w);
					}
					//si su valor es menor al ancho minimo necesario
					else
					{
						// el camino no es posible y se deja de buscar rutas por ese vertice
						distTo[w] = false;
					}
				}
			}
		}
	}

	//Devuelve si hay un camino posible desde el origen hasta el destino respetando la anchura minima
	bool sol(const int &destino){ return distTo[destino]; }

private:
	vector<bool> marked; //vector que guarda los vertices por los que vamos pasando
	vector<bool> distTo; //Vector que guarda si hay una ruta desde el origen hasta ese vertice
};

void cargarGrafo(GrafoValorado<int> &g, const int &E)
{
	for (int i = 0; i < E; i++)
	{
		int v1, v2, valor;
		cin >> v1 >> v2 >> valor;
		Arista<int> a = Arista<int>(v1 - 1, v2 - 1, valor);
		g.ponArista(a);
	}
}

bool resuelveCaso()
{
	int V, E;
	cin >> V >> E;

	if (!cin)
	{
		return false;
	}
	//Creamos el grafo valorado y lo cargamos
	GrafoValorado<int> g = GrafoValorado<int>(V);
	cargarGrafo(g, E);
	//iniciamos las consultas
	int K;
	cin >> K;
	for (int i = 0; i < K; i++)
	{
		int origen, destino, ancho;
		cin >> origen >> destino >> ancho;
		//creamos las rutas
		Ruta r = Ruta(g, origen - 1, ancho);
		//Vemos si hay un camino posible entre el origen y el destino y lo sacamos por pantalla
		if (r.sol(destino - 1))
		{
			cout << "SI\n";
		}
		else
		{
			cout << "NO\n";
		}
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