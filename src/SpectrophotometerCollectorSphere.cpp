/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/

#include "SpectrophotometerCollectorSphere.h"

#include <cassert>

namespace nix {

SpectrophotometerCollectorSphere::SpectrophotometerCollectorSphere()
 : CollectorSphere(2)
{
}

SpectrophotometerCollectorSphere::SpectrophotometerCollectorSphere(
	const bool /*upper*/, const bool /*lower, const Vector3 & up*/)
 : CollectorSphere{0}
{
}

SphericalCoordinates SpectrophotometerCollectorSphere::center(int /*sensorId*/) const
{
	assert(false);
	throw std::out_of_range("Sensor ID out of range.");
}

Scalar SpectrophotometerCollectorSphere::getSolidAngle(int /*sensorId*/) const
{
	return 0.0;
}

Scalar SpectrophotometerCollectorSphere::getProjectedSolidAngle(int /*sensorId*/) const
{
	return 0.0;
}

int SpectrophotometerCollectorSphere::getSensorId(const Ray3& /*photon*/) const noexcept
{
	return 0;
}

} // namespace nix

