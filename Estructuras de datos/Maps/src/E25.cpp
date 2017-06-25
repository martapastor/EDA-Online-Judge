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

DECLARA_EXCEPCION(FechaOcupada);

DECLARA_EXCEPCION(MedicoNoExistente);

DECLARA_EXCEPCION(NoHayPacientes);

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
		delete[]_v;
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

		delete[]viejo;
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
@file Lista.h

Implementacion del TAD lista, utilizando una
lista doblemente enlazada.

Estructura de Datos y Algoritmos
Facultad de Informatica
Universidad Complutense de Madrid

(c) Marco Antonio Gomez Martin, 2012
*/
#ifndef __LIST_H
#define __LIST_H

#include <cassert>

/**
Implementacion del TAD Lista utilizando una lista doblemente enlazada.

Las operaciones son:

- EmptyList: -> List. Generadora implementada en el
constructor sin parametros.
- Push_front: List, Elem -> List. Generadora.
- push_back: List, Elem -> List. Modificadora.
- front: List - -> Elem. Observadora parcial
- pop_front: List - -> List. Modificadora parcial
- back: List - -> Elem. Observadora parcial
- pop_back: List - -> List. Modificadora parcial
- empty: List -> Bool. Observadora
- size: List -> Entero. Obervadora.
- at: List, Entero - -> Elem. Observador parcial.

@author Marco Antonio Gomez Martin
*/
template <class T>
class List {
private:
	/**
	Clase nodo que almacena internamente el elemento (de tipo T),
	y dos punteros, uno al nodo anterior y otro al nodo siguiente.
	Ambos punteros podrian ser NULL si el nodo es el primero
	y/o ultimo de la lista enlazada.
	*/
	class Nodo {
	public:
		Nodo() : _sig(NULL), _ant(NULL) {}
		Nodo(const T &elem) : _elem(elem), _sig(NULL), _ant(NULL) {}
		Nodo(Nodo *ant, const T &elem, Nodo *sig) :
			_elem(elem), _sig(sig), _ant(ant) {}

		T _elem;
		Nodo *_sig;
		Nodo *_ant;
	};

public:

	/** Constructor; operacion EmptyList. */
	List() : _prim(NULL), _ult(NULL), _numElems(0) {}

	/** Destructor; elimina la lista doblemente enlazada. */
	~List() {
		libera();
	}

	/**
	Anade un nuevo elemento en la cabeza de la lista.
	Operacion generadora.

	@param elem Elemento que se anade en la cabecera de
	la lista.
	*/
	void push_front(const T &elem) {
		_prim = insertaElem(elem, NULL, _prim);
		if (_ult == NULL)
			_ult = _prim;
	}

	/**
	Anade un nuevo elemento al final de la lista (a la
	"derecha"). Operacion modificadora.

	push_back(e, EmptyList) = Cons(e, EmptyList)
	push_back(e, Push_front(x, xs)) = Push_front(x, push_back(e, xs))
	*/
	void push_back(const T &elem) {
		_ult = insertaElem(elem, _ult, NULL);
		if (_prim == NULL)
			_prim = _ult;
	}

	/**
	Devuelve el valor almacenado en la cabecera de la
	lista. Es un error preguntar por el primero de
	una lista vacia.

	front(Push_front(x, xs)) = x
	error front(EmptyList)

	@return Elemento en la cabecera de la lista.
	*/
	const T &front() const {
		if (empty())
			throw EmptyListException();
		return _prim->_elem;
	}

	/**
	Devuelve el valor almacenado en la ultima posicion
	de la lista (a la derecha).
	Es un error preguntar por el primero de una lista vacia.

	back(Push_front(x, xs)) = x           SI empty(xs)
	back(Push_front(x, xs)) = back(xs)  SI !empty(xs)
	error back(EmptyList)

	@return Elemento en la cola de la lista.
	*/
	const T &back() const {
		if (empty())
			throw EmptyListException();

		return _ult->_elem;
	}

	/**
	Elimina el primer elemento de la lista.
	Es un error intentar obtener el resto de una lista vacia.

	pop_front(Push_front(x, xs)) = xs
	error pop_front(EmptyList)
	*/
	void pop_front() {
		if (empty())
			throw EmptyListException();

		Nodo *aBorrar = _prim;
		_prim = _prim->_sig;
		borraElem(aBorrar);
		if (_prim == NULL)
			_ult = NULL;
	}

	/**
	Elimina el ultimo elemento de la lista.
	Es un error intentar obtener el inicio de una lista vacia.

	inicio(Push_front(x, EmptyList)) = EmptyList
	inicio(Push_front(x, xs)) = Push_front(x, inicio(xs)) SI !empty(xs)
	error inicio(EmptyList)
	*/
	void pop_back() {
		if (empty())
			throw EmptyListException();

		Nodo *aBorrar = _ult;
		_ult = _ult->_ant;
		borraElem(aBorrar);
		if (_ult == NULL)
			_prim = NULL;
	}

	/**
	Operacion observadora para saber si una lista
	tiene o no elementos.

	empty(EmptyList) = true
	empty(Push_front(x, xs)) = false

	@return true si la lista no tiene elementos.
	*/
	bool empty() const {
		return _prim == NULL;
	}

	/**
	Devuelve el numero de elementos que hay en la
	lista.
	size(EmptyList) = 0
	size(Push_front(x, xs)) = 1 + size(xs)

	@return Numero de elementos.
	*/
	unsigned int size() const {
		return _numElems;
	}

	/**
	Devuelve el elemento i-esimo de la lista, teniendo
	en cuenta que el primer elemento (first())
	es el elemento 0 y el ultimo es size()-1,
	es decir idx esta en [0..size()-1].
	Operacion observadora parcial que puede fallar
	si se da un indice incorrecto. El indice es
	entero sin signo, para evitar que se puedan
	pedir elementos negativos.

	elem(0, Push_front(x, xs)) = x
	elem(n, Push_front(x, xs)) = elem(n-1, xs) si n > 0
	error elem(n, xs) si !( 0 <= n < size(xs) )
	*/
	const T &at(unsigned int idx) const {
		if (idx >= _numElems)
			throw InvalidAccessException();

		Nodo *aux = _prim;
		for (int i = 0; i < idx; ++i)
			aux = aux->_sig;

		return aux->_elem;
	}

	/**
	Clase interna que implementa un iterador sobre
	la lista que permite recorrer la lista pero no
	permite cambiarlos.
	*/
	class ConstIterator {
	public:
		void next() {
			if (_act == NULL) throw InvalidAccessException();
			_act = _act->_sig;
		}

		const T &elem() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_elem;
		}

		bool operator==(const ConstIterator &other) const {
			return _act == other._act;
		}

		bool operator!=(const ConstIterator &other) const {
			return !(this->operator==(other));
		}

		const T& operator*() const {
			return elem();
		}

		ConstIterator &operator++() {
			next();
			return *this;
		}

		ConstIterator operator++(int) {
			ConstIterator ret(*this);
			operator++();
			return ret;
		}

	protected:
		// Para que pueda construir objetos del
		// tipo iterador
		friend class List;

		ConstIterator() : _act(NULL) {}
		ConstIterator(Nodo *act) : _act(act) {}

