#ifndef GRAFO_H
#define GRAFO_H

#include "Lista.h"
#include <string>
#include "Util.h"

template <class T> class Grafo{

	private:

		//directorio de vertices para mapear desde la matriz
		Lista <T>* vertices;

		ui ** matrizAdyacencia;

	public:

		/*
		 *post: la instancia de Grafo dirigido creada con: el primer nodo 'ALMACEN'
		 *      lista para su uso
		 */
		Grafo();

		/*
		 pre: el grafo existe  y el nodo no existe en el mismo
		 post: el grafo queda modificado por el agregado del nuevo nodo
		*/
		void agregarVertice(T v);

		/*
		 *pre: Los nodos v1 y v2 existen y la arista no existe
		 *post: agrega la arista entre v1 y v2, el Grafo queda modificado
		*/
		void agregarAristaDesde(T origen,T destino, ui peso);

		/*
		 *pre: el grafo existe y el nodo a eliminar
		 *      esta en él ademas no tiene aristas incidentes.
		 *post: el grafo queda modificado por la eliminación del nodo.
		*/
		void eliminarVertice(T v);

		/*
		 *pre: el grafo existe y la arista existe en él.
		 *post: el grafo queda modificado por la eliminación de la arista.
		*/
		void eliminarArista(T origen, T destino);

		/*
		 * pre: la arista existe en el grafo
		 * post:Devuelve el peso de la arista
		 */
		ui obtenerPesoArista(T origen, T destino);

		/*
		  post:devuelve si la arista existe, desde nodo origen hacia nodo destino,
		       en el Grafo.
		*/
		bool existeArista(T origen, T destino);

		/*
		 *post:devuelve si el nodo existe en el grafo
		*/
		bool existeVertice(T destino);

		/*
		 * post:devuelve las adyacencias del grafo
		 */
		ui ** obtenerAdyacencias();

		/* pre: grafo no vacio
		 * post: devuelve una lista de los vertices existentes en el grafo
		 */
		Lista <T>* obtenerVertices();

		/*
		 * post: Devuelve cantidad de nodos del grafo
		 */
		ui obtenerTamanio();

		/*
		 * post: devuelve costes minimos desde 'ALMACEN' a cualquier punto
		 */
		ui * camMinDijk();

		/*
		 * post:elimina el grafo
		 */
		~Grafo();

	private:

		 /*
		  * post: devuelve la "posicion" del nodo en el grafo, de no existir devuelve -1
		  */
		 int buscarVertice(T lugar);

		 /*
		  * post: devuelve si v en la fila posicion de la matriz
		  *       es adyacente a algun otro vertice,
		  *       es decir tiene al menos una arista incidente
		  */
		 bool esAdyacente(ui posicion);

		 /*
		  * post: adiciona un espacio mas a la matriz de adyacencia actual
		  *       con el agregado de un nuevo vertice
		  */
		 void agrandarMatrizAdyacencia();

		 /*
		  * pre:  posicion Borrado es la posicion en el directorio de vertices
		  *       del vertice a eliminar, 'posicionBorrado'>0
		  * post: resta un espacio a la matriz de adyacencia actual
		  *       con el borrado de un vertice
		  */
		 void achicarMatrizAdyacencia(ui posicionBorrado);

		 /*
		  * post:libera la memoria asociada a 'matrizAdyacencia',
		  *      asigna 'nuevaMatriz' a 'matrizAdyacencia'
		  */
		void asignarNueva(ui ** nuevaMatriz, ui tope);

		/*
		 * post:Devuelve una nueva matriz con el tope indicado
		 */
		ui ** crearMatriz(ui tope);

		/*
		 * post:carga el vector D con los pesos de las adyacencias del nodo ALMACEN
		 */
		void cargarD(ui * D, ui totalVertices, ui ** M);

		/*
		 * post: marca los vertices como no visitados desde 2 hasta totalVertices,
		 *       sumariza la cantVisitados.
		 */
		void marcarNoVisitados(bool * visit, ui totalVertices, ui cantVisitados);

		/*
		 * post: elige entre los candidatos(no visitados) el de menor peso y modifica la 'posMenor'
		 */
		void elegirMenorPeso(bool * visit,ui * D, ui totalVertices, int & posMenor);

		/*
		 * post: optimiza los candidatos, elige el camino de menor coste y lo guarda en D
		 */
		void  optimizarCandidatos(ui totalVertices,ui posMenor, ui ** M,
																bool * visit, ui & cantVisitados,
															    ui * D);


};

