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
		printf("\t\t-> %s, tiempo: %i.\n", i->destino, i->tiempo);
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
	obtenerTiempoTotalEnRuta(ruta);
	obtenerDistanciaTotalEnRuta(ruta);
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

//--------------	EJEMPLOS 
	{
	listaAristas *g = listaAristasNueva(); 
	listaAristas *u = listaAristasNueva();
	listaAristas *lc = listaAristasNueva();
	listaAristas *t = listaAristasNueva();
	listaAristas *sc = listaAristasNueva();
	listaAristas *p = listaAristasNueva();
	listaAristas *sr = listaAristasNueva();
	listaAristas *lf = listaAristasNueva();
	
	nodoVertice gv;
	nodoVertice uv;
	nodoVertice lcv;
	nodoVertice tv;
	nodoVertice scv;
	nodoVertice pv;
	nodoVertice srv;
	nodoVertice lfv;

	strcpy(gv.nombre,"Guatuso"); strcpy(gv.provincia,"Alajuela"); gv.poblacion = 12000; gv.aristas = g;
	strcpy(uv.nombre,"Upala"); strcpy(uv.provincia,"Alajuela"); uv.poblacion = 13000; uv.aristas = u;
	strcpy(lcv.nombre,"Los Chiles"); strcpy(lcv.provincia,"Alajuela"); lcv.poblacion = 14000; lcv.aristas = lc; 
	strcpy(tv.nombre,"Tilaran"); strcpy(tv.provincia,"Guanacaste"); tv.poblacion = 15000; tv.aristas = t;
	strcpy(scv.nombre,"San Carlos"); strcpy(scv.provincia,"Alajuela"); scv.poblacion = 16000; scv.aristas = sc;
	strcpy(pv.nombre,"Pital"); strcpy(pv.provincia,"Alajuela"); pv.poblacion = 17000; pv.aristas = p;
	strcpy(srv.nombre,"San Ramon"); strcpy(srv.provincia,"Alajuela"); srv.poblacion = 18000; srv.aristas = sr;
	strcpy(lfv.nombre,"La Fortuna"); strcpy(lfv.provincia,"Alajuela"); lfv.poblacion = 19000; lfv.aristas = lf;

	insertarVertice(V,gv);
	insertarVertice(V,uv);
	insertarVertice(V,lcv);
	insertarVertice(V,tv);
	insertarVertice(V,scv);
	insertarVertice(V,pv);
	insertarVertice(V,srv);
	insertarVertice(V,lfv);

	nodoArista g_t; strcpy(g_t.origen,"Guatuso"); strcpy(g_t.destino,"Tilaran"); g_t.tiempo = 10; g_t.distancia = 80; 
	nodoArista g_u; strcpy(g_u.origen,"Guatuso"); strcpy(g_u.destino,"Upala"); g_u.tiempo = 5; g_u.distancia = 40;
	nodoArista t_lc; strcpy(t_lc.origen,"Tilaran"); strcpy(t_lc.destino,"Los Chiles"); t_lc.tiempo = 6; t_lc.distancia = 120;
	nodoArista t_sc; strcpy(t_sc.origen,"Tilaran"); strcpy(t_sc.destino,"San Carlos"); t_sc.tiempo = 9; t_lc.distancia = 90;
	nodoArista t_sr; strcpy(t_sr.origen,"Tilaran"); strcpy(t_sr.destino,"San Ramon"); t_sr.tiempo = 14; t_lc.distancia = 60;
	nodoArista sr_g; strcpy(sr_g.origen,"San Ramon"); strcpy(sr_g.destino,"Guatuso"); sr_g.tiempo = 2; sr_g.distancia = 95;
	nodoArista sr_lf; strcpy(sr_lf.origen,"San Ramon"); strcpy(sr_lf.destino,"La Fortuna"); sr_lf.tiempo = 12; sr_lf.distancia = 35;
	nodoArista sc_g; strcpy(sc_g.origen,"San Carlos"); strcpy(sc_g.destino,"Guatuso"); sc_g.tiempo = 3; sc_g.distancia = 80;
	nodoArista sc_p; strcpy(sc_p.origen,"San Carlos"); strcpy(sc_p.destino,"Pital"); sc_p.tiempo = 4; sc_p.distancia = 40;
	nodoArista sc_sr; strcpy(sc_sr.origen,"San Carlos"); strcpy(sc_sr.destino,"San Ramon"); sc_sr.tiempo = 9; sc_sr.distancia = 30;
	nodoArista u_sc; strcpy(u_sc.origen,"Upala"); strcpy(u_sc.destino,"San Carlos"); u_sc.tiempo = 5; u_sc.distancia = 120;
	nodoArista u_lf; strcpy(u_lf.origen,"Upala"); strcpy(u_lf.destino,"La Fortuna"); u_lf.tiempo = 9; u_lf.distancia = 85;
	nodoArista u_lc; strcpy(u_lc.origen,"Upala"); strcpy(u_lc.destino,"Los Chiles"); u_lc.tiempo = 7; u_lc.distancia = 15;
	nodoArista lf_sc; strcpy(lf_sc.origen,"La Fortuna"); strcpy(lf_sc.destino,"San Carlos"); lf_sc.tiempo = 6; lf_sc.distancia = 30;
	nodoArista p_u; strcpy(p_u.origen,"Pital"); strcpy(p_u.destino,"Upala"); p_u.tiempo = 1; p_u.distancia = 150;
	nodoArista p_lf; strcpy(p_lf.origen,"Pital"); strcpy(p_lf.destino,"La Fortuna"); p_lf.tiempo = 15; p_lf.distancia = 70;
	nodoArista lc_p; strcpy(lc_p.origen,"Los Chiles"); strcpy(lc_p.destino,"Pital"); lc_p.tiempo = 3; lc_p.distancia = 45;

	insertarArista(gv.aristas, g_t);
	insertarArista(gv.aristas, g_u);
	insertarArista(tv.aristas, t_lc);
	insertarArista(tv.aristas, t_sc);
	insertarArista(tv.aristas, t_sr);
	insertarArista(srv.aristas, sr_g);
	insertarArista(srv.aristas, sr_lf);
	insertarArista(scv.aristas, sc_g);
	insertarArista(scv.aristas, sc_p);
	insertarArista(scv.aristas, sc_sr);
	insertarArista(uv.aristas, u_sc);
	insertarArista(uv.aristas, u_lf);
	insertarArista(uv.aristas, u_lc);
	insertarArista(lfv.aristas, lf_sc);
	insertarArista(pv.aristas, p_u);
	insertarArista(pv.aristas, p_lf);
	insertarArista(lcv.aristas, lc_p);
	}
//-----------------------------------------------------
	while(free){
		printf("\n*** Menu principal: *** \n");
		printf("1\t Construcion y edicion del grafo\n");
		printf("2\t Configuracion inicial\n");
		printf("3\t Simulacion\n");
		printf("4\t Estadisticas\n");
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
