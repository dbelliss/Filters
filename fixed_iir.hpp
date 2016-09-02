/*
 * fixediir.h
 *
 *  Created on: Jun 28, 2016
 *      Author: ubuntu
 */

#ifndef FIXEDIIR_H_
#define FIXEDIIR_H_

#include <types/fixedcomplex.hpp>
#include <core/filter_chain_element.hpp>
/*
 * Note that a[0] will be converted to 1
 * Block diagram: https://www.music.mcgill.ca/~gary/307/week2/img15.gif
 */



class fixediir : public FilterChainElement
{
public:

    bool input(const filter_io_t &data) override;
       /**
        * output - provide an output sample to the caller.
        * @return false if no output sample is available.
        */
    bool output(filter_io_t &data) override;

    void tick() override;

    fixediir(std::vector<FixedComplex16> aCoeffs,
    		std::vector<FixedComplex16> bCoeffs); //Constructor
    void iir(FixedComplex16 &input); //Filtering input data
    void reset(); //resets registers
    FixedComplex16 calculate(FixedComplex16 current); // Calculate output based on input

    int       						m_numXRegisters;
    int 							m_numYRegisters;
    std::vector<FixedComplex16> 	m_a; //a coefficients
    std::vector<FixedComplex16>   	m_b; //b coefficients
    std::vector<FixedComplex16> 	m_x; //x registers
    std::vector<FixedComplex16>  	m_y; //y registers
    FixedComplex16          		m_output;

};

#endif /* FIXEDIIR_H_ */
