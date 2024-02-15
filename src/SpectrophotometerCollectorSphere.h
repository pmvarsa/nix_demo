/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include "CollectorSphere.h"
#include <Scalar.h>
#include <SphericalCoordinates.h>
#include <Vector3.h>

namespace nix {

class Vector3;

/// A perfect spherical or hemispherical collector.
class SpectrophotometerCollectorSphere : public CollectorSphere
{
  public:
	/// Construct a complete SpectrophotometerCollectorSphere.
	/// Both halves (upper and lower) are enabled and the Z-axis is up.
	SpectrophotometerCollectorSphere();

	/// Construct a SpectrophotometerCollectorSphere specifying which halves
	/// (upper and/or lower) are to be enabled and which axis is up.
	/// \param upper Set to true if the upper half of the photo sphere should
	///        be enabled.
	/// \param lower Set to true if the lower half of the photo sphere should
	///        be enabled.
	/// \param up Specify the up direction.  The default is the z-axis. An
	///        arbitrary direction will be normalized.
	SpectrophotometerCollectorSphere(
		const bool upper, const bool lower/*, const Vector3& up = Vector3::ZAxis*/);

	/// Get the center of the specified sensor in sperical co-ordinates.
	/// \throws Throws std::out_of_range if sensorId is out of range.
	/// \param sensorId This must be 0 or 1.
	/// \return Return the location of the specified sensor. This is
	///         \f$(0, 0)\f$ for the upper hemisphere (if enabled), and
	///         \f$(\pi, 0)\f$ for the lower hemisphere (if enabled).
	SphericalCoordinates center(int sensorId) const;

	/// Get the solid angle (unit sphere area) of the specified hemisphere.
	/// \throws Throws std::out_of_range if sensorId is out of range.
	/// \param sensorId This must be 0 or 1.
	/// \return Returns \f$2\pi\f$
	Scalar getSolidAngle(int sensorId) const;

	/// Returns the projected solid angle of the specified hemisphere.
	/// \throws Throws std::out_of_range if sensorId is out of range.
	/// \param sensorId This must be 0 or 1.
	/// \return Returns \f$\pi\f$.
	Scalar getProjectedSolidAngle(int sensorId) const;

	/// Determine which hemipher a ray strikes.
	/// \param photon The ray is assumed to be inside the collector sphere.
	///        I.e. the eye point is totally ignored.
	/// \return Returns which hemisphere is struck.  This is always zero if
	///         only one hemisphere is struck. 0 or 1 if the full sphere is
	///         enabled, or -1 if no hemisphere is struck.
	int getSensorId(const Ray3& photon) const noexcept;

	/// Test if the upper hemisphere is enabled.
	/// \return Returns true if the upper hemisphere is enabled.
	inline bool upperEnabled() const noexcept { return true; }

	/// Test if the lower hemisphere is enabled.
	/// \return Returns true if the lower hemisphere is enabled.
	inline bool lowerEnabled() const noexcept { return false; }

	/// Provide read-only access to the up vector.
	/// \return Returns a const reference to the up vector.
	inline const Vector3 & up() const noexcept{ return _up; }

	/// Trival, generated destructor.
	virtual ~SpectrophotometerCollectorSphere() = default;
	
private:
	Vector3 _up;	///< The up direction of the sphere is typically the Z-axis

};

} // namespace nix

