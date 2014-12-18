#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "Interfaz.hpp"
#include "Agenda.hpp"

using namespace std;

namespace agenda {

void Interfaz::iniciarAgenda()
{
	while(!menuFuncion(menuAgenda()));
}

int Interfaz::menuAgenda()
{
	int salir = 0, seleccion;


	while (salir == 0)
	{
		system("cls");
		cout << "----- Agenda -----" << endl << endl;
		cout << "Menu:" << endl;
		cout << "1) Buscar contacto" << endl;
		cout << "2) Añadir contacto" << endl;
		cout << "3) Modificar contacto" << endl;
		cout << "4) Imprimir lista de contactos" << endl;
		cout << "5) Copia de seguridad" << endl;
		cout << "6) Borrar contacto" << endl;
		cout << "7) Contactos frecuentes" << endl;
		cout << "8) Contactos favoritos" << endl;
		cout << "0) Salir" << endl << endl;
		cout << "Seleccione una opción y pulse enter: ";

		cin >> seleccion;
		if ((seleccion >= 0) || (seleccion < 5))
		{
			salir = 1;
		}
		else
		{
			cout << "Seleccione una opcion correcta (pulse cualquier tecla para continuar):";
			getchar();
		}

	}
	return seleccion;
}

bool Interfaz::menuFuncion(int opc)
{
	switch(opc)
	{
	case 1: //Buscar contacto

		break;

	case 2: //Añadir contacto

		break;

	case 3: //Modificar contacto

		break;

	case 4: //Imprimir Agenda
		imprimirAgenda();
		break;

	case 5: //Copia de seguridad

		break;

	case 6: //Borrar contacto

		break;

	case 7: //Mostrar frecuentes
		verFrecuentes();
		break;

	case 8: //Mostrar favoritos
		verFavoritos();
		break;

	case 0: //Salir
		return false;
		break;

	default:
		cout << "Ha habido un problema en menuFunion" << cout;
	}
	return true;
}

void Interfaz::imprimirAgenda()
{

}
void Interfaz::verFavoritos()
{

}
void Interfaz::verFrecuentes()
{

}

}
