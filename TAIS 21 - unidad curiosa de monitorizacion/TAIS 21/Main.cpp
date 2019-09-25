#include <iostream>
#include <fstream>

#include "PriorityQueue.h"

using namespace std;

typedef struct
{
	int id;
	int tiempo;
	int tiempoConst;
}tUsuario;



bool operator < (tUsuario user1, tUsuario user2)
{
	if (user1.tiempo < user2.tiempo){ return true; }
	else if (user1.tiempo == user2.tiempo)
	{
		if (user1.id < user2.id){ return true; }
		else{ return false; }
	}
	else{ return false; }
	
}

void cargarUsuarios(const int &numUsu, PriorityQueue<tUsuario, std::less<tUsuario>> &envios)
{
	for (int i = 0; i < numUsu; i++)
	{
		//creamos usuario
		tUsuario usuario;
		int id, tiempo;
		//asignamos valores
		cin >> id >> tiempo;
		usuario.id = id;
		usuario.tiempoConst = tiempo;
		usuario.tiempo = tiempo;
		//guardamos
		envios.push(usuario);
	}
}

void envioUsuarios(const int &numUsu, const int &numE, PriorityQueue<tUsuario, std::less<tUsuario>> envios)
{
	for (int i = 0; i < numE; i++)
	{
		//sacamos el elemento con mayor prioridad
		tUsuario usuario = envios.top();
		envios.pop();
		//mandamos envio y mostramos
		cout << usuario.id << "\n";
		//actualizamos tiempo
		usuario.tiempo += usuario.tiempoConst;
		//guardamos
		envios.push(usuario);
	}
}

bool resuelveCaso()
{
	int numUsu, numE;
	PriorityQueue<tUsuario, std::less<tUsuario>> envios;
	cin >> numUsu;

	if (numUsu == 0)  // salida
		return false;

	//añadimos a los usuarios
	cargarUsuarios(numUsu, envios);

	//cargamos el numero de envios
	cin >> numE;

	//realizamos envios y sacamos por pantalla
	envioUsuarios(numUsu, numE, envios);

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
