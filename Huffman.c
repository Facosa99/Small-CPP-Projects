#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//-----------------------DECLARAMOS LA ESTRUCTURA QUE VAMOS A USAR PARA NUESTRO ARBOL---------------------------------------
struct Caracteres
{
	char 	Caracter	;					//Aqui se almacena el nodo del caracter, en caso de tener uno
	int		HayCaracter;					//Un (intento de) bool para saber si el nodo actual tiene caracter propio o es un nodo de union
	int		HayPadre;						//Un (intento de) bool para saber si el nodo actual tiene padre. Antes de crear el arbol, los nodos no estan relacionados, ninguno tiene padre. Una vez creado, todos tienen poadre excepto el nodo raiz
	int 	Frecuencia	;					//Numero de veces que el caracter se repite dentro del texto
	int		Huffman[20];					//Aqui almacenaremos el codigo. Es un arreglo porque asi es mas facil almacenar cada bit como un elemento independiente
	int		Padre;							//Nodo Padre
	int 	Posicion;						//Posicion actual con respecto al padre.	( 0-Izquierda / 1-Derecha )
	int		Derecha; 						//Hijo a la derecha							( 0-Izquierda / 1-Derecha )	
	int 	Izquierda;						//Hijo a la izquierda						( 0-Izquierda / 1-Derecha )	
	int		Visitado;						//Saber si este nodo ya fue visitado
	int		HuffBits;						//Cuantos bits abarca el codigo Huffman del caracter
	int 	Memoria;						//Consumo de memoria en codigo Huffman
};


struct 		Caracteres 	Caracter[300];		//Nuestro arreglo de estructuras. Cada estructura del arreglo es un nodo del arbol
int 		i, j, NodoActual, TotalCaracteres = 0;
int			ListaFrecuencias[300][2];		//Arreglo para ordernalos. Primer valor: indice ASCII. Segundo: frecuencia
int			ListaNodos[300][2];

void		OrdenarFrecuencias();
void		AsignarCaracteres();
void		ImprimirTexto();
void		CalcularFrecuencia();
void		CrearArbol();
void		ImprimirFrecuencia();
void		ContarCaracteres();
void 		AsignarHuffman();
void		CalcularMemoria();
void 		ImprimirArbol();

//-------------------------------------------DECLARAMOS EL TEXTO------------------------------------------------------------
//char Texto[1000] = "Mississippi River";
char Texto[1000] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum lacinia, mi nec scelerisque consectetur, diam lorem interdum lorem, eget consectetur lacus ligula quis augue. Duis tincidunt velit dui, iaculis aliquet nulla sollicitudin quis. Proin ut feugiat sem, sit amet mattis sapien. Nulla quam massa, lobortis non ultricies vel, egestas ac lorem. Nulla facilisi. Maecenas in volutpat ex, accumsan efficitur velit. Proin blandit nec est vitae malesuada. Ut laoreet, diam sodales posuere ullamcorper, tortor purus dapibus nisl, ac luctus velit mauris vitae nisl. Maecenas ultrices vitae odio a porta. In ut erat non nunc lacinia consequat eu ut ipsum. In pretium aliquet mi, et varius quam venenatis vel. Donec a fermentum felis, et porttitor ligula. Nam sit amet ante tincidunt, condimentum odio sed, molestie tellus. Donec tempor cursus elit, non fermentum mauris iaculis ac. Donec nec vehicula tellus, id lobortis lorem. Phasellus scelerisque diam id mauris viverra fermentum. Fusce ut nulla."; 

int main()
{	
	ImprimirTexto();	
	AsignarCaracteres();
	CalcularFrecuencia();	
	OrdenarFrecuencias();	
	ContarCaracteres();	
	CrearArbol();	
	AsignarHuffman();	
	CalcularMemoria();
	ImprimirArbol();
	ImprimirFrecuencia();	
	CalcularMemoria();	
}

void OrdenarFrecuencias() 
{
	
	//Guardamos las frecuencias en una lista
	for (i = 0; i < 300; i++) 
	{  
        ListaFrecuencias[i][0]	=	i;
        ListaFrecuencias[i][1]	=	Caracter[i].Frecuencia;
    }
    
	//Ordenamos dicha lista
    int j, i;
  	for (j = 0; j < 300 - 1; j++ ) 
	{
    	for (i = 0; i < 300 - j - 1; ++i) 
		{
    		if (ListaFrecuencias[i][1] > ListaFrecuencias[i + 1][1]) 
			{
        		int temp0 							= ListaFrecuencias[i][0];
        		ListaFrecuencias[i]		[0] 		= ListaFrecuencias[i+1][0];
        		ListaFrecuencias[i+1]	[0] 		= temp0;
        
        		int temp1 							= ListaFrecuencias[i]	[1];
        		ListaFrecuencias[i]		[1] 		= ListaFrecuencias[i+1]	[1];
        		ListaFrecuencias[i+1]	[1] 		= temp1;
      		}
    	}
  	}
}

