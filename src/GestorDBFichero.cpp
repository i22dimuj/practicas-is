/*
 * GestorDBFichero.cpp
 *
 *  Created on: 18/12/2014
 *      Author: i22caboc
 */

#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <stdlib.h>
#include "Agenda.hpp"
#include "GestorDBFichero.hpp"


#define MAX 50

using namespace std;

bool GestorDBFichero::guardar(list<Contacto> aux, string nombreFichero) {
	if(aux.empty())
		return false;

	list <Contacto>:: iterator iter;
	list <string>:: iterator itert;
	list <redSocial>:: iterator iterr;
	list <direccionPostal>:: iterator iterd;

	ofstream fichero;

	//Abrimos el fichero para escribir
	fichero.open(nombreFichero.c_str(), ios::out);

	//Escribimos los contactos en el fichero
	for (iter = aux.begin(); iter != aux.end(); iter++) {
		fichero << iter->getNombre() << ","
		<< iter->getApellido1() << ","
		<< iter->getApellido2() << ","
		<< iter->getDNI() << ","
		<< iter->getEmail() << ",";

		//Lista de telefonos
		fichero << iter->getTelefono().size() << ",";	//indicamos el numero de elementos
		if (iter->getTelefono().size() == 1) {
			itert = iter->getTelefono().begin();
			fichero << *itert << ",";
		} else {
			cout << "telefonoSize = " << iter->getTelefono().size() << endl;
			for (itert = iter->getTelefono().begin(); itert != iter->getTelefono().end(); itert++)
				fichero << *itert << ",";
		}

		//Lista de redes sociales
		fichero << iter->getRedSocial().size() << ",";
		if (iter->getRedSocial().size() == 0) {
			fichero << " ";
		} else if (iter->getRedSocial().size() == 1) {
			iterr = iter->getRedSocial().begin();
			fichero << iterr->twitter << ","
			<< iterr->facebook << ","
			<< iterr->gPlus << ","
			<< iterr->url << ",";
		}

		//Lista de direcciones postales
		fichero << iter->getDireccionPostal().size() << ",";

		if (iter->getDireccionPostal().size() == 0) {
			fichero << " ";
		} else if (iter->getDireccionPostal().size() == 1) {
			iterd = iter->getDireccionPostal().begin();
			fichero << iterd->municipio << ","
			<< iterd->provincia << ","
			<< iterd->calle << ","
			<< iterd->portal << ","
			<< iterd->piso << ","
			<< iterd->puerta << ","
			<< iterd->codigoPostal << ",";
		}

		if(iter->esFavorito())
			fichero << 1 << ",";
		else
			fichero << 0 << ",";

		fichero << iter->numeroBusquedas() << "\n";
	}

	fichero << "end";
	//Cerramos el fichero
	fichero.close();

	getchar();
  return true;
}



list<Contacto> GestorDBFichero::cargar(const string &fichero) {
	ifstream file(fichero.c_str());

	if (not file.is_open()) {
		cout << "El fichero no se ha podido abrir" << endl;
		getchar();
		getchar();
	}

	int cont;
	list<Contacto> contactos;
	string nombre, apellido1, apellido2, DNI, email, num_tel,
	telefono, num_red, num_dir,	favorito, busquedas;

	while (getline(file, nombre, ',')) {
		if (nombre != "end") {
			Contacto contacto;
			redSocial redes;
			direccionPostal direcciones;

			getline(file, apellido1, ',');
			getline(file, apellido2, ',');
			getline(file, DNI, ',');
			getline(file, email, ',');

			contacto.setNombre(string(nombre));
			contacto.setApellido1(string(apellido1));
			contacto.setApellido2(string(apellido2));
			contacto.setDNI(string(DNI));
			contacto.setEmail(string(email));

			//Leemos los telefonos
			getline(file, num_tel, ',');
			cont = atoi(num_tel.c_str());
			while (cont > 0) {
				getline(file, telefono, ',');
				contacto.addTelefono(telefono);
				cont--;
				cout << flush;
			}

			//Leemos las redes sociales
			getline(file, num_red, ',');
			cont = atoi(num_red.c_str());
			for (int i = 0; i < cont; i++) {
				getline(file, redes.twitter, ',');
				getline(file, redes.facebook, ',');
				getline(file, redes.gPlus, ',');
				getline(file, redes.url, ',');;

				contacto.addRedSocial(redes);
			}

			//Leemos las direcciones postales
			getline(file, num_dir, ',');
			cont = atoi(num_dir.c_str());
			while (cont > 0) {
				getline(file, direcciones.municipio, ',');
				getline(file, direcciones.provincia, ',');
				getline(file, direcciones.calle, ',');
				getline(file, direcciones.portal, ',');
				getline(file, direcciones.piso, ',');
				getline(file, direcciones.puerta , ',');
				getline(file, direcciones.codigoPostal, ',');

				contacto.addDireccionPostal(direcciones);
				cont--;
			}

			getline(file, favorito, ',');
			cout << favorito;
			int intFavorito = atoi(favorito.c_str());
			cout << intFavorito << endl;
			cout << contacto.esFavorito() << endl;

			if(intFavorito == 1)
				contacto.cambiaFavorito();

			cout << contacto.esFavorito() << endl;;

			getline(file, busquedas, '\n');
			contacto.setFrecuente(atoi(busquedas.c_str()));

			//Insertamos el contacto en la agenda
			contactos.push_back(contacto);
		}
	}

	file.close();
	return contactos;
}
