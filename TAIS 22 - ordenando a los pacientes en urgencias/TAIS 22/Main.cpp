#include <iostream>
#include <fstream>
#include <string>
#include "PriorityQueue.h"

using namespace std;

typedef struct
{
	string nombre;
	long long int gravedad;
	int tiempoLlegada;

}tPaciente;



bool operator > (const tPaciente paciente1, const tPaciente paciente2)
{
	if (paciente1.gravedad > paciente2.gravedad){ return true; }
	else if (paciente1.gravedad == paciente2.gravedad)
	{
		if (paciente1.tiempoLlegada < paciente2.tiempoLlegada){ return true; }
		else{ return false; }
	}
	else{ return false; }

}

void gestionEventos(const int numE, PriorityQueue<tPaciente, std::greater<tPaciente>> &pacientes)
{
	int enfLibre = 0;
	char evento;
	for (int i = 0; i < numE; i++)
	{
		cin >> evento;
		if (evento == 'A')
		{
			enfLibre++;
		}
		else if (evento == 'I')
		{
			tPaciente paciente;
			string nombre;
			long long int gravedad;

			cin >> nombre >> gravedad;

			paciente.nombre = nombre;
			paciente.gravedad = gravedad;
			paciente.tiempoLlegada = i + 1;

			pacientes.push(paciente);
		}

		if ((enfLibre > 0) && !pacientes.empty())
		{
			enfLibre--;

			cout << pacientes.top().nombre << "\n";

			pacientes.pop();
		}
	}

}

bool resuelveCaso()
{
	int numEventos;
	PriorityQueue<tPaciente, std::greater<tPaciente>> pacientes;
	cin >> numEventos;

	if (numEventos == 0)  // salida
		return false;

	//gestionemos los n eventos y mostramos a los pacientes por orden de atencion
	gestionEventos(numEventos, pacientes);

	//Marcamos el fin del caso
	cout << "---\n";

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
