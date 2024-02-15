/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#pragma once

#include <IMedium.h>

namespace nix {

class Medium : public IMedium
{
  public:
	Medium() = default;
	virtual ~Medium() = default;
};

}

