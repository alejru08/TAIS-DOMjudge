#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Serpientes
{
public:
	Serpientes(int N, int K, vector<int> const &saltos) :marked(N*N + 1, false), dist(N*N + 1), N(N), K(K)
	{
		//cargamos la casilla inicial
		marked[1] = true;
		queue<int> cola; 
		cola.push(1);
		dist[1] = 0;

		//mientras la cola tenga casillas
		while (!cola.empty())
		{
			//sacamos el siguiente elemento del tablero (casilla siguiente o de un salto)
			int p = cola.front(); 
			cola.pop();

			//vamos calculando las distancias segun las posibilidades del dado (1 - k)
			//En el caso de que la casilla en la que estamos más el dado no nos saque del tablero
			for (int i = 1; i <= K && p + i <= N*N; i++)
			{
				int w = p + i; //casilla a la que avanzariamos. Distancia
				//Si hay un salto en esa casilla, la siguiente casilla seria el destino del salto
				if (saltos[w] > 0)
				{
					w = saltos[w];
				}
				//Si no estaba marcado se actualiza la distancia(numeero de tiradas para llegar a esa casilla) 
				//Se marca la casilla y se encola para ver sus futuras posibilidades
				//Si la casilla en la que estamos es la ultima, hemos llegado a l ameta y salimos de la funcion
				if (!marked[w])
				{
					dist[w] = dist[p] + 1;
					if (w == N*N) return;
					marked[w] = true;
					cola.push(w);
				}

			}
		}
	}

	//Devuelve la distancia(en numero de movimientos) que hay de la casilla inicial a la final pasando por saltos
	int sol(){ return dist[N*N]; }

private:
	vector<bool> marked;
	vector<int> dist;
	int N;
	int K;
};

bool resuelveCaso()
{
	int N, K, S, E;
	cin >> N >> K >> S >> E;

	if (N == 0 && K == 0 && S == 0 && E == 0)
	{
		return false;
	}

	vector<int> saltos(N*N + 1); //1 - based

	int numSaltos = S + E;

	for(int i = 0; i < numSaltos; i++)
	{
		int o, d;
		cin >> o >> d;
		saltos[o] = d;
	}

	Serpientes s(N, K, saltos);

	cout << s.sol() << "\n";


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