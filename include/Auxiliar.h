#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T, class U>
void cambioPosicion(T* a, T* b, U* c, U* d)
{
    T temporal = *a;
    U temp = *c;
    *a = *b;
    *c = *d;
    *b = temporal;
    *d = temp;
}

template<typename T, class C>
int particion(vector<T>* vectorT, int inicio, int final, vector<C>* vectorC)
{
    T pivote = vectorT[0][final];
    int i = (inicio - 1);

    for(int j = inicio; j <= final-1; j++)
    {
        T nombre = vectorT[0][j];
        if(nombre < pivote)
        {
            i++;
            cambioPosicion(&vectorT[0][i], &vectorT[0][j], &vectorC[0][i], &vectorC[0][j]);
        }
    }
    cambioPosicion(&vectorT[0][i+1], &vectorT[0][final], &vectorC[0][i+1], &vectorC[0][final]);
    return(i+1);
}

namespace aux
{
    string aMinuscula(string cadena)
    {
        for (int i = 0; i < cadena.length(); i++)
        {
            cadena[i] = tolower(cadena[i]);
        }
        return cadena;
    }

    template<typename T, typename U>
    void ordenamientoRapido(vector<T>* vectorTipo,int inicio, int final, vector<U>* vectorC)
    {
        if(inicio < final)
        {
            int pi = particion(vectorTipo, inicio, final, vectorC);

            ordenamientoRapido(vectorTipo, inicio, pi-1, vectorC);
            ordenamientoRapido(vectorTipo, pi+1, final, vectorC);
        }
    }

    template<typename T>
    bool busquedaBinariaPuntual(int first, int last, T valor, vector <T> vectorTipo)   // busqueda binaria           
    {
        int med=(first+last)/2;
        if (last>=first)
        {  
            if (vectorTipo[med]==valor)
            {
                return true;                               
            }
            else if(vectorTipo[med]>valor)
            {
                return busquedaBinariaPuntual(first,med-1,valor, vectorTipo);
            }
            else
            {
                return busquedaBinariaPuntual(med+1,last,valor, vectorTipo);
            }
        }
        else
        {
            return false;
        }
    }

    template<typename T, class U>
    void busquedaBinariaMultiple(int first, int last, T valor, vector <T> vectorTipo, vector<U>* vectorResultados, vector<U> vectorClase)   // busqueda binaria           
    {
        int med=(first+last)/2;
        if (last>=first)
        {  
            if (vectorTipo[med]==valor)
            {
                vectorResultados->push_back(vectorClase[med]);
                if(med!=0)
                {   
                    int n=1;
                    while(valor==vectorTipo[med-n])
                    {
                        vectorResultados->push_back(vectorClase[med-n]);
                        n++;
                    }
                }

                if(med!=vectorTipo.size()-1)
                {
                    int m=1;

                    while(valor==vectorTipo[med+m])
                    {
                        vectorResultados->push_back(vectorClase[med+m]);
                        m++;
                    }
                }                   
            }

            else if(vectorTipo[med]>valor)
            {
                busquedaBinariaMultiple(first,med-1,valor, vectorTipo, vectorResultados, vectorClase);
            }
            else
            {
                busquedaBinariaMultiple(med+1,last,valor, vectorTipo, vectorResultados, vectorClase);
            }
        }
        else
        {
            cout << "No se encontro resultados" << endl;
        }

    }
}