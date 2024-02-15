/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/

#include "RayResult.h"

#include <type_traits>

namespace nix {

RayResult::RayResult(Interaction /*i*/)
{
}

bool RayResult::isMirror() const
{
	return (_flags & RayFlags::mirror) != RayFlags::none;
}

} // namespace nix

