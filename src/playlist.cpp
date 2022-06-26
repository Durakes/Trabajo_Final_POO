#ifndef __PLAYLIST_CPP__
#define __PLAYLIST_CPP__
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include "buscarCancion.cpp"
#include "..\include\Archivo.h"
#include "..\include\Auxiliar.h"
using namespace std;

void adicionarPlaylist(string,vector<Playlist>*,Archivo);
void listarPlaylist(string,vector<Playlist>*,Archivo);
void detallePlaylist(Playlist,vector<Playlist>*,Archivo);
void editarPlaylist(Playlist,vector<Playlist>*,Archivo);
void eliminarPlaylist(Playlist,vector<Playlist>*,Archivo);
void listarCanciones(Playlist,vector<Playlist>*,Archivo);
void eliminarCancion(Playlist,vector<Playlist>*,Archivo,vector<Cancion>*);

void menuPlaylist(string nombreUsuario)
{
	system("cls");
	int respuesta;
	Playlist objPlaylist;
	vector<Playlist> vectorPlaylist;
	Archivo archivoP(R"(..\docs\Playlists.csv)");
	archivoP.cargarDatos(objPlaylist,&vectorPlaylist);
	
	aux::cuadro(0,0,45, 13);

	aux::gotoxy(1,1);	cout << "Playlist";
	aux::gotoxy(1,3);	cout <<	"Crear una playlist ";			aux::gotoxy(25,3);	cout << "[1]";
	aux::gotoxy(1,4);	cout << "Mostrar tus playlist ";		aux::gotoxy(25,4);	cout << "[2]";
	aux::gotoxy(1,5);	cout << "Atras ";						aux::gotoxy(25,5);	cout << "[3]";
	aux::gotoxy(1,6);	cout << "Ingrese la opcion que desea > "; cin >> respuesta; cin.ignore();

	switch(respuesta)
	{
		case 1:
			adicionarPlaylist(nombreUsuario,&vectorPlaylist,archivoP);
			menuPlaylist(nombreUsuario);
			break;

        case 2:
			listarPlaylist(nombreUsuario,&vectorPlaylist,archivoP);
			menuPlaylist(nombreUsuario);
			break;

		case 3:
            system("cls");
			break;

		default: 
			aux::gotoxy(1,8);	cout << "* Ingrese una opcion correcta *" << endl;
			system("cls");
			menuPlaylist(nombreUsuario);
			break;
	}

}

void adicionarPlaylist(string nombreUsuario, vector<Playlist> *vectorPlaylist, Archivo archivoP)
{
	system("cls");
	int codigo=1;
	string nuevoNombre;
	string respuesta;

	if(vectorPlaylist->size() == 0)
	{
		codigo = 1;
	}else
	{
		codigo = vectorPlaylist->size() + 1;
	}

	aux::cuadro(0,0,50, 10);
	aux::gotoxy(1,1); cout << " Crea tu playlist " << endl;
	aux::gotoxy(1,3); cout << "* Indica el nombre para tu playlist > "; 
	aux::gotoxy(1,4); getline(cin, nuevoNombre);

	Playlist playlist(codigo,nuevoNombre,nombreUsuario);
	archivoP.grabarNuevaLinea(playlist);
	
	aux::gotoxy(1,6); 	cout << "La playlist se creo exitosamente!!!" << endl;
	aux::gotoxy(1,7);	system("pause");
}


void listarPlaylist(string nombreUsuario, vector<Playlist> *vectorPlaylist,Archivo archivoP)
{
	system("cls");
	int numero = 1;
	vector<int> codigos;
	vector<string> vectorUsuarios;
	vector<Playlist> vectorResultados;
	vector<string> vectorEstado;
	vector<Playlist> vectorFinal;

	for(Playlist playlist: vectorPlaylist[0])
	{
		vectorUsuarios.push_back(aux::aMinuscula(playlist.getUsuario()));
	}

	aux::ordenamientoRapido(&vectorUsuarios, 0, vectorUsuarios.size()-1, vectorPlaylist);
    aux::busquedaBinariaMultiple(0, vectorUsuarios.size()-1, aux::aMinuscula(nombreUsuario), vectorUsuarios, &vectorResultados, vectorPlaylist[0]);

	for(Playlist playlist: vectorResultados)
    {
        vectorEstado.push_back(playlist.getEstado());
    }

    string tipo = "true";
    aux::ordenamientoRapido(&vectorEstado, 0, vectorEstado.size()-1, &vectorResultados);
    aux::busquedaBinariaMultiple(0, vectorEstado.size()-1, tipo, vectorEstado, &vectorFinal, vectorResultados);

	for(int i = 0; i < vectorFinal.size(); i++)
	{
		aux::cuadro(0,0,60,vectorFinal.size() + 10);
		aux::gotoxy(1,1 + i);	cout << "Nro. Playlist: " << numero << "\t" << "Nombre: " << vectorFinal[i].getNombre() << endl;
		codigos.push_back(numero);
		numero++;
	}

	int respuesta;
	aux::gotoxy(1,vectorFinal.size() + 2); 	cout << "Ingrese el codigo de la playlist que desee elegir> "; cin >> respuesta; cin.ignore();
	detallePlaylist(vectorFinal[codigos[respuesta-1]-1],vectorPlaylist,archivoP);
	aux::gotoxy(1,vectorFinal.size() + 3);	system("pause");
}

