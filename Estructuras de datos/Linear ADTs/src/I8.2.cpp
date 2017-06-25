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
  @file Stack.h

  Implementacion del TAD Pila utilizando un
  vector dinamico cuyo tamano va creciendo si
  es necesario.

  Estructura de Datos y Algoritmos
  Facultad de Informatica
  Universidad Complutense de Madrid

 (c) Marco Antonio Gomez Martin, 2012
*/
#ifndef __STACK_H
#define __STACK_H

/**
 Implementacion del TAD Pila utilizando vectores dinamicos.

 Las operaciones son:

 - EmptyStack: -> Stack. Generadora implementada en el
   constructor sin parametros.
 - Push: Stack, Elem -> Stack. Generadora
 - pop: Stack - -> Stack. Modificadora parcial.
 - top: Stack - -> Elem. Observadora parcial.
 - empty: Stack -> Bool. Observadora.
 - size: Stack -> Entero. Observadora.

 @author Marco Antonio Gomez Martin
 */
template <class T>
class Stack {
public:

	/** Tamano inicial del vector dinamico. */
	static const int TAM_INICIAL = 10;

	/** Constructor; operacion EmptyStack */
	Stack() {
		inicia();
	}

	/** Destructor; elimina el vector. */
	~Stack() {
		libera();
	}

	/**
	 Apila un elemento. Operacion generadora.

	 @param elem Elemento a apilar.
	*/
	void push(const T &elem) {
		_v[_numElems] = elem;
		_numElems++;
		if (_numElems == _tam)
			amplia();
	}

	/**
	 Desapila un elemento. Operacion modificadora parcial,
	 que falla si la pila esta vacia.

	 pop(Push(elem, p)) = p
	 error: pop(EmptyStack)
	*/
	void pop() {
		if (empty())
			throw EmptyStackException();
		--_numElems;
	}

	/**
	 Devuelve el elemento en la cima de la pila. Operacion
	 observadora parcial, que falla si la pila esta vacia.

	 top(Push(elem, p) = elem
	 error: top(EmptyStack)

	 @return Elemento en la cima de la pila.
	 */
	const T &top() const {
		if (empty())
			throw EmptyStackException();
		return _v[_numElems - 1];
	}

	/**
	 Devuelve true si la pila no tiene ningun elemento.

	 empty(EmptyStack) = true
	 empty(Push(elem, p)) = false

	 @return true si la pila no tiene ningun elemento.
	 */
	bool empty() const {
		return _numElems == 0;
	}

	/**
	 Devuelve el numero de elementos que hay en la
	 pila.
	 size(EmptyStack) = 0
	 size(Push(elem, p)) = 1 + size(p)

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
	Stack(const Stack<T> &other) {
		copia(other);
	}

	/** Operador de asignacion */
	Stack<T> &operator=(const Stack<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparacion */
	bool operator==(const Stack<T> &rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		for (unsigned int i = 0; i < _numElems; ++i)
			if (_v[i] != rhs._v[i])
				return false;
		return true;
	}

	bool operator!=(const Stack<T> &rhs) const {
		return !(*this == rhs);
	}

protected:

	void inicia() {
		_v = new T[TAM_INICIAL];
		_tam = TAM_INICIAL;
		_numElems = 0;
	}

	void libera() {
		delete []_v;
		_v = NULL;
	}

	void copia(const Stack &other) {
		_tam = other._numElems + TAM_INICIAL;
		_numElems = other._numElems;
		_v = new T[_tam];
		for (unsigned int i = 0; i < _numElems; ++i)
			_v[i] = other._v[i];
	}

	void amplia() {
		T *viejo = _v;
		_tam *= 2;
		_v = new T[_tam];

		for (unsigned int i = 0; i < _numElems; ++i)
			_v[i] = viejo[i];

		delete []viejo;
	}

private:

	/** Puntero al array que contiene los datos. */
	T *_v;

	/** Tamano del vector _v. */
	unsigned int _tam;

	/** Numero de elementos reales guardados. */
	unsigned int _numElems;
};

#endif // __STACK_H



/**
  @file Cola.h

  Implementacion del TAD Cola utilizando una
  lista enlazada de nodos.

  Estructura de Datos y Algoritmos
  Facultad de Informatica
  Universidad Complutense de Madrid

 (c) Marco Antonio Gomez Martin, 2012
*/
#ifndef __LINKED_LIST_QUEUE_H
#define __LINKED_LIST_QUEUE_H

/**
 Implementacion del TAD Cola utilizando una lista enlazada.

 Las operaciones son:

 - EmptyQueue: -> Queue. Generadora implementada en el
   constructor sin parametros.
 - push_back: Queue, Elem -> Queue. Generadora
 - pop_front: Queue - -> Queue. Modificadora parcial.
 - front: Queue - -> Elem. Observadora parcial.
 - empty: Queue -> Bool. Observadora.
 - size: Queue -> Entero. Observadora.

 @author Marco Antonio Gomez Martin
 */
template <class T>
class Queue {
public:

	/** Constructor; operacion EmptyQueue */
	Queue() : _prim(NULL), _ult(NULL), _numElems(0) {
	}

	/** Destructor; elimina la lista enlazada. */
	~Queue() {
		libera();
		_prim = _ult = NULL;
	}

	/**
	 A�ade un elemento en la parte trasera de la cola.
	 Operaci�n generadora.

	 @param elem Elemento a a�adir.
	*/
	void push_back(const T &elem) {
		Nodo *nuevo = new Nodo(elem, NULL);

		if (_ult != NULL)
			_ult->_sig = nuevo;
		_ult = nuevo;
		// Si la cola estaba vacia, el primer elemento
		// es el que acabamos de anadir
		if (_prim == NULL)
			_prim = nuevo;
		_numElems++;
	}

	/**
	 Elimina el primer elemento de la cola.
	 Operacion modificadora parcial, que falla si
	 la cola esta vacia.

	 pop_front(Push_back(elem, EmptyQueue)) = EmptyQueue
	 pop_front(Push_back(elem, xs)) = push_back(elem, pop_front(xs)) si !empty(xs)
	 error: pop_front(EmptyQueue)
	*/
	void pop_front() {
		if (empty())
			throw EmptyQueueException();
		Nodo *aBorrar = _prim;
		_prim = _prim->_sig;
		delete aBorrar;
		--_numElems;
		// Si la cola se quedo vacia, no hay
		// ultimo
		if (_prim == NULL)
			_ult = NULL;
	}

	/**
	 Devuelve el primer elemento de la cola. Operacion
	 observadora parcial, que falla si la cola esta vacia.

	 front(Push_back(elem, EmptyQueue)) = elem
	 front(Push_back(elem, xs)) = primero(xs) si !empty(xs)
	 error: front(EmptyQueue)

	 @return El primer elemento de la cola.
	 */
	const T &front() const {
		if (empty())
			throw EmptyQueueException();
		return _prim->_elem;
	}

	/**
	 Devuelve true si la cola no tiene ningun elemento.

	 empty(EmptyQueue) = true
	 empty(Push_back(elem, p)) = false

	 @return true si la cola no tiene ningun elemento.
	 */
	bool empty() const {
		return _prim == NULL;
	}

	/**
	 Devuelve el numero de elementos que hay en la
	 cola.
	 size(EmptyQueue) = 0
	 size(Push_back(elem, p)) = 1 + size(p)

	 @return N�mero de elementos.
	 */
	int size() const {
		return _numElems;
	}

	// //
	// METODOS DE "FONTANERIA" DE C++ QUE HACEN VERSATIL
	// A LA CLASE
	// //

	/** Constructor copia */
	Queue(const Queue<T> &other) : _prim(NULL), _ult(NULL) {
		copia(other);
	}

