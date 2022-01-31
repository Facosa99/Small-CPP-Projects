#include <stdio.h>
#include <math.h>

//Declaramos nuestras variables globales
int		BitsInformacion;		//Cuantos bits contiene la palabra de entrada.
int 	Entrada[100];			//Usaremos este arreglo para almacenar nuestra palabra. Arreglo permite manejar cada digito por separado.
int 	Hamming[200];			//Aqui guardaremos la entrada con los bits de paridad ya agregados.
int		InvertirHamming[200];	//Para escribir de derecha a izquierda
int		ListaPosParidad[100];	//Una lista donde guardar las posiciones donde tenemos bits de paridad.
int		i, j, k, l;				//Nombres genericos para los contadores que se puedan llegar a necesitar.
int		P, Opcion;						
int		LongitudTotal;
int		Error;					//Aqui podremos elegir que bit sobreescribir para testear nuestro codigo
int		CodigoError[8];			//Aqui almacenaremos la dirección de donde se encuentra el bit alterado



//Declaramos las funciones que vamos a utilizar
void 	CrearHamming();		
void 	Debug();
void 	Paridad();
void 	Imparidad();
void 	AgregarError();
void 	EncontrarErrorPar();
void 	EncontrarErrorImpar();
void	Reparar();

void main ()
{
	printf("\n");
	printf("----------------------------------------CODIGO DE HAMMING------------------------------------------\n");
	printf("\n");
	
	CrearHamming();
	
	printf("Selecciona una opcion:\n	1 - Paridad		2 - Imparidad");
	printf("\n");	
	scanf ("%i", &Opcion);
	printf("\n");	
	switch (Opcion)
	{
		case 1:
			Paridad();
			AgregarError();
			EncontrarErrorPar();
		break;
			
		case 2:
			Imparidad();
			AgregarError();
			EncontrarErrorImpar();
		break;
		
		default:
			printf("Opcion Equivocada, el programa esta destinado a crashear a partir de este punto");
		break;
	}
	
	//Reparar();
	
	Debug();
}

void CrearHamming()
{
	for (i = 0 ; i <= 199 ; i++)
	{
		Hamming[i] = 0;
	}
	
	
	//Primero necesitamos saber cuantos bits tiene la palabra que se va a ingresar
	printf("Ingresa la cantidad de bits en la palabra que quieres codificar: ");
	scanf("%i", &BitsInformacion);
	printf("\n");
	
	//Pedimos cada Bit al usuario
	for( i = 0; i <= ( BitsInformacion - 1 ) ; i++)
	{
		printf("Ingresa el bit en la posicion %i:	", i);
		scanf ("%i", &Entrada[i]);
		printf("\n");
	}
	
	//Calculamos el valor de P
	i = 0;
	while ( i >= 0)
	{
		if ( 	pow(2,i) 	>=		i+BitsInformacion+1 )
		{
			P = i;
			i = -10;
			break;
		}
		else
		{
			i++;
		}
	}
	
	//Ahora que tenemos P y el numero de bits de información, podemos calcular la longitud total del mensaje
	LongitudTotal = P + BitsInformacion;
	
	//Llenamos nuestra lista para invertir
	j = LongitudTotal;
	for ( i = 0 ; i <= LongitudTotal-1 ; i++)
	{
		InvertirHamming[i]=j-1;
		j = j-1;
	}
	
	//Con esta información, comenzamos a crear nuestra tabla
	i 	= 	0;					//Contador para navegar el for
	j 	= 	0;					//Posicion respecto a la derecha
	k 	= 	0;					//Acumulador para agregar potencia
	l	=	BitsInformacion;	//Cola para saber cual es el siguiente bit de información por agregar
	for ( i = (LongitudTotal) ; i >= 0 ; i--)
	{		
		if ( pow(2,k) == j )		
		{
			Hamming[i] = 2;				//Si la potencia pendiente es igual a la posición actual (respecto a la derecha), colocar relleno de bit de paridad
			ListaPosParidad[k] = j-1;	//Guardamos la posicion actual como una de las que tienen paridad
			k++;
		}
		else							//Si no es de paridad, agregamos un bit de información
		{
			Hamming[i] = Entrada[l];
			l--;
		}		
		j++;
	}	
}

void Paridad()
{
	for (i = 0 ; i <= P-1 ; i++)	//Revisamos cada uno de los bits de paridad
	{
		int Acumulador;		Acumulador = -2;
		
		for ( j = pow(2,i) ; j <= LongitudTotal; j = j + 2 * pow(2,i) )
		{		
			for ( k = j ; k <= j + pow(2,i) - 1; k++)
			{
				if (k <= LongitudTotal)
				{
					Acumulador = Acumulador + Hamming[ InvertirHamming[k-1]];
				}				
			}			
		}
		l = pow(2,i);
		if( Acumulador % 2 == 0 )
		{			
			Hamming[InvertirHamming[l-1]] = 0;
		}
		else
		{
			
			Hamming[InvertirHamming[l-1]] = 1;
		}
	}
}
	
void Imparidad()
{
	for (i = 0 ; i <= P-1 ; i++)	//Revisamos cada uno de los bits de paridad
	{
		int Acumulador;		Acumulador = -2;
		
		for ( j = pow(2,i) ; j <= LongitudTotal; j = j + 2 * pow(2,i) )
		{		
			for ( k = j ; k <= j + pow(2,i) - 1; k++)
			{
				if (k <= LongitudTotal)
				{
					Acumulador = Acumulador + Hamming[ InvertirHamming[k-1]];
				}				
			}			
		}
		l = pow(2,i);
		if( Acumulador % 2 == 0 )
		{			
			Hamming[InvertirHamming[l-1]] = 1;
		}
		else
		{			
			Hamming[InvertirHamming[l-1]] = 0;
		}

	}
}
	
