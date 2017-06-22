/*
  Definicion de algunas excepciones de las distintas
  implementaciones de los TADs.

  Estructura de Datos y Algoritmos
  Facultad de Informatica
  Universidad Complutense de Madrid

 (c) Marco Antonio Gomez Martin, 2012
*/
#ifndef __EXCEPCIONES_H
#define __EXCEPCIONES_H

#include <string>
#include <iosfwd>
/**
 Clase de la que heredan todas las excepciones, y
 que proporciona el atributo que almacena el
 mensaje de error.
 */
class ExcepcionTAD {
public:
	ExcepcionTAD() {}
	ExcepcionTAD(const std::string &msg) : _msg(msg) {}

	const std::string msg() const { return _msg; }

	friend std::ostream &operator<<(std::ostream &out, const ExcepcionTAD &e);

protected:
	std::string _msg;
};

inline std::ostream &operator<<(std::ostream &out, const ExcepcionTAD &e) {
	out << e._msg;
	return out;
}


// Macro para declarar las clases de tipo excepcion
// que heredan de ExcepcionConMensaje, para ahorrar
// escribir muchas veces lo mismo...
#define DECLARA_EXCEPCION(Excepcion) \
class Excepcion : public ExcepcionTAD { \
public: \
Excepcion() {}; \
Excepcion(const std::string &msg) : ExcepcionTAD(msg) {} \
};

/**
 Excepcion generada por algunas operaciones de las pilas.
 */
DECLARA_EXCEPCION(EmptyStackException);

/**
 Excepcion generada por algunas operaciones de las pilas.
 */
DECLARA_EXCEPCION(FullStackException);

/**
 Excepcion generada por algunas de las operaciones de las colas.
 */
DECLARA_EXCEPCION(EmptyQueueException);

/**
 Excepcion generada por algunas operaciones de las colas dobles.
 */
DECLARA_EXCEPCION(EmptyDequeException);

/**
 Excepcion generada por algunas operaciones de las listas.
 */
DECLARA_EXCEPCION(EmptyListException);

/**
 Excepcion generada por accesos incorrectos a las listas
 (tanto a un numero de elemento incorrecto como por
 mal manejo de los iteradores).
 */
DECLARA_EXCEPCION(InvalidAccessException);

/**
 Excepcion generada por algunas operaciones de los
 arboles binarios.
 */
DECLARA_EXCEPCION(EArbolVacio);

/**
 Excepcion generada por algunas operaciones de los
 diccionarios y arboles de busqueda.
 */
DECLARA_EXCEPCION(EClaveErronea);

#endif // __EXCEPCIONES_H



/**
  @file DCola.h

  Implementacion del TAD doble cola, utilizando una
  lista doblemente enlazada con nodo fantasma o
  cabecera.

  Estructura de Datos y Algoritmos
  Facultad de Informatica
  Universidad Complutense de Madrid

 (c) Marco Antonio Gomez Martin, 2012
*/
#ifndef __DCOLA_H
#define __DCOLA_H

#include <cassert>

/**
 Implementacion del TAD Doble Cola utilizando una lista doblemente
 enlazada circular y con nodo fantasma.

 Las operaciones son:

 - EmptyDeque: -> Deque. Generadora implementada en el
   constructor sin parametros.
 - Push_back: Deque, Elem -> Deque. Generadora
 - push_front: Deque, Elem -> Deque. Modificadora.
 - pop_front: Deque - -> Deque. Modificadora parcial
 - pop_back: Deque - -> Deque. Modificadora parcial
 - front: Deque - -> Elem. Observadora parcial
 - back: Deque - -> Elem. Observadora parcial
 - empty: Deque -> Bool. Observadora

 @author Marco Antonio Gomez Martin
 */
template <class T>
class Deque {
public:

	/** Constructor; operacion EmptyDeque. */
	Deque() {
		_fantasma = new Nodo();
		_fantasma->_sig = _fantasma;
		_fantasma->_ant = _fantasma;
		_numElems = 0;
	}

	/** Destructor; elimina la lista doblemente enlazada. */
	~Deque() {
		libera();
	}

