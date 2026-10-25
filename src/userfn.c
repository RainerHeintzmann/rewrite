/*
 * userfn.c V1.00
 * Copyright (c) : Rainer Heintzmann
 *
 * User functions for 'rewrite'
 *
 */

#include <string.h>

#include "inout.h"
#include "real.h"
#include "bool.h"
#include "complex.h"
#include "vector.h"
#include "matrix.h"
#include "userfn.h"
#include "exact.h"		/* 2026: integer, rational */
#include "specfun.h"		/* 2026: special functions */

typedef struct {
char * name;
u_function * function;
} t_funct;

#define FN(x) {#x,(u_function *) &(x)}

t_funct (userfunction [])  = {
#define X(n) FN(n),
	SPECFUN_LIST
#undef X
	FN(show_int),
	FN(cmp_int),
	FN(cpy_int),
	FN(del_int),
	FN(read_int),
	FN(int_plus),
	FN(int_minus),
	FN(int_mult),
	FN(int_neg),
	FN(int_abs),
	FN(int_factorial),
	FN(int_mod),
	FN(int_quot),
	FN(int_gcd),
	FN(int_div),
	FN(int_gt),
	FN(int_ge),
	FN(int_lt),
	FN(int_le),
	FN(int_eq),
	FN(int_ne),
	FN(show_rat),
	FN(cmp_rat),
	FN(cpy_rat),
	FN(del_rat),
	FN(int2rat),
	FN(rat2real),
	FN(rat_plus),
	FN(rat_minus),
	FN(rat_mult),
	FN(rat_div),
	FN(rat_neg),
	FN(rat_abs),
	FN(rat_mi),
	FN(rat_pow),
	FN(rat_qpow),
	FN(nat_qpow),
	FN(int_pow),
	FN(int2int),
	FN(int2real),
	FN(real2real),
	FN(nat_pow),
	FN(rat_num),
	FN(rat_den),
	FN(rat_is_int),
	FN(rat_gt),
	FN(rat_ge),
	FN(rat_lt),
	FN(rat_le),
	FN(rat_eq),
	FN(rat_ne),
	FN(show_real),
	FN(cmp_real),	
	FN(cpy_real),	
	FN(del_real),	
	FN(show_bool),
	FN(cmp_bool),
	FN(greater_than),			
	FN(greater_equal),			
	FN(lower_than),			
	FN(lower_equal),			
	FN(equal),			
	FN(not_equal),			
	FN(and),			
	FN(or),			
	FN(not),			
	FN(is_int),			
	FN(plus),			
	FN(minus),			
	FN(mult),				
	FN(divide),		
	FN(ai),				
	FN(mi),				
	FN(r_exp),
	FN(power),			
	FN(r_ln),
	FN(sqrt_plain),
	FN(r_sin),
	FN(r_cos),		
	FN(r_tan),
	FN(r_sinh),
	FN(r_cosh),		
	FN(r_tanh),
	FN(r_arcsin),
	FN(r_arccos),
	FN(r_arctan),
	FN(factorial),
	FN(bessel),
	FN(integer),
	FN(r_sqr),
	FN(r_sqrt),
	FN(r_abs),
	FN(signum),
	FN(show_complex),
	FN(cmp_complex),	
	FN(cpy_complex),	
	FN(del_complex),	
	FN(real2cpx),		/* 2026: SUBSORT real,complex */
	FN(cpx2num),		/* 2026: SUBSORT complex,number */
	FN(cpx),					
	FN(c_plus),			
	FN(c_plus_r),		
	FN(r_plus_c),		
	FN(c_minus),			
	FN(c_minus_r),		
	FN(r_minus_c),		
	FN(c_mult),				
	FN(c_mult_r),			
	FN(r_mult_c),			
	FN(c_divide),		
	FN(c_divide_r),	
	FN(r_divide_c),	
	FN(c_ai),				
	FN(c_mi),				
	FN(c_exp),			

	FN(c_ln),
	FN(c_sin),			
	FN(c_cos),		
	FN(c_tan),		
	FN(c_power),      
	FN(c_power_r),
	FN(r_power_c),
	FN(c_real),
	FN(c_imag),
	FN(c_abs),
	FN(c_asqr),
/* FN(c_sqrt),
	FN(c_asinus),
	FN(c_acosinus),
	FN(c_atangens), */

	FN(show_mat),		
	FN(cmp_mat),
	FN(cpy_mat),
	FN(del_mat),
	FN(elem_mat),
	FN(zero_mat),
	FN(one_mat),
	FN(ch_mat),
	FN(mat_add),
	FN(real_mul_mat),
	FN(mat_mul_real),
	FN(mat_mul),
	FN(mat_trans),
	FN(mat_mul_vec),

	FN(show_vec),
	FN(cmp_vec),
	FN(cpy_vec),
	FN(del_vec),
	FN(elem_vec),
	FN(vec_part),
	FN(zero_vec),
	FN(one_vec),
	FN(ch_vec),
	FN(constr_vec),
	FN(vec_add),
	FN(vec_min_vec),
	FN(real_mul_vec),
	FN(vec_mul_real),
	FN(vec_div_real),
	FN(vec_x_vec),
	FN(vec_mul),
	FN(minus_vec),
	FN(vec_sqr),
	FN(vec_abs),
	FN(vec_middle),
	FN(vec_ms),
	FN(vec_rms),
	FN(vec_write),
	FN(sin_vec),
	FN(sinh_vec),
	FN(asin_vec),
	FN(cos_vec),
	FN(cosh_vec),
	FN(acos_vec),
	FN(tan_vec),
	FN(tanh_vec),
	FN(atan_vec),
	FN(log_vec),
	FN(exp_vec),
	FN(factorial_vec),
	FN(sqr_vec),
	FN(sqrt_vec),
	FN(abs_vec),
	FN(gen_vec),
	FN(eplus1_vec),
	FN(eplus2_vec),
	FN(emin1_vec),
	FN(emin2_vec),
	FN(epow_vec),
	FN(emul_vec),
	FN(ediv_vec),
	FN(plttest),
	FN(r_csc), FN(r_sec), FN(r_cot), FN(r_arccot),
	FN(r_coth), FN(r_sech), FN(r_csch),
	FN(r_arcsinh), FN(r_arccosh), FN(r_arctanh), FN(r_arccoth),
	FN(r_polylog), FN(r_productlog), FN(r_arctan2)
	} ;

int LASTFUNC = sizeof(userfunction)/sizeof(userfunction[0]);

u_function * give_ufn (char * name)
{	int i;
	for (i=0;i<LASTFUNC;i++)
	{
     if (strcmp(name,userfunction[i].name)==0)
     	 return userfunction[i].function;
  }
	printfErr(" --ERROR ATT : C-Function %s not Implemented \n",name);
	return NULL;
}

/* 2026: like give_ufn, but without an error message (NULL if unknown) */
u_function * give_ufn_quiet (char * name)
{	int i;
	for (i=0;i<LASTFUNC;i++)
		if (strcmp(name,userfunction[i].name)==0)
			return userfunction[i].function;
	return NULL;
}
