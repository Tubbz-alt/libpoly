/*
 * polynomial_internal.h
 *
 *  Created on: Mar 12, 2014
 *      Author: dejan
 */

#pragma once

#include "polynomial/polynomial.h"
#include "polynomial/coefficient.h"

typedef struct {

  /**
   * This bit is set for univariate polynomials. This property is invariant wrt
   * reordering.
   */

  unsigned univariate : 1;

  /**
   * This bit is set for primitive polynomials (gcd(coeff) = 1) and the lead
   * integer coefficient (lexicographically) is positive. This property is
   * not invariant with respect to reordering. For example y*x^2 + x is
   * primitive if x is the top variable and not primitive if y is the top
   * variable.
   */

  unsigned primitive  : 1;

  /**
   * This bit is set for known prime polynomials. This property is invariant
   * with respect to reordering.
   */

  unsigned prime      : 1;

  /**
   * This bit is if the polynomial is meant to be used externally. This means
   * that the context needs to be attached and that before every operations we
   * need to check if the variable order is correct.
   */
  unsigned external   : 1;

} polynomial_flags_t;

typedef struct polynomial_struct {
  /** The actual polynomial representation (so we can use it as a coefficient) */
  coefficient_t data;
  /** Flags as above */
  polynomial_flags_t flags;
  /** Context of the polynomial */
  const polynomial_context_t* ctx;
} polynomial_t;

void polynomial_construct(polynomial_t* A, const polynomial_context_t* ctx, int external);

void polynomial_construct_from_coefficient(polynomial_t* A, const polynomial_context_t* ctx, const coefficient_t* from, int external);

void polynomial_construct_copy(polynomial_t* A, const polynomial_t* from, int external);

void polynomial_construct_simple(polynomial_t* A, const polynomial_context_t* ctx, int external, const integer_t* c, variable_t x, unsigned n);

void polynomial_destruct(polynomial_t* A);

polynomial_t* polynomial_alloc(void);

polynomial_t* polynomial_new(const polynomial_context_t* ctx, int external);

void polynomial_swap(polynomial_t* A1, polynomial_t* A2);

void polynomial_assign(polynomial_t* A, const polynomial_t* from);

const polynomial_context_t* polynomial_context(const polynomial_t* A);

variable_t polynomial_top_variable(const polynomial_t* A);

size_t polynomial_degree(const polynomial_t* A);

void polynomial_get_coefficient(polynomial_t* C_p, const polynomial_t* A, size_t k);

int polynomial_is_constant(const polynomial_t* A);

int polynomial_is_zero(const polynomial_t* A);

int polynomial_sgn(const polynomial_t* A, const assignment_t* m);

int polynomial_cmp(const polynomial_t* A1, const polynomial_t* A2);

int polynomial_cmp_type(const polynomial_t* A1, const polynomial_t* A2);

int polynomial_divides(const polynomial_t* A1, const polynomial_t* A2);

int polynomial_print(const polynomial_t* A, FILE* out);

char* polynomial_to_string(const polynomial_t* A);

int polynomial_same_var_univariate(const polynomial_t* A1, const polynomial_t* A2);

void polynomial_add(polynomial_t* S, const polynomial_t* A1, const polynomial_t* A2);

void polynomial_sub(polynomial_t* S, const polynomial_t* A1, const polynomial_t* A2);

void polynomial_neg(polynomial_t* N, const polynomial_t* A);

void polynomial_mul(polynomial_t* P, const polynomial_t* A1, const polynomial_t* A2);

void polynomial_shl(polynomial_t* S, const polynomial_t* A, unsigned n);

void polynomial_pow(polynomial_t* P, const polynomial_t* A, unsigned n);

void polynomial_add_mul(polynomial_t* S, const polynomial_t* A1, const polynomial_t* A2);

void polynomial_sub_mul(polynomial_t* S, const polynomial_t* A1, const polynomial_t* A2);

void polynomial_div(polynomial_t* D, const polynomial_t* A1, const polynomial_t* A2);

void polynomial_rem(polynomial_t* R, const polynomial_t* A1, const polynomial_t* A2);

void polynomial_divrem(polynomial_t* D, polynomial_t* R, const polynomial_t* A1, const polynomial_t* A2);

void polynomial_derivative(polynomial_t* A_d, const polynomial_t* A);

void polynomial_gcd(polynomial_t* gcd, const polynomial_t* A1, const polynomial_t* A2);

void polynomial_lcm(polynomial_t* lcm, const polynomial_t* A1, const polynomial_t* A2);

void polynomial_resultant(polynomial_t* res, const polynomial_t* A, const polynomial_t* B);

void polynomial_psc(polynomial_t** psc, const polynomial_t* A, const polynomial_t* B);

void polynomial_reduce(const polynomial_t* A, const polynomial_t* B, polynomial_t* P, polynomial_t* Q, polynomial_t* R);