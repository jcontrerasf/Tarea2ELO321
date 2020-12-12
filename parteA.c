//! ELO321 - Teoría de Sistemas Operativos, 2020-2
/*!
* @file   : parteA.c 
* @author : Julio Contreras Fuica
* @author : Cristian González Bustos
* @date   : 10/12/2020
* @brief  : Parte A de la Tarea 2.
*/

// Compilar con: gcc parteA.c -o parteA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdint.h>


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


/*! \fn validity_check (struct indices i)
    \brief Verifica que cada dígito (1-9) aparezca
    \      una sola vez entre los indices dados.
    \param i Estructura con indices mínimos y máximos.
    \retval 1 si la verificación es correcta, 0 si no.
*/
int validity_check(struct indices i);


int main(){
    struct indices i;
    int j,k;
    int sub = 0;
    int correcto[9] = {1,1,1,1,1,1,1,1,1};
    int size = sizeof(correcto);

    //Comprobar filas
    for (j=0; j<=8; j++){
        i.init_row = j;
        i.fin_row = j;
        i.init_col = 0;
        i.fin_col = 8;
        if(validity_check(i)){
            rows_checked[j] = 1;
            printf("Fila %d está correcta\n",j);
        } else {
            printf("Fila %d está incorrecta\n",j);
        }
    }

    //Comprobar columnas
    for (k=0; k<=8; k++){
        i.init_row = 0;
        i.fin_row = 8;
        i.init_col = k;
        i.fin_col = k;
        if(validity_check(i)){
            cols_checked[k] = 1;
            printf("Columna %d está correcta\n",k);
        } else {
            printf("Columna %d está incorrecta\n",k);
        }
    }

    //Comprobar subcuadrículas
    for(j=0 ; j<=2; j++){
        for(k=0 ; k<=2; k++){
            i.init_row = 3*j;
            i.fin_row = 3*j + 2;
            i.init_col = 3*k;
            i.fin_col = 3*k + 2;
            if(validity_check(i)){
                sub_grids_checked[sub] = 1;
                printf("Subcuadrícula %d,%d está correcta\n",j,k);
            } else {
                printf("Subcuadrícula %d,%d está incorrecta\n",j,k);
            }
            sub++;
        }
    }


    //Comprobación final
    if (memcmp(rows_checked, correcto, size) + memcmp(cols_checked, correcto, size) + memcmp(sub_grids_checked, correcto, size) == 0)
    {
        printf("Sudoku correcto\n");
    } else {
        printf("Sudoku incorrecto\n");
    }
    return 0;
}


int validity_check(struct indices i){
    uint16_t comprobador = 0;
    int j,k;
    int n = 0;

    for(j=i.init_row ; j<=i.fin_row; j++){
        for(k=i.init_col ; k<=i.fin_col; k++){
            comprobador |= 1<<sudoku_array[j][k];
            printf("verificando: %d\n", sudoku_array[j][k]);
            n++;
        }
    }

    if(comprobador == 0x3fe && n == 9){ //0x3fe = 0b0000001111111110 (1s en posiciones del 1 al 9)
        return 1;
    } else {
        return 0;
    }
}