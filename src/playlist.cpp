#ifndef __PLAYLIST_CPP__
#define __PLAYLIST_CPP__
#include <iostream>
#include "..\include\Archive.h"
#include <algorithm>
#include <vector>
#include <cstring>
#include<string>
#include "buscarCancion.cpp"
using namespace std;

//Prototipos
//void menuPlaylist(string);
void adicionarPlaylist(string,vector<Playlist>*,Archive);
//void agregarCancionesPlaylist();
void listarPlaylist(string,vector<Playlist>*,Archive);
void detallePlaylist(Playlist,vector<Playlist>*,Archive);
//void BuscarPlaylist();
void EditarPlaylist(Playlist,vector<Playlist>*,Archive);
void EliminarPlaylist(Playlist,vector<Playlist>*,Archive);
//void mainPlaylist();
void listarCanciones(Playlist,vector<Playlist>*,Archive);
void EliminarCancion(Playlist,vector<Playlist>*,Archive,vector<Cancion>*);

//el name es igual al username, si es igual se agrega al vector
//para mostrar, se diferencia por el codigo

void menuPlaylist(string userName){
	int respuesta;
	Playlist objPlaylist;
	vector<Playlist> vectorPlaylist;
	Archive archiveP(R"(..\docs\Playlists.csv)");
	archiveP.cargarDatos(objPlaylist,&vectorPlaylist);
	cout<<"\n";

			cout<<"Playlist\n";
			cout<<"Crear una playlist 	[1]\n";
			cout<<"Mostrar tus playlist	[2]\n";
			cout<<"Salir								[3]\n";
			cout<<"Ingrese una opcion [1-3]:" ;
			cin>>respuesta;
			cin.ignore();
// referencia = &
			switch(respuesta)
			{
				case 1 : 	system("cls");
				adicionarPlaylist(userName,&vectorPlaylist,archiveP);
				system("pause");
				menuPlaylist(userName);
				break;

	      case 2 : 	system("cls");
				listarPlaylist(userName,&vectorPlaylist,archiveP);
			  system("pause");
				menuPlaylist(userName);
				break;

				case 3 : 	system("cls");
				cout<<"GRACIAS!!!";
				system("pause");
				exit(0);
				break;

				default : cout<<"* INGRESE UN OPCION CORRECTA [1-3] *"<<endl;
			}

}

void adicionarPlaylist(string userName,vector<Playlist>*vectorPlaylist,Archive archiveP)
{
	int code=1;
	string 	name;
	string 	respuesta;

	if(vectorPlaylist->size()==0){
		code=1;
	}else{
		code=vectorPlaylist->size()+1;
	}

				cout << "Crea tu playlist "<< endl;
				cout << "* Crea un nombre para tu playlist: "; getline(cin, name);


				//Crear el objeto de la clase alumno
				Playlist playlist(code,name,userName);
				archiveP.saveNewLine(playlist);

				cout<<"La playlist se creo exitosamente!!!"<<endl;
}


void listarPlaylist(string userName,vector<Playlist>*vectorPlaylist,Archive archiveP)
{
	int numero=1;
	vector<int> codigos;
		for(int i=0; i<vectorPlaylist->size(); i++)
		{
			if(vectorPlaylist[0][i].getUsuario()==userName&&vectorPlaylist[0][i].getEstado()=="true"){
				cout << "Nro. Playlist: " << numero << "\t" << "Nombre: " << vectorPlaylist[0][i].getNombre() << endl;
				numero++;
				codigos.push_back(vectorPlaylist[0][i].getCodigo());
			}
		}
		int respuesta;
		cout<<"Ingres el codigo de la playlist que desee elegir: ";
		cin>>respuesta;
		cin.ignore();
		detallePlaylist(vectorPlaylist[0][codigos[respuesta-1]-1],vectorPlaylist,archiveP);
}

void detallePlaylist(Playlist playlist,vector<Playlist>*vectorPlaylist,Archive archiveP){
	int respuesta;
	cout<<"Playlist: "<<playlist.getNombre()<<endl;
	cout<<"Editar Playlists			[1]"<<endl;
	cout<<"Eliminar Playlists		[2]"<<endl;
	cout<<"Moatrar Canciones		[3]"<<endl;
	cout<<"Ingrese respuesta: ";
	cin>>respuesta;
	cin.ignore();
	switch (respuesta) {
		case 1:
		system("cls");
		EditarPlaylist(playlist,vectorPlaylist,archiveP);
		system("pause");
		menuPlaylist(playlist.getUsuario());
		break;
		case 2:
		system("cls");
		EliminarPlaylist(playlist,vectorPlaylist,archiveP);
		system("pause");
		menuPlaylist(playlist.getUsuario());
		break;
		case 3:
		system("cls");
		listarCanciones(playlist,vectorPlaylist,archiveP);
		system("pause");
		menuPlaylist(playlist.getUsuario());
		break;
	}
}

