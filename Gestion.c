
/*** PRACTICA PRIMER TRIMESTRE -SISTEMA DE GESTION DE UN REPOSITORIO DE OBRAS DE ARTE-***/

//Librerias para que funcione la funcion de borrar pantalla system(CLEAR) para Windows y Linux
#ifdef _WIN32
#define CLEAR "cls"
#else 
#define CLEAR "clear"
#endif

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define NUMERO_OBRAS 20 //Numero maximo de obras

void presentacion(); //Imprimir por pantalla una bienvenida
void menu(); //Menu con las diferentes funciones del programa
void agregarObra(); //Permite agregar una obra
void consultaObra(); //Busca una funcion concreta por titulo
void ConsultaListado(); //Imprime toda la lista de obras
void consultaListadoOrdenado(); //Recoge la opcion por la que ordenar y deriva a la funcion correspondiente
void generaHtml(); //Genera todos los html de cada obra y una principal que incluye todas las obras
void generaHtmlEspecifico(char titulo[]); //Recibe una variable char (titulo), y genera la pagina html del titulo correspondiente
void almacenardatos(); //Pasa todas las obras a la estructura cuadros[]
void prepararcontenido(); //Borra todo el contenido de las variables de la estructura cuadros[]
void pedirNombreHtml(char titulo[]); //Recoge el titulo de una obra
void ordenarportitulo(); //Ordena el array de estructuras cuadros[] por titulo alfabeticamente [A-Z]
void ordenarporautor(); //Ordena el array de estructuras cuadros[] por autor alfabeticamente [A-Z]
void ordenarporanyo(); //Ordena el arrays de estructuras cuadros[] por anyo de creacion de mas antiguo a mas nuevo
void ordenar(int j);//Recibe el valor de j del bucle de las 3 funciones anteriores y ordena el array


FILE *obras; //Declaracion del fichero que vamos a usar en varias funciones

//Declaracion de nuestro tipo de datos para el array de estructuras cuadros[]
struct arte{
	char titulo[500];
	char autor[500];
	int anyo;
	char museo[500];
	char imagen[500];
};

struct arte cuadros[NUMERO_OBRAS]; //Declaracion del array de estructuras que vamos a usar para las obras
struct arte aux[NUMERO_OBRAS]; //Array que utilizaremos para la ordenación de obras


/**********  FUNCION PRINCIPAL  ******************************/

int main(void){

 	presentacion(); //llamamos a esta funcion para mostrar la bienvenida
	menu(); //llamamos al menu, del cual nos derivaremos a cada opcion
	
	return 0;
}
/***********************************************************/


/****** PRESENTACION  ******************************************************/

void presentacion(){

	system(CLEAR);

	printf("\n\n\t\t:*'*::*'*: Repositorio de Obras de Arte :*'*::*'*:\n\n");
	printf("\t\t\t\t        (0 0)\n");
	printf("\t\t\t\t ---oOO--(_)-------\n");
	printf("\t\t\t\t __________________\n");
	printf("\t\t\t\t|                  |\n");
	printf("\t\t\t\t|    BIENVENIDO    |\n");
	printf("\t\t\t\t|__________________|\n");
	printf("\t\t\t\t --------------oOO\n");
	printf("\t\t\t\t      |__|__|\n");
	printf("\t\t\t\t       || ||\n");
	printf("\t\t\t\t      ooO Ooo\n");

	printf("\n\tPulse ENTER para empezar...");
	getchar();
}
/****************************************************************************/


/******* FUNCION QUE NOS MUESTRA EL MENU **********************************/  

