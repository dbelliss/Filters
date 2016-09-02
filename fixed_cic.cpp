#include <filters/fixed_cic.hpp>

/*
 *
 * Using diagram
 * https://westcoastdsp.files.wordpress.com/2015/09/cic_block_diagram.jpg
 *
 */
fixedcic::fixedcic(int R, int aregs, int bregs) :
    FilterChainElement("FixedCIC"),
    m_r(R),
    m_numBRegisters(bregs),
    m_numARegisters(aregs),
    m_a(aregs),
    m_b(bregs)
{
    m_samples = 0;
    goodOutput = false;
}


bool fixedcic::input(const filter_io_t &data)
{
    assert(data.type == IO_TYPE_FIXED_COMPLEX);
    FixedComplex16 sample = data.fc;
    cic(sample);
    return true;
}

bool fixedcic::output(filter_io_t &data)
{
    if (goodOutput == true) {
        data = m_output;
        goodOutput = false;
        return true;
    }//Valid data
    else {
        return false;
    }//Not valid data
}

void fixedcic::tick()
{}

void fixedcic::cic(FixedComplex16 &input)
{
    goodOutput = false;
    FixedComplex16 temp; //Storage for integrate output
    temp = integrate(input); //Calculate filtered data
    if (!(this->downsample())) {//If not downsampled
        m_output = ((this->comb(temp))); //converts final value of comb to 16 bits.
        goodOutput= true;
    }
}

void fixedcic::reset()
{
    m_samples = 0; //reset sample count

    for (int i = 0; i < m_numBRegisters; i++) {
         m_b[i].real(0);
         m_b[i].imag(0);

     } //Initialize registers

     for (int i = 0; i < m_numARegisters; i++) {
         m_a[i].real(0);
         m_a[i].imag(0);
     } //Initialize registers
}

FixedComplex16 fixedcic::integrate(FixedComplex16 current)
{
    for (int i = 0; i < m_numBRegisters; i++) {
        current = current + m_b[i]; //Accumulate for each b register
        m_b[i] = current;
    }

    return current;
} //Performs filtering

FixedComplex16 fixedcic::comb(FixedComplex16 current)
{
    FixedComplex16 final;
    FixedComplex16 temp; //storage for swap

    final = current;

    for (int i = 0; i < m_numARegisters; i++) {
        temp = final;
        final = final - m_a[i]; //Accumulate for each b register
        m_a[i] = temp;
    }

    return final;
} //Performs

bool fixedcic::downsample()
{
    if ((m_samples % m_r) == 0) {
        m_samples++;
        return false;
    } else //otherwise do not comb
    {
        m_samples++;
        return true;
    }
}


