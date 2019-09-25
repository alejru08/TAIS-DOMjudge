// Alejandro Ruiz Martin

#include <iostream>
#include <fstream>

#include "PriorityQueue.h"

using namespace std;

typedef struct
{
	int caja;
	int tiempo;
}tCaja;



bool operator < (tCaja caja1, tCaja caja2)
{
	if (caja1.tiempo < caja2.tiempo){ return true; }
	else if (caja1.tiempo == caja2.tiempo)
	{
		if (caja1.caja < caja2.caja){ return true; }
		else{ return false; }
	}
	else{ return false; }
	
}

void clienteCaja(const int numC, int cl, PriorityQueue<tCaja, std::less<tCaja>> &cajas)
{
	for (int i = 0; i < numC; i++)
	{
		tCaja caja;
		caja.caja = i + 1;
		caja.tiempo = 0;
		cajas.push(caja);
	}

	for (int i = 0; i < cl; i++)
	{
		int time;
		tCaja caja = cajas.top();
		cajas.pop();

		cin >> time;
		caja.tiempo += time;

		cajas.push(caja);
	}

}

bool resuelveCaso()
{
	int numCajas, clientes;
	PriorityQueue<tCaja, std::less<tCaja>> cajas;
	cin >> numCajas >> clientes;

	if (numCajas == 0 && clientes == 0)  // salida
		return false;

	//asignamos cada cliente a una caja
	clienteCaja(numCajas, clientes, cajas);

	//mostramos la solucion
	cout << cajas.top().caja << endl;

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
