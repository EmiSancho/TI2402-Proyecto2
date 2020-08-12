/**
 * Hecho por Emilly Sancho y Daniegl Bogarin
 * para TI2402 - Algoritmos y estructuras de datos
 * Profesora: Maria Jose Artavia.
 * IS 2020 - Proyecto 2 - 29/07/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>     

#define NOMBRE_SIZE 50
#define PROVINCIA_SIZE 50

//--------------- DEFINICION DE ESTRUCTURAS
typedef struct nodoVertice nodoVertice;
typedef struct nodoArista nodoArista;

//--------------------------------------ARISTA

/**
 * @brief      estructura de nodo para las aristas del grafo
 */
struct nodoArista
{
	char origen[NOMBRE_SIZE];
	char destino[NOMBRE_SIZE];
	int tiempo;
	int distancia;	
	nodoArista *siguiente;
};

/**
 * @brief      estructura de lista para las aristas del grafo
 */
typedef struct listaAristas
{
	nodoArista *inicio;
}listaAristas;


/**
 * @brief      instancia de una nueva lista de aristas 
 * @param      ninguno
 * @return     puntero a una lista de aristas
 */
listaAristas *listaAristasNueva(){
	listaAristas *A;
	A = (listaAristas*)malloc(sizeof(listaAristas));
	A->inicio = NULL;
	return A;
}

/**
 * @brief      inserta una arista a una lista de aristas
 * @param      A     puntero a una lista de aristas
 * @param      a     nodo de tipo arista
 * @return     ninguno
 */
void insertarArista(listaAristas *A, nodoArista a){
	nodoArista *n, *aux;
	if(A->inicio == NULL){
		A->inicio = (nodoArista*)malloc(sizeof(nodoArista));
		strcpy(A->inicio->origen, a.origen);
		strcpy(A->inicio->destino, a.destino);
		A->inicio->tiempo = a.tiempo;
		A->inicio->distancia = a.distancia;
		A->inicio->siguiente = NULL;
	}	
	else{
		n = A->inicio;
		while(n!=NULL){
			aux = n;
			n = n->siguiente;
		}
		aux->siguiente = (nodoArista*)malloc(sizeof(nodoArista));
		strcpy(aux->siguiente->origen, a.origen);
		strcpy(aux->siguiente->destino,a.destino); 
		aux->siguiente->tiempo = a.tiempo;
		aux->siguiente->distancia = a.distancia;
		aux->siguiente->siguiente = NULL;

	}
}

/**
 * @brief      imprime en consola el destino y tiempo de cada arista
 * @param      A     puntero a una lista de aristas
 * @return     ninguno
 */
void mostrarAristas(listaAristas *A){
	
	for(nodoArista *i = A->inicio; i!=NULL; i=i->siguiente){
		printf("\t\t-> %s, tiempo: %i, distancia: %i.\n", i->destino, i->tiempo, i->distancia);
	}
}


/**
 * @brief      elimina una arista de una lista de aristas
 * @param      A     puntero a lista de aristas
 * @param      d     char nombre de la arista a eliminar
 * @return     0 si la arista se elimino y 1 si no fue eliminada
 */
int eliminarArista(listaAristas *A, char d[NOMBRE_SIZE]){
	nodoArista *a, *anterior = NULL;
	a = A->inicio; 

	if(A->inicio == NULL){
		return 1;
	}
	if(strcmp(A->inicio->destino, d)==0){
		A->inicio = A->inicio->siguiente;
		free(a);
		return 0;
	}

	else{
		anterior = A->inicio;
		a = anterior->siguiente;

		while(a!=NULL){
			if(strcmp(a->destino,d)==0 ){
				anterior->siguiente = a->siguiente;
				free(a);
				return 0;
				break;
			}
			if(strcmp(a->destino,d)==0 && a->siguiente == NULL){
				anterior->siguiente = NULL;
				return 0;
				break;
			}
			else{
				anterior = a;
				a = a->siguiente;
			}
		}

	return 1;

	}
}

/**
 * @brief      consulta si la arista existe dentro de la lista de aristas
 * @param      A     puntero a la lista de aristas
 * @param      origen     char del nombre del origen de la arista a buscar
 * @param      destino    char del nombre del destino de la arista a buscar
 * @return     puntero a la arista buscada, si no la encuentra retorna NULL
 */
nodoArista* consultarArista(listaAristas *A, char origen[NOMBRE_SIZE], char destino[NOMBRE_SIZE]){
	nodoArista *a = A->inicio;
	while(a!=NULL){
		if(strcmp(a->origen,origen)==0 && strcmp(a->destino,destino)==0){
			return a;
		}
		a = a->siguiente;
	}
	printf("\n\t****ERROR****\n\t%s no existe como arista, por favor insertelo. \n", origen );
	return NULL;
}

//--------------------------------------VERTICE

/**
 * @brief      estructura vertive para los vertices del grafo
 */
struct nodoVertice
{
	char nombre[NOMBRE_SIZE];
	char provincia[PROVINCIA_SIZE];
	int poblacion;
	listaAristas *aristas;
	nodoVertice *siguiente;
	