		// Puntero al nodo actual del recorrido
		Nodo *_act;
	};

	/**
	Clase interna que implementa un iterador sobre
	la lista que permite recorrer la lista e incluso
	alterar el valor de sus elementos.
	*/
	class Iterator {
	public:
		void next() {
			if (_act == NULL) throw InvalidAccessException();
			_act = _act->_sig;
		}

		const T &elem() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_elem;
		}

		void set(const T &elem) const {
			if (_act == NULL) throw InvalidAccessException();
			_act->_elem = elem;
		}

		bool operator==(const Iterator &other) const {
			return _act == other._act;
		}

		bool operator!=(const Iterator &other) const {
			return !(this->operator==(other));
		}

		const T& operator*() const {
			return elem();
		}

		T& operator*() {
			// Codigo identico al de elem() porque este es const,
			// por lo que no se puede usar desde aqui.
			if (_act == NULL) throw InvalidAccessException();
			return _act->_elem;
		}

		Iterator &operator++() {
			next();
			return *this;
		}

		Iterator operator++(int) {
			Iterator ret(*this);
			operator++();
			return ret;
		}

	protected:
		// Para que pueda construir objetos del
		// tipo iterador
		friend class List;

		Iterator() : _act(NULL) {}
		Iterator(Nodo *act) : _act(act) {}

		// Puntero al nodo actual del recorrido
		Nodo *_act;
	};

	/**
	Devuelve el iterador constante al principio de la lista.
	@return iterador al principio de la lista;
	coincidira con cend() si la lista esta vacia.
	*/
	ConstIterator cbegin() const {
		return ConstIterator(_prim);
	}

	/**
	@return Devuelve un iterador constante al final del recorrido
	(fuera de este).
	*/
	ConstIterator cend() const {
		return ConstIterator(NULL);
	}

	/**
	Devuelve el iterador no constante al principio de la lista.
	@return iterador al principio de la lista;
	coincidira con end() si la lista esta vacia.
	*/
	Iterator begin() {
		return Iterator(_prim);
	}

	/**
	@return Devuelve un iterador no constante al final del recorrido
	(fuera de este).
	*/
	Iterator end() const {
		return Iterator(NULL);
	}


	/**
	Permite eliminar de la lista el elemento
	apuntado por el iterador que se pasa como parametro.
	El iterador recibido DEJA DE SER VALIDO. En su
	lugar, debera utilizarse el iterador devuelto, que
	apuntara al siguiente elemento al borrado.
	@param it Iterador colocado en el elemento que se
	quiere borrar.
	@return Nuevo iterador colocado en el elemento siguiente
	al borrado (podria coincidir con final() si el
	elemento que se borro era el ultimo de la lista).
	*/
	Iterator erase(const Iterator &it) {
		if (it._act == NULL)
			throw InvalidAccessException();

		// Cubrimos los casos especiales donde
		// borramos alguno de los extremos
		if (it._act == _prim) {
			pop_front();
			return Iterator(_prim);
		}
		else if (it._act == _ult) {
			pop_back();
			return Iterator(NULL);
		}
		else {
			// El elemento a borrar es interno a la lista.
			Nodo *sig = it._act->_sig;
			borraElem(it._act);
			return Iterator(sig);
		}
	}

	/**
	Metodo para insertar un elemento en la lista
	en el punto marcado por el iterador. En concreto,
	se anade _justo antes_ que el elemento actual. Es
	decir, si it==l.primero(), el elemento insertado se
	convierte en el primer elemento (y el iterador
	apuntara al segundo). Si it==l.final(), el elemento
	insertado sera el ultimo (e it seguira apuntando
	fuera del recorrido).
	@param elem Valor del elemento a insertar.
	@param it Punto en el que insertar el elemento.
	*/
	void insert(const T &elem, const Iterator &it) {

		// Caso especial: anadir al principio
		if (_prim == it._act) {
			push_front(elem);
		}
		else
			// Caso especial: anadir al final
			if (it._act == NULL) {
				push_back(elem);
			}
		// Caso normal
			else {
				insertaElem(elem, it._act->_ant, it._act);
			}
	}

	// //
	// METODOS DE "FONTANERIA" DE C++ QUE HACEN VERSATIL
	// A LA CLASE
	// //

	/** Constructor copia */
	List(const List<T> &other) : _prim(NULL), _ult(NULL) {
		copia(other);
	}

	/** Operador de asignacion */
	List<T> &operator=(const List<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparacion */
	bool operator==(const List<T> &rhs) const {
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

	bool operator!=(const List<T> &rhs) const {
		return !(*this == rhs);
	}


protected:

	void libera() {
		libera(_prim);
		_prim = NULL;
		_ult = NULL;
	}

	void copia(const List<T> &other) {
		// En vez de trabajar con punteros en la insercion,
		// usamos ponDr
		_prim = 0;
		_numElems = 0;

		Nodo *act = other._prim;
		while (act != NULL) {
			push_back(act->_elem);
			act = act->_sig;
		}
	}

private:


	/**
	Inserta un elemento entre el nodo1 y el nodo2.
	Devuelve el puntero al nodo creado.
	Caso general: los dos nodos existen.
	nodo1->_sig == nodo2
	nodo2->_ant == nodo1
	Casos especiales: alguno de los nodos no existe
	nodo1 == NULL y/o nodo2 == NULL
	*/
	Nodo *insertaElem(const T &e, Nodo *nodo1, Nodo *nodo2) {
		Nodo *nuevo = new Nodo(nodo1, e, nodo2);
		if (nodo1 != NULL)
			nodo1->_sig = nuevo;
		if (nodo2 != NULL)
			nodo2->_ant = nuevo;
		_numElems++;
		return nuevo;
	}

	/**
	Elimina el nodo n. Si el nodo tiene nodos antes
	o despues, actualiza sus punteros anterior y siguiente.
	Caso general: hay nodos anterior y siguiente.
	Casos especiales: algunos de los nodos (anterior o siguiente
	a n) no existen.
	*/
	void borraElem(Nodo *n) {
		assert(n != NULL);
		Nodo *ant = n->_ant;
		Nodo *sig = n->_sig;
		if (ant != NULL)
			ant->_sig = sig;
		if (sig != NULL)
			sig->_ant = ant;
		_numElems--;
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
		assert(!prim || !prim->_ant);

		while (prim != NULL) {
			Nodo *aux = prim;
			prim = prim->_sig;
			delete aux;
		}
	}

	// Puntero al primer y ultimo elemento
	Nodo *_prim, *_ult;

	// Numero de elementos (numero de nodos entre _prim y _ult)
	unsigned int _numElems;
};

#endif // __LIST_H


/**
@file Hash.h

Declaracion e implementacion de funciones de localizacion para
tipos basicos y funcion generica que confia en la existencia
del metodo metodo hash de las clases.

Estructura de Datos y Algoritmos
Facultad de Informatica
Universidad Complutense de Madrid

(c) Antonio Sanchez Ruiz-Granados, 2012
*/

#ifndef __HASH_H
#define __HASH_H

#include <string>

// ----------------------------------------------------
//
// Funciones hash para distintos tipos de datos basicos
//
// ----------------------------------------------------


inline unsigned int hash(unsigned int clave) {
	return clave;
}

inline unsigned int hash(int clave) {
	return (unsigned int)clave;
}

inline unsigned int hash(char clave) {
	return clave;
}

// Fowler/Noll/Vo (FNV) -- adaptada de http://bretmulvey.com/hash/6.html
inline unsigned int hash(std::string clave) {
	const unsigned int p = 16777619; // primo grande
	unsigned int hash = 2166136261;  // valor inicial
	for (unsigned int i = 0; i<clave.size(); i++)
		hash = (hash ^ clave[i]) * p; // ^ es xor binario
									  // mezcla final
	hash += hash << 13;
	hash ^= hash >> 7;
	hash += hash << 3;
	hash ^= hash >> 17;
	hash += hash << 5;
	return hash;
}

/**
* Funcion hash generica para clases que implementen un
* metodo publico hash.
*/
template<class C>
unsigned int hash(const C &clave) {
	return clave.hash();
}


#endif // __HASH_H


/**
*  @file HashMap.h
*
*  Implementacion dinamica del TAD Dictionary utilizando
*  tablas de busqueda
*
*  Estructura de Datos y Algoritmos
*  Facultad de Informatica
*  Universidad Complutense de Madrid
*
* (c) Antonio Sanchez Ruiz-Granados, 2012
*/
#ifndef __HASHMAP_H
#define __HASHMAP_H

// funciones de hash a usar

/**
* Implementacion dinamica del TAD Dictionary utilizando
* una tabla hash abierta
*
* Las operaciones son:
*
* - HashMapVacio: operacion generadora que construye
* una tabla hash vacia
*
* - Insert(clave, valor): generadora que añade una
* nueva pareja (clave, valor) a la tabla. Si la
* clave ya estaba se sustituye el valor.
*
* - erase(clave): operacion modificadora. Elimina la
* clave de la tabla. Si la clave no esta,
* la operacion no tiene efecto.
*
* - at(clave): operacion observadora que devuelve
* el valor asociado a una clave. Es un error preguntar
* por una clave que no existe.
*
* - contains(clave): operacion observadora. Sirve para
* averiguar si una clave esta presente en la tabla.
*
* - empty(): operacion observadora que indica si
* la tabla tiene alguna clave introducida.
*
* @author Antonio Sanchez Ruiz-Granados
*/
template <class Clave, class Valor>
class HashMap {
private:
	/**
	* La tabla contiene un array de punteros a nodos. Cada nodo contiene una
	* clave, un valor y un puntero al siguiente nodo.
	*/
	class Nodo {
	public:
		/* Constructores. */
		Nodo(const Clave &clave, const Valor &valor) :
			_clave(clave), _valor(valor), _sig(NULL) {};

		Nodo(const Clave &clave, const Valor &valor, Nodo *sig) :
			_clave(clave), _valor(valor), _sig(sig) {};

		/* Atributos publicos. */
		Clave _clave;
		Valor _valor;
		Nodo *_sig;  // Puntero al siguiente nodo.
	};

public:

	/**
	* Tamaño inicial de la tabla.
	*/
	static const int TAM_INICIAL = 8;

	/** Constructor por defecto que implementa HashMapVacio */
	HashMap() : _v(new Nodo*[TAM_INICIAL]), _tam(TAM_INICIAL), _numElems(0) {
		for (unsigned int i = 0; i<_tam; ++i) {
			_v[i] = NULL;
		}
	}

	/** Destructor; elimina las listas enlazadas */
	~HashMap() {
		libera();
	}

	/**
	*	 Operacion generadora que añade una nueva clave/valor
	*	 a esta tabla
	*	 @param clave Clave nueva.
	*	 @param valor Valor asociado a esa clave. Si la clave
	*	 ya se habia insertado previamente, sustituimos el valor
	*	 viejo por el nuevo.
	*/
	void insert(const Clave &clave, const Valor &valor) {
		// Si la ocupacion es muy alta ampliamos la tabla
		float ocupacion = 100 * ((float)_numElems) / _tam;
		if (ocupacion > MAX_OCUPACION)
			amplia();

		// Obtenemos el indice asociado a la clave.
		unsigned int ind = ::hash(clave) % _tam;

		// Si la clave ya existia, actualizamos su valor
		Nodo *nodo = buscaNodo(clave, _v[ind]);
		if (nodo != NULL) {
			nodo->_valor = valor;
		}
		else {
			// Si la clave no existia, creamos un nuevo nodo y lo insertamos
			// al principio
			_v[ind] = new Nodo(clave, valor, _v[ind]);
			_numElems++;
		}
	}

	/**
	*	 Operacion modificadora que elimina una clave de la tabla.
	*	 Si la clave no existia la operacion no tiene efecto.
	*
	*	   erase(elem, EmptyHashMap) = HashMapVacio
	*	   erase(e, insert(c, v, arbol)) =
	*	                     inserta(c, v, erase(e, arbol)) si c != e
	*	   erase(e, insert(c, v, arbol)) = erase(e, arbol) si c == e
	*
	*	 @param clave Clave a eliminar.
	*/
	void erase(const Clave &clave) {
		// Obtenemos el indice asociado a la clave.
		unsigned int ind = ::hash(clave) % _tam;

		// Buscamos el nodo que contiene esa clave y el nodo anterior.
		Nodo *act = _v[ind];
		Nodo *ant = NULL;
		buscaNodo(clave, act, ant);

		if (act != NULL) {

			// Sacamos el nodo de la secuencia de nodos.
			if (ant != NULL) {
				ant->_sig = act->_sig;
			}
			else {
				_v[ind] = act->_sig;
			}

			// Borramos el nodo extraido.
			delete act;
			_numElems--;
		}
	}

	/**
	*	 Operacion observadora que devuelve el valor asociado
	*	 a una clave dada.
	*
	*	 at(e, insert(c, v, tabla)) = v si e == c
	*	 at(e, insert(c, v, tabla)) = at(e, tabla) si e != c
	*	 error at(EmptyHashMap)
	*
	*	 @param clave Clave por la que se pregunta.
	*/
	const Valor &at(const Clave &clave) const {
		// Obtenemos el indice asociado a la clave.
		unsigned int ind = ::hash(clave) % _tam;

		// Buscamos un nodo que contenga esa clave.
		Nodo *nodo = buscaNodo(clave, _v[ind]);
		if (nodo == NULL)
			throw EClaveErronea();

		return nodo->_valor;
	}

	/**
	*	 Operacion observadora que permite averiguar si una clave
	*	 determinada esta o no en la tabla hash.
	*
	*	 contains(e, EmptyHashMap) = false
	*	 contains(e, insert(c, v, arbol)) = true si e == c
	*	 contains(e, insert(c, v, arbol)) = contains(e, arbol) si e != c
	*
	*	 @param clave Clave por la que se pregunta.
	*	 @return true si el diccionario contiene un valor asociado
	*	 a esa clave.
	*/
	bool contains(const Clave &clave) const {
		// Obtenemos el indice asociado a la clave.
		unsigned int ind = ::hash(clave) % _tam;

		// Buscamos un nodo que contenga esa clave.
		Nodo *nodo = buscaNodo(clave, _v[ind]);
		return nodo != NULL;
	}

	/**
	*	 Operacion observadora que devuelve si el arbol
	*	 es vacio (no contiene elementos) o no.
	*
	*	 empty(EmptyHashMap) = true
	*	 empty(insert(c, v, arbol)) = false
	*/
	bool empty() const {
		return _numElems == 0;
	}

	/**
	*	 Sobrecarga del operador [] que permite acceder
	*	 al valor asociado a una clave y modificarlo.
	*	 Si el elemento buscado no estaba, se inserta uno
	*	 con el valor por defecto del tipo Valor.
	*/
	Valor &operator[](const Clave &clave) {
		// Obtenemos el indice asociado a la clave.
		unsigned int ind = ::hash(clave) % _tam;

		// Buscamos un nodo que contenga esa clave.
		Nodo *nodo = buscaNodo(clave, _v[ind]);
		if (nodo == NULL) {
			// No esta, lo añadimos y vemos donde quedo.
			insert(clave, Valor());
			// ind puede cambiar si al insertar hubo expansion
			ind = ::hash(clave) % _tam;
			nodo = buscaNodo(clave, _v[ind]);
		}
		return nodo->_valor;
	}

	// //
	// ITERADOR CONSTANTE Y FUNCIONES RELACIONADAS
	// //

	/**
	*	 Clase interna que implementa un iterador sobre
	*	 la lista que permite recorrer la tabla pero no
	*	 permite modificarla.
	*/
	class ConstIterator {
	public:
		void next() {
			if (_act == NULL) throw InvalidAccessException();

			// Buscamos el siguiente nodo de la lista de nodos.
			_act = _act->_sig;

			// Si hemos llegado al final de la lista de nodos, seguimos
			// buscando por el vector _v.
			while ((_act == NULL) && (_ind < _tabla->_tam - 1)) {
				++_ind;
				_act = _tabla->_v[_ind];
			}
		}

		const Clave &key() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_clave;
		}

		const Valor &value() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_valor;
		}

		bool operator==(const ConstIterator &other) const {
			return _act == other._act;
		}

		bool operator!=(const ConstIterator &other) const {
			return !(this->operator==(other));
		}

		ConstIterator &operator++() {
			next();
			return *this;
		}

		ConstIterator operator++(int) {
			ConstIterator ret(*this);
			operator++();
			return ret;
		}

	protected:
		// Para que pueda construir objetos del tipo iterador
		friend class HashMap;

		ConstIterator(const HashMap* tabla, Nodo* act, unsigned int ind)
			: _tabla(tabla), _act(act), _ind(ind) { }

		const HashMap *_tabla;  ///< Tabla que se esta recorriendo
		Nodo* _act;             ///< Puntero al nodo actual del recorrido
		unsigned int _ind;      ///< Indice actual en el vector _v
	};

	/**
	*	 Devuelve el iterador constante al principio del
	*	 diccionario (clave mas pequeña).
	*	 @return iterador al principio del recorrido;
	*	 coincidira con cend() si el diccionario esta vacio.
	*/
	ConstIterator cbegin() const {
		unsigned int ind = 0;
		Nodo *act = _v[0];
		while (ind < _tam - 1 && act == NULL) {
			ind++;
			act = _v[ind];
		}
		return ConstIterator(this, act, ind);
	}

	/**
	*	 @return Devuelve un iterador al final del recorrido
	*	 (fuera de este).
	*/
	ConstIterator cend() const {
		return ConstIterator(this, NULL, 0);
	}

	/**
	*	 @return Devuelve un iterador a la posicion de
	*	 clave, o al final del recorrido si clave no encontrada
	*/
	ConstIterator find(const Clave &clave) const {
		// Obtenemos el indice asociado a la clave.
		unsigned int ind = ::hash(clave) % _tam;

		// Buscamos un nodo que contenga esa clave.
		Nodo *nodo = buscaNodo(clave, _v[ind]);

		// si nodo == NULL, devuelve en realidad cend()
		return ConstIterator(this, nodo, ind);
	}

	// //
	// ITERADOR NO CONSTANTE Y FUNCIONES RELACIONADAS
	// //

	/**
	*	 Clase interna que implementa un iterador sobre
	*	 la arbol de busqueda que permite recorrer la lista e incluso
	*	 alterar el valor de sus elementos.
	*/
	class Iterator {
	public:
		void next() {
			if (_act == NULL) throw InvalidAccessException();

			// Buscamos el siguiente nodo de la lista de nodos.
			_act = _act->_sig;

			// Si hemos llegado al final de la lista de nodos, seguimos
			// buscando por el vector _v.
			while ((_act == NULL) && (_ind < _tabla->_tam - 1)) {
				++_ind;
				_act = _tabla->_v[_ind];
			}
		}

		const Clave &key() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_clave;
		}

		Valor &value() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_valor;
		}

		bool operator==(const Iterator &other) const {
			return _act == other._act;
		}

		bool operator!=(const Iterator &other) const {
			return !(this->operator==(other));
		}

		Iterator &operator++() {
			next();
			return *this;
		}

		Iterator operator++(int) {
			Iterator ret(*this);
			operator++();
			return ret;
		}

	protected:
		// Para que pueda construir objetos del tipo iterador
		friend class HashMap;

		Iterator(const HashMap* tabla, Nodo* act, unsigned int ind)
			: _tabla(tabla), _act(act), _ind(ind) { }

		const HashMap *_tabla;  ///< Tabla que se esta recorriendo
		Nodo* _act;             ///< Puntero al nodo actual del recorrido
		unsigned int _ind;      ///< indice actual en el vector _v
	};

	/**
	*	 Devuelve el iterador al principio de la lista.
	*	 @return iterador al principio de la lista;
	*	 coincidira con final() si la lista esta vacia.
	*/
	Iterator begin() {
		unsigned int ind = 0;
		Nodo *act = _v[0];
		while (ind < _tam - 1 && act == NULL) {
			ind++;
			act = _v[ind];
		}
		return Iterator(this, act, ind);
	}

	/**
	*	 @return Devuelve un iterador al final del recorrido
	*	 (fuera de este).
	*/
	Iterator end() const {
		return Iterator(this, NULL, 0);
	}

	/**
	*	 @return Devuelve un iterador a la posicion de
	*	 clave, o al final del recorrido si clave no encontrada
	*/
	Iterator find(const Clave &clave) {
		// Obtenemos el indice asociado a la clave.
		unsigned int ind = ::hash(clave) % _tam;

		// Buscamos un nodo que contenga esa clave.
		Nodo *nodo = buscaNodo(clave, _v[ind]);

		// si nodo == NULL, devuelve en realidad cend()
		return Iterator(this, nodo, ind);
	}


	// //
	// METODOS DE "FONTANERIA" DE C++ QUE HACEN VERSATIL
	// A LA CLASE
	// //

	/** Constructor copia */
	HashMap(const HashMap<Clave, Valor> &other) {
		copia(other);
	}

	/** Operador de asignacion */
	HashMap<Clave, Valor> &operator=(const HashMap<Clave, Valor> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

private:

	// Para que el iterador pueda acceder a la parte privada
	friend class Iterador;

	/**
	* Libera toda la memoria dinamica reservada para la tabla.
	*/
	void libera() {

		// Liberamos las listas de nodos.
		for (unsigned int i = 0; i<_tam; i++) {
			liberaNodos(_v[i]);
		}

		// Liberamos el array de punteros a nodos.
		if (_v != NULL) {
			delete[] _v;
			_v = NULL;
		}
	}

	/**
	* Libera un nodo y todos los siguientes.
	*
	* @param prim puntero al primer nodo de la lista a liberar.
	*/
	static void liberaNodos(Nodo *prim) {

		while (prim != NULL) {
			Nodo *aux = prim;
			prim = prim->_sig;
			delete aux;
		}
	}

	/**
	* Hace una copia de la tabla que recibe como parametro. Antes de llamar
	* a este metodo se debe invocar al metodo "libera".
	*
	* @param other tabla que se quiere copiar.
	*/
	void copia(const HashMap<Clave, Valor> &other) {
		_tam = other._tam;
		_numElems = other._numElems;

		// Reservar memoria para el array de punteros a nodos.
		_v = new Nodo*[_tam];
		for (unsigned int i = 0; i<_tam; ++i) {
			_v[i] = NULL;

			// Copiar la lista de nodos de other._v[i] a _v[i].
			// La lista de nodos queda invertida con respecto a la original.
			Nodo *act = other._v[i];
			while (act != NULL) {
				_v[i] = new Nodo(act->_clave, act->_valor, _v[i]);
				act = act->_sig;
			}
		}
	}

	/**
	* Este metodo duplica la capacidad del array de punteros actual.
	*/
	void amplia() {
		// Creamos un puntero al array actual y anotamos su tamaño.
		Nodo **vAnt = _v;
		unsigned int tamAnt = _tam;

		// Duplicamos el array en otra posicion de memoria.
		_tam *= 2;
		_v = new Nodo*[_tam];
		for (unsigned int i = 0; i<_tam; ++i)
			_v[i] = NULL;

		// Recorremos el array original moviendo cada nodo a la nueva
		// posicion que le corresponde en el nuevo array.
		for (unsigned int i = 0; i<tamAnt; ++i) {

			// IMPORTANTE: Al modificar el tamaño tambien se modifica el indice
			// asociado a cada nodo. Es decir, los nodos se mueven a posiciones
			// distintas en el nuevo array.

			// NOTA: por eficiencia movemos los nodos del array antiguo al
			// nuevo, no creamos nuevos nodos.

			// Recorremos la lista de nodos
			Nodo *nodo = vAnt[i];
			while (nodo != NULL) {
				Nodo *aux = nodo;
				nodo = nodo->_sig;

				// Calculamos el nuevo indice del nodo, lo desenganchamos del
				// array antiguo y lo enganchamos al nuevo.
				unsigned int ind = ::hash(aux->_clave) % _tam;
				aux->_sig = _v[ind];
				_v[ind] = aux;
			}
		}

		// Borramos el array antiguo (ya no contiene ningun nodo).
		delete[] vAnt;
	}

	/**
	* Busca un nodo a partir del nodo "act" que contenga la clave dada. Si lo
	* encuentra, "act" quedara apuntando a dicho nodo y "ant" al nodo anterior.
	* Si no lo encuentra "act" quedara apuntando a NULL.
	*
	* @param clave clave del nodo que se busca.
	* @param act [in/out] inicialmente indica el primer nodo de la busqueda y
	*            al finalizar indica el nodo encontrado o NULL.
	* @param ant [out] puntero al nodo anterior a "act" o NULL.
	*/
	static void buscaNodo(const Clave &clave, Nodo* &act, Nodo* &ant) {
		ant = NULL;
		bool encontrado = false;
		while ((act != NULL) && !encontrado) {

			// Comprobar si el nodo actual contiene la clave buscada
			if (act->_clave == clave) {
				encontrado = true;
			}
			else {
				ant = act;
				act = act->_sig;
			}
		}
	}

	/**
	* Busca un nodo a partir de "prim" que contenga la clave dada. A
	* diferencia del otro metodo "buscaNodo", este no devuelve un puntero al
	* nodo anterior.
	*
	* @param clave clave del nodo que se busca.
	* @param prim nodo a partir del cual realizar la busqueda.
	* @return nodo encontrado o NULL.
	*/
	static Nodo* buscaNodo(const Clave &clave, Nodo* prim) {
		Nodo *act = prim;
		Nodo *ant = NULL;
		buscaNodo(clave, act, ant);
		return act;
	}

	/**
	* Ocupacion maxima permitida antes de ampliar la tabla en tanto por cientos.
	*/
	static const unsigned int MAX_OCUPACION = 80;


	Nodo **_v;               ///< Array de punteros a Nodo.
	unsigned int _tam;       ///< Tamaño del array _v.
	unsigned int _numElems;  ///< Numero de elementos en la tabla.
};

