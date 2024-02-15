/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include <Scalar.h>
#include <stdexcept>

namespace nix {

class Ray3;
class SphericalCoordinates;

/// Interface definition of a vitual collector sphere.
class ICollectorSphere
{
  public:
	/// Clear all data that has been collected.
	virtual void Clear() = 0;

	/// Record a datum.
	/// \param photon The ray used to determine which patch was struck.
	virtual void Record(const Ray3& photon) = 0;

	/// Get the number of sensors.
	/// \return Returns a non-negative integer. If zero, this is a pretty useless
	///         collector sphere, but it's possible.
	virtual int numSensors() const = 0;

  protected:
	/// Compute which sensor was struck, if any, given a ray direction in the
	/// sphere.
	/// \param photon Must be a valid ray in the collector sphere.
	/// \return Returns a non-negative integer representing the sensor that was
	///         struck, or a negative number for no sensor being struck.
	virtual int getSensorId(const Ray3& photon) const = 0;

  public:
	/// Query the location of the center a sensor in spherical coordinates.
	/// \throw std::out_of_range Thrown when sensorId is out of range.
	/// \param sensorId Valid values are \f$ 0 \le \f$ sensorId < numSensors().
	/// \return Returns a copy of the co-ordinates.
	virtual SphericalCoordinates center(int sensorId) const = 0;

	/// Return the raw number of photons (Ray3 objects) that struck a sensor.
	/// \throw std::out_of_range Thrown when sensorId is out of range.
	/// \param sensorId Valid values are \f$ 0 \le \f$ sensorId < numSensors().
	/// \return The return value should be \f$ > 0\f$.
	virtual int hits(int sensorId) const = 0;

	/// Get the solid angle represented by this sensor.
	/// \throw std::out_of_range Thrown when sensorId is out of range.
	/// \param sensorId Valid values are \f$ 0 \le \f$ sensorId < numSensors().
	/// \return The return value should be \f$ > 0\f$.
	virtual Scalar getSolidAngle(int sensorId) const = 0;

	/// Get the area of the solid angle projected onto the test material.
	/// \throw std::out_of_range Thrown when sensorId is out of range.
	/// \param sensorId Valid values are \f$ 0 \le \f$ sensorId < numSensors().
	/// \return The return value should be \f$ > 0\f$.
	virtual Scalar getProjectedSolidAngle(int sensorId) const = 0;

	/// Default virtual destructor.
	virtual ~ICollectorSphere() = default;
};

} // namespace nix

