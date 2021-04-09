#ifndef _MATRIX_H_
#define _MATRIX_H_

// ベクトルのコピー -----------------------------------------------------------------------------------------

/* 第一引数：コピー先，第二引数：コピー元，第三引数：ベクトルの要素数 */
int copy_vector_double(double* a, const double* b, const int num_elements);




// ベクトルの初期化 -----------------------------------------------------------------------------------------

/* 第一引数：作成先のポインタ，第二引数；ベクトル要素数 */
int zeros_vector_double(double* a, const int num_elements);

/* 第一引数：作成先のポインタ，第二引数；ベクトル要素数 */
int ones_vector_double(double* a, const int num_elements);

/*
0からの順番ベクトルを作成(インデックスと同じ値が入る)
第一引数：作成先のポインタ，第二引数：ベクトル要素数
返り値：0
*/
int index_vector_double(double* a, const int num_elements);




// ベクトルの書き出し ----------------------------------------------------------------------------------------

/* 第一引数：書き出すベクトル，第二引数：ベクトル要素数 */
int printf_vector_double(const double* a, const int num_elements);

/*
行列を書き出す関数
第一引数：対象行列のポインタ，第二引数：ベクトル要素数
返り値：0
*/
int printf_matrix_double(double** a, const int num_row, const int num_col);




// ベクトルの要素の抜き出し ----------------------------------------------------------------------------------

/* 第一引数；対象ベクトルのポインタ，第二引数：ベクトル要素数 */
double max_vector_double(const double* a, const int num_elements);

/* 第一引数；対象ベクトルのポインタ，第二引数：ベクトル要素数 */
double min_vector_double(const double* a, const int num_elements);



// ベクトルの演算 --------------------------------------------------------------------------------------------------

/* 第一引数；加えられるベクトルのポインタ，第二引数：加えるベクトルのポインタ，第三引数：ベクトル要素数 */
int sum_b_to_a_double(double* a,const double* b, const int num_elements);

/* 第一引数；加えるベクトルのポインタ，第二引数：加えられるベクトルのポインタ，第三引数：ベクトル要素数 */
int k_times_double(double* a, const double k, const int num_elements);



// ノルムの計算 -------------------------------------------------------------------------------------------------------

/*
内積を計算する関数
第一引数：一つ目のベクトルのポインタ，第二引数：二つ目のベクトルのポインタ，第三引数：ベクトル要素数
返り値：内積
*/
double inner_product(const double* a, const double* b, const int num_elements);


/* 
第二ノルム(要素の二乗値の和)を計算する関数
第一引数；対象ベクトルのポインタ，第二引数：ベクトル要素数
返り値：0
*/
double nolm_2(const double* a, const int num_elements);


// ファイル関連 ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー

/*
csvファイルの行数と列数をカウントする関数
第一引数：ファイルポインタ，第二引数：行数，第三引数：列数
返り値：成功0，失敗1
*/
int csv_CountRowCol(const char *filename, int* const puiRow, int* const puiCol);

/*
csvファイルから2次元行列(double型)を読み取る関数
第一引数：ファイル名，第二引数：行列を格納するポインタ，第三引数：行数ポインタ，第四引数：列数ポインタ
返り値：成功0，失敗-1
*/
int read_matrix_csv(const char *filename, double*** const matrix, int* const num_row, int* const num_col);


#endif // _MATRIX_H_