#endif // __HASHMAP_H


/**
@file TreeMap.h

Implementacion dinamica del TAD Dictionary utilizando
arboles de busqueda.

Estructura de Datos y Algoritmos
Facultad de Informatica
Universidad Complutense de Madrid

(c) Marco Antonio Gomez Martin, 2012
*/
#ifndef __TREEMAP_H
#define __TREEMAP_H

/**
Implementacion dinamica del TAD Dictionary utilizando
arboles de busqueda (no auto-balanceados).

Las operaciones son:

- TreeMapVacio: operacion generadora que construye
un arbol de busqueda vacio.

- Insert(clave, valor): generadora que añade una
nueva pareja (clave, valor) al arbol. Si la
clave ya estaba se sustituye el valor.

- erase(clave): operacion modificadora. Elimina la
clave del arbol de busqueda.  Si la clave no esta,
la operacion no tiene efecto.

- at(clave): operacion observadora que devuelve
el valor asociado a una clave. Es un error preguntar
por una clave que no existe.

- contains(clave): operacion observadora. Sirve para
averiguar si se ha introducido una clave en el
arbol.

- empty(): operacion observadora que indica si
el arbol de busqueda tiene alguna clave introducida.

@author Marco Antonio Gomez Martin
*/
template <class Clave, class Valor>
class TreeMap {
private:
	/**
	Clase nodo que almacena internamente la pareja (clave, valor)
	y los punteros al hijo izquierdo y al hijo derecho.
	*/
	class Nodo {
	public:
		Nodo() : _iz(NULL), _dr(NULL) {}
		Nodo(const Clave &clave, const Valor &valor)
			: _clave(clave), _valor(valor), _iz(NULL), _dr(NULL) {}
		Nodo(Nodo *iz, const Clave &clave, const Valor &valor, Nodo *dr)
			: _clave(clave), _valor(valor), _iz(iz), _dr(dr) {}

