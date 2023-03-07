#ifndef ABB_H 
#define ABB_H 
#include <cassert>

template <typename T> 
class Abb {
public:
    Abb();
    const Abb& buscar(const T& e) const;
    Abb<T>& buscar(const T& e);
    void insertar(const T& e);
    void eliminar(const T& e);
    bool vacio() const;
    const T& elemento() const;
    const Abb& izqdo() const;
    const Abb& drcho() const;
    Abb(const Abb& A);
    Abb& operator =(const Abb& A); 
    ~Abb();

    void eliminar_subarbol(const T&);
private:
   struct arbol 
    {
        T elto;
        Abb izq, der;
        arbol(const T& e): elto{e}, izq{}, der{} {} 
    };
   arbol* r;   // raíz del árbol
   T borrarMin();
};


template <typename T>
inline Abb<T>::Abb() : r{nullptr} {}

template <typename T>
inline bool Abb<T>::vacio() const 
{
   return (r == nullptr);
}

template <typename T>
const Abb<T>& Abb<T>::buscar(const T& e) const
{
   if (r == nullptr)         // Árbol vacío, e no encontrado.
      return *this;
   else if (e < r->elto)     // Buscar en subárbol izqdo.
      return r->izq.buscar(e);
else if (r->elto < e) // Buscar en subárbol drcho. 
        return r->der.buscar(e);
   else                      // Encontrado e en la raíz.
      return *this;
}

template <typename T>
Abb<T>& Abb<T>::buscar(const T& e)
{
   if (r == nullptr)         // Árbol vacío, e no encontrado.
      return *this;
   else if (e < r->elto)     // Buscar en subárbol izqdo.
      return r->izq.buscar(e);
else if (r->elto < e) // Buscar en subárbol drcho. 
        return r->der.buscar(e);
   else                      // Encontrado e en la raíz.
      return *this;
}

template <typename T>
void Abb<T>::insertar(const T& e) 
{
    if (r == nullptr)
        r = new arbol(e);
    else if (e < r->elto)
            r->izq.insertar(e);
    else if (r->elto < e) 
            r->der.insertar(e);
}

template <typename T>
void Abb<T>::eliminar(const T& e) 
{
    if (r != nullptr)
    { 
        if (e < r->elto)
            r->izq.eliminar(e);
        else if (r->elto < e)
            r->der.eliminar(e);

        else{
            if (!r->izq.r && !r->der.r) { // 1. Raíz es hoja.
                delete r;
                r = nullptr; // El árbol queda vacío. 
            }
            else if (!r->der.r) { // 2. Raíz sólo tiene hijo izqdo. 
                arbol* a = r->izq.r;
                r->izq.r = nullptr; // Evita destruir el subárbol izqdo. 
                delete r;
                r = a; 
            }
            else if (!r->izq.r) { // 3. Raíz sólo tiene hijo drcho. 
                arbol* a = r->der.r;
                r->der.r = nullptr; // Evita destruir el subárbol drcho. 
                delete r;
                r = a; 
            }
            else   // 4. Raíz tiene dos hijos
                r->elto = r->der.borrarMin();
        }
    }
}

// Método privado
template <typename T>
T Abb<T>::borrarMin()   // Elimina el nodo que almacena el menor elemento del árbol. Devuelve el elemento del nodo eliminado. 
{
    if (r->izq.r == nullptr) { // Subárbol izquierdo vacío. 
        T e = r->elto;
        arbol* hd = r->der.r;
        r->der.r = nullptr; // Evita destruir subárbol drcho. 
        delete r;
        r = hd; // Sustituir r por el subárbol drcho.
        return e; 
    }
    else
        return r->izq.borrarMin();
}

template <typename T>
inline const T& Abb<T>::elemento() const 
{
   assert(r != nullptr);
   return r->elto;
}

template <typename T>
inline const Abb<T>& Abb<T>::izqdo() const
{
   assert(r != nullptr);
    return r->izq; 
}

template <typename T>
inline const Abb<T>& Abb<T>::drcho() const 
{
   assert(r != nullptr);
   return r->der;
}

template <typename T>
inline Abb<T>::Abb(const Abb<T>& A): r{nullptr}
{
    if (A.r != nullptr)
        r = new arbol(*A.r); // Copiar raíz y descendientes.
}

template <typename T>
Abb<T>& Abb<T>::operator =(const Abb<T>& A)
{
    if (this != &A) { // Evitar autoasignación. 
        this->~Abb(); // Vaciar el árbol.
        if (A.r != nullptr)
            r = new arbol(*A.r); // Copiar raíz y descendientes. 
    }
    return *this; 
}

template <typename T> Abb<T>::~Abb()
{
    if (r != nullptr) { // Árbol no vacío.
        delete r; // Destruir raíz y descendientes con r->~arbol() 
        r = nullptr; // El árbol queda vacío.
    } 
}

//EJERCICIO 1 PRACTICA 4

template <typename T>
void Abb<T>::eliminar_subarbol(const T& e)
{
    Abb <T> aux = buscar(e);
    if (!aux.vacio())
    {
        destruir(aux);
    }
}

template <typename T>
void destruir(Abb<T>& A)
{
    if(A.izqdo().vacio() && A.drcho().vacio()) //es hoja
    {
        A.eliminar(A.elemento());
    }
    else if(A.izqdo().vacio())
    {
        destruir(A.drcho());
        A.eliminar(A.elemento());
    }
    else 
    {
        destruir(A.izqdo());
        A.eliminar(A.elemento());
    }
}

#endif