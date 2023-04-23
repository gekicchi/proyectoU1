#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int i=0;

typedef struct guardian // combatientes del torneo
{
	char nombre[50];
	char tipo[11];
	int vida;
	int ataque;
	int defensa;
	struct guardian *next;
} Guardian;

typedef struct torneo // historial de partidas
{
	char dificultad[15];
	char resultado[15];
	int cantidadTurnos;
	int rivalesDerrotados;
	struct torneo *next;
} Torneo;

void AddTorneo(Torneo **head, Torneo* to) // añade torneos a fila
{
	to->next = NULL;
	if (*head == NULL) // lista vacia
		*head = to;
	else // lista con +1 torneo
	{
		Torneo *current = *head;
		while (current->next != NULL)
			current = current->next;
			
		current->next = to;
	}
}

void FreeTorneos(Torneo *head) // libera memoria de torneos
{
	Torneo *current = head;
	while(current != NULL)
	{
		Torneo *next = current->next;
		free(current);
		current = next;
	}
}

Guardian* CreateGuardian(char nom[], char ti[], int vi, int atk, int def) // crea guardianes con parametros dados
{
	Guardian *newGuardian = (Guardian*)malloc(sizeof(Guardian));
	
	strcpy(newGuardian->nombre, nom);
	strcpy(newGuardian->tipo, ti);
	newGuardian->vida = vi;
	newGuardian->ataque = atk;
	newGuardian->defensa = def;
	newGuardian->next = NULL;
	
	return newGuardian;
}

void AddGuardian(Guardian **head, Guardian *gu) // añade guardianes a lista/fila
{
	if (*head == NULL) // lista vacia
		*head = gu;
	else // lista con +1 guardian
	{
		Guardian *current = *head;
		while (current->next != NULL)
			current = current->next;
			
		current->next = gu;
	}
}

Guardian* GetGuardian(Guardian **head, int num) // saca guardian escogido de la lista
{
	if (head != NULL)
	{
		Guardian *prev = *head;
		Guardian *current = *head;
		Guardian *prox = current->next;
		
		while (current != NULL && num > 0)
		{
			prev = current;
			current = current->next;
			if (current != NULL)
				prox = current->next;
			
			num--;
		}
		
		if (current != NULL)
		{
			if (prev->nombre == current->nombre && current->next != NULL) // primer objeto en lista mayor a uno
			{
				*head = (*head)->next;
			}
			else if (prev->nombre != current->nombre && current->next != NULL) // objeto de en medio de la lista
			{
				prev->next = current->next;	
			}
			else if (prev->nombre != current->nombre && current->next == NULL) // objeto al final de lista mayor a uno
			{
				prev->next = NULL;
			}
			else if (prev->nombre == current->nombre && current->next == NULL) // unico objeto en lista
			{
				*head = NULL;
			}
			
			current->next = NULL;
			
			return current;
		}
	}
	printf("No hay mas Guardianes en lista.\n");
	return NULL;
}

Guardian* Dequeue(Guardian **top) // saca primer guardian de fila
{
	if (*top != NULL)
	{
		Guardian *current = *top;
		*top = (*top)->next;
		current->next = NULL;
		
		return current;
	}
	return NULL;
}

void FreeGuardians(Guardian *head) // libera memoria de guardianes
{
	Guardian *current = head;
	while(current != NULL)
	{
		Guardian *next = current->next;
		free(current);
		current = next;
	}
}

int GetListSize(Guardian *head) // devuelve el tamaño de la lista
{
	int tamano = 0;
	Guardian *current = head;
	while (current != NULL)
	{
		tamano++;
		current = current->next;
	}
	return tamano;
}

Guardian* CopyStats(Guardian *original, Guardian *copy) // traspasa los datos de un guardian a otro, usado para resetear al jugador despues de cada combate
{
	strcpy(copy->nombre, original->nombre);
	strcpy(copy->tipo, original->tipo);
	copy->vida = original->vida;
	copy->ataque = original->ataque;
	copy->defensa = original->defensa;
	
	return copy;
}