		Clave _clave;
		Valor _valor;
		Nodo *_iz;
		Nodo *_dr;
	};

public:

	/** Constructor; operacion EmptyTreeMap */
	TreeMap() : _ra(NULL) {
	}

	/** Destructor; elimina la estructura jerarquica de nodos. */
	~TreeMap() {
		libera();
		_ra = NULL;
	}

	/**
	Operacion generadora que añade una nueva clave/valor
	a un arbol de busqueda.
	@param clave Clave nueva.
	@param valor Valor asociado a esa clave. Si la clave
	ya se habia insertado previamente, sustituimos el valor
	viejo por el nuevo.
	*/
	void insert(const Clave &clave, const Valor &valor) {
		_ra = insertaAux(clave, valor, _ra);
	}

	/**
	Operacion modificadora que elimina una clave del arbol.
	Si la clave no existia la operacion no tiene efecto.

	erase(elem, EmptyTreeMap) = TreeMapVacio
	erase(e, insert(c, v, arbol)) =
	inserta(c, v, erase(e, arbol)) si c != e
	erase(e, insert(c, v, arbol)) = erase(e, arbol) si c == e

	@param clave Clave a eliminar.
	*/
	void erase(const Clave &clave) {
		_ra = borraAux(_ra, clave);
	}

	/**
	Operacion observadora que devuelve el valor asociado
	a una clave dada.

	at(e, insert(c, v, arbol)) = v si e == c
	at(e, insert(c, v, arbol)) = at(e, arbol) si e != c
	error at(EmptyTreeMap)

	@param clave Clave por la que se pregunta.
	*/
	const Valor &at(const Clave &clave) const {
		Nodo *p = buscaAux(_ra, clave);
		if (p == NULL)
			throw EClaveErronea();

		return p->_valor;
	}

