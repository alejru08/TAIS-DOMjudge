// Alejandro Ruiz Martin

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "bintree_eda.h"

using namespace std;

bool equilibrado(bintree<char> a, int &max)
{
	if (a.empty()) 
	{
		return true;
	}
	else 
	{
		//calcula las alturas del hijo izquierdo y derecho
		int altIz = 0, altDr = 0;
		bool aLeft = equilibrado(a.left(), altIz);
		bool aRight = equilibrado(a.right(), altDr);

		//actualiza el valor de la altura calculada
		max = std::max(altIz, altDr) + 1;

		//si los hijos están equilibrados y la diferencia de alturas está entre [0, 1] devuelve true
		return aLeft && aRight && ((altIz - altDr <= 1) && (altIz - altDr >= -1));
	}
}

bool resuelveCaso() {
	bintree<char> arbol;
	// cargar el arbol
	arbol = leerArbol('.');
	int alt = 0;
	if (equilibrado(arbol, alt))
	{
		cout << "SI\n";
	}
	else
	{
		cout << "NO\n";
	}
	

	// escribir sol

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	int numCasos;
	cin >> numCasos;

	for (int i = 0; i < numCasos; i++)
	{
		resuelveCaso();
	}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