int CompareNames(Guardian *head, char nom[]) // compara nombre ingresado con nombres de la lista de guardianes
{
	Guardian *current = head;
	while (current != NULL)
	{
		if (strcmp(current->nombre, nom) == 0)
			return 1;
		
		current = current->next;
	}
	
	return 0;
}

Guardian* SelectCharacter(Guardian **head, Guardian *pj) // seleccionar de lista de guardianes
{
	Guardian *current = *head;
	int pos = 1;
	int personaje;
	
	printf("\tNombre\t|  Tipo\t\t|  Vida\t|  Atk\t|  Def\t|\n");
	while (current != NULL)
	{
		printf("[%d]\t%s\t|  %s\t|  %d\t|  %d\t|  %d\t|\n", pos, current->nombre, current->tipo, current->vida, current->ataque, current->defensa);;
		pos++;
		current = current->next;
	}
	do{
		printf("\nIngrese Numero de Guardian: ");
		scanf("%d",&personaje);
		if (personaje < 1 || personaje > pos)
			printf("INGRESO DATO INVALIDO\n");
	} while (personaje < 1 || personaje > pos);
	
	pj = GetGuardian(head, personaje-1);
	
	return pj;
}

Guardian* CreateCharacter(Guardian *head, Guardian *pj) // crear personaje
{
	char nombre[50];
	int tipoN = 0;
	char tipo[11];
	int vida = 10*(rand()%20+40); //400 - 590
	int ataque = 10*(rand()%10+11); //110 - 200
	int defensa = 5*(rand()%14+6); //30 - 95
	
	printf("---Creacion de Personaje---\n");
	do{
		printf("Nombre: ");
		scanf("%s",nombre);
		if (CompareNames(head,nombre) == 1)
			printf("Nombre de Guardian Ocupado.\n");
	} while (CompareNames(head, nombre) == 1);
	
	printf("Tipo:\n");
	printf("[1] Vikingo\t[2] Mago\n[3] Nigromante\t[4] Bestia\n");
	do{
		printf("Clase: ");
		scanf("%d",&tipoN);
		if (tipoN < 1 || tipoN > 4)
			printf("INGRESO DATO INVALIDO\n");
	} while (tipoN < 1 || tipoN > 4);
	
	if (tipoN == 1)
		strcpy(tipo, "vikingo");
	else if (tipoN == 2)
		strcpy(tipo, "mago");
	else if (tipoN == 3)
		strcpy(tipo, "nigromante");
	else
		strcpy(tipo, "bestia");
		
	pj = CreateGuardian(nombre, tipo, vida, ataque, defensa);
	
	return pj;
}

void SelectTournament(Guardian **head, Guardian **top, Torneo *fight) // selecciona dificultad y crea cola de enfrentamientos
{
	srand(time(NULL));
	int dificultad = 0;
	
	Torneo *combate = fight;
	while (combate->next != NULL)
		combate = combate->next;
	
	printf("Seleccione Dificultad\n");
	printf("[1] Principiante\n[2] Intermedio\n[3] Experto\n[4] Volver\n");
	do{
		printf("Dificultad: ");
		scanf("%d", &dificultad);
		if (dificultad < 1 || dificultad > 4)
			printf("INGRESO DATO INVALIDO\n");
	} while (dificultad < 1 || dificultad > 4);
	
	int enfrentamientos = 2*dificultad+1;
	int tamano = GetListSize(*head);
	
	if (dificultad != 4 && tamano >= enfrentamientos)
	{
		for (i=0; i<enfrentamientos; i++)
		{
			int tamano = GetListSize(*head);
			int ran = rand()%tamano;
			
			Guardian *rival = GetGuardian(head, ran);
			AddGuardian(top, rival);
		}
		
		// sirven para almacenar la dificultad en el historial de torneos
		if (GetListSize(*top) == 3)
			strcpy(combate->dificultad, "Principiante");
		else if (GetListSize(*top) == 5)
			strcpy(combate->dificultad, "Intermedio");
		else if (GetListSize(*top) == 7)
			strcpy(combate->dificultad, "Experto");
	}
	else if (tamano < enfrentamientos)
	{
		printf("No hay Suficientes Guardianes para Realizar Torneo\n");
	}
}