template <class T> Grafo<T>::Grafo(){

	vertices = new Lista <T>;

	vertices->agregar("ALMACEN");

	matrizAdyacencia = crearMatriz(vertices->contarElementos());

	matrizAdyacencia[0][0]=0;

}

template <class T> bool Grafo<T>::existeVertice(T destino){
	bool existente=false;
	vertices->iniciarCursor();
	while(vertices->avanzarCursor() && !existente){
		existente = (vertices->obtenerCursor()==destino);
	}
	return existente;
}

template <class T> void Grafo<T>::agregarVertice(T v){
	if(!existeVertice(v)){

		vertices->agregar(v);

		agrandarMatrizAdyacencia();

	}
}

template <class T> ui Grafo<T>::obtenerTamanio(){

	return vertices->contarElementos();
}


template <class T> void Grafo<T>::agrandarMatrizAdyacencia(){

	//creo la nueva matriz con una fila columna mas para el nuevo vertice
	ui ** nuevaMatriz = crearMatriz(vertices->contarElementos());

	//copio los valores anteriores de la matriz anterior
	for(ui i=0;i<vertices->contarElementos()-1;i++){
		for(ui j=0;j<vertices->contarElementos()-1;j++){
			nuevaMatriz[i][j] = matrizAdyacencia[i][j];
		}
	}

	//inicializo la nueva fila
	for(ui i=0;i<vertices->contarElementos()-1;i++){
		nuevaMatriz[vertices->contarElementos()-1][i]=INFINITO;
	}
	//inicializo la nueva columna
	for(ui j=0;j<vertices->contarElementos()-1;j++){
		nuevaMatriz[j][vertices->contarElementos()-1]= INFINITO;
	}
	//peso diagonal lo inicializo en 0 porque no hay lazos en el grafo
	nuevaMatriz[vertices->contarElementos()-1][vertices->contarElementos()-1]=0;

	asignarNueva(nuevaMatriz,vertices->contarElementos()-1);

}

template <class T> void Grafo<T>::asignarNueva(ui ** nuevaMatriz,ui tope){

	//elimino la memoria asociada a la matriz anterior
	for(ui i=0;i<tope;i++){
		delete [] matrizAdyacencia[i];
	}
	delete [] matrizAdyacencia;

	//la 'matrizAdyacencia' es la 'nuevaMatriz'
	matrizAdyacencia = nuevaMatriz;

}

template <class T> void Grafo<T>::agregarAristaDesde(T v1,T v2,ui peso){

	if(existeVertice(v1) && existeVertice(v2)){

		int posV1=buscarVertice(v1);
		int posV2=buscarVertice(v2);

		matrizAdyacencia[posV1-1][posV2-1]=peso;

	}

}

template <class T> void Grafo<T>::eliminarVertice(T v){

	if(existeVertice(v)){

		int posicionDeBorrado=buscarVertice(v);

		if(!esAdyacente((ui)posicionDeBorrado-1)){

			vertices->remover((ui)posicionDeBorrado);

			achicarMatrizAdyacencia((ui)posicionDeBorrado-1);

		}else{
			throw std::string("No se puede eliminar un vertice adyacente a otro");
		}

	}
}

template <class T> ui ** Grafo<T>::crearMatriz(ui tope){
	ui ** nuevaMatriz = new ui*[tope];

	for(ui i=0;i<vertices->contarElementos();i++){
		nuevaMatriz[i]=new ui [tope];
	}
	return nuevaMatriz;
}

template <class T> void Grafo<T>::achicarMatrizAdyacencia(ui posicionBorrado){

	//creo la nueva matriz con un espacio menos que la actual
	ui ** nuevaMatriz=crearMatriz(vertices->contarElementos());

	//copio los valores anteriores de la matriz anterior
	int k =-1;
	int l;
	for(ui i=0;i<vertices->contarElementos()+1;i++){
		if(i!=posicionBorrado){
			k++;
			l=-1;
			for(ui j=0;j<vertices->contarElementos()+1;j++){
				if(j!=posicionBorrado){
					l++;
					nuevaMatriz[(ui)k][(ui)l]= matrizAdyacencia[i][j];
				}
			}
		}
	}

	asignarNueva(nuevaMatriz,vertices->contarElementos()+1);

}

template <class T> bool Grafo<T>::esAdyacente(ui posicion){

	bool adyacente=false;

	ui i=0;

	while(i<vertices->contarElementos() && !adyacente){

		adyacente=(matrizAdyacencia[i][posicion]!=INFINITO
				   && matrizAdyacencia[i][posicion]!=VACIO);

		i++;

	}

	return adyacente;
}

