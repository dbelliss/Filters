/*
 * XCorrelator.hpp
 *
 *  Created on: Jul 28, 2016
 *      Author: ubuntu
 */

#pragma once
#include <filters/fixedfft.hpp>
#include <vector>
#include <utils/utils.hpp>
#include <queue>

class XCorrelator
{
public:
    XCorrelator(int N); //N point fft and ifft.
    std::vector<FixedComplex64> xCorrelate(std::vector<FixedComplex64> x,std::vector<FixedComplex64> y); //cross correlates 2 vectors of FixedComplex<32>

private:
    unsigned int m_n;// n point fft and ifft
    std::vector<FixedComplex64> fft(std::vector<FixedComplex64> vals);//computes fft
	std::vector<FixedComplex64> ifft(std::vector<FixedComplex64> vals);//computes ifft
	std::vector<FixedComplex64> fftshift(std::vector<FixedComplex64> vals);//fftshifts the results
};