void PrintCharacterStatus(Guardian *personaje) // imprime datos de guardian deseado
{
	printf("---Estadisticas de %s---\n", personaje->nombre);
	printf("Tipo:    %s\n", personaje->tipo);
	printf("Vida:    %d\n", personaje->vida);
	printf("Ataque:  %d\n", personaje->ataque);
	printf("Defensa: %d\n", personaje->defensa);
	printf("-------------------------\n");
}

void StartFight(Guardian **top, Guardian **defeat, Guardian *pj, Torneo *fight) // aqui ocurre todo el combate
{
	srand(time(NULL));
	Guardian *jugador = pj;
	Guardian *rivalActual = Dequeue(top);
	Torneo *combate = fight;
	combate->rivalesDerrotados = 0;
	
	int turno = 0;							// turnos de combate
	int dadoJG = 0, dadoCPU = 0;			// relacionadas a dado
	int eleccionJG = 0, eleccionCPU = 0;	// eleccion ataque-defensa
	int vidaInicialJugador = 0, vidaInicialRival = 0;		// cantidad de vida con la que comienzan cada turno
	int vidaPerdidaJugador = 0, vidaPerdidaRival = 0;		// vida que pierden en un turno
	int cura = 0, desgaste = 0;				// relaciondas a la defensa
	int extraJG = 0, extraCPU = 0, loop = -1;				// turnos extra
	
	printf("-----------Torneo %s-----------\n",combate->dificultad);
	do{
		do {
			turno++;
			printf("--------TURNO %d--------\n",turno);
			PrintCharacterStatus(jugador);
			PrintCharacterStatus(rivalActual);
			printf("Que Quiere Hacer?\n");
			printf("[1] Atacar\t[2] Defender\n");
			do{
				printf("Eleccion: ");
				scanf("%d",&eleccionJG);
				if (eleccionJG < 1 || eleccionJG > 2)
					printf("INGRESO DATO INVALIDO\n");
			} while (eleccionJG < 1 || eleccionJG > 2);
			eleccionCPU = rand()%2+1;
			printf("\n");
			
			dadoJG = GetRollResult(1);
			sleep(1);
			dadoCPU = GetRollResult(0);
			sleep(1);
			printf("\n");
			
			// guarda con cuanta vida comenzaron el turno, esta cantidad se mantiene en el turno extra
			vidaInicialJugador = jugador->vida;
			vidaInicialRival = rivalActual->vida;
			
			do{
				// estos 3 if solo se activan si tienen acceso al turno extra
				if (extraJG == 1)
				{
					printf("Que Quiere Hacer?\n");
					printf("[1] Atacar\t[2] Defender\n");
					do{
						printf("Eleccion: ");
						scanf("%d",&eleccionJG);
						if (eleccionJG < 1 || eleccionJG > 2)
							printf("INGRESO DATO INVALIDO\n");
					} while (eleccionJG < 1 || eleccionJG > 2);
					dadoJG = GetRollResult(1);
					sleep(1);
				}
				if (extraCPU == 1)
				{
					eleccionCPU = rand()%2+1;
					dadoCPU = GetRollResult(0);
					sleep(1);
				}
				if (extraJG == 1 || extraCPU == 1)
					printf("\n");
				
				// atacar
				if (eleccionJG == 1 && jugador->vida > 0) // jugador eligio atacar y sigue con vida
				{
					printf("Jugador Ataca!\n");
					
					switch (dadoJG)
					{
						case 1:
							rivalActual->vida -= (jugador->ataque) * 4/5;
							printf("%s ha Quitado %d puntos de vida a %s\n",jugador->nombre, (jugador->ataque ) *4/5, rivalActual->nombre);
							break;
							
						case 3:
							rivalActual->vida -= jugador->ataque;
							printf("%s ha Quitado %d puntos de vida a %s\n",jugador->nombre, jugador->ataque, rivalActual->nombre);
							break;
							
						case 5:
							rivalActual->vida -= (jugador->ataque) * 13/10;
							printf("%s ha Quitado %d puntos de vida a %s\n",jugador->nombre, (jugador->ataque) * 13/10, rivalActual->nombre);
							break;
							
						default:
							printf("%s ha Bloqueado el Ataque de %s\n",rivalActual->nombre, jugador->nombre);
							break;
					}					
				}
				
				if (eleccionCPU == 1 && rivalActual->vida > 0) // cpu eligio atacar y sigue con vida
				{
					printf("Rival Ataca!\n");
					
					switch (dadoCPU)
					{
						case 1:
							jugador->vida -= (rivalActual->ataque) * 4/5;
							printf("%s ha Quitado %d puntos de vida a %s\n",rivalActual->nombre, (rivalActual->ataque) * 4/5, jugador->nombre);
							break;
							
						case 3:
							jugador->vida -= rivalActual->ataque;
							printf("%s ha Quitado %d puntos de vida a %s\n",rivalActual->nombre, rivalActual->ataque, jugador->nombre);
							break;
							
						case 5:
							jugador->vida -= (rivalActual->ataque) * 13/10;
							printf("%s ha Quitado %d puntos de vida a %s\n",rivalActual->nombre, (rivalActual->ataque) * 13/10, jugador->nombre);
							break;
							
						default:
							printf("%s ha Bloqueado el Ataque de %s\n",jugador->nombre, rivalActual->nombre);
							break;
					}	
				}
				
				// calculo de vida perdida en turno para luego calcular la curacion
				vidaPerdidaJugador = vidaInicialJugador - jugador->vida;
				vidaPerdidaRival = vidaInicialRival - rivalActual->vida;
				
				// defender
				if (eleccionJG == 2 && jugador->vida > 0) // jugador eligio defender y sigue con vida
				{
					printf("Jugador Defiende!\n");
					switch (dadoJG)
					{
						case 2:
							cura = (jugador->defensa)/2;
							if (cura > vidaPerdidaJugador) // si la cura potencial sobrepasa la vida perdida en el turno
								cura = vidaPerdidaJugador; // la cura solo puede ser tan grande como la vida que se acaba de perder
								
							jugador->vida += cura;
							printf("%s ha Curado %d  puntos del Dano Recibido\n",jugador->nombre, cura);
							break;
							
						case 4:
							cura = jugador->defensa;
							if (cura > vidaPerdidaJugador)
								cura = vidaPerdidaJugador;
								
							jugador->vida += cura;
							printf("%s ha Curado %d  puntos del Dano Recibido\n",jugador->nombre, cura);
							break;
							
						case 6:
							cura = (jugador->defensa) * 6/5;
							if (cura > vidaPerdidaJugador)
								cura = vidaPerdidaJugador;
								
							jugador->vida += cura;
							printf("%s ha Curado %d  puntos del Dano Recibido\n",jugador->nombre, cura);
							break;
							
						default:
							printf("%s ha Fallado en Defenderse\n",jugador->nombre);
							if (jugador->defensa > 30) // el desgaste ocurre mientras que la defensa sea mayor a 30
							{
								desgaste = (jugador->defensa) * 5/100;
								if (jugador->defensa - desgaste < 30) // si el desgaste dejara al jugador con menos de 30 en defensa
									desgaste = jugador->defensa - 30; // el desgaste es modificado para dejar la defensa en 30 exactamente
									
								jugador->defensa -= desgaste;
								printf("Su Defensa se desgasta en %d\n",desgaste);
							}
							break;
					}
				}
				
				if (eleccionCPU == 2 && rivalActual->vida > 0) // cpu eligio defender y sigue con vida
				{
					printf("Rival Defiende!\n");
					switch (dadoCPU)
					{
					case 2:
							cura = (rivalActual->defensa)/2;
							if (cura > vidaPerdidaRival) // si la cura potencial sobrepasa la vida perdida en el turno
								cura = vidaPerdidaRival; // la cura solo puede ser tan grande como la vida que se acaba de perder
								
							rivalActual->vida += cura;
							printf("%s ha Curado %d  puntos del Dano Recibido\n",rivalActual->nombre, cura);
							break;
							
						case 4:
							cura = rivalActual->defensa;
							if (cura > vidaPerdidaRival)
								cura = vidaPerdidaRival;
								
							rivalActual->vida += cura;
							printf("%s ha Curado %d  puntos del Dano Recibido\n",rivalActual->nombre, cura);
							break;
							
						case 6:
							cura = (rivalActual->defensa) * 6/5;
							if (cura > vidaPerdidaRival)
								cura = vidaPerdidaRival;
								
							rivalActual->vida += cura;
							printf("%s ha Curado %d  puntos del Dano Recibido\n",rivalActual->nombre, cura);
							break;
							
						default:
							printf("%s ha Fallado en Defenderse\n",rivalActual->nombre);
							if (rivalActual->defensa > 30) // el desgaste ocurre mientras que la defensa sea mayor a 30
							{
								desgaste = (rivalActual->defensa) * 5/100;
								if (rivalActual->defensa - desgaste < 30) // si el desgaste dejara al jugador con menos de 30 en defensa
									desgaste = rivalActual->defensa - 30; // el desgaste es modificado para dejar la defensa en 30 exactamente
									
								rivalActual->defensa -= desgaste;
								printf("Su Defensa se desgasta en %d\n",desgaste);
							}
							break;
					}
				}
				
				if (dadoJG == 6 || dadoCPU == 6 && loop == -1)
					printf("\n");
				if (dadoJG  == 6 && loop == -1 && jugador->vida > 0) // jugador saco un 6, aun no recibe turno extra y sigue con vida
				{
					extraJG = 1;
					printf("%s Consiguio un Movimiento Extra\n",jugador->nombre);
				}
				if (dadoCPU == 6 && loop == -1 && rivalActual->vida > 0) // cpu saco un 6, aun no recibe turno extra y sigue con vida
				{
					extraCPU = 1;
					printf("%s Consiguio un Movimiento Extra\n",rivalActual->nombre);
				}
				if (extraJG == 1 || extraCPU == 1)
				{
					loop *= -1; // esto previene que se tenga mas de un turno extra
					// las elecciones se resetean para prevenir problemas en el turno extra
					eleccionJG = 0;
					eleccionCPU = 0;
				}
			} while (loop == 1);
			sleep(1);
			printf("\n");
			
			// reinicio de variables
			extraJG = 0;
			extraCPU = 0;
			
		} while (rivalActual->vida > 0 && jugador->vida > 0);
		
		combate->cantidadTurnos += turno;
		turno = 0;
		
		if (jugador->vida > 0) // gana jugador
		{
			printf("Derrotaste a %s\n",rivalActual->nombre);
			
			jugador = CopyStats(jugador->next, jugador); // reinicia las stats del jugador
			combate->rivalesDerrotados++;
			AddGuardian(defeat, rivalActual); // añade guardian vencido a cola de derrotados
			rivalActual = Dequeue(top);
			
			if (rivalActual != NULL)
			{
				printf("Tu Siguiente Enfrentamiento sera con %s\n",rivalActual->nombre);
				printf("Revitalizando Antes de Continuar...\n");
				sleep(1);
			}
			else
			{
				printf("FELICIDADES. HAS SUPERADO EL TORNEO.\n");
				sleep(1);
				strcpy(combate->resultado, "Victoria");
			}
		}
		else // pierde jugador
		{
			printf("Has Sido Derrotado por %s\n",rivalActual->nombre);
			printf("La Gloria Solo Llega a Aquellos que Nunca se Rinden\n");
			sleep(1);
			strcpy(combate->resultado, "Derrota");
		}
	} while (rivalActual != NULL && jugador->vida > 0);
	
	printf("Puedes Ver tu Desempeno en la Ventana de Historial\n");
}