void menu(){

	int opcion; //almacenaremos la opcion elegida por el usuario
	char titulo[500]; //Almacenamos el titulo que recoge la funcion pedirNombreHtml


	puts("\n\nIntroduzca una de las siguientes opciones: \n\n");

	do{
		system(CLEAR);
		printf("\n\n\t _______________ M E N U ______________________\n\n");
		printf("\t|                                              |\n");
		printf("\t|                                              |\n");
		printf("\t|  1.- Agregar Obra.                           |\n");
		printf("\t|                                              |\n");
		printf("\t|  2.- Consultar Obra Concreta.                |\n");
		printf("\t|                                              |\n");
		printf("\t|  3.- Consultar Listado de Obra.              |\n");
		printf("\t|                                              |\n");
		printf("\t|  4.- Consultar Listado de Obra Ordenado.     |\n");
		printf("\t|                                              |\n");
		printf("\t|  5.- Generar documentos HTML.                |\n");
		printf("\t|                                              |\n");
		printf("\t|  6.- Generar Documento especifico HTML.      |\n");
		printf("\t|                                              |\n");
		printf("\t|  7.- Salir.                                  |\n");                             
		printf("\t|                                              |\n");
		printf("\t ______________________________________________\n");

		printf("\n\t  Opcion: ");
		scanf("%i",&opcion);

		switch(opcion){
			case 1:
				agregarObra();
				puts("\n\n\t>>> Se ha agregado su obra <<<");
				puts("\n\nPulse ENTER para volver al Menu Principal...");
				getchar();
				break;
			case 2:
				consultaObra();
				break;
			case 3:
				ConsultaListado();
				break;
			case 4:
				consultaListadoOrdenado();
				break;
			case 5:
				generaHtml();
				puts("\n\n\tSe ha generado el HTML principal.");
				puts("\n\nPulse ENTER para volver al Menu Principal...");
				getchar();
				break;
			case 6:
				pedirNombreHtml(titulo); //Recoge el titulo
				generaHtmlEspecifico(titulo); //Envia a esta funcion el titulo recogido de la funcion anterior
				puts("\n\nPulse ENTER para volver al Menu Principal...");
				getchar();
				break;
			case 7:
				break; // No realiza nada y sale del menu
			default:
				puts("\n\n\n\tOPCION INCORRECTA. Pulse ENTER para volver a introducir una opcion.\n");
				getchar();
				break;
		}

	}while(opcion!=7);

	system(CLEAR);
	puts("\n\n\n\n\n\n\n\n\n\t\t:*'*::*'*: >>> GRACIAS POR UTILIZARME <<< :*'*::*'*:\n\n\n\n\n");
	getchar();
}
/*************************************************************************************/



/********* FUNCION QUE NOS PERMITE AGREGAR UNA OBRA AL FICHERO ***********/

void agregarObra(){

	
	//Variables donde recogemos los datos introducidos por el usuario
	char titulo[500];
	char autor[500];
	char museo[500]; 
	int anyo;
	char imagen[500]; 


	system(CLEAR);


	obras=fopen("Obras.txt","a"); //Abre o crea el fichero Obras.txt en modo agregacion

	if(obras==NULL){ //Si el fichero que intenta abrir o crear no se ha creado, muestra un mensaje de error
		puts("Error al intentar abrir el archivo.");
	}else{

		//Recogemos los datos de la obra a agregar
		puts("\n__DATOS DE LA OBRA__\n");
		printf("\n- Introduzca el Titulo: [MAYUSCULAS]");
		setbuf(stdin,NULL); // Equivalente a fflush(stdin) pero que sirve para Windows y Linux
		gets(titulo);
		setbuf(stdin,NULL);
		printf("\n- Introduzca el Autor [Si no dispone, indicar ANONIMO]: [MAYUSCULAS]");
		gets(autor);
		setbuf(stdin,NULL);
		printf("\n- Introduzca el Anyo de creacion [Si no dispone, indicar 0]:  ");
		scanf("%i",&anyo);
		setbuf(stdin,NULL);
		printf("\n- Introduzca el Museo [Si no dispone, indicar PARTICULAR]: [MAYUSCULAS]");
		gets(museo);
		setbuf(stdin,NULL);
		printf("\n- Introduzca el Link de la imagen [Si no dispone, indicar SIN LINK]: ");
		gets(imagen);
		setbuf(stdin,NULL);  


		//Lo escribimos en el fichero Obras.txt
		fputs(titulo,obras);
		fputs("\n",obras);
		fputs(autor,obras);
		fputs("\n",obras);
		fprintf(obras,"%i\n",anyo);
		fputs(museo,obras);
		fputs("\n",obras);
		fputs(imagen,obras);
		fputs("\n",obras);
	}

	fclose(obras);
}
/************************************************************************************/