void detallePlaylist(Playlist playlist, vector<Playlist>*vectorPlaylist, Archivo archivoP)
{
	system("cls");
	int respuesta;

	vector<int> codigosCanciones;
	for(Playlist playlist: vectorPlaylist[0])
	{
		codigosCanciones.push_back(playlist.getCodigo());
	}
	aux::ordenamientoRapido(&codigosCanciones, 0, codigosCanciones.size()-1, vectorPlaylist);

	aux::cuadro(0,0,60,10);
	aux::gotoxy(1,1);	cout << "Playlist: " << playlist.getNombre();
	aux::gotoxy(1,3);	cout << "Editar Playlist"; 	aux::gotoxy(20,3);	cout << "[1]";
	aux::gotoxy(1,4);	cout << "Eliminar Playlist"; aux::gotoxy(20,4);	cout << "[2]";
	aux::gotoxy(1,5);	cout << "Mostrar Canciones"; aux::gotoxy(20,5);	cout << "[3]";
	aux::gotoxy(1,6);	cout << "Ingrese la opcion que desea > "; cin >> respuesta; cin.ignore();

	switch (respuesta)
	{
		case 1:
			editarPlaylist(playlist,vectorPlaylist,archivoP);
			menuPlaylist(playlist.getUsuario());
			break;

		case 2:
			eliminarPlaylist(playlist,vectorPlaylist,archivoP);
			menuPlaylist(playlist.getUsuario());
			break;

		case 3:
			listarCanciones(playlist,vectorPlaylist,archivoP);
			//system("pause");
			//menuPlaylist(playlist.getUsuario());
			break;
		
		default:
			menuPlaylist(playlist.getUsuario());
			break;
	}
}

void editarPlaylist(Playlist playlist, vector<Playlist>*vectorPlaylist, Archivo archivoP)
{
	system("cls");
	string nuevoNombre;
	aux::cuadro(0,0,60,10);
	aux::gotoxy(1,3); 	cout << "Ingresa el nuevo nombre > "; getline(cin,nuevoNombre);

	vectorPlaylist[0][playlist.getCodigo()-1].setNombre(nuevoNombre);
	archivoP.modificarPlaylist(*vectorPlaylist);
	
	aux::gotoxy(1,6);	cout << "El registro se modifico exitosamente!!!";
	aux::gotoxy(1,7);	system("pause");
}

void eliminarPlaylist(Playlist playlist, vector<Playlist>*vectorPlaylist, Archivo archivoP)
{
	system("cls");
	string respuesta;
	aux::cuadro(0,0,60,10);
	aux::gotoxy(1,2); cout << "Seguro que desea eliminar la playlist(Si|No): "; getline(cin,respuesta);
	transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);

	if(respuesta == "si")
	{
		vectorPlaylist[0][playlist.getCodigo()-1].setEstado("false");
		archivoP.modificarPlaylist(*vectorPlaylist);
		aux::gotoxy(1,4); 	cout << "La playlist se elimino exitosamente!!!";
		aux::gotoxy(1,5);	system("pause");
	}else
	{
		aux::gotoxy(1,4); 	cout << "La playlist no fue eliminada";
		aux::gotoxy(1,5);	system("pause");
	}
}