	//--- Para el Djisktra
	int pesoAcumulado; 
	nodoVertice *verticeAnterior;
	int etiqueta; 
};

/**
 * @brief      estructura de lista para los vertices del grafo
 */
typedef struct listaVertices
{
	nodoVertice *inicio;
}listaVertices;

/**
 * @brief      instancia una nueva lista de vertices
 * @return     puntero a la lista de vertices
 */
listaVertices *listaVerticesNueva(){
	listaVertices *V;
	V = (listaVertices*)malloc(sizeof(listaVertices));
	V->inicio = NULL;
	return V;
}

/**
 * @brief      inserta un vertice en una lista de vertices
 * @param      V     puntero a una lista de vertices
 * @param[in]  v     el vertice a insertar
 * @return     ninguno
 */
void insertarVertice(listaVertices *V, nodoVertice v){
	nodoVertice *n, *aux;
	if(V->inicio == NULL){
		V->inicio = (nodoVertice*)malloc(sizeof(nodoVertice));
		strcpy(V->inicio->nombre, v.nombre);
		strcpy(V->inicio->provincia, v.provincia);
		V->inicio->poblacion = v.poblacion;
		V->inicio->aristas = v.aristas;
		V->inicio->siguiente = NULL;
		V->inicio->pesoAcumulado = 0;
		V->inicio->verticeAnterior = NULL;
		V->inicio->etiqueta = 0;
	}	
	else{
		n = V->inicio;
		while(n!=NULL){
			aux = n;
			n = n->siguiente;
		}
		aux->siguiente = (nodoVertice*)malloc(sizeof(nodoVertice));
		strcpy(aux->siguiente->nombre, v.nombre);
		strcpy(aux->siguiente->provincia, v.provincia);
		aux->siguiente->poblacion = v.poblacion;
		aux->siguiente->aristas = v.aristas;
		aux->siguiente->siguiente = NULL;
		aux->siguiente->pesoAcumulado = 0;
		aux->siguiente->verticeAnterior = NULL;
		aux->siguiente->etiqueta = 0;
	}
}

/**
 * @brief      imprime en consola informacion sobre cada vertice de la lista
 * @param      V     puntero a la lista de vertice
 * @return     ninguno
 */
void mostrarVertices(listaVertices *V){
	printf("\tVertices:\n");
	for(nodoVertice *i = V->inicio; i!=NULL; i=i->siguiente){
		printf("\t%s, %s, población: %i.\n", i->nombre, i->provincia, i->poblacion);
	}
}

/**
 * @brief      consulta si el vertice existe dentro de la lista de vertices
 * @param      V     puntero a la lista de vertices
 * @param      n     char del nombre del vertice a buscar
 * @return     puntero al vertice buscado, si no lo encuentra retorna NULL
 */
nodoVertice* consultarVertice(listaVertices *V, char n[NOMBRE_SIZE]){
	nodoVertice *v = V->inicio;
	while(v!=NULL){
		if(strcmp(v->nombre,n)==0){
			return v;
		}
		v = v->siguiente;
	}
	printf("\n\t****ERROR****\n\t%s no existe como vertice, por favor insertelo. \n", n );
	return NULL;
}

/**
 * @brief      elimina un vertice de una lista de vertices
 * @param      V     puntero a una lista de vertices
 * @param      n     char del nombre del vertice a buscar
 * @param      p     char con la provincia del verticce a buscar
 * @return     0 si el vertice se elimino y 1 si no fue eliminado 
 */
int eliminarVertice(listaVertices *V, char n[NOMBRE_SIZE], char p[PROVINCIA_SIZE]){
	nodoVertice *v, *anterior = NULL;
	v = V->inicio; 

	
	if(strcmp(V->inicio->nombre,n)==0 && strcmp(V->inicio->provincia,p)==0){
		V->inicio = V->inicio->siguiente;
		free(v);
		return 0;
	}

	else{
		anterior = V->inicio;
		v = anterior->siguiente;

		while(v!=NULL){
			if(strcmp(v->nombre,n)==0 && strcmp(v->provincia,p)==0){
				anterior->siguiente = v->siguiente;
				free(v);
				return 0;
				break;
			}
			if(strcmp(v->nombre,n)==0 && strcmp(v->provincia,p)==0 && v->siguiente == NULL){
				anterior->siguiente = NULL;
				return 0;
				break;
			}
			else{
				anterior = v;
				v = v->siguiente;
			}
		}

	return 1;

	}

}

/**
 * @brief      cambia el parametro etiqueta de un nodo vertice
 * @param      V     puntero a la lista de vertices
 * @param      n     nombre del vertice a cambiar la etiqueta
 * @return     ninguno
 */
void cambiarEtiquetaAPermanente(listaVertices *V, char n[NOMBRE_SIZE]){
	nodoVertice *v = V->inicio;
	while(v!=NULL){
		if(strcmp(v->nombre,n)==0){
			v->etiqueta = 1;
		}
		v = v->siguiente;
	}
}

