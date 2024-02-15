/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/

#include <iostream>

#include "SphericalCoordinates.h"

namespace nix {

SphericalCoordinates::SphericalCoordinates()
{
}

SphericalCoordinates::SphericalCoordinates(Scalar /*polar*/, Scalar /*azimuthal*/, Scalar /*radius*/)
{
}

std::ostream & operator<<(std::ostream & os, const SphericalCoordinates & /*sc*/)
{
	return os;
}

} // namespace nix