void listarCanciones(Playlist playlist, vector<Playlist>*vectorPlaylist, Archivo archivoP)
{
	system("cls");
	Cancion objCancion;
	vector<Cancion> vectorCanciones;
	vector<Cancion> vectorCancionesPlaylist;
	Archivo archiveC(R"(..\docs\Canciones.csv)");
	archiveC.cargarDatos(objCancion,&vectorCanciones);

	int numero=1;
	int respuesta;

	vector<int> codigosCanciones;
	for(Cancion cancion: vectorCanciones)
	{
		codigosCanciones.push_back(cancion.getCodigo());
	}

	if(playlist.getCanciones().size() != 0)
	{
		for(int i=0; i < playlist.getCanciones().size(); i++)
		{
			aux::busquedaBinariaConjunta(0, vectorCanciones.size()- 1, playlist.getCanciones()[i], codigosCanciones, &vectorCancionesPlaylist, vectorCanciones);
		}

		aux::cuadro(0,0,60,vectorCancionesPlaylist.size() + 10);
		aux::gotoxy(1,1);	cout << "Lista de canciones de la playlist" << playlist.getNombre() << endl;

		for(int i = 0; i < vectorCancionesPlaylist.size(); i++)
		{
			aux::gotoxy(1,2 + i);	cout << "Nro. Cancion: " << numero << "\t" << "Nombre: " << vectorCancionesPlaylist[i].getNombre() << endl;
			numero++;
		}

		aux::gotoxy(1,vectorCancionesPlaylist.size() + 2);	cout << "Agregar canciones"; aux::gotoxy(20,vectorCancionesPlaylist.size() + 2);	cout << "[1]";
		aux::gotoxy(1,vectorCancionesPlaylist.size() + 3);	cout << "Eliminar canciones"; aux::gotoxy(20,vectorCancionesPlaylist.size() + 3);	cout << "[2]";
		aux::gotoxy(1,vectorCancionesPlaylist.size() + 4);	cout << "Atras";	aux::gotoxy(20,vectorCancionesPlaylist.size() + 4);	cout << "[3]";
		
		aux::gotoxy(1,vectorCancionesPlaylist.size() + 5);	cout << "Ingrese la opcion que desea > "; cin >> respuesta; cin.ignore();

	}
	else
	{
		aux::cuadro(0,0,60,vectorCancionesPlaylist.size() + 10);
		aux::gotoxy(1,3);	cout << "No tiene canciones en la playlist";
		aux::gotoxy(1,5);	cout << "Agregar canciones ";	aux::gotoxy(20,5); 	cout << "[1]";
		aux::gotoxy(1,6);	cout << "Volver atras ";		aux::gotoxy(20,6);	cout << "[3]";
		aux::gotoxy(1,7);	cout << "Ingrese la opcion que desea > "; cin >> respuesta; cin.ignore();
	}

	switch (respuesta)
	{
		case 1:
			system("cls");
			menuBuscarCancion(playlist.getUsuario(), to_string(playlist.getCodigo()));
			//menuPlaylist(playlist.getUsuario());
			break;
		case 2:
			eliminarCancion(playlist,vectorPlaylist,archivoP,&vectorCanciones);
			menuPlaylist(playlist.getUsuario());
			break;
		case 3:
			//menuPlaylist(playlist.getUsuario());
			break;
		default:
			listarCanciones(playlist, vectorPlaylist, archivoP);
			//exit(0);
			break;
	}
}

void eliminarCancion(Playlist playlist,vector<Playlist> *vectorPlaylist,Archivo archivoP,vector<Cancion> *vectorCanciones)
{
	system("cls");
	vector<int> codigosCanciones;
	vector<int> codigos;
	vector<Cancion> vectorCancionesPlaylist;
	int numero = 1;
	int respuesta;
	string rsp;
	for(Cancion cancion: vectorCanciones[0])
	{
		codigosCanciones.push_back(cancion.getCodigo());
	}
	
	for(int i=0; i < playlist.getCanciones().size(); i++)
	{
		aux::busquedaBinariaConjunta(0, vectorCanciones[0].size()- 1, playlist.getCanciones()[i], codigosCanciones, &vectorCancionesPlaylist, vectorCanciones[0]);
	}

	aux::cuadro(0,0,60,vectorCancionesPlaylist.size() + 13);
	aux::gotoxy(1,1);	cout << "Lista de canciones de la playlist" << playlist.getNombre() << endl;

	for(int i = 0; i < vectorCancionesPlaylist.size(); i++)
	{
		aux::gotoxy(1,3 + i);	cout << "Nro. Cancion: " << numero << "\t" << "Nombre: " << vectorCancionesPlaylist[i].getNombre() << endl;
		numero++;
		codigos.push_back(vectorCancionesPlaylist[i].getCodigo());
	}

	aux::gotoxy(1,vectorCancionesPlaylist.size() + 5); cout << "Ingrese el numero de la cancion que desea eliminar > ";	cin >> respuesta;	cin.ignore();

	aux::gotoxy(1,vectorCancionesPlaylist.size() + 6); cout << "Seguro que desea eliminar: " << vectorCanciones[0][codigos[respuesta-1]-1].getNombre() << " de playlist (SI/NO)";	getline(cin,rsp);

	transform(rsp.begin(), rsp.end(), rsp.begin(), ::tolower);
	
	if(rsp == "si")
	{
		vector<int> tempCancion = playlist.getCanciones();

		tempCancion.erase(tempCancion.begin()+(respuesta-1));
		
		vectorPlaylist[0][playlist.getCodigo()-1].setCanciones(tempCancion);
		archivoP.modificarPlaylist(*vectorPlaylist);

		aux::gotoxy(1,vectorCancionesPlaylist.size() + 8); 	cout << "La cancion se ha eliminado de la playlist" << endl;
		aux::gotoxy(1,vectorCancionesPlaylist.size() + 9);	system("pause");
	}else
	{
		aux::gotoxy(1,vectorCancionesPlaylist.size() + 8); 	cout << "La cancion no fue eliminada" << endl;
		aux::gotoxy(1,vectorCancionesPlaylist.size() + 9);	system("pause");
	}
}
#endif
