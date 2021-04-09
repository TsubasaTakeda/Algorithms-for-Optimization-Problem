#ifndef _OPTIMIZATION_H_
#define _OPTIMIZATION_H_


/*
勾配法
第一引数：収束条件値(勾配の最大要素)，第二引数：ステップサイズ，第三引数：目的関数(実質なくてもよい)，
第四引数：勾配関数，第五引数：初期解，第六引数：解ベクトルの要素数
返り値：0
*/
int gradient(const double epsilon, const double stepsize, const double (* function)(const double*), double* const (* nabla_function)(const double*), const double* x_first, const int x_elements);



/*
Momentum法
第一引数：収束条件値(勾配の最大要素)，第二引数：勾配のステップサイズ，第三引数：慣性のステップサイズ，
第四引数：目的関数(実質なくてもよい)，第五引数：勾配関数，第六引数：初期解，第七引数：解ベクトルの要素数
返り値：0
*/
int momentum(const double epsilon, const double stepsize, const double inertial, const double (* function)(const double*), double* const (* nabla_function)(const double*), const double* x_first, const int x_elements);



/*
Nesterov の加速勾配法
第一引数；収束判定値(勾配の最大要素)，第二引数：勾配のステップサイズ，第三引数：目的関数(実質なくてもよい)，
第四引数：勾配関数，第五引数：初期解，第六引数：解ベクトルの要素数
返り値：0
*/
int accelerate_gradient(const double epsilon, const double stepsize, const double (* function)(const double*), double* const (* nabla_function)(const double*), const double* x_first, const int x_elements);


/*
近接勾配法(with backtracking)
第一引数：収束判定値(勾配の最大要素)，第二引数：リプシッツ定数更新用の定数(1.0より大きい)，第三引数：初期リプシッツ定数(ステップサイズの逆数，1.0より大きい)，
第四引数：目的関数，第五引数：勾配関数，第六引数：初期解，第七引数：解ベクトルの要素数
返り値：0
*/
int proximal_gradient(const double epsilon, const double eta, double L, const double (* function)(const double*), double* const (* nabla_function)(const double*), const double* x_first, const int x_elements);


/*
FISTA
第一引数：収束判定値(勾配の最大要素)，第二引数：リプシッツ定数更新用の定数(1.0より大きい)，第三引数：初期リプシッツ定数(ステップサイズの逆数，0.0より大きい)，
第四引数：目的関数，第五引数：勾配関数，第六引数：初期解，第七引数：解ベクトルの要素数
返り値：0
*/
int FISTA(const double epsilon, const double eta, double L, const double (* function)(const double*), double* const (* nabla_function)(const double*), const double* x_first, const int x_elements);

/*
FISTA with リスタート
第一引数：収束判定値(勾配の最大要素)，第二引数：リプシッツ定数更新用の定数(1.0より大きい)，第三引数：初期リプシッツ定数(ステップサイズの逆数，0.0より大きい)，
第四引数：目的関数，第五引数：勾配関数，第六引数：初期解，第七引数：解ベクトルの要素数
返り値：0
*/
int FISTA_with_restart(const double epsilon, const double eta, double L, const double (* function)(const double*), double* const (* nabla_function)(const double*), const double* x_first, const int x_elements);


#endif // _OPTIMIZATION_H_