/**
 * @brief      immprime en consola la etiqueta de cada nodo
 * @param      V     puntero a la lista de vertices 
 * @return     ninguno
 */
void mostrarEtiquetas(listaVertices *V){
	printf("\t\nEtiquetas:\n");
	for(nodoVertice *i = V->inicio; i!=NULL; i=i->siguiente){
		printf("\t%s [%i,%s,%i]\n", i->nombre, i->pesoAcumulado, i->verticeAnterior->nombre, i->etiqueta);
	}
}

/**
 * @brief      modifica los valores de las etiquetas de los nodos adyacentes a un nodo dado
 * @param      V     puntero a la lista de vertices
 * @param      v     puntero del nodo cuyos adyacentes se van a modificar
 */
void etiquetarAdyacentes(listaVertices *V, nodoVertice *v){
	nodoVertice *aux;
	for(nodoArista *i=v->aristas->inicio; i!=NULL; i=i->siguiente){
		aux = consultarVertice(V,i->destino);
		if(aux->pesoAcumulado > v->pesoAcumulado + i->tiempo || aux->pesoAcumulado == 0 && aux->etiqueta == 0){
			aux->pesoAcumulado = v->pesoAcumulado + i->tiempo;
			aux->verticeAnterior = v;
			
		}
	}
}

/**
 * @brief      recorre la lista de vertices en busca de la etiqueta temporal de menor valor
 * @param      V     puntero a la lista de vertices
 * @return     puntero al nodo con la menor etiqueta temporal
 */
nodoVertice* buscarEtiquetaMenor(listaVertices *V){
	nodoVertice *menorVertice = V->inicio;
	int menorPesoAcumulado = menorVertice->pesoAcumulado;	

	for(nodoVertice *i = V->inicio; i!=NULL; i= i->siguiente){
		//printf("menor peso %i de %s\n", menorPesoAcumulado, menorVertice->nombre );
		if(menorVertice->etiqueta == 1 ){
			menorVertice = menorVertice->siguiente;
			menorPesoAcumulado = menorVertice->pesoAcumulado;
		}
		if(i->pesoAcumulado < menorPesoAcumulado && i->pesoAcumulado != 0 & i->etiqueta !=1 || menorPesoAcumulado == 0){
			menorPesoAcumulado = i->pesoAcumulado;
			menorVertice = i;
		}
	}

	printf("\n\tMenor peso: %i de %s\n", menorPesoAcumulado, menorVertice->nombre );
	return menorVertice;
	
}

/**
 * @brief      recorre la lista de vertices para comprobar si hay etiquetas temporales 
 * @param      V     puntero a la lista de vertices *
 * @return     0 si hay etiquetas temporales y 1 si todas son permanentes
 */
int etiquetasPermanentesCompletas(listaVertices *V){
	int e = 1 ;
	for(nodoVertice *i = V->inicio; i!=NULL; i=i->siguiente){
		if(i->etiqueta == 0){
			e = 0; 
		}
	}
	return e;
}

/**
 * @brief      recorre la lista de vertices cambiando los valores que se utilizan como etiqueta para el Djisktra
 * @param      V     puntero a la lista de vertices
 * @return     no aplica
 */
void limpiarEtiquetas(listaVertices *V){
	for(nodoVertice *i = V->inicio; i!=NULL; i=i->siguiente){
		i->pesoAcumulado = 0;
		i->verticeAnterior = NULL;
		i->etiqueta = 0;
	}
}

/**
 * @brief      encuentra el camino mas corto a cada nodo apartir de un origen
 * @param      V       puntero a la lista de vertices
 * @param      origen char al nodo desde el cual se calculan los caminos mas cortos
 */
void Djisktra(listaVertices *V, char origen[NOMBRE_SIZE]){
	
	cambiarEtiquetaAPermanente(V,origen);
	mostrarEtiquetas(V);
	if(etiquetasPermanentesCompletas(V) != 1){
		nodoVertice *v = consultarVertice(V,origen);
		etiquetarAdyacentes(V,v);
		nodoVertice *menorVertice = buscarEtiquetaMenor(V);
		Djisktra(V, menorVertice->nombre);
	}
}

/**
 * @brief      recorre una lista de vertices, busca la arista de este vertice al siguiente y suma el tiempo entre estos
 * @param      V     puntero a la lista de vertices
 * @return     int suma del total de tiempos entre vertices
 */
int obtenerTiempoTotalEnRuta(listaVertices *V){
	int tiempoTotal = 0;
	nodoArista *auxArista;
	for(nodoVertice *i = V->inicio; i!=NULL; i=i->siguiente){
		if(i->siguiente != NULL){
			auxArista = consultarArista(i->aristas,i->nombre,i->siguiente->nombre);
			tiempoTotal = tiempoTotal + auxArista->tiempo;
		}
	}
	printf("%i\n", tiempoTotal );
	return tiempoTotal;
}

