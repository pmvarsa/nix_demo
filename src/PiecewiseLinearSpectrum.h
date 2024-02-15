/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include "Scalar.h"
#include <complex>
#include <memory>
#include <string>
#include <vector>

namespace nix {

/// Specifies a set of values by wavelength.
/// In-between values are linearly interpolated (I presume).
class PiecewiseLinearSpectrum
{
  public:
	/// Default construct a PiecewiseLinearSpectrum object. This is akin to a
	/// vacuum.
	PiecewiseLinearSpectrum();

	/// Construct a PiecewiseLinearSpectrum with a low/high range, and uniform
	/// data between those values.
	/// \param name The name of the spectrum.
	/// \param low The lowest wavelength should be greater than 0.
	/// \param high The highest wavelength should be greater than low.
	/// \param values The values to be uniformly, linearly, interpolated.
	PiecewiseLinearSpectrum(const std::string & name, Scalar low, Scalar high,
							const std::vector<Scalar> & values);

	/// Construct a PiecewiseLinearSpectrum with specific wavelengths and the
	/// data points at those wavelengths. An exception will be thrown if the
	/// length of the wavelength vector does not match the length of the value
	/// vector.
	/// \param name The name of the spectrum.
	/// \param wavelengths The wavelength data elements.
	/// \param values The values for each wavelength.
	PiecewiseLinearSpectrum(const std::string & name,
							const std::vector<Scalar> & wavelengths,
							const std::vector<Scalar> & values);

	/// There are no resouces to be explicitly deleted.
	virtual ~PiecewiseLinearSpectrum() = default;

	/// Linearly interpolate to get a value at the specified wavelength.
	/// \param lambda The desire wavelength.
	/// \return Returns the interpolated value or zero if it is out of range.
	Scalar evaluate(Scalar lambda) const;

	/// Return the name of this spectrum.
	/// \return Returns the name of this spectrum.
	const std::string & name() const noexcept { return _name; }

	/// Provide access to the values for debugging.
	/// \return Returns a const reference to the internal member.
	const std::vector<Scalar> & values() const noexcept { return _values; }

	/// Return the lowest supported lambda value. Throws a std::runtime_error if there
	/// is no specified range.
	/// \return Returns the value pointed to by begin() in the set of lambdas.
	Scalar low() const;

	/// Return the highest supported lambda value. Throws a std::runtime_error if there
	/// is no specified range.
	/// \return Returns the value pointed to by rbegin()++ in the set of lambdas.
	Scalar high() const;
	
  private:
	std::string _name;					///< Names are nice, aren't they?
	std::vector<Scalar>	_wavelengths;	///< The set of wavelengths.
	std::vector<Scalar>	_values;		///< The values at each specified wavelength.
};

std::complex<Scalar> getComplexRefractiveIndex(
		const std::shared_ptr<const PiecewiseLinearSpectrum>& n,
		const std::shared_ptr<const PiecewiseLinearSpectrum>& k, Scalar lambda);

}

