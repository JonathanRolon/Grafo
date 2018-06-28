
# include "Grafo.h"
#include <iostream>

using namespace std;

int main(){

	string v1  = "MENDOZA";
	string v2  = "SAN JUAN";
	string v3  = "SAN LUIS";
	string v4  = "CORDOBA";

	Grafo<string> DG;//guardo el tipo de dato, no punteros porque
	                 //internamente el grafo es una lista dinamica

	DG.agregarVertice(v1);
	DG.agregarVertice(v2);
	DG.agregarVertice(v3);
	DG.agregarVertice(v4);

	DG.agregarAristaDesde("ALMACEN",v1,5);
	DG.agregarAristaDesde("ALMACEN",v3,32);
	DG.agregarAristaDesde("ALMACEN",v4,80);
	DG.agregarAristaDesde(v1,v2,60);
	DG.agregarAristaDesde(v2,v4,5);
	DG.agregarAristaDesde(v3,v2,25);
	DG.agregarAristaDesde(v3,v4,75);
	DG.agregarAristaDesde(v4,v3,10);

	unsigned  * vectorD = DG.camMinDijk();

	cout<<"vector D:"<<endl;

	for(int i=0; i<4; i++){//el vector D va hasta 4! no hasta 5 porque solo
		                   //me interesa los distintos del de salida

		cout<< vectorD[i]<< " ";
	}

	cout<< endl;

	delete [] vectorD;

	/* Para imprimmir las matrices en el Grafo.h :

		std::cout<<" matriz"<<std::endl;

		for(ui  i=0;i<vertices->contarElementos();i++){
			for(ui  j=0;j<vertices->contarElementos();j++){
				std::cout<<matrizAdyacencia[i][j]<<" ";
			}
			std::cout<<std::endl;
		}
		std::cout<<std::endl;

	*/



	return 0;
}