	/**
	Operacion observadora que permite averiguar si una clave
	determinada esta o no en el arbol de busqueda.

	contains(e, EmptyTreeMap) = false
	contains(e, insert(c, v, arbol)) = true si e == c
	contains(e, insert(c, v, arbol)) = contains(e, arbol) si e != c

	@param clave Clave por la que se pregunta.
	@return true si el diccionario contiene un valor asociado
	a esa clave.
	*/
	bool contains(const Clave &clave) const {
		return (buscaAux(_ra, clave) != NULL) ? true : false;
	}

	/**
	Operacion observadora que devuelve si el arbol
	es vacio (no contiene elementos) o no.

	empty(EmptyTreeMap) = true
	empty(insert(c, v, arbol)) = false
	*/
	bool empty() const {
		return _ra == NULL;
	}

	/**
	Sobrecarga del operador [] que permite acceder
	al valor asociado a una clave y modificarlo.
	Si el elemento buscado no estaba, se inserta uno
	con el valor por defecto del tipo Valor.
	*/
	Valor &operator[](const Clave &clave) {
		// Buscamos. Seria mejor hacerlo in-line; asi en
		// caso de no encontrarlo no hace falta buscar otra
		// vez donde insertar la clave.
		Nodo * ret = buscaAux(_ra, clave);
		if (ret == NULL) {
			// No esta, lo añadimos y vemos donde
			// quedo. Hay formas mas eficientes para evitar
			// recorridos por el arbol.
			insert(clave, Valor());
			ret = buscaAux(_ra, clave);
		}

		return ret->_valor;
	}

