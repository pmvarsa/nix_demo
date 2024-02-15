/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 ***************************************************************************/
#include "CollimatedBeamPhotometer.h"
#include "LuaGlobal.h"

#include <ICollectorSphere.h>

#include <iostream>
#include <memory>
#include <stdexcept>

// Headers required for multi-threading
#include <iostream>
#include <mutex>
#include <thread>
#include <cstdlib>
#include <atomic>
#include <future>

namespace nix {

const std::string CollimatedBeamPhotometer::_type{"CollimatedBeamPhotometer"};

CollimatedBeamPhotometer::CollimatedBeamPhotometer()
{
}

CollimatedBeamPhotometer::~CollimatedBeamPhotometer()
{
}

void CollimatedBeamPhotometer::SetCollectorSphere(std::unique_ptr<ICollectorSphere> cs)
{
	_cs = std::move(cs);
}

std::string CollimatedBeamPhotometer::type() const noexcept
{
	return _type;
}

void CollimatedBeamPhotometer::setCollectStatistics(bool /*collectStats*/)
{
}

bool CollimatedBeamPhotometer::isCollectingStats() const
{
	return false;
}

void CollimatedBeamPhotometer::print(std::ostream & /*os*/) const
{
}

std::ostream & operator<<(std::ostream & os,
						  const CollimatedBeamPhotometer & photometer)
{
	photometer.print(os);
	return os;
}

}

