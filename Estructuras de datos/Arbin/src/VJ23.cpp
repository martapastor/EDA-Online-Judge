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
		} else if (it._act == _ult) {
			pop_back();
			return Iterator(NULL);
		} else {
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
		} else
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
		_numElems ++;
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
		_numElems --;
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
	 Añade un elemento en la parte trasera de la cola.
	 Operacion generadora.

	 @param elem Elemento a añadir.
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



/**
  @file Arbin.h

  Implementacion dinamica del TAD Arbol Binario.

  Estructura de Datos y Algoritmos
  Facultad de Informatica
  Universidad Complutense de Madrid

 (c) Marco Antonio Gomez Martin, 2012
*/
#ifndef __ARBIN_H
#define __ARBIN_H

/**
 Implementacion dinamica del TAD Arbin utilizando
 nodos con un puntero al hijo izquierdo y otro al
 hijo derecho. La implementacion permite comparticion
 de estructura, manteniendola bajo control mediante
 conteo de referencias. La implementacion, sin embargo,
 es bastante artesanal, pues para no complicar el codigo
 excesivamente no se ha hecho uso de punteros inteligentes
 que incrementen y decrementen automaticamente esas
 referencias.

 Las operaciones son:

 - ArbolVacio: -> Arbin. Generadora implementada en el
   constructor sin parametros.
 - Cons: Arbin, Elem, Arbin -> Arbin. Generadora implementada
   en un constructor con tres parametros.
 - hijoIz, hijoDr: Arbin - -> Arbin. Observadoras que
   devuelven el hijo izquierdo o derecho de un arbol.
 - esVacio: Arbin -> Bool. Observadora que devuelve si
   un arbol binario es vacio.

 @author Marco Antonio Gomez Martin
 */
template <class T>
class Arbin {
public:

	/** Constructor; operacion ArbolVacio */
	Arbin() : _ra(NULL) {
	}

	/** Constructor; operacion Cons */
	Arbin(const Arbin &iz, const T &elem, const Arbin &dr) :
		_ra(new Nodo(iz._ra, elem, dr._ra)) {
		_ra->addRef();
	}

	Arbin(const T &elem) :
		_ra(new Nodo(NULL, elem, NULL)) {
		_ra->addRef();
	}

	/** Destructor; elimina la estructura jerarquica de nodos. */
	~Arbin() {
		libera();
		_ra = NULL;
	}

	/**
	 Devuelve el elemento almacenado en la raiz

	 raiz(Cons(iz, elem, dr)) = elem
	 error raiz(ArbolVacio)
	 @return Elemento en la raiz.
	 */
	const T &raiz() const {
		if (esVacio())
			throw EArbolVacio();
		return _ra->_elem;
	}

	/**
	 Devuelve un arbol copia del arbol izquierdo.
	 Es una operacion parcial (falla con el arbol vacio).

	 hijoIz(Cons(iz, elem, dr)) = iz
	 error hijoIz(ArbolVacio)
	*/
	Arbin hijoIz() const {
		if (esVacio())
			throw EArbolVacio();

		return Arbin(_ra->_iz);
	}

	/**
	 Devuelve un arbol copia del arbol derecho.
	 Es una operacion parcial (falla con el arbol vacio).

	 hijoDr(Cons(iz, elem, dr)) = dr
	 error hijoDr(ArbolVacio)
	*/
	Arbin hijoDr() const {
		if (esVacio())
			throw EArbolVacio();

		return Arbin(_ra->_dr);
	}

	/**
	 Operacion observadora que devuelve si el arbol
	 es vacio (no contiene elementos) o no.

	 esVacio(ArbolVacio) = true
	 esVacio(Cons(iz, elem, dr)) = false
	 */
	bool esVacio() const {
		return _ra == NULL;
	}

	// //
	// RECORRIDOS SOBRE EL ARBOL
	// //

	List<T> preorden() const {
		List<T> ret;
		preordenAcu(_ra, ret);
		return ret;
	}

	List<T> inorden() const {
		List<T> ret;
		inordenAcu(_ra, ret);
		return ret;
	}

	List<T> postorden() const {
		List<T> ret;
		postordenAcu(_ra, ret);
		return ret;
	}

	List<T> niveles() const {

		if (esVacio())
			return List<T>();

		List<T> ret;
		Queue<Nodo*> porProcesar;
		porProcesar.push_back(_ra);

		while (!porProcesar.empty()) {
			Nodo *visita = porProcesar.front();
			porProcesar.pop_front();
			ret.push_back(visita->_elem);
			if (visita->_iz!=NULL)
				porProcesar.push_back(visita->_iz);
			if (visita->_dr!=NULL)
				porProcesar.push_back(visita->_dr);
		}

		return ret;
	}

