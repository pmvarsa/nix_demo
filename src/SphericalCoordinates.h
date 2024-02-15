/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include "Scalar.h"

#include <iosfwd>

namespace nix {

/// Representation of an point in spherical coordinates.
/// Typically, the polar angle is denoted &theta;, the azimuthal angle
/// is denoted with &phi;, and the radius is denoted \f$r\f$.
class SphericalCoordinates
{
  public:
  	/// Default constructor
	/// All angles are in radians.
	/// Constructs an object with (0, 0, 1).
	SphericalCoordinates();

	/// Complete constructor with all values.
	/// All angles are in radians.
	/// \param polar The polar angle is away from nadir, or away from up.
	///        Typically in the range of [0-180].
	/// \param azimuthal The azimuthal angle is angle around the up direction.
	///        Typically in the range of [0-360).
	/// \param radius Default value is 1.
	SphericalCoordinates(Scalar polar, Scalar azimuthal, Scalar radius = 1.0);

	~SphericalCoordinates() = default;

};

/// Output a SphericalCoordinates object to \c os in a human readable format.
/// @see SphericalCoordinates::print()
///
/// \param os The output stream to send the formatted data to.
/// \param sc The SphericalCoordinates object to stream to output.
/// \return Returns \c os for chaining as per good coding standards.
std::ostream & operator<<(std::ostream & os,
						  const SphericalCoordinates & sc);

} // namespace nix

