#include "Util.h"

#include <iostream>

#include <limits>


void Util::pedirEntero(ui &destino,ui valorDefault){

	std::cin>>destino;

	if(std::cin.fail()){

		std::cin.clear();

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

		destino=valorDefault;

	}

}

ui Util::minimo(ui numero1,ui numero2){
	ui minimo=0;

	if(numero1<=numero2){
		minimo=numero1;
	}else{
		minimo=numero2;
	}
	return minimo;
}
