Integrante 1:
Julio Erik Contreras Fuica
ROL: 201721059-1
e-mail: julio.contrerasf@sansano.usm.cl

Integrante 2:
Cristian Andrés González Bustos
ROL:201704003-3
e-mail: cristian.gonzalezbu@sansano.usm.cl

-------------------------------------------------------------------------------------------

- parteA.c Corresponde al código para la parte A de la tarea.
Compilar con: $ gcc -lm -std=c99 -Wall -Wextra -D_XOPEN_SOURCE=700 parteA.c -o parteA -lrt
Ejectutar con: $ ./parteA n
Donde n corresponde al número para comenzar la Conjetura de Collatz

------------------------------------------------------------------------------------------

- parteA_Zombie.c Corresponde al código para la parte A de la tarea luego de agregar sleep().
Compilar con: $ gcc -lm -std=c99 -Wall -Wextra -D_XOPEN_SOURCE=700 parteA_Zombie.c -o parteA_Zombie -lrt
Ejectutar con: $ ./parteA_Zombie n &
Donde n corresponde al número para comenzar la Conjetura de Collatz
Ver procesos zombie con: $ ps -l

Ver archivo salida.jpg adjunto. Para identificar cúal era el proceso zombie, se ejecutó el comando ps -l luego de correr el programa en modo background. En la columna de más a la derecha (CMD) aparecen dos procesos como zombie. Sin embargo, al analizar la segunda columna de izquierda a derecha (S), se puede ver que uno de estos procesos está en estado S y otro en Z, que corresponden a Sleep y Zombie, respectivamente. Por lo tanto, este último corresponde al proceso hijo zombie, con PID = 21910.

Luego de que terminar la ejecución del programa, no hay procesos zombie.

--------------------------------------------------------------------------------------------

- parteB.c Corresponde al código para la parte B de la tarea.
Compilar con: $ gcc parteB.c -lpthread -o parteB
Ejecutar con: $ ./parteB

--------------------------------------------------------------------------------------------

- parteB_Modificado.c Corresponde al código para la parte B de la tarea, considerando el inciso 3.
Compilar con: $ gcc parteB_Modificado.c -lpthread -o parteB_mod
Ejecutar con: $ ./parteB_mod