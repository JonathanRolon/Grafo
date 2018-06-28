#ifndef VERTICE_H_
#define VERTICE_H_

#include "Lista.h"
#include <string>

typedef std::string T;

class Vertice{

    private:

		T etiqueta; // etiqueta  del vertice

		char cultivo;

    public:

		/*
		 *post: el vertice queda creado ,sin vertices adyacentes,
		 *		con una etiqueta y sin peso
		 */
		Vertice(T etiqueta, char cultivo);

		/*
		 *post: copia los datos de v al vertice actual
		 */
		Vertice( Vertice & v );

		/*
		 * post: devuelve el cultivo que acepta
		 */
		char obtenerCultivoAceptado();

		/*
		 * post:devuelve la etiqueta del vertice
		 */
		T obtenerEtiqueta();

};

Vertice::Vertice(T etiqueta, char cultivo) {

	this->etiqueta = etiqueta;

	this->cultivo=cultivo;

}

Vertice::Vertice( Vertice & v ){

	this->etiqueta=v.etiqueta;

	this->cultivo=v.cultivo;

}

T Vertice::obtenerEtiqueta(){

	return this->etiqueta;
}

char Vertice::obtenerCultivoAceptado(){

	return this->cultivo;
}

#endif /* VERTICE_H_ */