	/** Operador de asignacion */
	Queue<T> &operator=(const Queue<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparacion */
	bool operator==(const Queue<T> &rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		Nodo *p1 = _prim;
		Nodo *p2 = rhs._prim;
		while ((p1 != NULL) && (p2 != NULL)) {
			if (p1->_elem != p2->_elem)
				return false;
			p1 = p1->_sig;
			p2 = p2->_sig;
		}

		return (p1 == NULL) && (p2 == NULL);
	}

	bool operator!=(const Queue<T> &rhs) const {
		return !(*this == rhs);
	}

protected:

	void libera() {
		libera(_prim);
	}

	void copia(const Queue &other) {

		if (other.empty()) {
			_prim = _ult = NULL;
			_numElems = 0;
		} else {
			Nodo *act = other._prim;
			Nodo *ant;
			_prim = new Nodo(act->_elem);
			ant = _prim;
			while (act->_sig != NULL) {
				act = act->_sig;
				ant->_sig = new Nodo(act->_elem);
				ant = ant->_sig;
			}
			_ult = ant;
			_numElems = other._numElems;
		}
	}

private:

	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y un puntero al nodo siguiente, que podria ser NULL si
	 el nodo es el ultimo de la lista enlazada.
	 */
	class Nodo {
	public:
		Nodo() : _sig(NULL) {}
		Nodo(const T &elem) : _elem(elem), _sig(NULL) {}
		Nodo(const T &elem, Nodo *sig) :
		    _elem(elem), _sig(sig) {}

		T _elem;
		Nodo *_sig;
	};

	/**
	 Elimina todos los nodos de la lista enlazada cuyo
	 primer nodo se pasa como parametro.
	 Se admite que el nodo sea NULL (no habra nada que
	 liberar).
	 */
	static void libera(Nodo *prim) {
		while (prim != NULL) {
			Nodo *aux = prim;
			prim = prim->_sig;
			delete aux;
		}
	}

	/** Puntero al primer elemento. */
	Nodo *_prim;

	/** Puntero al ultimo elemento. */
	Nodo *_ult;

	/** Numero de elementos */
	int _numElems;
};

#endif // __LINKED_LIST_QUEUE_H


#include <iostream>
#include <sstream>
#include <string>
using namespace std;

bool dehesapila(Queue<int> colaIni, Queue<int> colaFin);

int main() {

	int N;
	cin >> N;

	while (N != 0) {
		Queue<int> colaIni, colaFin;

		int n;
		string line;
		getline(cin, line);
		istringstream iss(line);

		while (iss >> n) {
			colaFin.push_back(n);
		}

		for (int i = 1; i <= N; i++) {
			colaIni.push_back(i);
		}

		if (dehesapila(colaIni, colaFin)) {
			cout << "POSSIBLE" << endl;
		}
		else {
			cout << "IMPOSSIBLE" << endl;
		}

		cin >> N;
	}

	return 0;
}

bool dehesapila(Queue<int> colaIni, Queue<int> colaFin) {
	Stack<int> pila;

	pila.push(colaIni.front());
	colaIni.pop_front();
	cout << "Wagon " << pila.top() << " in" << endl;

	// Apilamos los vagones hasta encontrar el primero que se quiere sacar:
	while(pila.top() != colaFin.front()) {
		pila.push(colaIni.front());
		colaIni.pop_front();
		cout << "Wagon " << pila.top() << " in" << endl;
	}

	// A partir de aquí, el orden de los vagones que se quieren sacar debe adaptarse
	// al orden que tienen la cola inicial y la pila de la estación:
	while (!colaFin.empty()) {
		if(pila.empty()) {
			if(colaFin.front() > colaIni.front()) {
				pila.push(colaIni.front());
				colaIni.pop_front();
				cout << "Wagon " << pila.top() << " in" << endl;
			}
			else if(colaFin.front() == colaIni.front()) {
				pila.push(colaIni.front());
				colaIni.pop_front();
				cout << "Wagon " << pila.top() << " in" << endl;
				cout << "Wagon " << pila.top() << " out" << endl;
				colaFin.pop_front();
				pila.pop();
			}
			else {
				return false;
			}
		}
		else if(colaIni.empty()) {
			if (colaFin.front() == pila.top()) {
				cout << "Wagon " << pila.top() << " out" << endl;
				colaFin.pop_front();
				pila.pop();
			}
			else {
				return false;
			}
		}
		else {
			if (colaFin.front() == pila.top()) {
				cout << "Wagon " << pila.top() << " out" << endl;
				colaFin.pop_front();
				pila.pop();
			}
			else if(colaFin.front() > colaIni.front()) {
				pila.push(colaIni.front());
				colaIni.pop_front();
				cout << "Wagon " << pila.top() << " in" << endl;
			}
			else if(colaFin.front() == colaIni.front()) {
				pila.push(colaIni.front());
				colaIni.pop_front();
				cout << "Wagon " << pila.top() << " in" << endl;

				cout << "Wagon " << pila.top() << " out" << endl;
				colaFin.pop_front();
				pila.pop();
			}
			else {
				return false;
			}
		}
	}

	return true;
}