/****************** BUSCA E IMPRIME LOS DATOS DE UNA OBRA CONCRETA ************************/
void consultaObra(){

	char titulo[500]; //Variable  donde recogemos el titulo de la obra que vamos a buscar
	int i; //Contador que utilizaremos en los bucles
	int posicion; //Variable que utilizaremos para eliminar el salto de linea del titulo que vamos a busar

	system(CLEAR);
	puts("\n\nIntroduzca el Titulo de la obra que quiere buscar: [MAYUSCULAS]");
	setbuf(stdin,NULL);
	gets(titulo);

	almacenardatos(); //Llamamos a esta funcion, la cual nos almacenará del fichero todas las obras a nuestro array de estructuras cuadros[]

	//Eliminamos el salto de linea del final de cada titulo y lo sustituimos por \0
	for(i=0;i<NUMERO_OBRAS;i++){
	posicion=strlen(cuadros[i].titulo)-1;
	cuadros[i].titulo[posicion]='\0';
	}

	//Bucle que imprime los datos de la obra cuando la ha encontrado
	for(i=0;i<NUMERO_OBRAS;i++){
		if(strcmp(titulo,cuadros[i].titulo)==0){ //Compara titulo introducido con los .titulo del array
			printf("\nTitulo: %s",cuadros[i].titulo);
			printf("\nAutor: %s",cuadros[i].autor);
			printf("Anyo: %i",cuadros[i].anyo);
			printf("\nMuseo: %s",cuadros[i].museo);
			printf("Link de la imagen: %s",cuadros[i].imagen);
			break; //Si ha encontrado el titulo, el bucle se rompe para no leer todas las posiciones del arrays
		}
	}
	//Aviso si no ha encontrado el titulo introducido
	if(i==NUMERO_OBRAS){
		printf("\n\t\t---->  TITULO NO ENCONTRADO  <----");
	}

	
	puts("\n\nPulse Enter para volver al Menu Principal...");
	getchar();


	fclose(obras);

}
/************************************************************************/



/************** IMPRIME EL LISTADO COMPLETO DE OBRAS DEL FICHERO ****************/

void ConsultaListado(){

	//Variables donde guardaremos los datos de las obras del fichero
	char lista[500];
	char titulo[500];
	char autor[500];
	int anyo;
	char museo[500];
	char imagen[500];
	
	obras=fopen("Obras.txt","r"); //Abrimos el fichero que vamos a leer

	if(obras==NULL){ //Si no encuentra el fichero muestra un mensaje de error
		puts("Error al intentar abrir el archivo.");
	}else{
		system(CLEAR);
		while((fgets(titulo,500,obras))!=NULL){ //A medida que va leyendo el fichero lo va mostrando

			printf("\nTitulo: %s",titulo);
			fgets(autor,500,obras);
			printf("Autor: %s",autor);
			fscanf(obras,"%i\n",&anyo);
			printf("Anyo: %i\n",anyo);
			fgets(museo,500,obras);
			printf("Museo: %s",museo);
			fgets(imagen,500,obras);
			printf("Link de la Imagen: %s",imagen);

		}
		puts("\n\nPulse Enter para volver al Menu Principal...");
		getchar();
		getchar();

	}

	fclose(obras);

}
/*************************************************************/


