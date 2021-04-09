#include "optimization.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>


double backtracking(double L, const double eta, const double (* function)(const double*), double* const (* nabla_function)(const double*), const double* x, const int x_elements);


/*
勾配法
第一引数：収束条件値(勾配の最大要素)，第二引数：ステップサイズ，第三引数：目的関数(実質なくてもよい)，
第四引数：勾配関数，第五引数：初期解，第六引数：解ベクトルの要素数
返り値：0
*/
int gradient(const double epsilon, const double stepsize, const double (* function)(const double*), double* const (* nabla_function)(const double*), const double* x_first, const int x_elements){

    double *x = malloc(sizeof(double)*x_elements);
    double *nabla;

    // 初期解の代入
    copy_vector_double(x, x_first, x_elements);


    // 反復回数
    int k = 0;

    while(1){

        // 勾配の計算
        nabla = nabla_function(x);

        // 勾配を確認したいときは on に
        // printf_vector_double(nabla, x_elements);
        // printf("max = %f\nmin = %f\n", max_vector_double(nabla, x_elements), min_vector_double(nabla, x_elements));

        // 収束判定
        if(max_vector_double(nabla, x_elements) < epsilon && min_vector_double(nabla, x_elements) > -epsilon){
            break;
        }

        k++;

        // 解の更新
        k_times_double(nabla, -stepsize, x_elements);
        sum_b_to_a_double(x, nabla, x_elements);

        free(nabla);

        
        // 現在の解を書き出ししたいときは on 
        // printf_vector_double(x, x_elements);
            
        // 目的関数値を計算したいときは on 
        // printf("objective = %f", function(x));

    }

    printf_vector_double(x, x_elements);
    printf("iteration = %d\n", k);
    
    free(nabla);
    free(x);

    return 0;

}


/*
Momentum法
第一引数：収束条件値(勾配の最大要素)，第二引数：勾配のステップサイズ，第三引数：慣性のステップサイズ，
第四引数：目的関数(実質なくてもよい)，第五引数：勾配関数，第六引数：初期解，第七引数：解ベクトルの要素数
返り値；0
*/
int momentum(const double epsilon, const double stepsize, const double inertial, const double (* function)(const double*), double* const (* nabla_function)(const double*), const double* x_first, const int x_elements){

    double *x = malloc(sizeof(double)*x_elements);
    double *x_delta = malloc(sizeof(double)*x_elements);
    double *nabla;

    // 初期解の代入
    copy_vector_double(x, x_first, x_elements);
    zeros_vector_double(x_delta, x_elements);

    // 反復回数
    int k = 0;


    while(1){

        //勾配の計算
        nabla = nabla_function(x);


        // 勾配を確認したいときは on に
        // printf_vector_double(nabla, x_elements);
        // printf("max = %f\nmin = %f\n", max_vector_double(nabla, x_elements), min_vector_double(nabla, x_elements));

        // 収束判定
        if(max_vector_double(nabla, x_elements) < epsilon && min_vector_double(nabla, x_elements) > -epsilon){
            break;
        }

        k++;
        
        // 慣性方向の移動
        k_times_double(x_delta, inertial, x_elements);
        sum_b_to_a_double(x, x_delta, x_elements);

        // 勾配方向の移動
        k_times_double(nabla, -stepsize, x_elements);
        sum_b_to_a_double(x, nabla, x_elements);

        // このループでの移動の大きさを更新
        sum_b_to_a_double(x_delta, nabla, x_elements);

        free(nabla);

        // 現在の解を書き出ししたいときは on 
        // printf_vector_double(x, x_elements);
            
        // 目的関数値を計算したいときは on 
        // printf("objective = %f", function(x));

    }

    printf_vector_double(x, x_elements);
    printf("iteration = %d\n", k);
    
    free(nabla);
    free(x_delta);
    free(x);

    return 0;

}


