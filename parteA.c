//! ELO321 - Teoría de Sistemas Operativos, 2020-2
/*!
* @file   : parteA.c 
* @author : Julio Contreras Fuica
* @author : Cristian González Bustos
* @date   : 10/12/2020
* @brief  : Parte A de la Tarea 2.
*/

//#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <fcntl.h>
//#include <sys/shm.h>
//#include <sys/stat.h>
//#include <sys/mman.h>
#include <sys/types.h>
//#include <sys/wait.h>
//#include <unistd.h>
//#include <math.h>
#include <stdint.h>


/*! \fn validity_check ()
    \brief Verifica filas, columnas o subcuadrículas del Sudoku
    \param 
*/
int validity_check();

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

struct indices {
            int init_row;  // fila inicial
            int fin_row;   // fila final
            int init_col;  // columna inicial
            int fin_col;   // columna final
};



int main(){
    struct indices i;
    i.init_row = 1;
    i.fin_row = 1;
    i.init_col = 0;
    i.fin_col = 8;
    
    if(validity_check(i)){
        printf("Validación exitosa\n");
    } else {
        printf("Validación fallida\n");
    }
    return 0;
}


int validity_check(struct indices i){
    uint16_t comprobador = 0;
    int j,k;

    for(j=i.init_row ; j++ ; j<i.fin_row){
        for(k=i.init_col ; k++ ; k<i.fin_col){
            comprobador |= 1<<sudoku_array[j][k];
            printf("verificando: %d\n", sudoku_array[j][k]);
            printf("comprobador: %x\n", comprobador);
        }
    }

    if(comprobador == 0b0111111111){
        return 1;
    } else {
        return 0;
    }
}