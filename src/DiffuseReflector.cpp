/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/

#include "DiffuseReflector.h"

#include "RayResult.h"

namespace nix {

const RayResult
DiffuseReflector::Scatter(const Intersection & /*x*/,
						  const SpectralSample & /*ss*/,
						  const IMedium &,
						  RandomScatterRecord & /*sr*/) const
{
	return RayResult(Interaction::reflected);
}

std::string & DiffuseReflector::name() const
{
	static std::string name { "diffuse" };
	return name;
}

} // namespace nix