	/**
	 Anade un elemento por la parte de atras de la cola.
	 Es una operacion generadora.
	*/
	void push_back(const T &e) {
		insertaElem(e, _fantasma->_ant, _fantasma);
		_numElems++;
	}

	/**
	 Devuelve el primer elemento de la cola; es una operacion
	 observadora parcial, pues es un error preguntar por
	 el primer elemento de una doble cola vacia.

	 primero(Push_back(elem, EmptyDeque)) = elem
	 primero(Push_back(elem, xs)) = primero(xs) si !empty(xs)
	 error: primero(EmptyDeque)
	 */
	const T &front() const {
		if (empty())
			throw EmptyDequeException();
		return _fantasma->_sig->_elem;
	}


	/**
	 Elimina el primer elemento de la doble cola.
	 Operacion modificadora parcial, que falla si
	 esta vacia.

	 pop_front(Push_back(elem, EmptyDeque)) = EmptyDeque
	 pop_front(Push_back(elem, xs)) = Push_back(elem, pop_front(xs)) si !empty(xs)
	 error: pop_front(EmptyDeque)
	*/
	void pop_front() {
		if (empty())
			throw EmptyDequeException();

		borraElem(_fantasma->_sig);
		--_numElems;
	}

	/**
	 Anade un elemento a la parte delantera de una doble cola.
	 Operacion modificadora.

	 push_front(elem, EmptyDeque) = Push_back(elem, EmptyDeque)
	 push_front(elem, Push_back(x, xs)) =
		Push_back(x, push_front(elem, xs))

	 @param e Elemento que se anade
	 */
	void push_front(const T &e) {
		insertaElem(e, _fantasma, _fantasma->_sig);
		++_numElems;
	}

	/**
	 Devuelve el ultimo elemento de la doble cola. Es
	 un error preguntar por el ultimo de una doble cola vacia.

	 back(Push_back(x, xs)) = x
	 error: back(EmptyDeque)

	 @return ultimo elemento de la cola.
	 */
	const T &back() const {
		if (empty())
			throw EmptyDequeException();
		return _fantasma->_ant->_elem;
	}

	/**
	 Elimina el ultimo elemento de la doble cola. Es
	 un error quitar el ultimo de una doble cola vacia.

	 pop_back(Push_back(x, xs)) = xs
	 error: pop_back(EmptyDeque)
	 */
	void pop_back() {
		if (empty())
			throw EmptyDequeException();

		borraElem(_fantasma->_ant);
		--_numElems;
	}

	/**
	 Operacion observadora para saber si una doble cola
	 tiene o no elementos.

	 empty(EmptyDeque) = true
	 empty(Push_back(x, xs)) = false

	 @return true si la doble cola no tiene elementos.
	 */
	bool empty() const {
		return _fantasma->_sig == _fantasma;
		/* return _numElems == 0; */
	}

	/**
	 Devuelve el numero de elementos que hay en la
	 doble cola.
	 size(EmptyDeque) = 0
	 size(Push_back(elem, p)) = 1 + size(p)

	 @return Numero de elementos.
	 */
	int size() const {
		return _numElems;
	}

	// //
	// METODOS DE "FONTANERIA" DE C++ QUE HACEN VERSATIL
	// A LA CLASE
	// //

	/** Constructor copia */
	Deque(const Deque<T> &other) : _fantasma(NULL) {
		copia(other);
	}