template <class T> void Grafo<T>::eliminarArista(T origen, T destino){

	if(existeArista(origen,destino)){

		int posO = buscarVertice(origen)-1;

		int posD = buscarVertice(destino)-1;

		matrizAdyacencia[(ui)posO][(ui)posD]=INFINITO;
	}

}

template <class T>bool Grafo<T>::existeArista(T origen, T destino){

	bool existe=false;

	if(existeVertice(origen) && existeVertice(destino)){

		int posO = buscarVertice(origen)-1;

		int posD = buscarVertice(destino)-1;

		existe = (matrizAdyacencia[(ui)posO][(ui)posD]!=INFINITO
				  && matrizAdyacencia[(ui)posO][(ui)posD]!=0);

	}

	return existe;
}


template <class T> int Grafo<T>::buscarVertice(T lugar){

	bool existe=false;
	int  posicionBusqueda=0;

	vertices->iniciarCursor();
	while(!existe && vertices->avanzarCursor()){

		posicionBusqueda++;
		if(vertices->obtenerCursor()==lugar){
			existe=true;
		}
	}
	if(!existe){
		posicionBusqueda=-1;
	}
	return posicionBusqueda;
}

template <class T> Lista <T>* Grafo<T>::obtenerVertices(){

	if(vertices->estaVacia()){
		throw std::string("Grafo vacio");
	}

	return vertices;
}

template <class T> ui Grafo<T>::obtenerPesoArista(T origen, T destino){

	ui peso=0;

	if(existeArista(origen,destino)){

		int posO = buscarVertice(origen)-1;

		int posD = buscarVertice(destino)-1;

		peso = matrizAdyacencia[posO][posD];
	}

	return peso;
}

template <class T> void Grafo<T>::cargarD(ui * D, ui totalVertices, ui ** M){

	ui j = 1;

	ui i= 0;

	while( j<totalVertices){

		D[i] = M[0][j];
		j++;
		i++;
	}
}

template <class T> void Grafo<T>::marcarNoVisitados(bool * visit, ui totalVertices, ui cantVisitados){

	ui j=0;

	while( j<totalVertices-1){

		visit[j] = false;
		j++;
	}

	cantVisitados++;

}

template <class T> void Grafo<T>::elegirMenorPeso(bool * visit,ui * D, ui totalVertices, int & posMenor){

	ui menorPeso = INFINITO+1;
	ui j=0;

	while(j < totalVertices-1){

		if(visit[j] == false && D[j]<menorPeso){

			posMenor = (int)j;

			menorPeso = D[j];

		}
		j++;
	}

	menorPeso = INFINITO+1;
}

template <class T> void  Grafo<T>::optimizarCandidatos(ui totalVertices,ui posMenor, ui ** M,
														bool * visit, ui & cantVisitados,
													    ui * D){

	ui j;

	if(posMenor >= 0){

		visit[(ui)posMenor]=true;

		j=1;

		while(j<totalVertices){

			if(M[posMenor+1][j]!=INFINITO && M[posMenor+1][j]!=0){

				ui numero1 = D[j-1];
				ui numero2 = D[(ui)posMenor] + M[posMenor+1][j];

				D[j-1] = Util::minimo(numero1,numero2);

			}
			j++;
		}
	}

	cantVisitados++;
}

template <class T> ui * Grafo<T>::camMinDijk(){

	//visitados contiene si todos los vertices que fueron visitados
	//exceptuando el primero que no me incumbe porque es el de salida

	ui totalVertices = this->vertices->contarElementos();
	ui ** M=this->matrizAdyacencia;
	bool  * visitados = new bool [totalVertices-1];
	ui cantidadVisitados = 0;
	ui * D = new ui [totalVertices-1];

	 //marco los no visitados

	marcarNoVisitados(visitados,totalVertices,cantidadVisitados);

	/*cargo los pesos en D que tiene los pesos de los
	  vertices desde 2 hasta totalVertices*/

	cargarD(D,totalVertices,M);

	int posicionMenorPeso = -1;

	while(cantidadVisitados < totalVertices){

		elegirMenorPeso(visitados,D,totalVertices,posicionMenorPeso);

		optimizarCandidatos(totalVertices, posicionMenorPeso, M, visitados, cantidadVisitados, D);

	}

	delete [] visitados;

	return D;
}

template <class T> Grafo<T> ::~Grafo(){

	for(ui i=0;i<vertices->contarElementos();i++){
		delete [] matrizAdyacencia[i];
	}
	delete [] matrizAdyacencia;

	delete vertices;

}

#endif /* GRAFO_H */