void EditarPlaylist(Playlist playlist,vector<Playlist>*vectorPlaylist,Archive archiveP){
	string nuevoNombre;
	cout<<"Ingresa el nuevo nombre: "<<endl;
	getline(cin,nuevoNombre);
	vectorPlaylist[0][playlist.getCodigo()-1].setNombre(nuevoNombre);
	archiveP.modificarPlaylist(*vectorPlaylist);
	cout<<"El registro se modifico exitosamente!!!";
}

void EliminarPlaylist(Playlist playlist,vector<Playlist>*vectorPlaylist,Archive archiveP){
	string respuesta;
	cout<<"Seguro que desea eliminar la playlist(Si|No): "<<endl;
	getline(cin,respuesta);
	transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);
	if(respuesta=="si"){
		vectorPlaylist[0][playlist.getCodigo()-1].setEstado("false");
		archiveP.modificarPlaylist(*vectorPlaylist);
		cout<<"El registro se elimino exitosamente!!!";
	}else{
		cout<<"La playlist no fue eliminada";
	}
}

void listarCanciones(Playlist playlist,vector<Playlist>*vectorPlaylist,Archive archiveP){
	cout<<"Lista de canciones para la playlist"<<playlist.getNombre()<<endl;
	Cancion objCancion;
	vector<Cancion> vectorCanciones;
	Archive archiveC(R"(..\docs\Canciones.csv)");
	archiveC.cargarDatos(objCancion,&vectorCanciones);
	int numero=1;
	int respuesta;
	if(playlist.getCanciones().size()!=0){
		for(int i=0; i<playlist.getCanciones().size(); i++){
			for(int k=0; k<vectorCanciones.size();k++){
				if(playlist.getCanciones()[i]==vectorCanciones[k].getCodigo()){
					cout << numero << "\t" << "Nombre: " << vectorCanciones[k].getNombre() << "\t" << "Artista: " << vectorCanciones[k].getAutor() << endl;
					numero++;
					break;
				}
			}
		}
		cout<<"Agregar canciones			[1]"<<endl;
		cout<<"Eliminar canciones			[2]"<<endl;
		cout<<"Volver atras						[3]"<<endl;
		cin>>respuesta;
		cin.ignore();

	}
	else{
		cout<<"No tiene canciones en la playlist"<<endl;
		cout<<"Agregar canciones			[1]"<<endl;
		cout<<"Volver atras						[3]"<<endl;
		cin>>respuesta;
		cin.ignore();
	}
	switch (respuesta) {
		case 1:
					system("cls");
					//Funcion de jaquie Menu Buscar
					menuPlaylist(playlist.getUsuario());
					break;
		case 2:
					system("cls");
					EliminarCancion(playlist,vectorPlaylist,archiveP,&vectorCanciones);
					system("pause");
					menuPlaylist(playlist.getUsuario());
					break;
		case 3:
					system("cls");
					menuPlaylist(playlist.getUsuario());
					break;
		default:
					exit(0);
					break;
	}
}

void EliminarCancion(Playlist playlist,vector<Playlist>*vectorPlaylist,Archive archiveP,vector<Cancion>*vectorCanciones){
	cout<<"Total canciones: "<<endl;
	vector<int> codigos;
	int numero=1;
	int respuesta;
	string rsp;
	for(int i=0; i<playlist.getCanciones().size(); i++){
		for(int k=0; k<vectorCanciones->size();k++){
			if(playlist.getCanciones()[i]==vectorCanciones[0][k].getCodigo()){
				cout << numero << "\t" << "Nombre: " << vectorCanciones[0][k].getNombre() << "\t" << "Artista: " << vectorCanciones[0][k].getAutor() << endl;
				numero++;
				codigos.push_back(vectorCanciones[0][k].getCodigo());
				break;
			}
		}
	}
	cout<<"Ingrese el numero de la cancion que desea eliminar: "<<endl;
	cin>>respuesta;
	cin.ignore();
	cout<<"Seguro que desea eliminar: "<<vectorCanciones[0][codigos[respuesta-1]-1].getNombre()<<" de playlist (SI/NO)"<<endl;
	getline(cin,rsp);
	transform(rsp.begin(), rsp.end(), rsp.begin(), ::tolower);
	if(rsp=="si"){
		vector<int> tempCancion=playlist.getCanciones();
		cout<<playlist.getCodigo()<<endl;
		tempCancion.erase(tempCancion.begin()+(respuesta-1));
		vectorPlaylist[0][playlist.getCodigo()-1].setCanciones(tempCancion);
		archiveP.modificarPlaylist(*vectorPlaylist);
		cout<<"La cancion se ha eliminado de la playlist"<<endl;
	}else{
		cout<<"La cancion no fue eliminada"<<endl;
	}
}
#endif