/************* PERMITE ELEGIR QUE ORDENACION PREFIERE EL USUARIO **********************************************/

void consultaListadoOrdenado(){

	int opcion; //Variable para lamacenar la opcion elegida por el usuario

	prepararcontenido();
	almacenardatos();


	do{
		system(CLEAR);
		puts("\n\n1 - Ordenar lista por Titulo\n2 - Ordenar lista por Autor\n3 - Ordenar lista por Anyo\n4 - Volver al Menu Principal\n");
		printf("Opcion: ");
		scanf("%i",&opcion);

		switch(opcion){
			case 1:
				ordenarportitulo(); //llamamos a la funcion que lo ordenara por titulo
				break;
			case 2:	
				ordenarporautor(); //llamamos a la funcion que lo ordenara por autor
				break;
			case 3:
				ordenarporanyo(); //llamamos a la funcion que lo ordenara por anyo
				break;
			case 4:
				break;
			default:
				puts("\n\n\n\tOPCION INCORRECTA. Pulse ENTER para volver a introducir una opcion.\n");
				getchar();
				system(CLEAR);
				break;
		}
	}while(opcion!=4);


}
/***************************************************************/


/*********** GENERA UN HTML PRINCIPAL Y HTML POR CADA OBRA ***********************/

void generaHtml(void){

	FILE *html; // Variable para nuestros ficheros
	int i; // Contador para los bucles
	char titulo[500]; //Variable que enviaremos a la funcion generarHtmlEspecifico
	int posicion; // Variable que nos permitira sustituir  \n por \0 de los titulos


	prepararcontenido(); //llamamos a esta funcion para borrar primero el contenido de nuestro array de estructuras
	almacenardatos(); //Almacenamos desde el fichero Obras.txt todas las obras en el array de estructuras cuadros[]

	for(i=0;i<NUMERO_OBRAS;i++){
		if((strcmp(cuadros[i].titulo,""))!=0){  //Para no enviar los datos de las posiciones del array que esten vacias, comparamos para ver si tiene contenido
			posicion=strlen(cuadros[0].titulo)-1; //Igualamos posicion al largo de titulo - 1
			cuadros[0].titulo[posicion]='\0'; //Sustituimos la ultima posicion de cuadros[].titulo por \0, eliminando asi el salto de linea
			strcpy(titulo,cuadros[i].titulo); //Copiamos el contenido de cuadros[].titulo a titulo, ya que enviaremos titulo y sera modificado en el destino
			generaHtmlEspecifico(titulo); //Llamamos a esta funcion y le enviamos titulo para que genere por cada titulo un HTML
		}
	}
	
	html=fopen("Principal.html","w"); // Creamos o sobreescribimos un HTML con el nombre Principal

	if(html==NULL){ // Emite un error si no se ha creado el archivo 
		puts("Error al intentar crear el archivo.");
	}else{	

		//Escribimos en el archivo HTML nuestro codigo HTML 
		fputs("<!DOCTYPE html>\n",html);
		fputs("<html lang='es'>\n",html);
		fputs("<head>\n",html);
		fputs("\t<meta charset='UTF-8'>\n",html);
		fputs("\t<title>PRINCIPAL</title>\n",html); //Como titulo de la pagina sera Principal
		fputs("</head>\n",html);
		fputs("<body>\n",html);

		//Para poder incluir todos las obras en este HTML Principal, acudimos a un bucle que nos irá escribiendo los datos de todas las obras de forma secuencial
		for(i=0;i<NUMERO_OBRAS;i++){
			if((strcmp(cuadros[i].titulo," "))!=0){ //Solo escribira los datos que tengan contenido

				fputs("<blockquote>",html);
				fputs("\n",html);

				//Escribimos el titulo y el enlace de la obra
				fprintf(html,"<a href='%s.html' target=_blank>",cuadros[i].titulo);	//Escribimos el titulo y el enlace
				fprintf(html,"%s","<h1>");
				fputs(cuadros[i].titulo,html);
				fprintf(html,"%s","</h1>");
				fputs("</a>",html);
				//Escribimos el autor
				fprintf(html,"%s","<h2>");
				fputs(cuadros[i].autor,html);
				fprintf(html,"%s","</h2>");
				//Escribimos el anyo
				fprintf(html,"%s","<h2>");
				fprintf(html,"%i\n",cuadros[i].anyo);
				fprintf(html,"%s","</h2>");
				//Escribimos el museo
				fprintf(html,"%s","<h2>");
				fputs(cuadros[i].museo,html);
				fprintf(html,"%s","</h2>");

				//Escribimos la url de la imagen el cual nos mostrara en el HTML directamente una imagen
				fprintf(html,"%s","<img src='");
				fprintf(html,"%s",cuadros[i].imagen);
				fprintf(html,"%s","' />" );
				fputs("\n",html);
				//Escribimos una linea horizontal para separa cada obra
				fputs("<hr/>",html);

			}
		}

		fputs("</body>\n",html); 
		fputs("</html>\n",html); //Cierre del codigo HTML
	}

	fclose(html);
}
/*******************************************************/


