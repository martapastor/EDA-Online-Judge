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

#include <iostream>
#include <string>
using namespace std;

int main() {

	Stack<int> suma;
	int input;
	cin >> input;

	while (input != -1) {
		if (input == 0) {
			suma.push(input);
		}
	    else {
				while (input > 0) {
				suma.push(input%10);
				input = input/10;
			}
		}

		int total = 0;
		for(int i = suma.size(); i > 1; i--){
			total += suma.top();

			cout << suma.top() << " + ";
			suma.pop();
		}

		total += suma.top();
		cout << suma.top() << " = " << total << endl;
		suma.pop();

		cin >> input;
	}

	return 0;
}
