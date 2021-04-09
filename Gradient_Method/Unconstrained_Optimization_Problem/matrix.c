#include "matrix.h"
#include <stdio.h>
#include <float.h>
#include <stdlib.h>



// ベクトルのコピー -----------------------------------------------------------------------------------------


/* 
ベクトルのコピーを作成する関数
第一引数：コピー先，第二引数：コピー元，第三引数：ベクトルの要素数 
返り値：0
*/
int copy_vector_double(double* a, const double* b, const int num_elements){

    for(int i = 0; i < num_elements; i++){

        a[i] = b[i];

    }

    return 0;

}





// ベクトルの初期化 -----------------------------------------------------------------------------------------

/*
全要素が0.0のベクトルを作成
第一引数：作成先のポインタ，第二引数；ベクトル要素数
返り値：0
*/
int zeros_vector_double(double* a, const int num_elements){

    for(int i = 0; i < num_elements; i++){
        a[i] = 0.0;
    }

    return 0;

}


/*
全要素が1.0のベクトルを作成
第一引数：作成先のポインタ，第二引数；ベクトル要素数
返り値：0
*/
int ones_vector_double(double* a, const int num_elements){

    for(int i = 0; i < num_elements; i++){
        a[i] = 1.0;
    }

    return 0;

}

/*
0からの順番ベクトルを作成(インデックスと同じ値が入る)
第一引数：作成先のポインタ，第二引数：ベクトル要素数
返り値：0
*/
int index_vector_double(double* a, const int num_elements){
    
    for(int i = 0; i < num_elements; i++){
        a[i] = (double)i;
    }

    return 0;

}







// ベクトルの書き出し ----------------------------------------------------------------------------------------

/* 
ベクトルを書き出す関数 
第一引数：対象ベクトルのポインタ，第二引数：ベクトル要素数
返り値：0
*/
int printf_vector_double(const double* a, const int num_elements){

    
    printf("vector = \n ");

    for(int i = 0; i < num_elements; i++){

        printf("%f   ", a[i]);
    }

    printf("\n\n");

    return 0;

}

/*
行列を書き出す関数
第一引数：対象行列のポインタ，第二引数：ベクトル要素数
返り値：0
*/
int printf_matrix_double(double** a, const int num_row, const int num_col){

    printf("matrix = \n");

    for(int row = 0; row < num_row; row++){
        for(int col = 0; col < num_col; col++){

            printf("%f   ", a[row][col]);

        }
        printf("\n");
    }

    printf("\n");

    return 0;

}






// ベクトルの要素の抜き出し ----------------------------------------------------------------------------------

/*
ベクトルの最大要素の値を出す関数 
第一引数；対象ベクトルのポインタ，第二引数：ベクトル要素数
返り値：対象ベクトルの最大要素の値
*/
double max_vector_double(const double* a, const int num_elements){

    double max = -DBL_MAX;

    for(int i = 0; i < num_elements; i++){

        if(max < a[i]){
            max = a[i];
        }

    }

    return max;

}

/*
ベクトルの最小要素の値を出す関数 
第一引数；対象ベクトルのポインタ，第二引数：ベクトル要素数
返り値：対象ベクトルの最小要素の値
*/
double min_vector_double(const double* a, const int num_elements){

    double min = DBL_MAX;

    for(int i = 0; i < num_elements; i++){

        if(min > a[i]){
            min = a[i];
        }

    }

    return min;

}







// ベクトルの演算 --------------------------------------------------------------------------------------------------

/*
ベクトルaをベクトルbに足す関数 
第一引数；加えるベクトルのポインタ，第二引数：加えられるベクトルのポインタ，第三引数：ベクトル要素数
返り値：0
*/
int sum_b_to_a_double(double* a, const double* b, const int num_elements){

    for(int i = 0; i < num_elements; i++){

        a[i] += b[i];
    
    }

    return 0;

}

