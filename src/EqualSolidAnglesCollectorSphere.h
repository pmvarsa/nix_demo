/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include "CollectorSphere.h"
#include <Scalar.h>
#include <SphericalCoordinates.h>

namespace nix {

/**
 * This ICollectorSphere class sub-divides the unit sphere into equal area
 * sensors.
 */
class EqualSolidAnglesCollectorSphere : public CollectorSphere
{
public:
	/// Fully construct an instance providing all the necessary parameters.
	/// \param stacks The number of required stacks.
	/// \param slices The number of required slices.
	/// \param upper Set to true to measure reflectance.
	/// \param lower Set to true to measure transmittance.
	EqualSolidAnglesCollectorSphere(int stacks, int slices, bool upper, bool lower);

	/// \copydoc ICollectorSphere::center(int)
	SphericalCoordinates center(int sensorId) const override;
	/// \copydoc ICollectorSphere::getSolidAngle(int)
	Scalar getSolidAngle(int sensorId) const override;
	/// \copydoc ICollectorSphere::getProjectedSolidAngle(int)
	Scalar getProjectedSolidAngle(int sensorId) const override;
	/// \copydoc ICollectorSphere::getSensorId(int)
	int getSensorId(const Ray3& photon) const override;

	/// Get the number of stacks.
	/// \return Returns a positive integer if it is in a good state.
	int stacks() const { return 0; }

	/// Get the number of slices.
	/// \return Returns a positive integer if it is in a good state.
	int slices() const { return 0; }

	/// Test if the upper hemisphere is enabled.
	/// \return Returns true if the upper hemisphere is enabled.
	bool upper() const { return true; }

	/// Test if the lower hemisphere is enabled.
	/// \return Returns true if the lower hemisphere is enabled.
	bool lower() const { return false; }

	virtual ~EqualSolidAnglesCollectorSphere();
};

} // namespace nix