	// //
	// OTRAS OPERACIONES OBSERVADORAS
	// //

	/**
	 Devuelve el numero de nodos de un arbol.
	 */
	unsigned int numNodos() const {
		return numNodosAux(_ra);
	}

	/**
	 Devuelve la talla del arbol.
	 */
	unsigned int talla() const {
		return tallaAux(_ra);
	}

	/**
	 Devuelve el numero de hojas de un arbol.
	 */
	unsigned int numHojas() const {
		return numHojasAux(_ra);
	}

	// //
	// METODOS DE "FONTANERIA" DE C++ QUE HACEN VERSATIL
	// A LA CLASE
	// //

	/** Constructor copia */
	Arbin(const Arbin<T> &other) : _ra(NULL) {
		copia(other);
	}

	/** Operador de asignacion */
	Arbin<T> &operator=(const Arbin<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparacion */
	bool operator==(const Arbin<T> &rhs) const {
		return comparaAux(_ra, rhs._ra);
	}

	bool operator!=(const Arbin<T> &rhs) const {
		return !(*this == rhs);
	}

protected:

	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y los punteros al hijo izquierdo y al hijo derecho, asi
	 como el numero de referencias que hay.
	 */
	class Nodo {
	public:
		Nodo() : _iz(NULL), _dr(NULL), _numRefs(0) {}
		Nodo(Nodo *iz, const T &elem, Nodo *dr) :
			_elem(elem), _iz(iz), _dr(dr), _numRefs(0) {
			if (_iz != NULL)
				_iz->addRef();
			if (_dr != NULL)
				_dr->addRef();
		}

		void addRef() { assert(_numRefs >= 0); _numRefs++; }
		void remRef() { assert(_numRefs > 0); _numRefs--; }

		T _elem;
		Nodo *_iz;
		Nodo *_dr;

		int _numRefs;
	};

	/**
	 Constructor protegido que crea un arbol
	 a partir de una estructura jerarquica existente.
	 Esa estructura jerarquica SE COMPARTE, por lo que
	 se añade la referencia.
	 Se utiliza en hijoIz e hijoDr.
	 */
	Arbin(Nodo *raiz) : _ra(raiz) {
		if (_ra != NULL)
			_ra->addRef();
	}

	void libera() {
		libera(_ra);
	}

	void copia(const Arbin &other) {
		assert(this != &other);
		_ra = other._ra;
		if (_ra != NULL)
			_ra->addRef();
	}

	// //
	// METODOS AUXILIARES PARA LOS RECORRIDOS
	// //

	static void preordenAcu(Nodo *ra, List<T> &acu) {
		if (ra == NULL)
			return;

		acu.push_back(ra->_elem);
		preordenAcu(ra->_iz, acu);
		preordenAcu(ra->_dr, acu);
	}

	static void inordenAcu(Nodo *ra, List<T> &acu) {
		if (ra == NULL)
			return;

		inordenAcu(ra->_iz, acu);
		acu.push_back(ra->_elem);
		inordenAcu(ra->_dr, acu);
	}

	static void postordenAcu(Nodo *ra, List<T> &acu) {
		if (ra == NULL)
			return;

		postordenAcu(ra->_iz, acu);
		postordenAcu(ra->_dr, acu);
		acu.push_back(ra->_elem);
	}

	// //
	// METODOS AUXILIARES (RECURSIVOS) DE OTRAS OPERACIONES
	// OBSERVADORAS
	// //

	static unsigned int numNodosAux(Nodo *ra) {
		if (ra == NULL)
			return 0;
		return 1 + numNodosAux(ra->_iz) + numNodosAux(ra->_dr);
	}

	static unsigned int tallaAux(Nodo *ra) {
		if (ra == NULL)
			return 0;

		int tallaiz = tallaAux(ra->_iz);
		int talladr = tallaAux(ra->_dr);
		if (tallaiz > talladr)
			return 1 + tallaiz;
		else
			return 1 + talladr;
	}

	static unsigned int numHojasAux(Nodo *ra) {
		if (ra == NULL)
			return 0;

		if ((ra->_iz == NULL) && (ra->_dr == NULL))
			return 1;

		return numHojasAux(ra->_iz) + numHojasAux(ra->_dr);
	}

private:

	/**
	 Elimina todos los nodos de una estructura arborea
	 que comienza con el puntero ra.
	 Se admite que el nodo sea NULL (no habra nada que
	 liberar).
	 */
	static void libera(Nodo *ra) {
		if (ra != NULL) {
			ra->remRef();
			if (ra->_numRefs == 0) {
				libera(ra->_iz);
				libera(ra->_dr);
				delete ra;
			}
		}
	}

	/**
	 Compara dos estructuras jerarquicas de nodos,
	 dadas sus raices (que pueden ser NULL).
	 */
	static bool comparaAux(Nodo *r1, Nodo *r2) {
		if (r1 == r2)
			return true;
		else if ((r1 == NULL) || (r2 == NULL))
			// En el if anterior nos aseguramos de
			// que r1 != r2. Si uno es NULL, el
			// otro entonces no lo sera, luego
			// son distintos.
			return false;
		else {
			return (r1->_elem == r2->_elem) &&
				comparaAux(r1->_iz, r2->_iz) &&
				comparaAux(r1->_dr, r2->_dr);
		}
	}

protected:
	/**
	 Puntero a la raiz de la estructura jerarquica
	 de nodos.
	 */
	Nodo *_ra;
};

#endif // __ARBIN_H


#include <iostream>
using namespace std;

void fillArbinPreorden(Arbin<int> &arbol);
void numEquipos(Arbin<int> arbol, int &equipos, int &maxExcursionistas);

int main() {

	int testcases;
	cin >> testcases;

	for (int i = 0; i < testcases; i++) {
		Arbin<int> excursionistas;
		fillArbinPreorden(excursionistas);

		int equipos = 0, maxExcursionistas = 0;

		if (!excursionistas.esVacio()) {
			numEquipos(excursionistas, equipos, maxExcursionistas);
		}

		cout << equipos << " " << maxExcursionistas << endl;
	}

	return 0;
}

void fillArbinPreorden(Arbin<int> &arbol) {
	int n;
	Arbin<int> hijoIz;
	Arbin<int> hijoDr;

	cin >> n;

	if (n != -1) {
		fillArbinPreorden(hijoIz); // Recorre todos los nodos por el hijo izquierdo hasta toparse con una hoja
		fillArbinPreorden(hijoDr);  // Recorre el hijo derecho del nodo inmediatamente superior, empezando éste a recorrer este a su vez por sus hijos izquierdos

		arbol = Arbin<int>(hijoIz, n, hijoDr);
	}
}

// No tiene mucho sentido que nos den los nodos de un árbol como entrada en recorrido
// inorden o postorden ya que si queremos indicar dónde acaba cada rama (es decir, los
// hijos son nodos nulos) con un recorrido que no comienza por la raiz no tendría ningún
// sentido ya que siempre empezaría por -1. Por ello, los enunciados nos pasan la información
// de los nodos del árbol en recorrido de preorden.

void numEquipos(Arbin<int> arbol, int &equipos, int &maxExcursionistas) {
	int equiposIz = 0, equiposDr = 0;
	int maxExcursionistasIz = 0, maxExcursionistasDr = 0;
	Arbin<int> hijoIz = arbol.hijoIz();
	Arbin<int> hijoDr = arbol.hijoDr();

	if(hijoIz.esVacio() && hijoDr.esVacio()) {
		if (arbol.raiz() != 0) {
			equipos++;
			maxExcursionistas += arbol.raiz();
		}
	}
	else if(hijoIz.esVacio()) {
		numEquipos(hijoDr, equiposDr, maxExcursionistasIz);
		if(arbol.raiz() != 0 && equiposDr == 0) {
			equipos++;
			maxExcursionistas += arbol.raiz();
		}
	}
	else if(hijoDr.esVacio()) {
		numEquipos(hijoIz, equiposIz, maxExcursionistasDr);
		if(arbol.raiz() != 0 && equiposIz == 0) {
			equipos++;
			maxExcursionistas += arbol.raiz();
		}
	}
	else {
		numEquipos(hijoIz, equiposIz, maxExcursionistasIz);
		numEquipos(hijoDr, equiposDr, maxExcursionistasDr);
		if(arbol.raiz() != 0 && equiposIz == 0 && equiposDr == 0) {
			equipos++;
			maxExcursionistas += arbol.raiz();
		}
	}

	equipos += equiposIz + equiposDr;
	if (maxExcursionistasIz > maxExcursionistasDr) {
		maxExcursionistas = maxExcursionistasIz + arbol.raiz();
	}
	else {
		maxExcursionistas = maxExcursionistasDr + arbol.raiz();
	}
}
