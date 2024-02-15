/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include "Medium.h"

namespace nix {

class VacuumMedium : public Medium
{
  public:
	/// Default construction of a VacuumMedium just calls through to Medium.
	VacuumMedium() {};

  public:
	virtual ~VacuumMedium() = default;
};

}

