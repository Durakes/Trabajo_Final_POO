#include <iostream>
#include <vector>
#include <fstream>
#include"playlist.h"
using std::stoi;
using namespace std;


class PlaylistVector{
    private:
        vector<Playlist> vectorPlaylist;
    public:
        PlaylistVector(){
            vector<Playlist> vectorPlaylist;/*CREA EL OBJETO*/
			cargarDatosDelArchivoAlVector();
        }
        void add(Playlist obj){
            vectorPlaylist.push_back(obj);/*ALMACENA LOS DATOS*/
        }
        Playlist get(int pos){
            return vectorPlaylist[pos];/*RETORNA LOS DATOS POR POSICIONES*/
        }
        int rows(){
            return vectorPlaylist.size();/*ENUMERA LA CANTIDAD DE OBJETOS U DATOS QUE ALMACENA EL VECTOR, RETORNA LOS ELEMENTOS*/
        }

        Playlist buscarPorCodigo(int codigo){
            for (Playlist x : vectorPlaylist){//TODOS LOS OBJETOS DEL VECTORALUMNO PASAN A X
                if (codigo == x.getCodigoPlaylist()){//SI EL CODIGO QUE ESTAS BUSCANDO SE ENCUENTRA ALMACENADO EN EL VECTOR
                    return x;//SI ES ASI, SE RETORNA
                }
            }
        }

        Playlist buscarPorNombre(string nombre){
            for (Playlist x : vectorPlaylist){//TODOS LOS OBJETOS DEL VECTORALUMNO PASAN A X
                if (nombre == x.getNombrePlaylist()){//SI EL CODIGO QUE ESTAS BUSCANDO SE ENCUENTRA ALMACENADO EN EL VECTOR
                    return x;//SI ES ASI, SE RETORNA
                }
            }
        }

        int getPostArray(Playlist obj){
            for (int i = 0; i < vectorPlaylist.size(); i++){//AQUI RECORRE TODOS LOS DATOS DENTRO DEL VECTOR
                if (obj.getNombrePlaylist() == vectorPlaylist[i].getNombrePlaylist()){//SI LOS DATOS SON IGUALES, RETORNA LA POSICION
                    return i;/*Retorna la posicion del 
                    elemento dentro del vector*/
                }
            }
        }
        void remove(Playlist obj){
            vectorPlaylist.erase(vectorPlaylist.begin() + getPostArray(obj));//ERASE ES PARA BORRAR, VECTORALUMNO.BEGIN() PARA AGARRAR LA PRIMERA POSICION QUE ES CERO Y SUMARLO MAS LA POSICION QUE SOLICITAS, PARA QUE TE SALGA ESA Y LA BORRES.
        }	
			
		int getCorrelativo(){
			if(vectorPlaylist.size() == 0)
			{
				return 1;
			}
			else
			{
				return vectorPlaylist[vectorPlaylist.size() - 1].getCodigoPlaylist() + 1;
			}
		}
			
		void grabarEnArchivo(Playlist playlist){
			try {		
				fstream archivoPlaylist;
				archivoPlaylist.open("../docs/Playlist.csv", ios::app);
				if (archivoPlaylist.is_open()){
					archivoPlaylist<<playlist.getCodigoPlaylist()<<";"<<playlist.getNombrePlaylist()<<";"<<endl;
					archivoPlaylist.close();			
				}
			}
			catch(exception e){
				cout<< "Ocurrio un error al grabar el registro :/";
			}
		}

        void cargarDatosDelArchivoAlVector()
			{
				try
				{
					int i;
					size_t posicion; //Cantidad maxima
					string linea;
					string temporal[2];
					fstream archivoPlaylist;
					archivoPlaylist.open("../docs/Playlist.csv", ios::in);
					if(archivoPlaylist.is_open())
					{
						while(!archivoPlaylist.eof())
						{
							while(getline(archivoPlaylist,linea))
							{
								i = 0;
								while((posicion = linea.find(";")) != string::npos) // string::npos = -1
								{
									temporal[i] = linea.substr(0, posicion); //substr obtiene/ saca una parte de la cadena
									linea.erase(0, posicion + 1); //se pone +1 para borrar el primer string(0) mas el ";"
									i++; 
								}
								
								//Crear un bojeto de tipo alumno
								Playlist playlist;
								playlist.setCodigoPlaylist(std::stoi(temporal[0])); //std::stoi -- cambiar de string a entero
								playlist.setNombrePlaylist(temporal[1]);
								
								add(playlist);
							}						
						}
						archivoPlaylist.close();
					}
					else{
						cout<< "Ocurrio un error al grabar el registro :/";
					} 
				}
				catch(exception e)
				{
					cout<< "Ocurrio un error al grabar el registro :/";
				}
			}

			bool modificar(Playlist obj, string name) // obj encontrado y nombre
			{
				for(int i = 0; i < rows(); i++)
				{
					if(obj.getCodigoPlaylist() == get(i).getCodigoPlaylist())
					{
						vectorPlaylist[i].setNombrePlaylist(name);
						return true;
					}
				}
				return false;
			}
        	
			void grabarModificarEliminarArchivo()
			{
				try
				{
					fstream archivoPlaylist;
					archivoPlaylist.open("../docs/Playlist.csv", ios::out);
					if (archivoPlaylist.is_open())
					{
						for (Playlist x : vectorPlaylist)
						{
							archivoPlaylist << x.getCodigoPlaylist() << ";" << x.getNombrePlaylist() << ";" << "\n";
						}
						archivoPlaylist.close();
					}		
				}
				catch (exception e)
				{
					cout << "Ocurrio un error al grabar en el archivo";
				}
			}
			
};