/********* GENERA UN HTML CONCRETO ********************************************/

void generaHtmlEspecifico(char titulo[]){

	FILE *html;
	int posicion;
	int i;
	
	char extension[]=".html"; //Cadena de caracteres que nos da la extension del archivo HTML que creamos

	prepararcontenido();
	almacenardatos();

	//Borrarmos el salto de linea de todos los titulos para poder concatenarlos con la variable extension (.html)
	for(i=0;i<NUMERO_OBRAS;i++){

	posicion=strlen(cuadros[i].titulo)-1;
	cuadros[i].titulo[posicion]='\0';
	posicion=strlen(cuadros[i].autor)-1;
	cuadros[i].autor[posicion]='\0';
	posicion=strlen(cuadros[i].museo)-1;
	cuadros[i].museo[posicion]='\0';
	posicion=strlen(cuadros[i].imagen)-1;
	cuadros[i].imagen[posicion]='\0';
	
	}

	for(i=0;i<NUMERO_OBRAS;i++){
		if(strcmp(titulo,cuadros[i].titulo)==0){ //Si la variable titulo que recibe de la funcion pedirNombreHtml() o generarHtml() es igual a un algun titulo del array de estructuras...
			
			strcat(titulo,extension); //Concatena el titulo con la extension .html

			html=fopen(titulo,"w"); //Creamos o sobreescribimos el archivo .html con el formato: titulo de la obra.html

			if(obras==NULL){
				puts("Error al intentar crear el archivo.");
			}else{
				//Escribimos en el archivo HTML nuestro codigo HTML
				fputs("<!DOCTYPE html>\n",html);
				fputs("<html lang='es'>\n",html);
				fputs("<head>\n",html);
				fputs("\t<meta charset='UTF-8'>\n",html);
				fprintf(html,"\t<title>%s</title>\n",cuadros[i].titulo); //Como titulo de la pagina sera el titulo de la obra concreta
				fputs("</head>\n",html);
				fputs("<body bgcolor='#98DFDE'>\n",html);

				
				fputs("<blockquote>",html);
				fputs("\n",html);
				//Escribimos el titulo de la obra
				fprintf(html,"%s","<h1>");
				fputs(cuadros[i].titulo,html);
				fprintf(html,"%s","</h1>");
				//Escribimos el autor de la obra
				fprintf(html,"%s","<h2>");
				fputs(cuadros[i].autor,html);
				fprintf(html,"%s","</h2>");
				//Escribimos el anyo de la obra
				fprintf(html,"%s","<h2>");
				fprintf(html,"%i\n",cuadros[i].anyo);
				fprintf(html,"%s","</h2>");
				//Escribimos el museo de la obra
				fprintf(html,"%s","<h2>");
				fputs(cuadros[i].museo,html);
				fprintf(html,"%s","</h2>");
				//Insertamos una linea horizontal que separa el texto de la imagen
				fputs("<hr/>",html);
				//Escribimos la url de la imagen que nos mostrara una imagen directamente en el HTML
				fprintf(html,"%s","<img src='");
				fprintf(html,"%s",cuadros[i].imagen);
				fprintf(html,"%s","' />" );
				fputs("\n",html);


				fputs("</blockquote>",html);
				fputs("</body>\n",html);
				fputs("</html>\n",html); //Cierre del HTML
			}


			fclose(html);
			break;
		}
	}	
	if(i==NUMERO_OBRAS){ // Si el valor de i es igual al maximo de vueltas del bucle es que no ha encontrado el titulo
		printf("\n\t\t---->  TITULO NO ENCONTRADO  <----");
	}else{
		printf("\n\n\tSe ha generado la pagina de la obra %s.\n",titulo);
	}
}
/*********************************************************/

