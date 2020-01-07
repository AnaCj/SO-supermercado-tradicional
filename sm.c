#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

int ncajas;	//numero de cajas
int nclientes;		//numero de clientes
pthread_mutex_t *cajas;		//array de cajas, cada caja es un mutex
int *espera_clientes;		//tiempo de espera de cada cliente

void *cliente(void * num){
	int cajaRandom;		//caja a la que le vamos a asignar
	int cliente_id = *(int *)num;	//identificador del cliente
	int tini;	//tiempo de inicio de espera
	int tfin;	//tiempo de fin de espera

	srand(time(0));		//crea una semilla
	printf("Cliente %d realizando compra.\n", cliente_id);
	sleep((rand() % 2) + 1);	//espera mientras compra
	cajaRandom=(rand()%ncajas);	//le asignamos una caja random
	tini = clock();
	
	printf("Cliente %d asignado a caja %d.\n", cliente_id, cajaRandom);
	// Inicio sección crítica
	pthread_mutex_lock(&(cajas[cajaRandom]));	//bloquea el mutex de su caja
	tfin = clock();
	
	printf("Cliente %d atendido\n", cliente_id);
	sleep( (rand() % 2) + 1);	//espera mientras es atendido
	espera_clientes[cliente_id] = tfin-tini;
	
	printf("Cliente %d saliendo despues de esperar %d .\n", cliente_id, tfin-tini);
	pthread_mutex_unlock(&(cajas[cajaRandom]));	//libera el mutex de su caja
	// Fin sección crítica

	return 0;
}

int main (int argc, char *argv[]){

	int i;		//contador
	int *cliente_id;	//array dinamico de identificadores para los clientes
	pthread_t *th;		//array de threads que actuaran como clientes
	float media;
	float desviacion;
	float aux;

	if (argc==2){		//si solo nos pasan el numero de cajas
		ncajas=atoi(argv[1]);
		nclientes=20*ncajas;
	}
	else if (argc==3){	//si nos pasan el numero de cajas y el numero de clientes
		ncajas=atoi(argv[1]);
		nclientes=atoi(argv[2]);
	}	
	else{		//si no nos pasan argumentos
		printf("Error. Llamar al programa de la forma: %s CAJAS [CLIENTES].\n", argv[0]);
		return -1;
	}
	//reservamos memoria
	cajas = malloc(ncajas*sizeof(pthread_mutex_t));
	cliente_id = malloc(nclientes*sizeof(int));
	th = malloc(nclientes*sizeof(pthread_t));
	espera_clientes = malloc(nclientes*sizeof(int));

	for (i = 0; i<ncajas; i++){	//inicializamos los mutex, cajas
		pthread_mutex_init(&(cajas[i]),NULL);
	}
	for(i = 0; i < nclientes; i++) {	//creamos los clientes, threads
		cliente_id[i] = i;
		pthread_create(&(th[i]),NULL,cliente,(void*)&(cliente_id[i]));
	}
	for (i = 0; i<nclientes; i++){		//sincronizamos los clientes
		pthread_join(th[i],NULL);
	}
	for (i = 0; i<ncajas; i++){	//destruimos los mutex, cajas
		pthread_mutex_destroy(&(cajas[i]));
	}
	media = 0;
	for (i = 0; i<nclientes; i++){		//calculamos la media
		media = media + espera_clientes[i];
	}
	media = media/nclientes;
	desviacion = 0;
	for (i = 0; i<nclientes; i++){		//calculamos la desviacion tipica
		aux = (espera_clientes[i]-media)*(espera_clientes[i]-media);
		desviacion = desviacion + aux;
	}
	desviacion = desviacion/8;
	desviacion = sqrt(desviacion);
	
	//liberamos memoria
	free(cajas);
	free(cliente_id);
	free(th);
	free(espera_clientes);
	
	printf("Supermercado cerrado.\n");
	printf("Tiempo medio de espera: %f.\n", media);
	printf("Desviación típica del tiempo medio de espera: %f.\n", desviacion);
	return 0;
}
