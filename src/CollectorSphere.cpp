/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/

#include "CollectorSphere.h"

#include <cassert>

namespace nix {

CollectorSphere::CollectorSphere(int /*numSensors*/)
 : ICollectorSphere()/*, _sensors(numSensors, Sensor())*/
{
}

void CollectorSphere::initSensors(int /*numSensors*/)
{
}

void CollectorSphere::Clear()
{
}

void CollectorSphere::Record(const Ray3& /*photon*/)
{
}

int CollectorSphere::hits(int /*sensorId*/) const
{
	return 0;
}

} // namespace nix

