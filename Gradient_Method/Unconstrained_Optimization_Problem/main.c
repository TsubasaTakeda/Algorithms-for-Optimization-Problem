#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "matrix.h"
#include "optimization.h"


/*---------------------------------------------------
いじるところはここから
(使いたい目的関数と勾配関数を作成)
---------------------------------------------------*/


// 目的関数のポインタを作成
double function_1(const double* x){

    double obj = 0.0;

    for(int i=0; i<10; i++){
        // obj += x[i]*x[i];
        obj += x[i]*x[i] + x[i] + exp(x[i]);
    }

    return obj;

}

// 勾配関数のポインタを作成
double* function_nabla_1(const double* x){

    double* nabla = malloc(sizeof(double)*10);

    zeros_vector_double(nabla, 10);

    for(int i=0; i<10; i++){
        // nabla[i] = 2*x[i];
        nabla[i] = 2*x[i] + 1 + exp(x[i]);
    }


    return nabla;

}


/*---------------------------------------------------
ここまでと
---------------------------------------------------*/



void main(){

    double (* function)(const double*);
    double* (* nabla_function)(const double*);

    function = function_1;
    nabla_function = function_nabla_1;

    double *x = malloc(sizeof(double)*10);

    for(int i = 0; i < 10; i++){
        x[i] = 0.1*i;
    }

    /*---------------------------------------------------
    ここから，必要なもの以外をコメントアウト
    (各種パラメータは自分でいじってね)
    ---------------------------------------------------*/

        printf("\n\n");
        printf("Gradient Method:\n");
        gradient(0.00005, 0.1, function, nabla_function, x, 10);
        printf("\n\n");

        // printf("Momentum Method:\n");
        // momentum(0.00005, 0.1, 0.3, function, nabla_function, x, 10);
        // printf("\n\n");

        // printf("Nesterov's Accelerate Gradient Method:\n");
        // accelerate_gradient(0.00005, 0.1, function, nabla_function, x, 10);
        // printf("\n\n");

        // printf("Proximal Gradient Method:\n");
        // proximal_gradient(0.00005, 1.1, 0.01, function, nabla_function, x, 10);
        // printf("\n\n");

        // printf("FISTA:\n");
        // FISTA(0.00005, 1.1, 0.01, function, nabla_function, x, 10);
        // printf("\n\n");

        // printf("FISTA with restart:\n");
        // FISTA_with_restart(0.00005, 1.1, 0.01, function, nabla_function, x, 10);
        // printf("\n\n");

    /*---------------------------------------------------
    ここまで
    ---------------------------------------------------*/



    // csvファイルの double型数値 を読み取る関数
    // 便利だからぜひ使ってね

    char *filename;
    filename = "matrix.csv";
    double** matrix;
    int num_row;
    int num_col;

    read_matrix_csv(filename, &matrix, &num_row, &num_col);

    printf_matrix_double(matrix, num_row, num_col);

    free(matrix);

}