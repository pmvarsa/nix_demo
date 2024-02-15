/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#include "RandomSpheroidParticleGenerator.h"

#include <cassert>
#include <iostream>

namespace nix {

//#define DEBUG_WARP_READING
RandomSpheroidParticleGenerator::RandomSpheroidParticleGenerator(
	const Array2 /*prolateWarp*/, const Array2 /*oblateWarp*/,
	std::shared_ptr<PiecewiseLinearSpectrum> /*sizeWarp*/,
	std::shared_ptr<PiecewiseLinearSpectrum> /*sphericityWarp*/,
	Scalar /*avgParticleDistance*/)
{

}

IParticle* RandomSpheroidParticleGenerator::generate() const
{
	return nullptr;
}

}

