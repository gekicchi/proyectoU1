PROBLEMA
se desea crear un producto computacional que actue como la propuesta de videojuego "The Guardians Tournament".
este juego requiere de:
- una lista de guardianes de los cuales el jugador podra elegir uno o crear uno nuevo
- el poder participar de torneos donde el jugador podra enfrentar a 3, 5 o 7 guardianes dependiendo de la dificultad que se elija.
- la no repeticion de guardianes dentro de un mismo torneo o en torneos subsiguientes
- un sistema de combate que contenga el atacar y defender lanzando un dado que defina la calidad del resultado, ademas del poder tener un turno si el dado lanza un 6
- un sistema que permita ver el historial de torneos en los cuales el jugador haya participado

SOLUCION
para poder llevar a cabo esto se han realizado las siguientes funcionalidades:
- 2 estructuras, "Guardian" la cual almacena los datos de todos los posibles combatientes y "Torneo" que almacena los datos de cada torneo para ver en el historial
- la inclusion de un archivo de texto llamado "guardianes.txt" que incluye toda la informacion necesaria para crear 26 guardianes distintos
- 1 lista que almacene a los 26 guardianes, de la cual se puede sacar 1 guardian si es que el jugador elige ocupar uno, tambien se pueden sacar al azar guardianes para crear filas de rivales a enfrentar, las cuales a su vez son luego usadas para crear una fila de guardianes derrotados
- 1 fila de torneos, los cuales son manipulados a tiempo real para almacenar la informacion que luego puede ser vista en el historial de batalla, esta informacion incluye: dificultad, cantidad total de turnos, resultado (victoria o derrota) y cantidad de guardianes derrotados (los cuales son luego mostrados usando la fila de guardianes derrotados)
- distintas funciones las cuales permiten al jugador: elegir personaje, crear personaje, seleccionar torneo, participar de un torneo, ver historial de torneos, ver estadisticas tanto de su personaje como del rival actual, ver resultado del lanzamiento del dado en combate.
- distintas funciones de manejo de listas/filas: crear guardian, añadir guardian a lista, sacar guardian de lista, liberar memoria de lista de guardianes, añadir torneo a fila, liberar memoria de torneos
- funciones miscelaneas: ver tamaño de lista/fila deseada, copiar datos de un guardian a otro, comparar nombre ingresado con nombres de los guardianes de la lista