void AsignarCaracteres()
{
	for (i = 0; i < 127; i++)
   {
   		Caracter[i].Posicion 	= 2;
   		Caracter[i].Caracter 	= i;
   		Caracter[i].HayPadre	= 0;
   		Caracter[i].HayCaracter	= 1;
		Caracter[i].Frecuencia 	= 0; 	
		Caracter[i].Visitado	= 0;
		Caracter[i].Derecha		= 0;
		Caracter[i].Izquierda	= 0;	
		Caracter[i].Padre		= 0;
		Caracter[i].HuffBits	= 0;
		for ( j = 19 ; j <= 0 ; j++)
		{
			Caracter[i].Huffman[j] = 0;
			
		}
   }
   	for (i = 128; i < 300; i++)
   {
   		Caracter[i].Posicion 	= 2;
   		Caracter[i].Caracter 	= 'x';	
   		Caracter[i].HayCaracter = 0;
		Caracter[i].Frecuencia 	= 0; 
		Caracter[i].HayPadre	= 0;	
		Caracter[i].Visitado	= 0;
		Caracter[i].Derecha		= 0;
		Caracter[i].Izquierda	= 0;	
		Caracter[i].Padre		= 0;
		Caracter[i].HuffBits	= 0;
   }
      	for (i = 0; i < 300; i++)
   {
   		for(j = 0 ; j <= 19 ; j++)
   		{
   			Caracter[i].Huffman[j] = 0;
		}
   }
}

void ImprimirTexto()
{
	printf("Tu texto es: \n");
	for ( i = 0 ; i <= 1000 ; i++)
	{
		printf("%c", Texto[i]);
	}
	printf("\n");	
}

void CalcularFrecuencia()
{
	int c;
	for ( i = 0 ; i <= 1000 ; i++)
	{
		for ( c = 32 ; c <= 126 ; c++)
		{
			if ( Texto[i] == c)
			{
				Caracter[c].Frecuencia = Caracter[c].Frecuencia + 1;
			}
		}
	}
}

void CrearArbol()
{	
	NodoActual = 140;
	for ( i = 0 ; i <= 300 ; i++)
	{
		ListaNodos[i][0] = ListaFrecuencias[i][0];
		ListaNodos[i][1] = ListaFrecuencias[i][1];		
	}
	
	
	NodoActual = 140;	
	i = 0;
	//Vamos por el primer elemento de la lista
	for ( i = 0 ; i <= 299 ; i++ )
	{	
		if( ListaFrecuencias[i][1] > 0 && Caracter[ListaFrecuencias[i][0]].Visitado == 0)	
		{
			//printf(" El nodo menor es %i\n", Caracter[ListaFrecuencias[i][0]].Caracter);
			Caracter[ListaFrecuencias[i][0]].Visitado 		= 	1;
			Caracter[ListaFrecuencias[i][0]].Posicion		=	1;
			Caracter[ListaFrecuencias[i][0]].HayPadre		=	1;
			Caracter[ListaFrecuencias[i][0]].Padre			=	NodoActual;
			Caracter[NodoActual].Derecha 					= 	ListaFrecuencias[i][0];
			
			if ( ListaFrecuencias[i+1][1] > 0 && Caracter[ListaFrecuencias[i+1][0]].Visitado == 0 )
			{
				//printf(" El segundo nodo menor es %i\n", Caracter[ListaFrecuencias[i+1][0]].Caracter);
				Caracter[ListaFrecuencias[i+1][0]].Visitado =	1;
				Caracter[ListaFrecuencias[i+1][0]].Posicion	=	0;
				Caracter[ListaFrecuencias[i+1][0]].HayPadre	=	1;
				
				Caracter[ListaFrecuencias[i+1][0]].Padre	=	NodoActual;
				Caracter[NodoActual].Izquierda				= 	ListaFrecuencias[i+1][0];
			}
			Caracter[NodoActual].Frecuencia = ListaFrecuencias[i][1] + ListaFrecuencias[i+1][1];
			ListaFrecuencias[NodoActual][1] = Caracter[NodoActual].Frecuencia;
			
			OrdenarFrecuencias();			
			
			//Reiniciamos el contador para volver a buscar los dos nodos mas pequeños
			i = 0;
			
			//Si el nodo raiz cubre todos los caracteres, sobrecargamos el contador para cerrar el ciclo for, pues el arbol está completado
			if ( Caracter[NodoActual].Frecuencia == TotalCaracteres) { i = 1000;  }			
			
			//Pasamos al siguiente nodo en caso de seguir
			NodoActual 						= NodoActual + 1;			
		}
		
		
	}
	
	
}

