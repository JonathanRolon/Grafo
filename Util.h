#ifndef UTIL_H_

#define UTIL_H_

typedef unsigned ui;
#include <limits>
const unsigned VACIO=0;
const ui TOPE_JUGADORES=100;
const ui TOPE_TURNOS=1000;
const ui TOPE_FILAS=300;
const ui TOPE_COLUMNAS=300;
const ui INFINITO=std::numeric_limits<unsigned int>::max()-5000;

namespace Util{

	/*Funcion que pide y valida un entero al usuario.

	 Recibe como parametros, una variable entera por referencia donde se alojara el resultado obtenido

	 y una variable entera como valor por defecto en caso de no poder validar la entrada del usuario*/

	void pedirEntero(ui &destino,ui valorDefault=-1);

	/*PRE: numero1 y numero2 ambos positivos
	  POST: devuelve el menor de ellos
	 */

	ui minimo(ui numero1,ui numero2);

}



#endif
