/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/

#include "SpectralSample.h"

#include <algorithm>
#include <cassert>
#include <cstddef>

namespace nix {

SpectralSample::SpectralSample()
{
}

SpectralSample::SpectralSample(const SpectralSample& /*other*/)
{
}

SpectralSample::SpectralSample(Scalar /*wavelength*/, Scalar /*value*/)
{
}

SpectralSample&	SpectralSample::operator=(const SpectralSample& /*other*/)
{
	return *this;
}

}

