//! ELO321 - Teoría de Sistemas Operativos, 2020-2
/*!
* @file   : parteC.c 
* @author : Julio Contreras Fuica
* @author : Cristian González Bustos
* @date   : 10/12/2020
* @brief  : Parte C de la Tarea 2.
*/

// Compilar con: gcc tarea2/parteC.c -lpthread -o parteC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdint.h>
#include <pthread.h>


int sudoku_array[9][9]  = {{6,2,4,5,3,9,1,8,7},
                           {5,1,9,7,2,8,6,3,4},
                           {8,3,7,6,1,4,2,9,5},
                           {1,4,3,8,6,5,7,2,9},
                           {9,5,8,2,4,7,3,6,1},
                           {7,6,2,3,9,1,4,5,8},
                           {3,7,1,9,5,6,8,4,2},
                           {4,9,6,1,8,2,5,7,3},
                           {2,8,5,4,7,3,9,1,6}};

int rows_checked[9];
int cols_checked[9];
int sub_grids_checked[9];
const int correcto[9] = {1,1,1,1,1,1,1,1,1};
int size = sizeof(correcto);

struct indices {
            int init_row;  // fila inicial
            int fin_row;   // fila final
            int init_col;  // columna inicial
            int fin_col;   // columna final
};

struct timeval tv1, tv2;

/*! \fn validity_check (struct indices i)
    \brief Verifica que cada dígito (1-9) aparezca
    \      una sola vez entre los indices dados.
    \param i Estructura con indices mínimos y máximos.
    \retval 1 si la verificación es correcta, 0 si no.
*/

void* validity_check_r (void*);
void* validity_check_c (void*);
void* validity_check_s (void*);


int main(){
    struct indices i;
    int j,k,m,n;
    int sub = 0;

    gettimeofday(&tv1, NULL);

    for (m = 0; m < 1; m++)
    {
    
        pthread_t threadID [18];
        pthread_attr_t attr [18];
        
        // filas
        i.init_col = 0;
        i.fin_col = 8;
        i.init_row = 0;
        i.fin_row = 8;
        
        pthread_attr_init(&attr[0]);
        pthread_create(&threadID[0], &attr[0], validity_check_r, &i);
        
        // columnas
        pthread_attr_init(&attr[1]);
        pthread_create(&threadID[1], &attr[1], validity_check_c, &i);
    
    
//        //Comprobar filas
//        for (j=0; j<=2; j++){
//            i.init_row = 3*j;
//            i.fin_row = 3*j+2;
//            i.init_col = 0;
//            i.fin_col = 8;
//            pthread_attr_init(&attr[j]);
//            pthread_create(&threadID[j], &attr[j], validity_check_r, &i);
//        }
//
//        //Comprobar columnas
//        for (k=0; k<=2; k++){
//            i.init_row = 0;
//            i.fin_row = 8;
//            i.init_col = 3*k;
//            i.fin_col = 3*k+2;
//            pthread_attr_init(&attr[k+3]);
//            pthread_create(&threadID[k+3], &attr[k+3], validity_check_c, &i);
//        }

//        //Comprobar subcuadrículas
//        for(j=0 ; j<=2; j++){
//            for(k=0 ; k<=2; k++){
//                i.init_row = 3*j;
//                i.fin_row = 3*j + 2;
//                i.init_col = 3*k;
//                i.fin_col = 3*k + 2;
//                if(validity_check(i)){
//                    sub_grids_checked[sub] = 1;
//                }
//                sub++;
//            }
//        }

//        pthread_join(threadID[0], NULL);
//        pthread_join(threadID[1], NULL);

        for (n = 0; n <= 1; n++)
          pthread_join(threadID[n], NULL);
        
        
        
        
        gettimeofday(&tv2, NULL);
        printf ("Tiempo hasta repetión n° %d: %f sec\n", m, (double) (tv2.tv_usec - tv1.tv_usec) / 1000000.0 + (double) (tv2.tv_sec - tv1.tv_sec));
    }
    gettimeofday(&tv2, NULL);
    printf("Tiempo promedio de %d repeticiones: %f sec\n", m, ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000.0 + (double) (tv2.tv_sec - tv1.tv_sec)) );
    
    //Comprobación final
    if (memcmp(rows_checked, correcto, size) + memcmp(cols_checked, correcto, size) == 0) //memcmp(sub_grids_checked, correcto, size)
    {
        printf("Sudoku correcto\n");
    } else {
        printf("Sudoku incorrecto\n");
    }
    

    return 0;
}


void* validity_check_r (void*s){
    int comprobador[9] = {0,0,0,0,0,0,0,0,0};
    int j,k;
    struct indices i = *(struct indices*)s;

    for(j=i.init_row ; j<=i.fin_row; j++){
        for(k=i.init_col ; k<=i.fin_col; k++){
            comprobador[sudoku_array[j][k]-1] = 1;
            //printf("verificando: %d. ", sudoku_array[j][k]);
            //printf("ID: %u\n", pthread_self() );
        }
        if(memcmp(comprobador, correcto, size) == 0) {
          rows_checked[j] = 1;
          //printf("Fila %d está correcta. ",j);
          //printf("ID: %u\n\n", pthread_self() );
        }
        else {
          //printf("Fila %d está INCORRECTA. ",j);
          //printf("ID: %u\n\n", pthread_self() );
        }
        memset (comprobador, 0, size);
    }
    pthread_exit(0);
}

void* validity_check_c (void*s){
    int comprobador[9] = {0,0,0,0,0,0,0,0,0};
    int j,k;
    struct indices i = *(struct indices*)s;

    for(k=i.init_col ; k<=i.fin_col; k++){
        for(j=i.init_row ; j<=i.fin_row; j++){
            comprobador[sudoku_array[j][k]-1] = 1;
            //printf("VERIFICANDO: %d\n", sudoku_array[j][k]);
        }
        if(memcmp(comprobador, correcto, size) == 0) {
          cols_checked[k] = 1;
          //printf("Columna %d está correcta\n",k);
        }
        else {
          printf("Columna %d está INCORRECTA\n",k);
        }
        memset (comprobador, 0, size);
    }
    pthread_exit(0);
}

//void* validity_check_s (void*s){
//    int comprobador[9] = {0,0,0,0,0,0,0,0,0};
//    int j,k;
//
//    for(j=i.init_row ; j<=i.fin_row; j++){
//        for(k=i.init_col ; k<=i.fin_col; k++){
//            comprobador[sudoku_array[j][k]-1] = 1;
//            printf("verificando: %d\n", sudoku_array[j][k]);
//        }
//    }
//    pthread_exit(0);
//}