void AsignarHuffman()
{
	int NumBits;		//Almacenar cuantos bits tiene el caracter en codigo Huffman
	NumBits = 0;
	for ( i = 32 ; i <= 300 ; i++)
	{
		NumBits = 1;
		NodoActual = i;
		j = 7;
		for ( j = 19 ; j >= 0 ; j = j-1)
		{
			if(Caracter[NodoActual].Posicion == 0)
			{
				Caracter[i].Huffman[j] = 0;
				
			}
			else
			{
				Caracter[i].Huffman[j] = 1;
				
			}
			NodoActual = Caracter[NodoActual].Padre;
			
			if ( Caracter[NodoActual].HayPadre)
			{
				NumBits	= NumBits + 1;
			}
		}
		Caracter[i].HuffBits = NumBits;		
	}
}

void ImprimirArbol()
{
	printf("----------Lista de Frecuencias----------\nASCII     Caracter   Frecuencia  Huffman  Posicion HIzquierdo 	HDerecho\n");
}

void ContarCaracteres()
{
	//Contamos cuantos caracteres hay en total
  	for (i = 0 ; i <= 300 ; i++)
  	{
  		TotalCaracteres = TotalCaracteres + ListaFrecuencias[i][1];
	}
}

void ImprimirFrecuencia()
{	
				printf("-----------------------------------------------------------Resultado------------------------------------------------------------\n");
				printf("ASCII        ");	
				printf("Caracter     ");
				printf("Frec.    ");
				printf("Huffman         ");
				printf("Posicion     ");
				printf("Izquierda    	");
				printf("Derecha      ");
				printf("Padre      ");
				printf("Bits     ");
				printf("Memoria      ");
				printf("\n");

	for ( i = 32 ; i <= 299 ; i++)
	{	
		if ( ListaFrecuencias[i][1] >= 1 && Caracter[ListaFrecuencias[i][0]].HayCaracter == 1)	//&& Caracter[ListaFrecuencias[i][0]].HayCaracter == 1
		{
			if ( ListaFrecuencias[i][0] > 99 ) 
			{
				printf("%i          ", ListaFrecuencias[i][0]);								//Codigo ASCII de caracteres mayores al 100
			}
			else
			{
				printf("0%i          ", ListaFrecuencias[i][0]);							//Codigo ASCII de caracteres entre el 32 y el 99
			}
				printf("%c            ", Caracter[ListaFrecuencias[i][0]].Caracter);		//Caracter
				printf("%i 	   ", ListaFrecuencias[i][1]);									//Frecuencia
				int k;
				k = 20 - Caracter[ListaFrecuencias[i][0]].HuffBits;
				for (j = k ; j <= 19 ; j++)													//Codigo de Huffman
				{
					printf("%i", Caracter[ListaFrecuencias[i][0]].Huffman[j]);
				}
				
				printf("		%i        ", Caracter[ListaFrecuencias[i][0]].Posicion);		//Posicion
				printf("    %i        ", Caracter[ListaFrecuencias[i][0]].Izquierda);			//Hijo izquierdo
				printf("   	%i", 		 Caracter[ListaFrecuencias[i][0]].Derecha);				//Hijo Derecho
				printf(" 	  	%i", 	 Caracter[ListaFrecuencias[i][0]].HayPadre);			//HayPadre
				printf("   	%i        ", 	 Caracter[ListaFrecuencias[i][0]].HuffBits);				//Numero de bits en codigo huffman
				printf("%i", 	 Caracter[ListaFrecuencias[i][0]].Memoria);						//Memoeria abarcada
				
				printf("\n");																//Salto de linea
		}

	}		
	int PesoASCII; 		PesoASCII = (TotalCaracteres*8);
	printf("\nEl total de caracteres es %i, por lo que el texto almacenado en codigo ASCII abarca %i bits\n", TotalCaracteres, PesoASCII);
	
	int PesoHuff;	PesoHuff = 0;
	
	for ( i = 0 ; i <= 300 ; i++ )
	{
		if ( Caracter[i].HayCaracter == 1)
		{
			PesoHuff = PesoHuff + Caracter[i].Memoria;
		}		
	}
	printf("En comparacion, el texto almacenado en codigo Huffman abarca %i bits\n", PesoHuff, (PesoHuff / PesoASCII) );   
}

void CalcularMemoria()
{
	for ( i = 0 ; i <= 300 ; i++)
	{
		Caracter[i].Memoria = Caracter[i].Frecuencia * Caracter[i].HuffBits;
	}
}


