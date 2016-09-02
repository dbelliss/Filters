/*
 * cic.h
 *
 *  Created on: Jul 7, 2016
 *      Author: ubuntu
 */

#ifndef CIC_H_
#define CIC_H_

#include <vector>

#include <core/filter_chain_element.hpp>
#include <types/fixedcomplex.hpp>
/*
 *
 * Block diagram: http://www.ni.com/cms/images/devzone/ph/image3222866864835185780.jpg
 */
class fixedcic : public FilterChainElement
{
public:

    bool input(const filter_io_t &data) override;
    bool output(filter_io_t &data) override;
    void tick() override;
    fixedcic(int R, int aregs, int bregs); //Constructor takes in decimation factor and number of regs on each side.
    void cic(FixedComplex16 &input); //actual filtering of data. Returns number of outputs
    FixedComplex16 integrate(FixedComplex16 current); //integrate side of filter (+)
    FixedComplex16 comb(FixedComplex16 current); //comb side of filter (-)
    bool downsample(); //returns false when the sample should be passed
    void reset();

    bool 							goodOutput; //indicates when output is ready
    int                         	m_r; //Decimation factor
    int                         	m_numBRegisters; //number of b registers
    int                         	m_numARegisters; //number of a registers
    int                   			m_samples; //How many samples have been processed
    std::vector<FixedComplex16> 	m_a; //a registers
    std::vector<FixedComplex16>  	m_b; //b registers
    FixedComplex16          		m_output;
};

#endif /* CIC_H_ */
