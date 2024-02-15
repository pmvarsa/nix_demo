/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include "Scalar.h"

#include <cassert>
#include <utility>
#include <vector>

namespace nix {

struct SpectralSampleImpl;	//!< implementation of SpectralSample

//! A set of wavelength-amplitude pairs
class SpectralSample
{
  public:
	SpectralSample();
	SpectralSample(const SpectralSample& other);
	SpectralSample(Scalar wavelength, Scalar value);
	virtual ~SpectralSample() = default;
	
	SpectralSample&	operator=(const SpectralSample& other);
};

}

