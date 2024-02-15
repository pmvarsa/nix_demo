/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/

#include "PiecewiseLinearSpectrum.h"
#include <Scalar.h>
#include <cassert>
#include <cmath>
#include <iostream>

namespace nix {

PiecewiseLinearSpectrum::PiecewiseLinearSpectrum()
 : _name("vacuum"), _wavelengths(), _values()
{
	_wavelengths.push_back(380.);
	_wavelengths.push_back(2500.);
	_values.push_back(1.);
	_values.push_back(1.);
}

PiecewiseLinearSpectrum::PiecewiseLinearSpectrum(
	const std::string & name, Scalar low, Scalar high,
	const std::vector<Scalar> & values)
  : _name(name)
{
	_wavelengths.push_back(low);
	_wavelengths.push_back(high);
	_values = values;
}

PiecewiseLinearSpectrum::PiecewiseLinearSpectrum(
	const std::string & name,
	const std::vector<Scalar> & wavelengths,
	const std::vector<Scalar> & values)
  : _name(name)
{
	if (wavelengths.size() != values.size()) {
		throw std::runtime_error("Wavelength size does not match value size.");
	}
	_wavelengths = wavelengths;
	_values = values;
}

Scalar PiecewiseLinearSpectrum::low() const
{
	if (_wavelengths.empty()) {
		throw std::runtime_error(
			"No wavelengths specified in call to PiecewiseLinearSpectrum::low()");
	}
	return * _wavelengths.begin();
}

Scalar PiecewiseLinearSpectrum::high() const
{
	if (_wavelengths.empty()) {
		throw std::runtime_error(
			"No wavelengths specified in call to PiecewiseLinearSpectrum::low()");
	}
	return * _wavelengths.rbegin()++;
}

Scalar PiecewiseLinearSpectrum::evaluate(Scalar /*lambda*/) const
{
	return 0;
}

std::complex<Scalar> getComplexRefractiveIndex(
		const std::shared_ptr<const PiecewiseLinearSpectrum>& n,
		const std::shared_ptr<const PiecewiseLinearSpectrum>& k, Scalar lambda)
{
	return std::complex<Scalar>(n ? n->evaluate(lambda) : 1.0, k ? k->evaluate(lambda) : 0.0);
}

}