/*
Nesterov の加速勾配法
第一引数；収束判定値(勾配の最大要素)，第二引数：勾配のステップサイズ，第三引数：目的関数(実質なくてもよい)，
第四引数：勾配関数，第五引数：初期解，第六引数：解ベクトルの要素数
返り値：0
*/
int accelerate_gradient(const double epsilon, const double stepsize, const double (* function)(const double*), double* const (* nabla_function)(const double*), const double* x_first, const int x_elements){

    // 暫定解等の領域確保
    double *x = malloc(sizeof(double)*x_elements);
    double *x_delta = malloc(sizeof(double)*x_elements);
    double *x_nabla;

    // 慣性方向のみ移動した解の領域確保
    double *y = malloc(sizeof(double)*x_elements);
    double *y_nabla = malloc(sizeof(double));
    // 慣性方向のステップサイズを決定する変数
    double rho_0 = 0;
    double rho_1 = 0;
    double gamma = 0;

    // 初期解の代入
    copy_vector_double(x, x_first, x_elements);
    copy_vector_double(y, x_first, x_elements);
    zeros_vector_double(x_delta, x_elements);

    // 反復回数
    int k = 0;


    while(1){

        //勾配の計算
        x_nabla = nabla_function(x);


        // 勾配を確認したいときは on に
        // printf_vector_double(x_nabla, x_elements);
        // printf("max = %f\nmin = %f\n", max_vector_double(x_nabla, x_elements), min_vector_double(x_nabla, x_elements));

        // 収束判定
        if(max_vector_double(x_nabla, x_elements) < epsilon && min_vector_double(x_nabla, x_elements) > -epsilon){
            break;
        }


        free(x_nabla);

        k++;

        // 慣性方向の更新のための要素を作成
        free(y_nabla);
        y_nabla = nabla_function(y);
        k_times_double(y_nabla, -stepsize, x_elements);


        // 暫定解の更新
        copy_vector_double(x, y, x_elements);
        sum_b_to_a_double(x_delta, y_nabla, x_elements);
        sum_b_to_a_double(x, y_nabla, x_elements);

        rho_0 = rho_1;
        rho_1 = (1 + sqrt(1 + 4*rho_0*rho_0))/2.0;
        gamma = (rho_0 - 1)/rho_1;

        // 次ステップ用の暫定解の慣性方向への更新
        k_times_double(x_delta, gamma, x_elements);
        copy_vector_double(y, x, x_elements);
        sum_b_to_a_double(y, x_delta, x_elements);
        


        // 暫定解を書き出ししたいときは on 
        // printf_vector_double(x, x_elements);
            
        // 目的関数値を計算したいときは on 
        // printf("objective = %f", function(x));

    }

    printf_vector_double(x, x_elements);
    printf("iteration = %d\n", k);
    
    free(x_nabla);
    free(y_nabla);
    free(x_delta);
    free(x);
    free(y);

    return 0;

}



/*
近接勾配法(with backtracking)
第一引数：収束判定値(勾配の最大要素)，第二引数：リプシッツ定数更新用の定数(1.0より大きい)，第三引数：初期リプシッツ定数(ステップサイズの逆数，0.0より大きい)，
第四引数：目的関数，第五引数：勾配関数，第六引数：初期解，第七引数：解ベクトルの要素数
返り値：0
*/
int proximal_gradient(const double epsilon, const double eta, double L, const double (* function)(const double*), double* const (* nabla_function)(const double*), const double* x_first, const int x_elements){

    // 暫定解等の領域確保
    double *x = malloc(sizeof(double)*x_elements);
    double *nabla;

    // 初期解の代入
    copy_vector_double(x, x_first, x_elements);

    // iota(ステップサイズを決定する変数)の保管場所
    double iota;

    // 反復回数
    int k = 0;


    while(1){

        //勾配の計算
        nabla = nabla_function(x);


        // 勾配を確認したいときは on に
        // printf_vector_double(nabla, x_elements);
        // printf("max = %f\nmin = %f\n", max_vector_double(nabla, x_elements), min_vector_double(nabla, x_elements));

        // 収束判定
        if(max_vector_double(nabla, x_elements) < epsilon && min_vector_double(nabla, x_elements) > -epsilon){
            break;
        }
        
        k++;

        // backtracking によるリプシッツ定数の取得
        iota = backtracking(L, eta, function, nabla_function, x, x_elements);
        L = pow(eta, iota)*L;

        // リプシッツ定数(ステップサイズの逆数)の確認
        // printf("Lipsitz = %f\n", L);

        // 暫定解の更新
        k_times_double(nabla, -1/L, x_elements);
        sum_b_to_a_double(x, nabla, x_elements);

        free(nabla);


        // 暫定解を書き出ししたいときは on 
        // printf_vector_double(x, x_elements);
            
        // 目的関数値を計算したいときは on 
        // printf("objective = %f", function(x));

    }

    printf_vector_double(x, x_elements);
    printf("iteration = %d\n", k);
    
    free(nabla);
    free(x);

    return 0;
}