	/** Operador de asignacion */
	Deque<T> &operator=(const Deque<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparacion. */
	bool operator==(const Deque<T> &rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		Nodo *p1 = _fantasma->_sig;
		Nodo *p2 = rhs._fantasma->_sig;
		while ((p1 != _fantasma) && (p2 != rhs._fantasma)) {
			if (p1->_elem != p2->_elem)
				return false;
			p1 = p1->_sig;
			p2 = p2->_sig;
		}

		return (p1 == _fantasma) && (p2 == rhs._fantasma);
	}

	bool operator!=(const Deque<T> &rhs) const {
		return !(*this == rhs);
	}

protected:

	void libera() {
		// Usamos libera(nodo), pero antes quitamos
		// la circularidad para evitar bucle
		// infinito...
		_fantasma->_ant->_sig = NULL;
		_fantasma->_ant = NULL;
		libera(_fantasma);
		_fantasma = NULL;
	}

	void copia(const Deque<T> &other) {
		// En vez de trabajar con punteros en la insercion,
		// usamos ponDetras.
		_fantasma = new Nodo();
		_fantasma->_sig = _fantasma;
		_fantasma->_ant = _fantasma;
		_numElems = 0;

		Nodo *act = other._fantasma->_sig;
		while (act != other._fantasma) {
			push_back(act->_elem);
			act = act->_sig;
		}
	}

private:

	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y dos punteros, uno al nodo anterior y otro al nodo siguiente.
	 Ambos punteros podrian ser NULL si el nodo es el primero
	 y/o ultimo de la lista enlazada.
	 */
	class Nodo {
	public:
		Nodo() : _sig(NULL) {}
		Nodo(const T &elem) : _elem(elem), _sig(NULL), _ant(NULL) {}
		Nodo(Nodo *ant, const T &elem, Nodo *sig) :
		    _elem(elem), _sig(sig), _ant(ant) {}

		T _elem;
		Nodo *_sig;
		Nodo *_ant;
	};

	/**
	 Inserta un elemento entre el nodo1 y el nodo2.
	 Devuelve el puntero al nodo creado.
	 Caso general: los dos nodos existen.
	    nodo1->_sig == nodo2
	    nodo2->_ant == nodo1
	 Casos especiales: alguno de los nodos no existe
	    nodo1 == NULL y/o nodo2 == NULL
	*/
	static Nodo *insertaElem(const T &e, Nodo *nodo1, Nodo *nodo2) {
		Nodo *nuevo = new Nodo(nodo1, e, nodo2);
		if (nodo1 != NULL)
			nodo1->_sig = nuevo;
		if (nodo2 != NULL)
			nodo2->_ant = nuevo;
		return nuevo;
	}

	/**
	 Elimina el nodo n. Si el nodo tiene nodos antes
	 o despues, actualiza sus punteros anterior y siguiente.
	 Caso general: hay nodos anterior y siguiente.
	 Casos especiales: algunos de los nodos (anterior o siguiente
	 a n) no existen.
	*/
	static void borraElem(Nodo *n) {
		if (n == NULL)
			return;

		Nodo *ant = n->_ant;
		Nodo *sig = n->_sig;
		if (ant != NULL)
			ant->_sig = sig;
		if (sig != NULL)
			sig->_ant = ant;
		delete n;
	}

	/**
	 Elimina todos los nodos de la lista enlazada cuyo
	 primer nodo se pasa como parametro.
	 Se admite que el nodo sea NULL (no habra nada que
	 liberar). En caso de pasarse un nodo valido,
	 su puntero al nodo anterior debe ser NULL (si no,
	 no seria el primero de la lista!).
	 */
	static void libera(Nodo *prim) {
		if (prim == NULL)
			return;

		assert(!prim || !prim->_ant);

		while (prim != NULL) {
			Nodo *aux = prim;
			prim = prim->_sig;
			delete aux;
		}
	}

	// Puntero al nodo fantasma
	Nodo *_fantasma;

	// Numero de elementos
	unsigned int _numElems;
};

#endif // __DCOLA_H


#include <iostream>
using namespace std;

int main() {

	Deque<int> alumnos;
	int total, salto;
	cin >> total >> salto;

	while (total != 0 && salto != 0) {
		for (int i = 0; i < total; i++) {
			alumnos.push_back(i+1);
		}

		int n = 1;
		while (alumnos.size() > 1) {
			if (n%salto == 0) {
				alumnos.pop_front();
			}
			else {
				alumnos.push_back(alumnos.front());
				alumnos.pop_front();
			}
			n++;
		}

		cout << alumnos.front() << endl;
		alumnos.pop_front();
		cin >> total >> salto;
	}

	return 0;
}
