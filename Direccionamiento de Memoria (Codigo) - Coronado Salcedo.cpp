#include <stdio.h>
#include <stdlib.h>
#define CACHE 32
#define MEMORIA 128
#define BLOQUE 8
#define tamanioIndiceCache 2
#define tamanioIndiceEtiqueta 2
#define direccionesCache 4
#define direccionesMemoria 16
#define tamanioOffset 3
#define tamanioControl 7
//Funciones//
void capturaControl();
void llenarCache();
void imprimirCache();
void llenarMemoria();
void imprimirMemoria();
void llenarEtiqueta();
void imprimirEtiqueta(int);
void imprimirIndiceCache(int);
void stringToBool();
void imprimirControl();
void imprimirIndiceMemoria(int);
void decodificarControl();
void tipoOperacion();
void memoriaToCache();
void cambiarEtiqueta();
//Variables//
int indiceEtiqueta = 0;
int indiceCache = 0;
int indiceMemoria = 0;
int indiceOffset = 0;
int cache[direccionesCache][BLOQUE];
int memoria[direccionesMemoria][BLOQUE];
int etiqueta[tamanioIndiceEtiqueta*2];
bool control[tamanioControl];
char controlAuxiliar[tamanioControl];
int indiceCacheConstante[direccionesCache] = {00, 01, 10, 11};


int main(){
	llenarCache();
	llenarMemoria();
	llenarEtiqueta();
	while(1)
	{
		imprimirCache();
		imprimirMemoria();
		capturaControl();
		stringToBool();
		//imprimirControl();
		decodificarControl();
		tipoOperacion();
	}
return 0;
}

void capturaControl()
{
	printf("\nControl: ");
	scanf("%s",&controlAuxiliar);
}

void stringToBool()
{
	for(int i=0;i<tamanioControl;i++)
	control[i] = ((int)controlAuxiliar[i]) - '0';
}

void imprimirControl()
{
	for(int i=0;i<tamanioControl;i++)
	printf("%d", control[i]);
}

void llenarCache()
{
	for(int i=0; i<direccionesCache;i++)
	{
		for(int j=0;j<BLOQUE;j++)
		{
			cache[i][j] = 0;
		}
	}
}

void llenarMemoria()
{
	for(int i=0; i<direccionesMemoria;i++)
	{
		for(int j=0;j<BLOQUE;j++)
		{
			if(j==0)
				memoria[i][j] = i*BLOQUE;
			else
				memoria[i][j] = memoria[i][j-1] + 1;
		}
	}
}

void llenarEtiqueta()
{
	etiqueta[0] = 00;
	etiqueta[1] = 01;
	etiqueta[2] = 10;
	etiqueta[3] = 11;
}

void imprimirCache()
{
	printf("Etq Ind\t\t Cache\n");
	for(int i=0; i<direccionesCache;i++)
	{
		imprimirEtiqueta(i);
		imprimirIndiceCache(i);
		for(int j=0;j<BLOQUE;j++)
		{
			if(cache[i][j]<10)
			printf("00%d ", cache[i][j]);
			else if(cache[i][j]<100 && cache[i][j]>9)
			printf("0%d ", cache[i][j]);
			else
			printf("%d ", cache[i][j]);
		}
		printf("\n");
	}
}

void imprimirMemoria()
{
	int numero=0;
	printf("\n Indice\t\t Memoria\n");
	for(int i=0; i<direccionesMemoria;i++)
	{
		imprimirIndiceMemoria(numero);
		for(int j=0;j<BLOQUE;j++)
		{
			if(memoria[i][j]<10)
			printf("00%d ", memoria[i][j]);
			else if(memoria[i][j]<100 && memoria[i][j]>9)
			printf("0%d ", memoria[i][j]);
			else
			printf("%d ", memoria[i][j]);
		}
		printf("\n");
		numero++;
	}
}

void imprimirIndiceCache(int indice)
{
	if(indice==0)
	printf("%02i ",indiceCacheConstante[indice]);
	else if(indice==1)
	printf("%02i ",indiceCacheConstante[indice]);
	else if(indice==2)
	printf("%02i ",indiceCacheConstante[indice]);
	else if(indice==3)
	printf("%02i ",indiceCacheConstante[indice]);
	printf("| ");
}

