/*
 * fixediir.cpp
 *
 *  Created on: Jun 28, 2016
 *      Author: ubuntu
 */
/*
 *
 * NOTE: First a coefficient must be 1. If it is not, the algorithm will proceed as if it is 1 anyway
 * Using this diagram
 * https://www.music.mcgill.ca/~gary/307/week2/img15.gif
 *
 *
 */
#include <filters/fixed_iir.hpp>

void fixediir::reset()
{
    for (int i = 0; i < m_numXRegisters; i++) {
        m_x[i].real(0);
        m_x[i].imag(0);

    } //Initialize registers

    for (int i = 0; i < m_numYRegisters; i++) {
        m_y[i].real(0);
        m_y[i].imag(0);
    } //Initialize registers

}

bool fixediir::input(const filter_io_t &data)
{

    assert(data.type == IO_TYPE_FIXED_COMPLEX);
    FixedComplex16 sample = data.fc;
    iir(sample);
    return true;
}

bool fixediir::output(filter_io_t &data)
{
    data = m_output;
    return true;
}

void fixediir::tick()
{

}

fixediir::fixediir(std::vector<FixedComplex16> aCoeffs, std::vector<FixedComplex16> bCoeffs) :
                FilterChainElement("FixedIIR"),
                m_numXRegisters(bCoeffs.size()),
                m_numYRegisters(aCoeffs.size()),
                m_a(m_numYRegisters),
                m_b(m_numXRegisters),
                m_x(m_numXRegisters),
                m_y(m_numYRegisters)
{
        m_a = aCoeffs; //Gets coefficient data for right side
        m_b = bCoeffs; //Gets coefficient data for left side
} //Constructs filter based on number of registers on each side and the values of those registers

void fixediir::iir(FixedComplex16 &input)
{

    FixedComplex16 currenty, centerTap;
    centerTap = (input * m_b[0]); // x[0] * b[0]

    for (int i = 1; i < m_numXRegisters; i++)
        centerTap = centerTap + (m_x[i] * m_b[i]); //Accumulate for each x register
    currenty = (centerTap); // Coefficient of a[0] = 1
    for (int i = 1; i < m_numYRegisters; i++) {
        currenty = (currenty) - (m_a[i] * m_y[i]); //Accumulate
    }
    for (int i = m_numXRegisters - 1; i > 1; i--)
        m_x[i] = m_x[i - 1]; //Moves everything up one register

    for (int i = m_numYRegisters - 1; i > 1; i--)
        m_y[i] = m_y[i - 1]; //Moves everything up one register

    m_x[1] = input; //Moves x[0] to x[1]
    m_y[1] = currenty; //Moves y[0] to y[1]

    m_output = currenty; //Calculate filtered data
} //Filters input data and places filtered data in output. Takes in input values, output array, and number of inputs.