/*
ベクトルaをk倍する関数
第一引数；加えるベクトルのポインタ，第二引数：加えられるベクトルのポインタ，第三引数：ベクトル要素数
返り値：0
*/
int k_times_double(double* a, const double k, const int num_elements){

    for(int i = 0; i < num_elements; i++){
        a[i] = a[i]*k;
    }

    return 0;

}



// ノルムの計算------------------------------------------------------------------------------------------------------

/*
内積を計算する関数
第一引数：一つ目のベクトルのポインタ，第二引数：二つ目のベクトルのポインタ，第三引数：ベクトル要素数
返り値：内積
*/
double inner_product(const double* a, const double* b, const int num_elements){

    double inner_product = 0.0;

    for(int i = 0; i < num_elements; i++){
        inner_product += a[i]*b[i];
    }

    return inner_product;

}


/* 
第二ノルム(要素の二乗値の和)を計算する関数
第一引数；対象ベクトルのポインタ，第二引数：ベクトル要素数
返り値：0
*/
double nolm_2(const double* a, const int num_elements){

    double nolm = 0.0;

    for(int i = 0; i < num_elements; i++){
        nolm += a[i]*a[i];
    }

    return nolm;

}



// ファイル関連の関数 --------------------------------------------------------------------------------------------------


/*
csvファイルの行数と列数をカウントする関数
第一引数：ファイルポインタ，第二引数：行数，第三引数：列数
返り値：成功0，失敗1
*/
int csv_CountRowCol(const char *filename, int* const num_row, int* const num_col){

    int row, col;
    char chData;
    FILE *fp;

    *num_row = 0;
    *num_col = 0;

    fp = fopen(filename, "r");

    // ファイルの存在チェック
    if(fp == NULL){
        printf("cannot find the file!\n");
        return -1;
    }

    if(fgetc(fp) == EOF){ // ファイルの中身がない場合の処理

        printf("this file has no contents!\n");
        return -1;

    }
    fseek(fp, 0, SEEK_SET);

    row = 1;
    col = 1;

    while(fscanf(fp, "%c", &chData) != EOF){
        // カンマの場合
        if(chData == ','){
            col++;
        }
        // 改行コードの場合
        if(chData == '\n'){
            col++;
            row++;
        }
    }

    col = col/row;

    *num_row = row;
    *num_col = col;
    fclose(fp);


    return 0;

}


/*
csvファイルから2次元行列(double型)を読み取る関数
第一引数：ファイル名，第二引数：「行列を格納するポインタ」のポインタ，第三引数：行数ポインタ，第四引数：列数ポインタ
返り値：成功0，失敗-1
*/
int read_matrix_csv(const char *filename, double*** const matrix, int* const num_row, int* const num_col){

    char chData;

    // 行数と列数を読み取る
    if(csv_CountRowCol(filename, num_row, num_col)){
        return -1;
    }

    FILE *fp = fopen(filename, "r");

    // 領域確保
    matrix[0] = malloc(sizeof(double*)*(*num_row));
    for(int i = 0; i < *num_row; i++){
        matrix[0][i] = malloc(sizeof(double)*(*num_col));
    }

    for(int row_index=0; row_index < *num_row; row_index++){
        for(int col_index=0; col_index < *num_col; col_index++){

            char data[256];
            for(int i = 0; i < 256; i++){
                data[i]='\0';
            }
            int ch_counter = 0;

            while(fscanf(fp, "%c", &chData) != EOF){

                // 「,」または「\n」が来たらループを抜ける
                if((chData == ',') || (chData == '\n')){
                    break;
                } else {
                    data[ch_counter] = chData;
                    ch_counter++;
                }

            }


            data[ch_counter] = '\0';
            matrix[0][row_index][col_index] = atof(data);

        }
    }

    // printf_matrix_double(matrix[0], *num_row, *num_col);

    fclose(fp);
    return 0;

}