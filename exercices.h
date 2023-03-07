#ifndef PRACTICA4_H
#define PRACTICA4_H

#include "abb.h"

//EJERCICIO 2
template <typename T>
void equilibrar(Abb<T>& A) 
{   
    if(!A.vacio())
    {
        size_t t = contar_nodos(A);
        T vector[t];
        size_t indice = 0;
        rellenar_vector(indice,vector,A);
        //REORGANIZAMOS EL ARBOL
        Abb<T> B;
        rellenar_arbol(B,0,t-1,vector);
        A = B;
    }


}

template <typename T>
int contar_nodos(const Abb<T>& A)
{
    if(A.vacio())
        return 0;
    else
        return 1+contar_nodos(A.izqdo())+contar_nodos(A.drcho());
}

template <typename T>
void rellenar_vector(size_t i, T* &vector, const Abb<T>& A)
{
    if(!A.izqdo().vacio())
        rellenar_vector(i,vector,A.izqdo());

    vector[i] = A.elemento();
    i++;
    if(!A.drcho().vacio())
    {
        rellenar_vector(i,vector,A.drcho());
    }
    
}

template <typename T>
void rellenar_arbol(Abb<T>& A, int inicio, int fin,T* &vector)
{
    if(fin >= inicio)
    {
        int mediana = (inicio+fin)/2;
        A.insertar(vector[mediana]);
        rellenar_arbol(A.izqdo(),inicio,mediana-1,vector);
        rellenar_arbol(A.drcho(),mediana+1,fin,vector);
    }
}

//EJERCICIO 3
template <typename T>
using Conjunto = Abb<T>;

template <typename T>
Conjunto<T> union_conjuntos(const Conjunto<T>& A,const Conjunto<T>& B)
{
    Conjunto<T> Union = A;
    anadir_elementos(Union,A,B);
    equilibrar(Union);

    return Union;
}

template <typename T>
Conjunto<T> anadir_elementos(Conjunto<T>& U,const Conjunto<T>& A,const Conjunto<T>& B)
{
    if(!B.vacio())
    {
        if(!A.buscar(B.elemento()))
        {
            U.insertar(B.elemento());
        }
        anadir_elementos(U,A,B.izqdo());
        anadir_elementos(U,A,B.drcho());
    }
}



//EJERCICIO 4
template <typename T>
Conjunto<T> interseccion_conjuntos(const Conjunto<T>& A,const Conjunto<T>& B)
{
    Conjunto<T> Interseccion = B;
    anadir_elementos(Interseccion,A,B);
    equilibrar(Interseccion);

    return Interseccion;
}

template <typename T>
Conjunto<T> eliminar_elementos(Conjunto<T>& I,const Conjunto<T>& A,const Conjunto<T>& B)
{
    if(!B.vacio())
    {
        if(!A.buscar(B.elemento()))
        {
            I.eliminar(B.elemento());
        }
        anadir_elementos(I,A,B.izqdo());
        anadir_elementos(I,A,B.drcho());
    }
}

//EJERCICIO 5

template <typename T>
Conjunto<T> operador_rombo(const Conjunto<T>& A,const Conjunto<T>& B)
{
    Conjunto<T> C = union_conjuntos(A,B);

    formar_rombo(C,interseccion_conjuntos(A,B));
    equilibrar(C);
    return C;
}

template <typename T>
bool pertenece(const Conjunto<T>& C, const T& elto)
{
    if(C.buscar(elto).vacio())
        return false;
    else
        return true;
}

template <typename T>
void formar_rombo(Conjunto<T>& C,const Conjunto<T>& I)
{
    if(!C.vacio())
    {
        equilibrar(C); //Para busqueda O log
        if(pertenece(I,C.elemento()))
            C.eliminar(C.elemento());
        
        formar_rombo(C.izqdo(),I);
        formar_rombo(C.drcho(),I);
    }

}

#endif