/*
FISTA
第一引数：収束判定値(勾配の最大要素)，第二引数：リプシッツ定数更新用の定数(1.0より大きい)，第三引数：初期リプシッツ定数(ステップサイズの逆数，0.0より大きい)，
第四引数：目的関数，第五引数：勾配関数，第六引数：初期解，第七引数：解ベクトルの要素数
返り値：0
*/
int FISTA(const double epsilon, const double eta, double L, const double (* function)(const double*), double* const (* nabla_function)(const double*), const double* x_first, const int x_elements){

    // 暫定解等の領域確保
    double *x = malloc(sizeof(double)*x_elements);
    double *y = malloc(sizeof(double)*x_elements);
    double *delta_x = malloc(sizeof(double)*x_elements);
    double *x_nabla;
    double *y_nabla = malloc(sizeof(double)*x_elements);


    // 初期解の代入
    copy_vector_double(x, x_first, x_elements);
    copy_vector_double(y, x_first, x_elements);
    zeros_vector_double(delta_x, x_elements);


    // iota(勾配方向のステップサイズを決定する変数)の保管場所
    double iota;

    // 慣性方向のステップサイズを決定するための変数の置き場所
    double t_0 = 1.0;
    double t_1 = (1.0 + sqrt(1.0 + 4.0*t_0*t_0))/2.0;

    // 反復回数
    int k = 0;


    while(1){


        // 勾配の計算
        x_nabla = nabla_function(x);

        // 勾配を確認したいときは on に
        // printf_vector_double(x_nabla, x_elements);
        // printf("max = %f\nmin = %f\n", max_vector_double(x_nabla, x_elements), min_vector_double(x_nabla, x_elements));

        // 収束判定
        if(max_vector_double(x_nabla, x_elements) < epsilon && min_vector_double(x_nabla, x_elements) > -epsilon){
            break;
        }


        k++;


        // backtracking によるリプシッツ定数の取得
        iota = backtracking(L, eta, function, nabla_function, y, x_elements);
        L = pow(eta, iota)*L;
        

        // リプシッツ定数(ステップサイズの逆数)の確認
        // printf("Lipsitz = %f\n", L);



        // 暫定解の更新
        free(y_nabla);
        y_nabla = nabla_function(y);
        k_times_double(y_nabla, -1/L, x_elements);
        copy_vector_double(x, y, x_elements);
        sum_b_to_a_double(x, y_nabla, x_elements);
        sum_b_to_a_double(delta_x, y_nabla, x_elements);

        // 暫定解の書き出し
        // printf_vector_double(x, x_elements);
        

        // 次ステップのための慣性方向の移動
        t_0 = t_1;
        t_1 = (1.0 + sqrt(1.0 + 4.0*t_0*t_0))/2.0;
        k_times_double(delta_x, (t_0-1)/t_1, x_elements);
        copy_vector_double(y, x, x_elements);
        sum_b_to_a_double(y, delta_x, x_elements);

        // 慣性方向のみ移動した解の書き出し
        // printf_vector_double(y, x_elements);

        // 慣性方向のステップサイズ
        // printf("stepsize of momentum = %f\n", (t_0 - 1)/t_1);

        free(x_nabla);


        // 暫定解を書き出ししたいときは on 
        // printf_vector_double(x, x_elements);
            
        // 目的関数値を計算したいときは on 
        // printf("objective = %f\n", function(x));

    }

    printf_vector_double(x, x_elements);
    printf("iteration = %d\n", k);
    
    free(x_nabla);
    free(y_nabla);
    free(x);
    free(y);

    return 0;
}