	// //
	// ITERADOR CONSTANTE Y FUNCIONES RELACIONADAS
	// //

	/**
	Clase interna que implementa un iterador sobre
	la lista que permite recorrer el arbol pero no
	permite modificarlo.
	*/
	class ConstIterator {
	public:
		void next() {
			if (_act == NULL) throw InvalidAccessException();

			// Si hay hijo derecho, saltamos al primero
			// en inorden del hijo derecho
			if (_act->_dr != NULL)
				_act = primeroInOrden(_act->_dr);
			else {
				// Si no, vamos al primer ascendiente
				// no visitado. Para eso consultamos
				// la pila; si ya esta vacia, no quedan
				// ascendientes por visitar
				if (_ascendientes.empty())
					_act = NULL;
				else {
					_act = _ascendientes.top();
					_ascendientes.pop();
				}
			}
		}

		const Clave &key() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_clave;
		}

		const Valor &value() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_valor;
		}

		bool operator==(const ConstIterator &other) const {
			return _act == other._act;
		}

		bool operator!=(const ConstIterator &other) const {
			return !(this->operator==(other));
		}

		ConstIterator &operator++() {
			next();
			return *this;
		}

		ConstIterator operator++(int) {
			ConstIterator ret(*this);
			operator++();
			return ret;
		}

	protected:
		// Para que pueda construir objetos del
		// tipo iterador
		friend class TreeMap;

		ConstIterator() : _act(NULL) {}
		ConstIterator(Nodo *act) {
			_act = primeroInOrden(act);
		}

		/**
		Busca el primer elemento en inorden de
		la estructura jerarquica de nodos pasada
		como parametro; va apilando sus ascendientes
		para poder "ir hacia atras" cuando sea necesario.
		@param p Puntero a la raiz de la subestructura.
		*/
		Nodo *primeroInOrden(Nodo *p) {
			if (p == NULL)
				return NULL;

			while (p->_iz != NULL) {
				_ascendientes.push(p);
				p = p->_iz;
			}
			return p;
		}

		// Puntero al nodo actual del recorrido
		// NULL si hemos llegado al final.
		Nodo *_act;

		// Ascendientes del nodo actual
		// an por visitar
		Stack<Nodo*> _ascendientes;
	};

	/**
	Devuelve el iterador constante al principio del
	diccionario (clave mas pequea).
	@return iterador al principio del recorrido;
	coincidir con cend() si el diccionario esta vacio.
	*/
	ConstIterator cbegin() const {
		return ConstIterator(_ra);
	}

	/**
	@return Devuelve un iterador al final del recorrido
	(fuera de ste).
	*/
	ConstIterator cend() const {
		return ConstIterator(NULL);
	}

	ConstIterator find(const Clave &c) const {
		Stack<Nodo*> ascendientes;
		Nodo *p = _ra;
		while ((p != NULL) && (p->_clave != c)) {
			if (p->_clave > c) {
				ascendientes.push(p);
				p = p->_iz;
			}
			else
				p = p->_dr;
		}
		ConstIterator ret;
		ret._act = p;
		if (p != NULL)
			ret._ascendientes = ascendientes;
		return ret;
	}

	// //
	// ITERADOR NO CONSTANTE Y FUNCIONES RELACIONADAS
	// //

	/**
	Clase interna que implementa un iterador sobre
	la arbol de busqueda que permite recorrer la lista e incluso
	alterar el valor de sus elementos.
	*/
	class Iterator {
	public:
		void next() {
			if (_act == NULL) throw InvalidAccessException();

			// Si hay hijo derecho, saltamos al primero
			// en inorden del hijo derecho
			if (_act->_dr != NULL)
				_act = primeroInOrden(_act->_dr);
			else {
				// Si no, vamos al primer ascendiente
				// no visitado. Para eso consultamos
				// la pila; si ya esta vacia, no quedan
				// ascendientes por visitar
				if (_ascendientes.empty())
					_act = NULL;
				else {
					_act = _ascendientes.top();
					_ascendientes.pop();
				}
			}
		}

		const Clave &key() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_clave;
		}

		Valor &value() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_valor;
		}

		bool operator==(const Iterator &other) const {
			return _act == other._act;
		}

		bool operator!=(const Iterator &other) const {
			return !(this->operator==(other));
		}

		Iterator &operator++() {
			next();
			return *this;
		}

		Iterator operator++(int) {
			Iterator ret(*this);
			operator++();
			return ret;
		}

	protected:
		// Para que pueda construir objetos del
		// tipo iterador
		friend class TreeMap;

		Iterator() : _act(NULL) {}
		Iterator(Nodo *act) {
			_act = primeroInOrden(act);
		}

		/**
		Busca el primer elemento en inorden de
		la estructura jerarquica de nodos pasada
		como parametro; va apilando sus ascendientes
		para poder "ir hacia atras" cuando sea necesario.
		@param p Puntero a la raiz de la subestructura.
		*/
		Nodo *primeroInOrden(Nodo *p) {
			if (p == NULL)
				return NULL;

			while (p->_iz != NULL) {
				_ascendientes.push(p);
				p = p->_iz;
			}
			return p;
		}

		// Puntero al nodo actual del recorrido
		// NULL si hemos llegado al final.
		Nodo *_act;

		// Ascendientes del nodo actual
		// an por visitar
		Stack<Nodo*> _ascendientes;
	};

	/**
	Devuelve el iterador al principio de la lista.
	@return iterador al principio de la lista;
	coincidir con final() si la lista esta vacia.
	*/
	Iterator begin() {
		return Iterator(_ra);
	}

	/**
	@return Devuelve un iterador al final del recorrido
	(fuera de ste).
	*/
	Iterator end() const {
		return Iterator(NULL);
	}

	Iterator find(const Clave &c) {
		Stack<Nodo*> ascendientes;
		Nodo *p = _ra;
		while ((p != NULL) && (p->_clave != c)) {
			if (p->_clave > c) {
				ascendientes.push(p);
				p = p->_iz;
			}
			else
				p = p->_dr;
		}
		Iterator ret;
		ret._act = p;
		if (p != NULL)
			ret._ascendientes = ascendientes;
		return ret;
	}


	// //
	// METODOS DE "FONTANERA" DE C++ QUE HACEN VERSTIL
	// A LA CLASE
	// //

	/** Constructor copia */
	TreeMap(const TreeMap<Clave, Valor> &other) : _ra(NULL) {
		copia(other);
	}

	/** Operador de asignacin */
	TreeMap<Clave, Valor> &operator=(const TreeMap<Clave, Valor> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

protected:

	/**
	Constructor protegido que crea un arbol
	a partir de una estructura jerarquica de nodos
	previamente creada.
	Se utiliza en hijoIz e hijoDr.
	*/
	TreeMap(Nodo *raiz) : _ra(raiz) {
	}

	void libera() {
		libera(_ra);
	}

	void copia(const TreeMap &other) {
		_ra = copiaAux(other._ra);
	}

private:

	/**
	Elimina todos los nodos de una estructura arbrea
	que comienza con el puntero ra.
	Se admite que el nodo sea NULL (no habra nada que
	liberar).
	*/
	static void libera(Nodo *ra) {
		if (ra != NULL) {
			libera(ra->_iz);
			libera(ra->_dr);
			delete ra;
		}
	}

	/**
	Copia la estructura jerarquica de nodos pasada
	como parametro (puntero a su raiz) y devuelve un
	puntero a una nueva estructura jerarquica, copia
	de anterior (y que, por tanto, habra que liberar).
	*/
	static Nodo *copiaAux(Nodo *ra) {
		if (ra == NULL)
			return NULL;

		return new Nodo(copiaAux(ra->_iz),
			ra->_clave, ra->_valor,
			copiaAux(ra->_dr));
	}

	/**
	Inserta una pareja (clave, valor) en la estructura
	jerarquica que comienza en el puntero pasado como parametro.
	Ese puntero se admite que sea NULL, por lo que se creara
	un nuevo nodo que pasara a ser la nueva raiz de esa
	estructura jerarquica. El metodo devuelve un puntero a la
	raiz de la estructura modificada. En condiciones normales
	coincidir con el parametro recibido; solo cambiara si
	la estructura era vacia.
	@param clave Clave a insertar. Si ya aparecia en la
	estructura de nodos, se sobreescribe el valor.
	@param valor Valor a insertar.
	@param p Puntero al nodo raiz donde insertar la pareja.
	@return Nueva raiz (o p si no cambia).
	*/
	static Nodo *insertaAux(const Clave &clave, const Valor &valor, Nodo *p) {

		if (p == NULL) {
			return new Nodo(clave, valor);
		}
		else if (p->_clave == clave) {
			p->_valor = valor;
			return p;
		}
		else if (clave < p->_clave) {
			p->_iz = insertaAux(clave, valor, p->_iz);
			return p;
		}
		else { // (clave > p->_clave)
			p->_dr = insertaAux(clave, valor, p->_dr);
			return p;
		}
	}

	/**
	Busca una clave en la estructura jerarquica de
	nodos cuya raiz se pasa como parametro, y devuelve
	el nodo en la que se encuentra (o NULL si no esta).
	@param p Puntero a la raiz de la estructura de nodos
	@param clave Clave a buscar
	*/
	static Nodo *buscaAux(Nodo *p, const Clave &clave) {
		if (p == NULL)
			return NULL;

		if (p->_clave == clave)
			return p;

		if (clave < p->_clave)
			return buscaAux(p->_iz, clave);
		else
			return buscaAux(p->_dr, clave);
	}

	/**
	Elimina (si existe) la clave/valor de la estructura jerarquica
	de nodos apuntada por p. Si la clave aparecia en la propia raiz,
	esta cambiara, por lo que se devuelve la nueva raiz. Si no cambia
	se devuelve p.

	@param p raiz de la estructura jerarquica donde borrar la clave.
	@param clave Clave a borrar.
	@return Nueva raiz de la estructura, tras el borrado. Si la raiz
	no cambia, se devuelve el propio p.
	*/
	static Nodo *borraAux(Nodo *p, const Clave &clave) {

		if (p == NULL)
			return NULL;

		if (clave == p->_clave) {
			return borraRaiz(p);
		}
		else if (clave < p->_clave) {
			p->_iz = borraAux(p->_iz, clave);
			return p;
		}
		else { // clave > p->_clave
			p->_dr = borraAux(p->_dr, clave);
			return p;
		}
	}

	/**
	Borra la raiz de la estructura jerarquica de nodos
	y devuelve el puntero a la nueva raiz que garantiza
	que la estructura sigue siendo valida para un arbol de
	busqueda (claves ordenadas).
	*/
	static Nodo *borraRaiz(Nodo *p) {

		Nodo *aux;

		// Si no hay hijo izquierdo, la raiz pasa a ser
		// el hijo derecho
		if (p->_iz == NULL) {
			aux = p->_dr;
			delete p;
			return aux;
		}
		else
			// Si no hay hijo derecho, la raiz pasa a ser
			// el hijo izquierdo
			if (p->_dr == NULL) {
				aux = p->_iz;
				delete p;
				return aux;
			}
			else {
				// Convertimos el elemento mas pequeño del hijo derecho
				// en la raiz.
				return mueveMinYBorra(p);
			}
	}

	/**
	metodo auxiliar para el borrado; recibe un puntero a la
	raiz a borrar. Busca el elemento mas pequeño del hijo derecho
	que se convertira en la raiz (que devolvera), borra la antigua
	raiz (p) y "cose" todos los punteros, de forma que ahora:

	- El minimo pasa a ser la raiz, cuyo hijo izquierdo y
	derecho eran los hijos izquierdo y derecho de la raiz
	antigua.
	- El hijo izquierdo del padre del elemento mas pequeño
	pasa a ser el antiguo hijo derecho de ese minimo.
	*/
	static Nodo *mueveMinYBorra(Nodo *p) {

		// Vamos bajando hasta que encontramos el elemento
		// mas pequeño (aquel que no tiene hijo izquierdo).
		// Vamos guardando tambien el padre (que sera null
		// si el hijo derecho es directamente el elemento
		// mas pequeño).
		Nodo *padre = NULL;
		Nodo *aux = p->_dr;
		while (aux->_iz != NULL) {
			padre = aux;
			aux = aux->_iz;
		}

		// aux apunta al elemento mas pequeño.
		// padre apunta a su padre (si el nodo es hijo izquierdo)

		// Dos casos dependiendo de si el padre del nodo con
		// el minimo es o no la raiz a eliminar
		// (=> padre != NULL)
		if (padre != NULL) {
			padre->_iz = aux->_dr;
			aux->_iz = p->_iz;
			aux->_dr = p->_dr;
		}
		else {
			aux->_iz = p->_iz;
		}

		delete p;
		return aux;
	}

	/**
	Puntero a la raiz de la estructura jerarquica
	de nodos.
	*/
	Nodo *_ra;
};

