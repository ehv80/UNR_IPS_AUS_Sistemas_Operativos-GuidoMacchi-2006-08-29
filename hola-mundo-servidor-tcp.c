/* Archivo: hola-mundo-servidor-tcp.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/* DEFINICIONES */
#define PORT 5000
#define SIZE 1024

/* SINONIMOS */
typedef struct sockaddr * sad;	
//	sad	puntero a una struct sockaddr

/* FUNCIONES */
void error(char * s)
{
	perror(s);
	exit(-1);
}

/* FUNCION PRINCIPAL */
int main()
{
	int s, s1;
	char linea[SIZE];
	int cuanto, L;
	
	if( (s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		error("socket");
	
	struct sockaddr_in sin, sin1; //Leer: man 7 ip	
	//sin y sin1 son del tipo: struct sockaddr_in
	
	sin.sin_family = AF_INET;	  //Leer: man 7 ip
	sin.sin_port = htons(PORT);       //Host To Network Short. Leer: man 3 htons 
	sin.sin_addr.s_addr = INADDR_ANY; //Cualquier interface. 
	
	if( bind(s, (sad)&sin, sizeof sin) < 0)
		error("bind");
	
	if( listen(s, 5) < 0 )
		error("listen");
	
	L = sizeof(sin1);
	if((s1 = accept(s, (sad)&sin1, &L)) < 0) //Recibe por s. Atiende por s1.
		error("accept");
	
	cuanto = read(s1, linea, SIZE); //Leer: man 2 read
	linea[cuanto] = 0;
	printf("De %s : %d llega ···> %s \n",
			inet_ntoa(sin1.sin_addr),
			ntohs(sin1.sin_port),
			linea);
	write(s1, "CHAU !", 5);
	
	//Los sockets abiertos deben cerrarse.
	close(s1), close(s);

	return 0;	//Finalización exitosa
}
/* Fin Archivo: hola-mundo-servidor-tcp.c */