/*
FISTA with リスタート
第一引数：収束判定値(勾配の最大要素)，第二引数：リプシッツ定数更新用の定数(1.0より大きい)，第三引数：初期リプシッツ定数(ステップサイズの逆数，0.0より大きい)，
第四引数：目的関数，第五引数：勾配関数，第六引数：初期解，第七引数：解ベクトルの要素数
返り値：0
*/
int FISTA_with_restart(const double epsilon, const double eta, double L, const double (* function)(const double*), double* const (* nabla_function)(const double*), const double* x_first, const int x_elements){

    // 暫定解等の領域確保
    double *x = malloc(sizeof(double)*x_elements);
    double *y = malloc(sizeof(double)*x_elements);
    double *delta_x = malloc(sizeof(double)*x_elements);
    double *x_nabla;
    double *y_nabla = malloc(sizeof(double)*x_elements);


    // 初期解の代入
    copy_vector_double(x, x_first, x_elements);
    copy_vector_double(y, x_first, x_elements);
    zeros_vector_double(delta_x, x_elements);


    // iota(勾配方向のステップサイズを決定する変数)の保管場所
    double iota;

    // 慣性方向のステップサイズを決定するための変数の置き場所
    double t_0 = 1.0;
    double t_1 = 1.0;

    // 反復回数
    int k = 0;


    while(1){


        // backtracking によるリプシッツ定数の取得
        iota = backtracking(L, eta, function, nabla_function, y, x_elements);
        L = pow(eta, iota)*L;
        

        // リプシッツ定数(ステップサイズの逆数)の確認
        // printf("Lipsitz = %f\n", L);



        // 暫定解の更新
        free(y_nabla);
        y_nabla = nabla_function(y);
        k_times_double(y_nabla, -1/L, x_elements);
        copy_vector_double(x, y, x_elements);
        sum_b_to_a_double(x, y_nabla, x_elements);
        sum_b_to_a_double(delta_x, y_nabla, x_elements);
        
        k++;

        // 勾配の計算
        x_nabla = nabla_function(x);

        // 勾配を確認したいときは on に
        // printf_vector_double(x_nabla, x_elements);
        // printf("max = %f\nmin = %f\n", max_vector_double(x_nabla, x_elements), min_vector_double(x_nabla, x_elements));

        // 収束判定
        if(max_vector_double(x_nabla, x_elements) < epsilon && min_vector_double(x_nabla, x_elements) > -epsilon){
            break;
        }


        // 次ステップのための慣性方向の移動
        if(inner_product(x_nabla, delta_x, x_elements) > 0.0){
            t_1 = 1.0;
        }
        t_0 = t_1;
        t_1 = (1.0 + sqrt(1.0 + 4.0*t_0*t_0))/2.0;
        k_times_double(delta_x, (t_0-1)/t_1, x_elements);
        copy_vector_double(y, x, x_elements);
        sum_b_to_a_double(y, delta_x, x_elements);

        free(x_nabla);


        // 暫定解を書き出ししたいときは on 
        // printf_vector_double(x, x_elements);
            
        // 目的関数値を計算したいときは on 
        // printf("objective = %f", function(x));

    }

    printf_vector_double(x, x_elements);
    printf("iteration = %d\n", k);
    
    free(x_nabla);
    free(y_nabla);
    free(x);
    free(y);

    return 0;
}















/*
backtracking (AlgorithmファイルのFISTAのアルゴリズムを参照)
第一引数：現在のリプシッツ定数，第二引数：リプシッツ定数更新用の定数，
第三引数：目的関数，第四引数：勾配関数，第五引数：利用する暫定解，第六引数：解ベクトルの要素数
返り値：iota(本来は自然数だが，便宜上double型で返す)
*/
double backtracking(const double L, const double eta, const double (* function)(const double*), double* const (* nabla_function)(const double*), const double* x, const int x_elements){

    double F,Q;

    double iota = 0.0;
    double* y = malloc(sizeof(double)*x_elements);

    double obj = function(x);
    double* nabla = nabla_function(x);
    double nolm = nolm_2(nabla, x_elements);

    // 確認用
    // printf_vector_double(nabla, x_elements);
    // printf("obj = %f\nnolm = %f\n", obj, nolm);

    while(1){

        Q = obj - nolm/(2 * pow(eta, iota) * L);

        // Fの移動先のベクトルを取得
        copy_vector_double(y, nabla, x_elements);
        k_times_double(y, -1.0/(pow(eta, iota)*L), x_elements);
        sum_b_to_a_double(y, x, x_elements);

        F = function(y);

        if(F <= Q){
            break;
        }

        iota += 1.0;

    }    

    // printf("F = %f\nQ = %f\n", F, Q);
    
    free(nabla);
    free(y);

    return iota;

}