/**
 * @brief      recorre una lista de vertices, busca la arista de este vertice al siguiente y suma la distancia entre estos
 * @param      V     puntero a la lista de vertices
 * @return     int suma del total de distancias entre vertices
 */
int obtenerDistanciaTotalEnRuta(listaVertices *V){
	int distanciaTotal = 0;
	nodoArista *auxArista;
	for(nodoVertice *i = V->inicio; i!=NULL; i=i->siguiente){
		if(i->siguiente != NULL){
			auxArista = consultarArista(i->aristas,i->nombre,i->siguiente->nombre);
			distanciaTotal = distanciaTotal + auxArista->distancia;
		}
	}
	printf("%i\n", distanciaTotal );
	return distanciaTotal;
	
}

/**
 * @brief      calcula la ruta de vertices que hay que seguir para llegar de un nodo A a un nodo B
 * @param      V        puntero a la lista de vertices
 * @param      origen   vertice origen de la ruta
 * @param      destino  vertice destino de la ruta
 * @return     puntero a la lista de vertices que contiene la ruta
 */
listaVertices* mostrarRuta(listaVertices *V, char origen[NOMBRE_SIZE], char destino[NOMBRE_SIZE]){
	nodoVertice *aux =	consultarVertice(V,destino);
	listaVertices *auxRuta = listaVerticesNueva();
	listaVertices *ruta = listaVerticesNueva();
	while(aux!=NULL){
		insertarVertice(auxRuta,*aux);
		aux = aux->verticeAnterior;
	}

	aux = auxRuta->inicio;
	while(aux!=NULL){
		if(aux->siguiente == NULL){
			insertarVertice(ruta,*aux);
			eliminarVertice(auxRuta, aux->nombre, aux->provincia);
			aux = auxRuta->inicio;
		}
		aux = aux->siguiente;

	}
	free(auxRuta);
	aux = consultarVertice(V,destino);
	insertarVertice(ruta, *aux);

	//---------------- borrar
	mostrarVertices(ruta);
	// obtenerTiempoTotalEnRuta(ruta);
	// obtenerDistanciaTotalEnRuta(ruta);
	//---------------------------------
	
	return ruta;
}



//--------------- MAIN Y PRUEBAS

/**
 * @brief      funcion main
 * @return     0 si la ejecucion fue exitosa
 */
