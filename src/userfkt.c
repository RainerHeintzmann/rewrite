/*
 * userfkt.c V1.00
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
#include "userfkt.h"
#include "exact.h"		/* 2026: integer, rational */
#include "specfun.h"		/* 2026: special functions */

typedef struct {
char * name;
u_function * function;
} t_funct;

#define FKT(x) {#x,(u_function *) &(x)}

t_funct (userfunction [])  = {
#define X(n) FKT(n),
	SPECFUN_LIST
#undef X
	FKT(show_int),
	FKT(cmp_int),
	FKT(cpy_int),
	FKT(del_int),
	FKT(read_int),
	FKT(int_plus),
	FKT(int_minus),
	FKT(int_mult),
	FKT(int_neg),
	FKT(int_abs),
	FKT(int_factorial),
	FKT(int_mod),
	FKT(int_quot),
	FKT(int_gcd),
	FKT(int_div),
	FKT(int_gt),
	FKT(int_ge),
	FKT(int_lt),
	FKT(int_le),
	FKT(int_eq),
	FKT(int_ne),
	FKT(show_rat),
	FKT(cmp_rat),
	FKT(cpy_rat),
	FKT(del_rat),
	FKT(int2rat),
	FKT(rat2real),
	FKT(rat_plus),
	FKT(rat_minus),
	FKT(rat_mult),
	FKT(rat_div),
	FKT(rat_neg),
	FKT(rat_abs),
	FKT(rat_mi),
	FKT(rat_pow),
	FKT(rat_qpow),
	FKT(nat_qpow),
	FKT(int_pow),
	FKT(int2int),
	FKT(int2real),
	FKT(real2real),
	FKT(nat_pow),
	FKT(rat_num),
	FKT(rat_den),
	FKT(rat_is_int),
	FKT(rat_gt),
	FKT(rat_ge),
	FKT(rat_lt),
	FKT(rat_le),
	FKT(rat_eq),
	FKT(rat_ne),
	FKT(show_real),
	FKT(cmp_real),	
	FKT(cpy_real),	
	FKT(del_real),	
	FKT(show_bool),
	FKT(cmp_bool),
	FKT(greater_than),			
	FKT(greater_equal),			
	FKT(lower_than),			
	FKT(lower_equal),			
	FKT(equal),			
	FKT(not_equal),			
	FKT(and),			
	FKT(or),			
	FKT(not),			
	FKT(is_int),			
	FKT(plus),			
	FKT(minus),			
	FKT(mult),				
	FKT(divide),		
	FKT(ai),				
	FKT(mi),				
	FKT(r_exp),
	FKT(power),			
	FKT(r_ln),
	FKT(wurzel),
	FKT(r_sin),
	FKT(r_cos),		
	FKT(r_tan),
	FKT(r_sinh),
	FKT(r_cosh),		
	FKT(r_tanh),
	FKT(r_arcsin),
	FKT(r_arccos),
	FKT(r_arctan),
	FKT(factorial),
	FKT(bessel),
	FKT(integer),
	FKT(r_sqr),
	FKT(r_sqrt),
	FKT(r_abs),
	FKT(signum),
	FKT(show_complex),
	FKT(cmp_complex),	
	FKT(cpy_complex),	
	FKT(del_complex),	
	FKT(real2cpx),		/* 2026: SUBSORT real,complex */
	FKT(cpx2num),		/* 2026: SUBSORT complex,number */
	FKT(cpx),					
	FKT(c_plus),			
	FKT(c_plus_r),		
	FKT(r_plus_c),		
	FKT(c_minus),			
	FKT(c_minus_r),		
	FKT(r_minus_c),		
	FKT(c_mult),				
	FKT(c_mult_r),			
	FKT(r_mult_c),			
	FKT(c_divide),		
	FKT(c_divide_r),	
	FKT(r_divide_c),	
	FKT(c_ai),				
	FKT(c_mi),				
	FKT(c_exp),			

	FKT(c_ln),
	FKT(c_sin),			
	FKT(c_cos),		
	FKT(c_tan),		
	FKT(c_power),      
	FKT(c_power_r),
	FKT(r_power_c),
	FKT(c_real),
	FKT(c_imag),
	FKT(c_abs),
	FKT(c_asqr),
/* FKT(c_wurzel),
	FKT(c_asinus),
	FKT(c_acosinus),
	FKT(c_atangens), */

	FKT(show_mat),		
	FKT(cmp_mat),
	FKT(cpy_mat),
	FKT(del_mat),
	FKT(elem_mat),
	FKT(zero_mat),
	FKT(one_mat),
	FKT(ch_mat),
	FKT(mat_add),
	FKT(real_mul_mat),
	FKT(mat_mul_real),
	FKT(mat_mul),
	FKT(mat_trans),
	FKT(mat_mul_vec),

	FKT(show_vec),
	FKT(cmp_vec),
	FKT(cpy_vec),
	FKT(del_vec),
	FKT(elem_vec),
	FKT(vec_part),
	FKT(zero_vec),
	FKT(one_vec),
	FKT(ch_vec),
	FKT(constr_vec),
	FKT(vec_add),
	FKT(vec_min_vec),
	FKT(real_mul_vec),
	FKT(vec_mul_real),
	FKT(vec_div_real),
	FKT(vec_x_vec),
	FKT(vec_mul),
	FKT(minus_vec),
	FKT(vec_sqr),
	FKT(vec_abs),
	FKT(vec_middle),
	FKT(vec_ms),
	FKT(vec_rms),
	FKT(vec_write),
	FKT(sin_vec),
	FKT(sinh_vec),
	FKT(asin_vec),
	FKT(cos_vec),
	FKT(cosh_vec),
	FKT(acos_vec),
	FKT(tan_vec),
	FKT(tanh_vec),
	FKT(atan_vec),
	FKT(log_vec),
	FKT(exp_vec),
	FKT(factorial_vec),
	FKT(sqr_vec),
	FKT(sqrt_vec),
	FKT(abs_vec),
	FKT(gen_vec),
	FKT(eplus1_vec),
	FKT(eplus2_vec),
	FKT(emin1_vec),
	FKT(emin2_vec),
	FKT(epow_vec),
	FKT(emul_vec),
	FKT(ediv_vec),
	FKT(plttest),
	FKT(r_csc), FKT(r_sec), FKT(r_cot), FKT(r_arccot),
	FKT(r_coth), FKT(r_sech), FKT(r_csch),
	FKT(r_arcsinh), FKT(r_arccosh), FKT(r_arctanh), FKT(r_arccoth),
	FKT(r_polylog), FKT(r_productlog), FKT(r_arctan2)
	} ;

int LASTFUNC = sizeof(userfunction)/sizeof(userfunction[0]);

u_function * give_ufkt (char * name)
{	int i;
	for (i=0;i<LASTFUNC;i++)
	{
     if (strcmp(name,userfunction[i].name)==0)
     	 return userfunction[i].function;
  }
	printfErr(" --ERROR ATT : C-Function %s not Implemented \n",name);
	return NULL;
}

/* 2026: like give_ufkt, but without an error message (NULL if unknown) */
u_function * give_ufkt_quiet (char * name)
{	int i;
	for (i=0;i<LASTFUNC;i++)
		if (strcmp(name,userfunction[i].name)==0)
			return userfunction[i].function;
	return NULL;
}
