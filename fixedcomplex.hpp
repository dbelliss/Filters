/*
 * FixedComplex.h
 *
 *  Created on: Jun 24, 2016
 *      Author: ubuntu
 */

#ifndef FixedComplex_H_
#define FixedComplex_H_


#include <complex>
#include <types/fixedpoint.hpp>

template <size_t N, size_t M>
using FixedComplex2 = std::complex <FixedPoint <N, M> >;

typedef FixedComplex2<16, 1> FixedComplex16;
typedef FixedComplex2<32, 17> FixedComplex32;
typedef FixedComplex2<64, 49> FixedComplex64;

typedef std::complex<sc_fix> FixedComplex;

#endif /* FixedComplex_H_ */
