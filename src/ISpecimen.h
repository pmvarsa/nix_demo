/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include <string>

namespace nix {

class Intersection;
class IMedium;
class RandomScatterRecord;
class RayResult;
class SpectralSample;

class ISpecimen
{
  public:

	/// Peform the scattering computation after intersection of a Ray with a
	/// specimen.
	/// @param x The Intersection object contains the Ray3, distance along the
	///        ray and the intersection Point3 on the sample.
	/// @param ss The set of wavelengths to scatter through the medium with their
	///        associated intensities.
	/// @param ambient The medium surrounding the sample.
	/// @param sr The resulting scatter record.
	/// @return Return's data about what happened to the ray during scattering.
	virtual const RayResult Scatter(const Intersection & x,
									const SpectralSample & ss,
									const IMedium & ambient,
									RandomScatterRecord & sr) const = 0;

	/// Provide a name for parameter name output.
	/// @return Returns a reference to a sting name.
	virtual std::string & name() const = 0;

	/// Default virtual destructor.
	virtual ~ISpecimen() = default;
};

}

