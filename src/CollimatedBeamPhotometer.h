/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include <functional>
#include <iosfwd>
#include <memory>

#include <Scalar.h>
#include <SphericalCoordinates.h>

namespace nix {

class ICollectorSphere;
class Intersection;
class ISpecimen;
class ScatteringData;

/**
 * Concrete representation of a Collimated Beam Photometer.
 *
 * The photometer is modelled in such a way as to be quite generic with respect
 * to data collection. I.e. Various ICollectorSphere instances can be used
 * depending upon the desired data to be recorded.
 *
 * The CollimatedBeamPhotometer only acts on one incident angle and one
 * wavelength at a time.  Clear() must be called for it to be reused on either
 * a new wavelength or a new incident angle.
 */
class CollimatedBeamPhotometer
{
  public:
	/// Default construct a CollimatedBeamPhotometer.
	/// Constructed with an intersection point at the origin illuminated from
	/// the zenith toward nadir, no collector sphere, no specimen, an
	/// unrealistic wavelength of zero, zero rays to cast, and no statistics
	/// being collected.
	CollimatedBeamPhotometer();

	/// Non-trivial destructor.
	/// The intersection point, \c _x, must be deleted.
	virtual ~CollimatedBeamPhotometer();

	/// Return some std::string useful for printing debug output.
	std::string type() const noexcept;

	/// Query the number of rays cast so far.
	/// \return The return value is \f$ \ge 0 \f$.
	unsigned numPhotonsCast() const { return 0; }

	/// Query the wavelength currently being tested.
	/// \return Returns the wavelength in nanometres.
	Scalar wavelength() const { return 0.0; }

	/// Return the incident angle that each ray is being cast from.
	/// \return A copy is returned.
	SphericalCoordinates getIncidentAngle() const { return SphericalCoordinates(); }

	/// Set the collector sphere to be used.
	/// The collector sphere pointer will now be owned by the CollimatedBeamPhotometer.
	/// \param cs A unique pointer to an ICollectorSphere.
	void SetCollectorSphere(std::unique_ptr<ICollectorSphere> cs);

	/// Set whether or not statistics will be colleced with this execution.
	/// Collecting statistics has a performance impact by introducing an extra
	/// point of thread contention, since the statistics object needs to be
	/// written to with mutual exclusion.
	///
	/// \param collectStats If true, statistics will be collected.
	void setCollectStatistics(bool collectStats);

	/// Check if the flag is set to collect statistics during program execution.
	/// \return Returns \c true if statistics are being collected.
	bool isCollectingStats() const;

	/// Output the instance to the specified stream in a human readable format.
	/// \param os The output stream to send the formatted data to.
	void print(std::ostream & os) const;

  private:
	static const std::string _type;	///< The photometer type

	/// The collector sphere used to collect results.
	std::unique_ptr<ICollectorSphere> _cs;
};

/// Output a CollimatedBeamPhotometer to the specified output stream in a
/// human readable format.
/// \see CollimatedBeamPhotometer::print()
///
/// \param os The output stream to send the formatted data to.
/// \param photometer The CollimatedBeamPhotometer object to output.
/// \return Returns \c os for chaining as per good coding standards.
std::ostream & operator<<(std::ostream & os,
						  const CollimatedBeamPhotometer & photometer);

}

