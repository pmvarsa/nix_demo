/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#include "EqualSolidAnglesCollectorSphere.h"

#include <cassert>
#include <cmath>

#include <iostream>

namespace nix {

EqualSolidAnglesCollectorSphere::EqualSolidAnglesCollectorSphere(
		int /*stacks*/, int /*slices*/, bool /*upper*/, bool /*lower*/)
  : CollectorSphere(0)
{
}

EqualSolidAnglesCollectorSphere::~EqualSolidAnglesCollectorSphere()
{
}

SphericalCoordinates EqualSolidAnglesCollectorSphere::center(int /*sensorId*/) const
{
	return SphericalCoordinates(0, 0);
}

Scalar EqualSolidAnglesCollectorSphere::getSolidAngle(int /*sensorId*/) const
{
	return 0.0;
}

Scalar EqualSolidAnglesCollectorSphere::getProjectedSolidAngle(int /*sensorId*/) const
{
	return 0;
}

int EqualSolidAnglesCollectorSphere::getSensorId(const Ray3& /*photon*/) const
{
	return 0;
}

} // namespace nix