int GetRollResult(int quien)
{
	srand(time(NULL));
	int dado = rand()%6+1;
	if (quien == 1) // usuario
		printf("Usted ha Lanzado un %d\n",dado);
	else // rival
		printf("Rival ha Lanzado un %d\n",dado);
	return dado;
}

void GetResult(Torneo *head, Guardian *top)
{
	Torneo *current = head;
	Guardian *vencido = top;
	while (current != NULL)
	{
		printf("---Torneo %s---\n",current->dificultad);
		printf("Resultado: %s\n",current->resultado);
		printf("Turnos: %d\n",current->cantidadTurnos);
		printf("Rivales:\n");	
		int rivales = current->rivalesDerrotados;
		for (i=0; i<rivales; i++) // imprimo nombre de los guardianes derrotados en el torneo
		{
			if (vencido != NULL)
			{
				if (i == 0)
					printf("%s ",vencido->nombre);
				else
					printf("-> %s ",vencido->nombre);
					
				vencido = vencido->next;
			}
			else
				break;
		}
		printf("\n----------------------\n");
		
		current = current->next;
	}
}

int main(int argc, char *argv[])
{
	char *file_name = argv[1];
	FILE *file = fopen(file_name, "r");
	
	Guardian *original = NULL;
	char line[100];
	
	while (fgets(line, 100, file) != NULL) // lee archivo de texto
	{
		char *token;
		token = strtok(line, ",");
		char nombre[50];
		strcpy(nombre, token);
		char tipo[11];
		token = strtok(NULL, ",");
		strcpy(tipo, token);
		int vida = atoi(strtok(NULL, ","));
		int ataque = atoi(strtok(NULL, ","));
		int defensa = atoi(strtok(NULL, ","));
		
		Guardian *newGuardian = CreateGuardian(nombre, tipo, vida, ataque, defensa);
		AddGuardian(&original, newGuardian);
	}
	
	fclose(file);
	
	Guardian *rivales = NULL, *derrotados = NULL, *personaje = NULL, *copia = (Guardian*)malloc(sizeof(Guardian));
	Torneo *historial = NULL;
	int eleccion = 0;
	
	do{
		printf("----------------------------------------------------\n");
		printf("--------------The Guardians Tournament--------------\n");
		printf("----------------------------------------------------\n\n");
		
		printf("Que desea hacer?\n");
		printf("[1] Seleccionar Torneo\n[2] Elegir Guardian\n[3] Crear Guardian\n[4] Ver Historial\n[5] Salir\n");
		do{
			printf("Eleccion: ");
			scanf("%d",&eleccion);
			if (eleccion < 1 || eleccion > 5)
				printf("INGRESO DATO INVALIDO\n");
		} while (eleccion < 1 || eleccion > 5);
		printf("\n");
		
		switch(eleccion)
		{
			case 1: // seleccionar torneo
				if (personaje != NULL)
				{
					personaje = CopyStats(copia, personaje); // reinicia las stats del jugador en caso de haber perdido torneo anterior
					Torneo *nuevoTorneo = (Torneo*)malloc(sizeof(Torneo));
					AddTorneo(&historial, nuevoTorneo);
					SelectTournament(&original, &rivales, nuevoTorneo);
					printf("\n");
					
					StartFight(&rivales, &derrotados, personaje, nuevoTorneo);
				}
				else if (personaje == NULL)
					printf("Imposible Comenzar Torneo Antes de Elegir Personaje.\n");
					
				printf("\n");
				break;
				
			case 2: // elegir guardian
				if (personaje == NULL)
				{
					personaje = SelectCharacter(&original, personaje);
					// la copia sirve para poder reiniciar las stats luego de cada pelea
					personaje->next = copia;
					copia = CopyStats(personaje, copia);
					PrintCharacterStatus(personaje);
				}
				else
					printf("Usted ya Tiene un Personaje.\n");
					
				printf("\n");
				break;
				
			case 3: // crear guardian
				if (personaje == NULL)
				{
					personaje = CreateCharacter(original, personaje);
					// la copia sirve para reiniciar stats luego de cada pelea
					personaje->next = copia;
					copia = CopyStats(personaje, copia);
					PrintCharacterStatus(personaje);
				}
				else
					printf("Usted ya Tiene un Personaje.\n");
					
				printf("\n");
				break;
				
			case 4: // ver historial
				if (historial != NULL)
					GetResult(historial, derrotados);
				else
					printf("No hay Torneos que Mostrar.\n");
					
				printf("\n");
				break;
				
			case 5: // salir
				printf("ADIOS!\n");
				FreeGuardians(original);
				FreeGuardians(rivales);
				FreeGuardians(personaje);
				FreeGuardians(derrotados);
				FreeTorneos(historial);
				break;
		}
	} while (eleccion != 5);
	
	return 0;
}