/****** FUNCION QUE RECOGE EL TITULO DE LA OBRA ************************/

void pedirNombreHtml(char titulo[]){ //Recbie la variable titulo[] de la funcion generarHtml() y sera modificada aqui por referencia
	system(CLEAR);
	puts("\n\nIntroduzca el Titulo de la obra que quiere buscar: [MAYUSCULAS]");
	setbuf(stdin,NULL); //Equivalente a fflush(stdin) que sirve para Windows y Linux
	gets(titulo);
}
/*********************************************************/


/********* COMPARA Y MUESTRA LAS OBRAS ORDENADAS POR TITULO *********************/
void ordenarportitulo(void){

	int i; //Contador para el primer bucle
	int j; //Contador para le segundo bulce y variable que enviaremos a la funcion ordenar(j)

	prepararcontenido();
	almacenardatos();

	system(CLEAR);
	//Comparacion de todas las posiciones del titulo del array de estructuras
	for(i=0;i<NUMERO_OBRAS;i++){ 
		for(j=0;j<NUMERO_OBRAS-1;j++){
			if(strcmp(cuadros[j+1].titulo,cuadros[j].titulo)==-1){ //Comparacion por la Tabla ASCII, si el primer titulo es mayor que el segundo..

				ordenar(j); //Llamamos esta funcion para que con el metodo burbuja ordene todo el arrays
			}
		}
	}

	//Mostramos el contenido del array ordenado
	for(i=0;i<NUMERO_OBRAS;i++){
		if((strcmp(cuadros[i].titulo," "))!=0){  //Si el contenido de una posicion del array es vacia no lo mostrara
			printf("\nTitulo:%s",cuadros[i].titulo);
			printf("Autor: %s",cuadros[i].autor);
			printf("Anyo: %i\n",cuadros[i].anyo);
			printf("Museo: %s\n",cuadros[i].museo);
			printf("Link de la Imagen: %s\n",cuadros[i].imagen);

		};
	}

	puts("Pulse ENTER para volver al Menu anterior...");
	getchar();
	
}
/***********************************************************/



/************* COMPARA Y MUESTRA LAS OBRAS ORDENADAS POR AUTOR ****************************/
void ordenarporautor(void){

	int i;
	int j;

	prepararcontenido();
	almacenardatos();

	system(CLEAR);

	//Tiene el mismo funcionamiento que la funcion anterior ordenarportitulo()
	for(i=0;i<NUMERO_OBRAS;i++){
		for(j=0;j<NUMERO_OBRAS-1;j++){
			if(strcmp(cuadros[j+1].autor,cuadros[j].autor)==-1){

				ordenar(j);	
			}
		}
	}

	for(i=0;i<NUMERO_OBRAS;i++){
		if((strcmp(cuadros[i].titulo," "))!=0){
			printf("\nTitulo:%s",cuadros[i].titulo);
			printf("Autor: %s",cuadros[i].autor);
			printf("Anyo: %i\n",cuadros[i].anyo);
			printf("Museo: %s\n",cuadros[i].museo);
			printf("Link de la Imagen: %s\n",cuadros[i].imagen);

		};
	}

	puts("Pulse ENTER para volver al Menu anterior...");
	getchar();

}
/***********************************************************/


