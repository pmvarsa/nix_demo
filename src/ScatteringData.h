/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include "Scalar.h"

#include <iosfwd>
#include <map>

namespace nix {

class RayResult;

/// Specify the numeric type for interger statistical data.
using counter = long long int;

/**
 * This class is used to record scattering event data for ray propogation
 * through a material. It is tailored for use with the Test1Material class.
 *
 * For simplicity, this class only supports integer values for the wavelength.
 */
class ScatteringData
{
};

/**
 * Print out the data in readable form.
 *
 * @see ScatteringData::print()
 *
 * @param os The output stream to write to.
 * @param p The data to write.
 *
 * @returns Returns the \c os parameter as per best practices.
 */
std::ostream & operator<<(std::ostream & os, const ScatteringData & p);

} // namespace nix

