#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#include "ConjuntosDisjuntos.h"

void cargarConjuntos(ConjuntosDisjuntos &part, int M)
{
	//Mientras que uqeden grupos por formar
	while (M--)
	{
		//Introducimos el tamaño del grupo
		int tam;
		cin >> tam;
		//Si el grupo no es vacio
		if (tam > 0)
		{
			//metemos el primer valor del grupo
			int prim, otro;
			cin >> prim;
			//lo decrementamos porque el vector va de 0 a N-1 y no de 1 a N
			--prim;
			//conectamos ese valor con el resto de valores del grupo, si los hay
			for (int i = 1; i < tam; i++)
			{
				cin >> otro;
				--otro;
				part.unir(prim, otro);
			}
		}
	}
}

bool resuelveCaso()
{
	int N, M;
	 //Introducimos las N personas y los M grupos
	cin >> N >> M;
	if (!std::cin)
		return false;

	//Creamos el sistema de conjuntos con N valores sin unir
	ConjuntosDisjuntos part = ConjuntosDisjuntos(N);
	//Unimos esos valores y los juntamos en M grupos
	cargarConjuntos(part, M);

	//Sacamos por pantalla lo que tarda cada valor en cominarse con los valores que pueda
	cout << part.tam(0);
	for (int i = 1; i < N; i++)
	{
		cout << " " << part.tam(i);
	}

	cout << "\n";

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