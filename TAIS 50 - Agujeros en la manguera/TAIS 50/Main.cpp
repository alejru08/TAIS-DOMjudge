#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int minParches(vector<int> a, const int& L)
{
	int parches = 0;
	int agujeros = a.size();
	//Cargamos el caso inicial con el rpimer parche empezando por el final
	//Sacamos el vector y ponemos parches a 1 para tapar ese agujero
	int act = a.back();
	a.pop_back();
	parches++;

	//Comprobamos cuantos agujeros puede tapar el parche
	for (int i = 1; i < agujeros; i++)
	{
		//Sacamos el siguiente elemento del final del vector
		int sig = a.back();
		a.pop_back();
		//Si la ultima posicion que podria cubrir ese parche es mayor a la pasocion del siguiente agujero 
		//el parche no cubre el agujero "sig"
		if (act - L > sig)
		{
			//El parche queda colocado, otro para el nuevo agujero y vemos cuantos podria cubrir si quedasen agujeros
			act = sig;
			parches++;
		}
	}
	//Devolvemos el numero de parches necesarios para cubrir todos los agujeros
	return parches;
}

void cargarAgujeros(vector<int> &a, const int& N)
{
	for (int i = 0; i < N; i++)
	{
		int num;
		cin >> num;
		a.push_back(num); //metemos al final del vector
	}
}

bool resuelveCaso()
{
	//N = numero de agujeros; L = longitud del parche
	int N, L;
	cin >> N >> L;

	if (!cin)
	{
		return false;
	}
	//Cargamos el vector con la posicion a la que esta cada parche
	vector<int> agujeros;
	cargarAgujeros(agujeros, N);
	//Calculamos el unmero minimo de parches que necesitaremos de longitud L
	int parches = minParches(agujeros, L);
	cout << parches << "\n";

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