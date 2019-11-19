#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int sol(vector<int> M, vector<int> m, const int &n, const int &v)
{
	int sol = 0, contM = 0, contm = 0;
	
	int mayor = M.back(), menor = m.back();
	M.pop_back();
	m.pop_back();
	//sacamos pila con mas carga e incrementamos su contador
	//sacamos pila con menos carga e incrementamos (no incrementamos para poder probar el ultimo caso posible)
	contM++;

	//Mientras que haya pilas 
	while (contM + contm < n)
	{
		//Si la pila con mas carga + pila con menos carga es mayor o igual al minimo voltaje
		if (mayor + menor >= v)
		{
			//incrementamos solucion y sacamos la siguiente pila de mayor voltaje
			sol++;
			mayor = M.back();
			M.pop_back();
			contM++;
		}
		//sacamos la siguiente pila de menor voltaje e incrementamos cu contador
		menor = m.back();
		m.pop_back();
		contm++;
	}

	return sol;
}

void resuelveCaso()
{
	int N, V;
	vector<int> pilasM, pilasm;

	cin >> N >> V;

	//cargamos los vectores de rivales(r) y Broncos(b)
	for (int i = 0; i < N; i++)
	{
		int voltaje;
		cin >> voltaje;
		pilasM.push_back(voltaje);
	}
	pilasm = pilasM;
	sort(pilasM.begin(), pilasM.end(), less<int>()); //M: al final el mayor
	sort(pilasm.begin(), pilasm.end(), greater<int>()); //m: al final el menor

	//calculamos la maxima puntuacion posible y la mostramos por pantalla
	cout << sol(pilasM, pilasm, N, V) << "\n";
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