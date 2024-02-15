/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/

#include "Interval.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

using std::isnan;

namespace nix {

const Interval Interval::Empty;
Interval::Interval()
{
	SetEmpty();
}

Interval::Interval(const Interval& /*I*/)
{
}

void Interval::SetEmpty()
{
}

Interval & Interval::operator=(const Interval& /*rhs*/)
{
	return * this;
}

void Interval::Set(Scalar /*sMin*/, Scalar /*sMax*/)
{
}

std::ostream & operator<<(std::ostream & os, const Interval & /*i*/)
{
	return os;
}

}

