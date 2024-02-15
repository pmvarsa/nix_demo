/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/

#include "Vector3.h"

#include <cassert>
#include <iostream>

namespace nix {

const Vector3 Vector3::ZAxis(0.0, 0.0, 1.0);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

std::ostream& Vector3::Print(std::ostream &os) const
{
	return os;
}

std::ostream& operator<<(std::ostream &os, const Vector3 &/*v*/)
{
	return os;
}

}