void AgregarError()
{
	printf("Tu mensaje ha sido codificado como ");
	for (i = 0 ; i <= (LongitudTotal-1) ; i++)
	{
		printf("%i", Hamming[i]);
	}
	printf(", en que bit del 0 al %i deseas agregar un error?:\n", (LongitudTotal-1));
	scanf ("%i", &Error);
	printf("\n");
	
	if ( Hamming[Error] == 1 )
	{
		printf("La posicion se ha reemplazado por 0");
		Hamming[Error] = 0;
	}
	else
	{
		printf("La posicion se ha reemplazado por 1");
		Hamming[Error] = 1;
	}
	printf("\n");
}

void EncontrarErrorPar()
{
	printf("El error se encuentra en la posicion ");
	for (i = 0 ; i <= P-1 ; i++)	//Revisamos cada uno de los bits de paridad
	{
		int Acumulador;		Acumulador = 0;
		
		for ( j = pow(2,i) ; j <= LongitudTotal; j = j + 2 * pow(2,i) )
		{		
			for ( k = j ; k <= j + pow(2,i) - 1; k++)
			{
				if (k <= LongitudTotal)
				{
					Acumulador = Acumulador + Hamming[ InvertirHamming[k-1]];
				}				
			}			
		}
		l = pow(2,i);	
		printf("%i", Acumulador % 2 );
		//CodigoError[InvertirHamming[l-1]] = Acumulador % 2;
		CodigoError[i] = Acumulador % 2;

	}
	printf("\n");
}

void EncontrarErrorImpar()
{
	printf("El error se encuentra en la posicion ");
	for (i = 0 ; i <= P-1 ; i++)	//Revisamos cada uno de los bits de paridad
	{
		int Acumulador;		Acumulador = 0;
		
		for ( j = pow(2,i) ; j <= LongitudTotal; j = j + 2 * pow(2,i) )
		{		
			for ( k = j ; k <= j + pow(2,i) - 1; k++)
			{
				if (k <= LongitudTotal)
				{
					Acumulador = Acumulador + Hamming[ InvertirHamming[k-1]];
				}				
			}			
		}
		l = pow(2,i);	
		
		if ( Acumulador % 2 == 0 )
		{
			printf("1");
		    CodigoError[i] = 1;
		}
		else
		{
			printf("0");
		    CodigoError[i] = 0;
		}
		

	}
	printf("\n");
}

void Debug()
{
	printf("\n");
	printf("P es igual a:                                   %i", P);
	printf("\n");
	
	printf("El numero de bits de informacion es:            %i", BitsInformacion);
	printf("\n");
	
	printf("La longitud total del mensaje es:               %i", LongitudTotal);
	printf("\n");
	
	printf("La palabra de entrada es:                       ");
	for (i = 0 ; i <= (BitsInformacion-1) ; i++)
	{
		printf("%i", Entrada[i]);
	}
	
	printf("\n");
	printf("La palabra en Hamming es:                       ");
	for (i = 0 ; i <= (LongitudTotal-1) ; i++)
	{
		printf("%i", Hamming[i]);
	}
	
	printf("\n");
	printf("Las posiciones de paridad son (De Der. a Izq):  ");
	for (i = 0 ; i <= P-1 ; i++)
	{
		printf("%i ", ListaPosParidad[i]+1);
	}
	printf("\n");
	printf("InvertirHamming:                                ");
	for (i = 0 ; i <= (LongitudTotal-1) ; i++)
	{
		printf("%i ", InvertirHamming[i]);
	}
	printf("\n");
	printf("El bit seleccionado para el error es:           %i", Error);
	printf("\n");
	printf("El codigo de error es:                          ");
	for (i = P-1 ; i >= 0 ; i--)
	{
		printf("%i", CodigoError[i]);
	}
}

void Reparar()
{
	printf("\n");
	printf("P es igual a:                                   %i", P);
	printf("\n");
	
	printf("El numero de bits de informacion es:            %i", BitsInformacion);
	printf("\n");
	
	printf("La longitud total del mensaje es:               %i", LongitudTotal);
	printf("\n");
	
	printf("La palabra de entrada es:                       ");
	for (i = 0 ; i <= (BitsInformacion-1) ; i++)
	{
		printf("%i", Entrada[i]);
	}
	
	printf("\n");
	printf("La palabra en Hamming es:                       ");
	for (i = 0 ; i <= (LongitudTotal-1) ; i++)
	{
		printf("%i", Hamming[i]);
	}
	
	printf("\n");
	printf("Las posiciones de paridad son (De Der. a Izq):  ");
	for (i = 0 ; i <= P-1 ; i++)
	{
		printf("%i ", ListaPosParidad[i]+1);
	}
	printf("\n");
	printf("InvertirHamming:                                ");
	for (i = 0 ; i <= (LongitudTotal-1) ; i++)
	{
		printf("%i ", InvertirHamming[i]);
	}
	printf("\n");
	printf("El bit seleccionado para el error es:           %i", Error);
	printf("\n");
	printf("El codigo de error es:                          ");
	for (i = P-1 ; i >= 0 ; i--)
	{
		printf("%i", CodigoError[i]);
	}
}