int main()
{
	int accion;
	listaVertices *V;
	V = listaVerticesNueva();

	nodoVertice tempVertice;
	nodoArista tempArista; 
	int pasajerosMinimosTren, pasajerosMinimosBus, pasajerosMinimosTaxi, pasajerosMinimosVehiculo = 0;
	int pasajerosMaximosTren, pasajerosMaximosBus, pasajerosMaximosTaxi, pasajerosMaximosVehiculo = 0;
	int simulacionesTren, simulacionesBus, simulacionesTaxi, simulacionesVehiculo = 0;
	char origen[NOMBRE_SIZE];

//--------------	GRAFO PRE CARGADO
	listaAristas *aCoruna  = listaAristasNueva();
	listaAristas *aVigo  = listaAristasNueva();
	listaAristas *aOviedo = listaAristasNueva();
	listaAristas *aValladolid = listaAristasNueva();
	listaAristas *aBilbao = listaAristasNueva();
	listaAristas *aZaragoza = listaAristasNueva(); 
	listaAristas *aMadrid = listaAristasNueva(); 
	listaAristas *aBadajoz = listaAristasNueva(); 
	listaAristas *aCadiz = listaAristasNueva();
	listaAristas *aSevilla = listaAristasNueva(); 
	listaAristas *aJaen = listaAristasNueva(); 
	listaAristas *aGranada = listaAristasNueva();
	listaAristas *aMurcia = listaAristasNueva(); 
	listaAristas *aAlbacete = listaAristasNueva(); 
	listaAristas *aValencia = listaAristasNueva(); 
	listaAristas *aBarcelona = listaAristasNueva(); 
	listaAristas *aGerona = listaAristasNueva();

	nodoVertice coruna, vigo, oviedo, valladolid, bilbao, zaragoza, madrid, badajoz, cadiz, sevilla, jaen, granada, murcia, albacete, valencia, barcelona, gerona; 

	strcpy(coruna.nombre,"Coruña"); strcpy(coruna.provincia,"A Coruña"); coruna.poblacion = 1147223; coruna.aristas = aCoruna;
	strcpy(vigo.nombre,"Vigo"); strcpy(vigo.provincia,"Pontevedra"); vigo.poblacion = 963711; vigo.aristas = aVigo;
	strcpy(oviedo.nombre,"Oviedo"); strcpy(oviedo.provincia,"Asturias"); oviedo.poblacion = 1081373; oviedo.aristas = aOviedo;
	strcpy(valladolid.nombre,"Valladolid"); strcpy(valladolid.provincia,"Valladolid"); valladolid.poblacion = 534098; valladolid.aristas = aValladolid;
	strcpy(bilbao.nombre,"Bilbao"); strcpy(bilbao.provincia,"Vizcaya"); bilbao.poblacion = 1155622; bilbao.aristas = aBilbao;
	strcpy(zaragoza.nombre,"Zaragoza"); strcpy(zaragoza.provincia,"Zaragoza"); zaragoza.poblacion = 973111; zaragoza.aristas = aZaragoza;
	strcpy(madrid.nombre,"Madrid"); strcpy(madrid.provincia,"Madrid"); madrid.poblacion = 6489578; madrid.aristas = aMadrid;
	strcpy(badajoz.nombre,"Badajoz"); strcpy(badajoz.provincia,"Badajoz"); badajoz.poblacion = 693271; badajoz.aristas = aBadajoz;
	strcpy(cadiz.nombre,"Cadiz"); strcpy(cadiz.provincia,"Cadiz"); cadiz.poblacion = 1243091; cadiz.aristas = aCadiz;
	strcpy(sevilla.nombre,"Sevilla"); strcpy(sevilla.provincia,"Sevilla"); sevilla.poblacion = 1928123; sevilla.aristas = aSevilla;
	strcpy(jaen.nombre,"Jaen"); strcpy(jaen.provincia,"Jaen"); jaen.poblacion = 670594; jaen.aristas = aJaen;
	strcpy(granada.nombre,"Granada"); strcpy(granada.provincia,"Granada"); granada.poblacion = 924927; granada.aristas = aGranada;
	strcpy(murcia.nombre,"Murcia"); strcpy(murcia.provincia,"Murcia"); murcia.poblacion = 1470982; murcia.aristas = aMurcia;
	strcpy(albacete.nombre,"Albacete"); strcpy(albacete.provincia,"Albacete"); albacete.poblacion = 402746; albacete.aristas = aAlbacete;
	strcpy(valencia.nombre,"Valencia"); strcpy(valencia.provincia,"Valencia"); valencia.poblacion = 2578134; valencia.aristas = aValencia;
	strcpy(barcelona.nombre,"Barcelona"); strcpy(barcelona.provincia,"Barcelona"); barcelona.poblacion = 5529121; barcelona.aristas = aBarcelona;
	strcpy(gerona.nombre,"Gerona"); strcpy(gerona.provincia,"Gerona"); gerona.poblacion = 756212; gerona.aristas = aGerona;

	insertarVertice(V,coruna); insertarVertice(V,vigo); insertarVertice(V,oviedo); insertarVertice(V,valladolid); insertarVertice(V,bilbao); insertarVertice(V,zaragoza); insertarVertice(V,madrid);
	insertarVertice(V,badajoz); insertarVertice(V,cadiz); insertarVertice(V,sevilla); insertarVertice(V,jaen); insertarVertice(V,granada); insertarVertice(V,murcia); insertarVertice(V,albacete);
	insertarVertice(V,valencia); insertarVertice(V,barcelona); insertarVertice(V,gerona);
		
	nodoArista auxArista;
	strcpy(auxArista.origen,"Coruña"); strcpy(auxArista.destino,"Vigo"); auxArista.tiempo = 45; auxArista.distancia = 171; insertarArista(coruna.aristas, auxArista);
	strcpy(auxArista.origen,"Coruña"); strcpy(auxArista.destino,"Valladolid"); auxArista.tiempo = 310; auxArista.distancia = 455; insertarArista(coruna.aristas, auxArista);
	strcpy(auxArista.origen,"Vigo"); strcpy(auxArista.destino,"Coruña"); auxArista.tiempo = 45; auxArista.distancia = 171; insertarArista(vigo.aristas, auxArista);
	strcpy(auxArista.origen,"Vigo"); strcpy(auxArista.destino,"Valladolid"); auxArista.tiempo = 160; auxArista.distancia = 356; insertarArista(vigo.aristas, auxArista);
	strcpy(auxArista.origen,"Valladolid"); strcpy(auxArista.destino,"Coruña"); auxArista.tiempo = 310; auxArista.distancia = 455; insertarArista(valladolid.aristas, auxArista);
	strcpy(auxArista.origen,"Valladolid"); strcpy(auxArista.destino,"Vigo"); auxArista.tiempo = 160; auxArista.distancia = 356; insertarArista(valladolid.aristas, auxArista);
	strcpy(auxArista.origen,"Valladolid"); strcpy(auxArista.destino,"Bilbao"); auxArista.tiempo = 150; auxArista.distancia = 280; insertarArista(valladolid.aristas, auxArista);
	strcpy(auxArista.origen,"Valladolid"); strcpy(auxArista.destino,"Madrid"); auxArista.tiempo = 70; auxArista.distancia = 193; insertarArista(valladolid.aristas, auxArista);
	strcpy(auxArista.origen,"Oviedo"); strcpy(auxArista.destino,"Bilbao"); auxArista.tiempo = 120; auxArista.distancia = 304; insertarArista(oviedo.aristas, auxArista);
	strcpy(auxArista.origen,"Bilbao"); strcpy(auxArista.destino,"Oviedo"); auxArista.tiempo = 120; auxArista.distancia = 304; insertarArista(bilbao.aristas, auxArista);
	strcpy(auxArista.origen,"Bilbao"); strcpy(auxArista.destino,"Valladolid"); auxArista.tiempo = 150; auxArista.distancia = 280; insertarArista(bilbao.aristas, auxArista);
	strcpy(auxArista.origen,"Bilbao"); strcpy(auxArista.destino,"Madrid"); auxArista.tiempo = 190; auxArista.distancia = 395; insertarArista(bilbao.aristas, auxArista);
	strcpy(auxArista.origen,"Bilbao"); strcpy(auxArista.destino,"Zaragoza"); auxArista.tiempo = 140; auxArista.distancia = 324; insertarArista(bilbao.aristas, auxArista);
	strcpy(auxArista.origen,"Badajoz"); strcpy(auxArista.destino,"Madrid"); auxArista.tiempo = 310; auxArista.distancia = 403; insertarArista(badajoz.aristas, auxArista);
	strcpy(auxArista.origen,"Madrid"); strcpy(auxArista.destino,"Valladolid"); auxArista.tiempo = 70; auxArista.distancia = 193; insertarArista(madrid.aristas, auxArista);
	strcpy(auxArista.origen,"Madrid"); strcpy(auxArista.destino,"Bilbao"); auxArista.tiempo = 190; auxArista.distancia = 395; insertarArista(madrid.aristas, auxArista);
	strcpy(auxArista.origen,"Madrid"); strcpy(auxArista.destino,"Zaragoza"); auxArista.tiempo = 141; auxArista.distancia = 325; insertarArista(madrid.aristas, auxArista);
	strcpy(auxArista.origen,"Madrid"); strcpy(auxArista.destino,"Albacete"); auxArista.tiempo = 110; auxArista.distancia = 251; insertarArista(madrid.aristas, auxArista);
	strcpy(auxArista.origen,"Madrid"); strcpy(auxArista.destino,"Jaen"); auxArista.tiempo = 24; auxArista.distancia = 335; insertarArista(madrid.aristas, auxArista);
	strcpy(auxArista.origen,"Madrid"); strcpy(auxArista.destino,"Badajoz"); auxArista.tiempo = 310; auxArista.distancia = 403; insertarArista(madrid.aristas, auxArista);
	strcpy(auxArista.origen,"Cadiz"); strcpy(auxArista.destino,"Sevilla"); auxArista.tiempo = 90; auxArista.distancia = 125; insertarArista(cadiz.aristas, auxArista);
	strcpy(auxArista.origen,"Sevilla"); strcpy(auxArista.destino,"Cadiz"); auxArista.tiempo = 90; auxArista.distancia = 125; insertarArista(sevilla.aristas, auxArista);
	strcpy(auxArista.origen,"Sevilla"); strcpy(auxArista.destino,"Jaen"); auxArista.tiempo = 60; auxArista.distancia = 242; insertarArista(sevilla.aristas, auxArista);
	strcpy(auxArista.origen,"Sevilla"); strcpy(auxArista.destino,"Granada"); auxArista.tiempo = 103; auxArista.distancia = 256; insertarArista(sevilla.aristas, auxArista);
	strcpy(auxArista.origen,"Jaen"); strcpy(auxArista.destino,"Madrid"); auxArista.tiempo = 24; auxArista.distancia = 335; insertarArista(jaen.aristas, auxArista);
	strcpy(auxArista.origen,"Jaen"); strcpy(auxArista.destino,"Granada"); auxArista.tiempo = 13; auxArista.distancia = 99; insertarArista(jaen.aristas, auxArista);
	strcpy(auxArista.origen,"Jaen"); strcpy(auxArista.destino,"Sevilla"); auxArista.tiempo = 60; auxArista.distancia = 242; insertarArista(jaen.aristas, auxArista);
	strcpy(auxArista.origen,"Granada"); strcpy(auxArista.destino,"Jaen"); auxArista.tiempo = 13; auxArista.distancia = 99; insertarArista(granada.aristas, auxArista);
	strcpy(auxArista.origen,"Granada"); strcpy(auxArista.destino,"Murcia"); auxArista.tiempo = 130; auxArista.distancia = 278; insertarArista(granada.aristas, auxArista);
	strcpy(auxArista.origen,"Granada"); strcpy(auxArista.destino,"Sevilla"); auxArista.tiempo = 103; auxArista.distancia = 256; insertarArista(granada.aristas, auxArista);
	strcpy(auxArista.origen,"Albacete"); strcpy(auxArista.destino,"Madrid"); auxArista.tiempo = 110; auxArista.distancia = 251; insertarArista(albacete.aristas, auxArista);
	strcpy(auxArista.origen,"Albacete"); strcpy(auxArista.destino,"Valencia"); auxArista.tiempo = 70; auxArista.distancia = 191; insertarArista(albacete.aristas, auxArista);
	strcpy(auxArista.origen,"Albacete"); strcpy(auxArista.destino,"Murcia"); auxArista.tiempo = 12; auxArista.distancia = 150; insertarArista(albacete.aristas, auxArista);
	strcpy(auxArista.origen,"Murcia"); strcpy(auxArista.destino,"Albacete"); auxArista.tiempo = 12; auxArista.distancia = 150; insertarArista(murcia.aristas, auxArista);
	strcpy(auxArista.origen,"Murcia"); strcpy(auxArista.destino,"Valencia"); auxArista.tiempo = 220; auxArista.distancia = 241; insertarArista(murcia.aristas, auxArista);
	strcpy(auxArista.origen,"Murcia"); strcpy(auxArista.destino,"Granada"); auxArista.tiempo = 130; auxArista.distancia = 278; insertarArista(murcia.aristas, auxArista);
	strcpy(auxArista.origen,"Valencia"); strcpy(auxArista.destino,"Barcelona"); auxArista.tiempo = 120; auxArista.distancia = 349; insertarArista(valencia.aristas, auxArista);
	strcpy(auxArista.origen,"Valencia"); strcpy(auxArista.destino,"Murcia"); auxArista.tiempo = 220; auxArista.distancia = 241; insertarArista(valencia.aristas, auxArista);
	strcpy(auxArista.origen,"Valencia"); strcpy(auxArista.destino,"Albacete"); auxArista.tiempo = 70; auxArista.distancia = 191; insertarArista(valencia.aristas, auxArista);
	strcpy(auxArista.origen,"Zaragoza"); strcpy(auxArista.destino,"Bilbao"); auxArista.tiempo = 140; auxArista.distancia = 324; insertarArista(zaragoza.aristas, auxArista);
	strcpy(auxArista.origen,"Zaragoza"); strcpy(auxArista.destino,"Madrid"); auxArista.tiempo = 141; auxArista.distancia = 325; insertarArista(zaragoza.aristas, auxArista);
	strcpy(auxArista.origen,"Zaragoza"); strcpy(auxArista.destino,"Barcelona"); auxArista.tiempo = 80; auxArista.distancia = 296; insertarArista(zaragoza.aristas, auxArista);
	strcpy(auxArista.origen,"Barcelona"); strcpy(auxArista.destino,"Zaragoza"); auxArista.tiempo = 80; auxArista.distancia = 296; insertarArista(barcelona.aristas, auxArista);
	strcpy(auxArista.origen,"Barcelona"); strcpy(auxArista.destino,"Gerona"); auxArista.tiempo = 24; auxArista.distancia = 100; insertarArista(barcelona.aristas, auxArista);
	strcpy(auxArista.origen,"Barcelona"); strcpy(auxArista.destino,"Valencia"); auxArista.tiempo = 120; auxArista.distancia = 349; insertarArista(barcelona.aristas, auxArista);
	strcpy(auxArista.origen,"Gerona"); strcpy(auxArista.destino,"Barcelona"); auxArista.tiempo = 24; auxArista.distancia = 100; insertarArista(gerona.aristas, auxArista);
//-----------------------------------------------------
	

	while(free){
		printf("\n*** Menu principal: *** \n");
		printf("1\t Construcion y edicion del grafo\n");
		printf("2\t Configuracion inicial\n");
		printf("3\t Simulacion\n");
		printf("4\t Estadisticas\n");
		printf("5\t Djisktra\n");
		printf("6\t Ruta\n");
		printf("0\t Salir.\n");
		printf("\nSeleccione una accion de menu realizar: ");
		scanf("%i", &accion);
			if(accion == 0 || accion > 6){
				break;
			}
			
			if(accion == 5){
				limpiarEtiquetas(V);
				printf("\tInserte vertice origen del Dijkstra: ");
				fgets(tempVertice.nombre, NOMBRE_SIZE, stdin);
				scanf("%[^\n]", tempVertice.nombre);
				Djisktra(V,tempVertice.nombre);
			}

			if(accion == 6){
				printf("\tInserte el origen de la ruta: ");
				fgets(tempArista.origen, NOMBRE_SIZE, stdin);
				scanf("%[^\n]", tempArista.origen);
				printf("\tInserte el destino de la ruta: ");
				fgets(tempArista.destino, NOMBRE_SIZE, stdin);
				scanf("%[^\n]", tempArista.destino);
				mostrarRuta(V, tempArista.origen,tempArista.destino);
			}

			if(accion == 1){
				printf("\n*** Menu del GRAFO: *** \n");
				printf("1\t Crear VERTICE.\n");
				printf("2\t Eliminar VERTICE.\n");
				printf("3\t Mostrar lista de vertices.\n");
				printf("4\t Crear ARISTA.\n");
				printf("5\t Eliminar ARISTA.\n");
				printf("6\t Mostrar lista de aristas.\n");
				printf("0\t Salir del grafo.\n");

				while(free){
				printf("\nSeleccione una accion de grafo a realizar: ");
				scanf("%i", &accion);
					if(accion == 0 || accion > 6){
						break;
					}

					if(accion == 1){
						listaAristas *A;
						A = listaAristasNueva(); 
						tempVertice.aristas = A;

						printf("\tInserte el NOMBRE del vertice a crear: ");
						fgets(tempVertice.nombre, NOMBRE_SIZE, stdin);
						scanf("%[^\n]", tempVertice.nombre);

						printf("\tInserte la PROVINCIA del vertice: ");
						fgets(tempVertice.provincia, PROVINCIA_SIZE, stdin);
						scanf("%[^\n]", tempVertice.provincia);

						printf("\tInserte la POBLACION del vertice: ");
						scanf("%i", &tempVertice.poblacion);

						insertarVertice(V, tempVertice);
					}//fin accion 1 del grafo

					if(accion == 2){
						if(V->inicio == NULL)
						{
							printf("\t***ERROR*** \n\tNo hay vertices para borrar.\n");		
						}
						else{
							printf("\tInserte el NOMBRE del vertice a borrar: ");
							fgets(tempVertice.nombre, NOMBRE_SIZE, stdin);
							scanf("%[^\n]", tempVertice.nombre);

							printf("\tInserte la PROVINCIA del vertice: ");
							fgets(tempVertice.provincia, PROVINCIA_SIZE, stdin);
							scanf("%[^\n]", tempVertice.provincia);

							if(eliminarVertice(V,tempVertice.nombre,tempVertice.provincia) == 1){
								printf("\t***ERROR***\n\tEse vertice no existe \n");
							}
						}
					}//fin accion 2 del grafo

					if(accion == 3){
						mostrarVertices(V);
					}

					if(accion == 4){
						printf("\tInserte el ORIGEN de la arista: ");
						
						fgets(tempArista.origen, NOMBRE_SIZE, stdin);
						scanf("%[^\n]", tempArista.origen);
						nodoVertice *tempV = consultarVertice(V,tempArista.origen);

						if(tempV!=NULL){
							printf("\tInserte el DESTINO de la arista: ");
							fgets(tempArista.destino, NOMBRE_SIZE, stdin);
							scanf("%[^\n]", tempArista.destino);

							if(consultarVertice(V,tempArista.destino)!=NULL){
								printf("\tInserte el TIEMPO de viaje: ");
								scanf("%i", &tempArista.tiempo);

								printf("\tInserte la DISTANCIA de viaje: ");
								scanf("%i", &tempArista.distancia);
								
								insertarArista(tempV->aristas, tempArista);
							}
						}
				
					}//fin accion 4 del grafo
					
					if(accion == 5){
						printf("\tInserte el ORIGEN de la arista a borrar: ");
						fgets(tempArista.origen, NOMBRE_SIZE, stdin);
						scanf("%[^\n]", tempArista.origen);
						nodoVertice *tempV = consultarVertice(V,tempArista.origen);

						if(tempV!=NULL){
							printf("\tInserte el DESTINO de la arista: ");
							fgets(tempArista.destino, NOMBRE_SIZE, stdin);
							scanf("%[^\n]", tempArista.destino);

							if(consultarVertice(V,tempArista.destino)!=NULL){
								if(eliminarArista(tempV->aristas, tempArista.destino)==1){
									printf("\t***ERROR*** \n\tEsta arista no existe.\n");
								}
							}
						}
						
					}//fin accion 5 del grafo

					if(accion == 6){
						printf("\n\tAristas por vertice:\n");
						for(nodoVertice *i = V->inicio; i!=NULL; i=i->siguiente){
							if(i->aristas->inicio != NULL){
								printf("\t%s:\n", i->nombre);
								mostrarAristas(i->aristas);
							}
							
						}
					} //fin accion 6 del grafo
				}//fin del while del grafo
			}//fin if accion 1 del menu principal

			if(accion == 2){
				printf("\n*** Menu de Configuracion: ***\n");
				printf("\tInserte la cantidad MINIMA de pasajeros para el TREN: ");
				scanf("%i", &pasajerosMinimosTren);
				printf("\tInserte la cantidad MAXIMA de pasajeros para el TREN: ");
				scanf("%i", &pasajerosMaximosTren);	
				printf("\tInserte la cantidad MINIMA de pasajeros para el BUS: ");
				scanf("%i", &pasajerosMinimosBus);
				printf("\tInserte la cantidad MAXIMA de pasajeros para el BUS: ");
				scanf("%i", &pasajerosMaximosBus);
				printf("\tInserte la cantidad MINIMA de pasajeros para el TAXI: ");
				scanf("%i", &pasajerosMinimosTaxi);
				printf("\tInserte la cantidad MAXIMA de pasajeros para el TAXI: ");
				scanf("%i", &pasajerosMaximosTaxi);
				printf("\tInserte la cantidad MINIMA de pasajeros para el VEHICULO: ");
				scanf("%i", &pasajerosMinimosVehiculo);
				printf("\tInserte la cantidad MAXIMA de pasajeros para el VEHICULO: ");
				scanf("%i", &pasajerosMaximosVehiculo);
				printf("\tGRACIAS!\n");
			}//fin accion 3 del menu principal
			
			if(accion == 3){ 
				//METER AQUI EL CODIGO DE LA SIMULACION

			}

	}//fin while del menu principal

	return 0;
}