/********** COMPARA Y MUESTRA LAS OBRAS ORDENADAS POR ANYO *******************/
void ordenarporanyo(void){

	int i;
	int j;

	system(CLEAR);

	prepararcontenido();
	almacenardatos();

	//Tiene el mismo funcionamiento que las dos funciones anteriores ordenarPorTitulo() y ordenarPorAutor
	for(i=0;i<NUMERO_OBRAS;i++){
		for(j=0;j<NUMERO_OBRAS-1;j++){
			if(cuadros[j+1].anyo<cuadros[j].anyo){ //Comparacion normal de numeros menor que...

				ordenar(j);	
			}
		}
	}

	for(i=0;i<NUMERO_OBRAS;i++){
		if((strcmp(cuadros[i].titulo," "))!=0){ 
			printf("\nTitulo:%s",cuadros[i].titulo);
			printf("Autor: %s",cuadros[i].autor);
			printf("Anyo: %i\n",cuadros[i].anyo);
			printf("Museo: %s\n",cuadros[i].museo);
			printf("Link de la Imagen: %s\n",cuadros[i].imagen);

		};
	}

	puts("Pulse ENTER para volver al Menu anterior...");
	getchar();
}
/*******************************************************************/


/********* ALMACENA TODAS LAS OBRAS DEL FICHERO **********************************/
void almacenardatos(void){

	FILE *obras;
	
	int i=0; // Contador para bulce while que empieza en 0 ya que sera la primera posicion de nuestro array de estructuras

	
	obras=fopen("Obras.txt","r+"); //Abrimos el fichero Obras.txt para su lectura

	if(obras==NULL){ //Mensaje de error si no encuentra el fichero
		puts("Error al intentar abrir el archivo.");
	}else{


	while((fgets(cuadros[i].titulo,500,obras))!=NULL){ //Lee la primera linea hasta encontrar un nulo, es decir "nada" y lo almacena en cada una de las variables siguientes
			setbuf(stdin,NULL);
			fgets(cuadros[i].autor,500,obras);
			setbuf(stdin,NULL);
			fscanf(obras,"%i\n",&cuadros[i].anyo);
			setbuf(stdin,NULL);
			fgets(cuadros[i].museo,500,obras);
			setbuf(stdin,NULL);
			fgets(cuadros[i].imagen,500,obras);
			setbuf(stdin,NULL);
			i++; //Contador que aumenta en 1 uen cada vuelta del bulce while para las posiciones del array de estructuras
		}
	}

	fclose(obras);
}
/*******************************************************************/


/******** BORRA TODO EL CONTENIDO DEL ARRAY DE ESTRUCTURAS CUADROS[] ******/
void prepararcontenido(void){

	int i;

	for(i=0;i<NUMERO_OBRAS;i++){

		strcpy(cuadros[i].titulo," ");
		strcpy(cuadros[i].autor," ");
		cuadros[i].anyo=0;
		strcpy(cuadros[i].museo," ");
		strcpy(cuadros[i].imagen," ");

		}

}
/*******************************************************************/


/********** FUNCION QUE ORDENA POR EL METODO DE LA BURBUJA ********************/

void ordenar(int j){ //Recibe la variable j de las 3 funciones de ordenacion anteriores

	//Utilizamos como auxiliar el array de estructuras creado con el mismo tipo que cuadros[] 
	aux[j]=cuadros[j];
	cuadros[j]=cuadros[j+1];
	cuadros[j+1]=aux[j];

}
/***************************************************************************************/