#endif // __TREEMAP_H


#include <string>

// Esto es como hacer un struct de un único campo:
using medico = string;
using paciente = string;

#ifndef _FECHA_H
#define _FECHA_H

class Fecha {

public:

	// Sobrecarga del operador menor para poder comparar fechas de tipo Fecha directamente:
	bool operator<(const Fecha &f) const {

	}

	int dia() {
		return _dia;
	}

	int hora() {
		return _hora;
	}

	int minuto() {
		return _minuto;
	}

	string getHoraMinuto() {
		return _hora + ":" + _minuto;
	}

	void setDia(int dia) {
		_dia = dia;
	}

	void setHora(int hora) {
		_hora = hora;
	}

	void setMinuto(int minuto) {
		_minuto = minuto;
	}

private:
	int _dia;
	int _hora;
	int _minuto;
};

#endif // _FECHA_H

class Consultorio {

public:

	void nuevoMedico(medico m) {
		if (!agenda.contains(m)) {
			// ¿Cómo creo un HashMap vacío por defecto para un nuevo médico? : el símbolo {}
			// llama al constructor de la clase, permitiéndonos crear un HashMap vacío.
			agenda.insert(m, {});
		}
	}

	void pideConsulta(paciente p, medico m, Fecha f) {
		if (!agenda.contains(m)) {
			throw MedicoNoExistente("Medico no existente");
		}

		// ¿Cómo accedo a la clave de un HashMap dentro de un HashMap?
		if (agenda.at(m).at(f).empty()) {
			throw FechaOcupada("Fecha ocupada");
		}

		// ¿Y cómo añado un par al HashMap interno? : Utilizamos el operador [] que está sobrecargado
		// para permitirnos hacer la misma operación que at() pero modificando el HashMap asociado al médico m.
		agenda[m].insert(f, p);
	}