void imprimirEtiqueta(int indice)
{
	if(indice==0)
	printf("%02i ",etiqueta[indice]);
	else if(indice==1)
	printf("%02i ",etiqueta[indice]);
	else if(indice==2)
	printf("%02i ",etiqueta[indice]);
	else if(indice==3)
	printf("%02i ",etiqueta[indice]);
	printf("| ");
}

void imprimirIndiceMemoria(int numero)
{
	switch(numero)
	{
		case 0: printf("0 0 0 0 | "); break;
		case 1: printf("0 0 0 1 | "); break;
		case 2: printf("0 0 1 0 | "); break;
		case 3: printf("0 0 1 1 | "); break;
		case 4: printf("0 1 0 0 | "); break;
		case 5: printf("0 1 0 1 | "); break;
		case 6: printf("0 1 1 0 | "); break;
		case 7: printf("0 1 1 1 | "); break;
		case 8: printf("1 0 0 0 | "); break;
		case 9: printf("1 0 0 1 | "); break;
		case 10: printf("1 0 1 0 | "); break;
		case 11: printf("1 0 1 1 | "); break;
		case 12: printf("1 1 0 0 | "); break;
		case 13: printf("1 1 0 1 | "); break;
		case 14: printf("1 1 1 0 | "); break;
		case 15: printf("1 1 1 1 | "); break;
	}
}

void decodificarControl()
{
	indiceEtiqueta = 0;
	indiceCache = 0;
	indiceMemoria = 0;
	indiceOffset = 0;
	indiceEtiqueta += control[0];
	indiceEtiqueta = indiceEtiqueta << 1;
	indiceEtiqueta += control[1];
	printf("\nIndice etiqueta: %d\n", indiceEtiqueta);
	indiceCache += control[2];
	indiceCache = indiceCache << 1;
	indiceCache += control[3];
	printf("Indice cache: %d\n", indiceCache);
	indiceMemoria = (indiceEtiqueta << 2) | indiceCache;
	printf("Indice memoria: %d\n", indiceMemoria);
	indiceOffset += control[4];
	indiceOffset = indiceOffset << 1;
	indiceOffset += control[5];
	indiceOffset = indiceOffset << 1;
	indiceOffset += control[6];
	printf("Indice offset: %d\n", indiceOffset);
}

void tipoOperacion()
{
	if(indiceCache != indiceEtiqueta)
	{
	printf("\nEl indice de la cache y la etiqueta son diferentes.\n");
	memoriaToCache();
	}

	else
	{
		printf("\nEl indice de la cache y la etiqueta son iguales.\n");
		memoriaToCache();
	}
}

void memoriaToCache()
{
	if(cache[indiceCache][indiceOffset] == memoria[indiceMemoria]
	[indiceOffset])
	printf("Los valores son iguales. Es un hit.\n\n");
	else
	{
		printf("Los valores son diferentes. Es un miss.\n");
		if(etiqueta[indiceEtiqueta] !=
		indiceCacheConstante[indiceCache])
		cambiarEtiqueta();
		cache[indiceCache][indiceOffset] =
		memoria[indiceMemoria][indiceOffset];
		printf("Valor agregado a la cache.\n\n");
	}
}

void cambiarEtiqueta()
{
	int auxiliarDecodificador[tamanioIndiceEtiqueta*2];
	int auxiliarCambio=0;
	for(int i=0;i<tamanioIndiceEtiqueta*2;i++)
	switch(etiqueta[i])
	{
		case 0: auxiliarDecodificador[i]=0;
		break;
		case 1: auxiliarDecodificador[i]=1;
		break;
		case 10: auxiliarDecodificador[i]=2;
		break;
		case 11: auxiliarDecodificador[i]=3;
		break;
	}
	for(int i=0;i<tamanioIndiceEtiqueta*2;i++)
	if(auxiliarDecodificador[i] == indiceEtiqueta)
	{
		auxiliarCambio = etiqueta[i];
		etiqueta[i] = etiqueta[indiceCache];
		etiqueta[indiceCache] = auxiliarCambio;
		break;
	}
	//Rellena de 0 la fila despues del cambio de etiqueta//
	for(int i;i<BLOQUE;i++)
	cache[indiceCache][i] = 0;
	//Rellena la fila de lo que hay en la memoria//
	/*for(int i;i<BLOQUE;i++)
	cache[indiceCache][i] = memoria[indiceMemoria][i];*/
	printf("La etiqueta ha sido modificada\n");
}
