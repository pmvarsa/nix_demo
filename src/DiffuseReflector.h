/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include "Scalar.h"

#include <ISpecimen.h>

namespace nix {

class RayResult;

/// Model a pefectly diffuse reflector.
class DiffuseReflector : virtual public ISpecimen
{
  public:

	/// Default default constructor.
	DiffuseReflector() = default;

	/// Default virtual destructor.
	virtual ~DiffuseReflector() = default;

	/// Return a random direction, since this is diffuse.
	/// @param x The intersection point is stored as part of the resulting
	///        RandomScatterRecord.
	/// @param ss Stored as part of the resulting RandomScatterRecord.
	/// @param ambient Ignored.
	/// @param sr The resulting scatter record.
	/// @return Returns Returns a RayResult object indicating that the ray was
	///         reflected.
	virtual const RayResult Scatter(const Intersection & x,
									const SpectralSample & ss,
									const IMedium & ambient,
									RandomScatterRecord & sr) const;

	/// Return the name of the string.
	/// @return Returns "diffuse".
	std::string & name() const override;
};

} // namespace nix