	paciente siguientePaciente(medico m) {
		paciente sigPaciente;

		if (!agenda.contains(m)) {
			throw MedicoNoExistente("Medico no existente");
		}

		if (agenda.at(m).empty()) {
			throw NoHayPacientes("No hay pacientes");
		}

		// Suponemos que el siguiente paciente es el que tiene una fecha menor. Como la lista de relación entre fechas
		// y pacientes es un TreeMap, un iterador al principio del mismo nos devolverá el valor mínimo de dicho TreeMap
		// y, por lo tanto, es directamente la fecha menor:
		auto it = agenda.at(m).cbegin();
		sigPaciente = it.value();
		// El tipo auto nos crea un iterador del tipo que deba ser automáticamente (por si no sabemos exactamente si 
		// es un string, un int, o un tipo declarado por nosotros).

		return sigPaciente;
	}

	void atiendeConsulta(medico m) {
		// Si el médico no existe, se lanza la excepción MedicoNoExistente:
		if (m == NULL) {
			throw MedicoNoExistente("Medico no existente");
		}

		if (agenda.at(m).empty()) {
			throw NoHayPacientes("No hay pacientes");
		}

		// En este caso, como queremos modificar (borrar para ser exactos) la siguiente cita del medico m,
		// realizamos la operación de acceso con el operador sobrecargado [] que nos permite modificar los
		// valores asociados a la clave m, y un iterador no constante:
		auto it = agenda[m].begin();
		agenda[m].erase(it.key());
	}

	List<paciente> listaPacientes(medico m, int d) {
		List<paciente> lista;

		if (!agenda.contains(m)) {
			throw MedicoNoExistente("Medico no existente");
		}

		auto it = agenda.at(m).cbegin();
		while (it != agenda.at(m).cend()) {
			lista.push_back(it);
			it++;
		}

		return lista;
	}


private:
	// Cada médico puede tener n pacientes diferentes.
	// Cada paciente sólo puede tener aginado un único médico.

	// Cada paciente puede tener n fechas diferentes con su médico.
	// Cada médico sólo puede tener asignado un paciente a una única fecha.

	// Podemos tener: un HasMap paciente -> medico con otro HashMap fecha -> paciente para cada medico
	// o podemos tener un HasMap medico -> agenda, siendo agenda directamente otro HashMap fecha -> paciente
	// de tal forma que para cada médico, se nos devuelve toda la información de sus citas.
	HashMap<medico, TreeMap<Fecha, paciente>> agenda;
};

#include <iostream>
#include <sstream>
using namespace std;

int main() {

	int testcases;
	Consultorio centromedico;

	cin >> testcases;

	for (int i = 0; i < testcases; i++) {
		string instruccion;
		string line;
		getline(cin, line);

		stringstream iss(line);
		while (iss >> instruccion) {
			// ¿Esto tendría sentido hacerlo con varios cases?
			if (instruccion == "nuevoMedico") {
				iss >> instruccion;
				medico m = instruccion;

				centromedico.nuevoMedico(m);
			}
			else if (instruccion == "pideConsulta") {
				paciente p;
				medico m;
				Fecha f;

				int n;

				iss >> instruccion;
				p = instruccion;
				iss >> instruccion;
				m = instruccion;
				iss >> n;
				f.setDia(n);
				iss >> n;
				f.setHora(n);
				iss >> n;
				f.setMinuto(n);

				centromedico.pideConsulta(p, m, f);
			}
			else if (instruccion == "siguientePaciente") {

			}
			else if (instruccion == "atiendeConsulta") {

			}
			else if (instruccion == "listaPacientes") {

			}
			else {

			}
		}
	}

	return 0;
}

void siguientePaciente(Consultorio centromedico, medico m) {
	paciente sigPaciente;

	try {
		sigPaciente = centromedico.siguientePaciente(m);

		cout << "Siguiente paciente doctor " << m.nombre << endl;
		cout << sigPaciente.nombre;
	}
	catch (ExcepcionTAD e) {
		e.msg();
	}
}

void listaPacientes(Consultorio centromedico, medico m, int d) {
	List<paciente> lista;

	try {
		lista = centromedico.listaPacientes(m, d);

		cout << "Doctor " << m.nombre << " dia " << d << endl;
		for (int i = 0; i < lista.size(); i++) {
			cout << lista.front().nombre << " " << lista.front().fecha.getHoraMinuto() << endl;
		}
	}
	catch (ExcepcionTAD e) {
		e.msg();
	}
}
