/*
 * value.h
 *
 *  Created on: Apr 3, 2014
 *      Author: dejan
 */

#pragma once

#include "poly.h"

#include "integer.h"
#include "rational.h"
#include "dyadic_rational.h"
#include "algebraic_number.h"

#include <stdio.h>

/** Types of values for the assignment */
typedef enum {
  LP_VALUE_NONE,
  LP_VALUE_INTEGER,
  LP_VALUE_DYADIC_RATIONAL,
  LP_VALUE_RATIONAL,
  LP_VALUE_ALGEBRAIC
} lp_value_type_t;

/** A value is a choice of the available types */
typedef union {
  lp_integer_t z;
  lp_rational_t q;
  lp_dyadic_rational_t dy_q;
  lp_algebraic_number_t a;
} lp_value_union_t;

/** A value is a tagged union of available type */
struct lp_value_struct {
  lp_value_type_t type;
  lp_value_union_t value;
};

/** Construct a value */
void lp_value_construct(lp_value_t* v, lp_value_type_t type, const void* data);

/** Construct a copy of the given value */
void lp_value_construct_copy(lp_value_t* v, const lp_value_t* from);

/** Destruct the value */
void lp_value_destruct(lp_value_t* v);

/** Get the approximate value */
void lp_value_approximate(const lp_value_t* v, lp_interval_t* approx);

/** Compare two values. */
int lp_value_cmp(const lp_value_t* v1, const lp_value_t* v2);

/** Void version of the comparison, use with care. */
int lp_value_cmp_void(const void* v1, const void* v2);

/** Print the value */
int lp_value_print(const lp_value_t* v, FILE* out);