/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include <ICollectorSphere.h>
#include <Scalar.h>
#include <SphericalCoordinates.h>

#include <vector>

namespace nix {

class Ray3;

/// Abstract base class for virtual collector sphere implementations.
class CollectorSphere : virtual public ICollectorSphere
{
  protected:
	/// Base class construction.
	/// \param numSensors The number of sensors must be positive.
    CollectorSphere(int numSensors);

  public:
	/// Trivial, generated, virtual destructor.
	virtual ~CollectorSphere() = default;

	/// \copydoc ICollectorSphere::Clear()
	void Clear() final;
	/// \copydoc ICollectorSphere::Record(const Ray3&)
	void Record(const Ray3& photon) final;
	/// \copydoc ICollectorSphere::numSensors()
	int numSensors() const final { return _sensors.size(); }
	/// \copydoc ICollectorSphere::hits(int)
	int hits(int sensorId) const override;

  protected:
	/// Derived classes can use this method to set the number of sensors
	void initSensors(int numSensors);
	
  private:
	/// Helper class to store sensor hit counts.
	struct Sensor {
		int	_count;	///< Number of hits.

		/// Construct with default hit counts of zero.
		Sensor() : _count(0) {}
	};

	/// Each sensor has its own hit counts.  The sensor ID is used as
	/// an index to this array.
	std::vector<Sensor>	_sensors;
};

} // namespace nix

