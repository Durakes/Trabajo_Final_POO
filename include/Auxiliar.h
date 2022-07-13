#ifndef __AUXILIAR_H__
#define __AUXILIAR_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <windows.h>

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
    int i = inicio - 1;

    for(int j = inicio; j <= final - 1; j++)
    {
        T nombre = vectorT[0][j];
        if(nombre < pivote)
        {
            i++;
            cambioPosicion(&vectorT[0][i], &vectorT[0][j], &vectorC[0][i], &vectorC[0][j]);
        }
    }
    cambioPosicion(&vectorT[0][i + 1], &vectorT[0][final], &vectorC[0][i + 1], &vectorC[0][final]);
    return(i + 1);
}

namespace aux
{
    void gotoxy(int x, int y)
    {
        HANDLE hcon;
        hcon = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD dwPos;
        dwPos.X = x;
        dwPos.Y = y;
        SetConsoleCursorPosition(hcon, dwPos);
    }

    void cuadro(int x1, int y1, int x2, int y2)
    {
        for(int i = x1; i < x2; i++)
        {
            gotoxy(i,y1); printf("%c", 205);
            gotoxy(i,y2); printf("%c", 205);
        }

        for(int i = y1; i < y2; i++)
        {
            gotoxy(x2,i); printf("%c", 186);
            gotoxy(x1,i); printf("%c", 186);
        }

        gotoxy(x1,y1); printf("%c", 201);
        gotoxy(x2,y1); printf("%c", 187);
        gotoxy(x1,y2); printf("%c", 200);
        gotoxy(x2,y2); printf("%c", 188);
    }

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

            ordenamientoRapido(vectorTipo, inicio, pi - 1, vectorC);
            ordenamientoRapido(vectorTipo, pi + 1, final, vectorC);
        }
    }

    template<typename T>
    bool busquedaBinariaPuntual(int primero, int ultimo, T valor, vector <T> vectorTipo)          
    {
        int mitad = (primero + ultimo)/2;
        if (ultimo >= primero)
        {  
            if (vectorTipo[mitad] == valor)
            {
                return true;                               
            }
            else if(vectorTipo[mitad] > valor)
            {
                return busquedaBinariaPuntual(primero, mitad - 1, valor, vectorTipo);
            }
            else
            {
                return busquedaBinariaPuntual(mitad + 1, ultimo, valor, vectorTipo);
            }
        }
        else
        {
            return false;
        }
    }

    template<typename T, class U>
    void busquedaBinariaConjunta(int primero, int ultimo, T valor, vector<T> vectorTipo, vector<U>* vectorFinal, vector<U> vectorReferencia)         
    {
        int mitad = (primero + ultimo)/2;
        if (ultimo >= primero)
        {  
            if (vectorTipo[mitad] == valor)
            {
                vectorFinal->push_back(vectorReferencia[mitad]);                               
            }
            else if(vectorTipo[mitad] > valor)
            {
                busquedaBinariaConjunta(primero, mitad - 1, valor, vectorTipo, vectorFinal, vectorReferencia);
            }
            else
            {
                busquedaBinariaConjunta(mitad + 1, ultimo, valor, vectorTipo, vectorFinal, vectorReferencia);
            }
        }
    }

    template<typename T, class U>
    void busquedaBinariaUsuario(int primero, int ultimo, T valor, vector<T> vectorTipo, U* objFinal, vector<U> vectorReferencia)           
    {
        int mitad = (primero + ultimo)/2;
        if (ultimo >= primero)
        {  
            if (vectorTipo[mitad] == valor)
            {
                *objFinal = vectorReferencia[mitad];                               
            }
            else if(vectorTipo[mitad] > valor)
            {
                busquedaBinariaUsuario(primero, mitad - 1, valor, vectorTipo, objFinal, vectorReferencia);
            }
            else
            {
                busquedaBinariaUsuario(mitad + 1, ultimo, valor, vectorTipo, objFinal, vectorReferencia);
            }
        }
    }


    template<typename T, class U>
    void busquedaBinariaMultiple(int primero, int ultimo, T valor, vector <T> vectorTipo, vector<U>* vectorResultados, vector<U> vectorClase)       
    {
        int mitad = (primero + ultimo)/2;
        if (ultimo >= primero)
        {  
            if (vectorTipo[mitad] == valor)
            {
                vectorResultados->push_back(vectorClase[mitad]);
                if(mitad != 0)
                {   
                    int n = 1;
                    while(valor == vectorTipo[mitad - n])
                    {
                        vectorResultados->push_back(vectorClase[mitad - n]);
                        n++;
                    }
                }
                if(mitad != vectorTipo.size() - 1)
                {
                    int m = 1;

                    while(valor == vectorTipo[mitad + m])
                    {
                        vectorResultados->push_back(vectorClase[mitad + m]);
                        m++;
                    }
                }                   
            }
            else if(vectorTipo[mitad] > valor)
            {
                busquedaBinariaMultiple(primero, mitad - 1, valor, vectorTipo, vectorResultados, vectorClase);
            }
            else
            {
                busquedaBinariaMultiple(mitad + 1, ultimo, valor, vectorTipo, vectorResultados, vectorClase);
            }
        }
    }
}
#endif