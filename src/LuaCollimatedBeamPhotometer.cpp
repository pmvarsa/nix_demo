/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the CollimatedBeamPhotometer class.                  *
 ***************************************************************************/

#include "LuaCollimatedBeamPhotometer.h"
#include "LuaEqualSolidAnglesCollectorSphere.h"
#include "LuaSpectrophotometerCollectorSphere.h"
#include "ICollectorSphere.h"

#include <iostream>

namespace nix {
namespace lua {

const std::string LuaCollimatedBeamPhotometer::luaType
	{"nix.collimated_beam_photometer"};

// This array contains a nix_photometer.function_name to C++ implementation
// It must be null-terminated.
const luaL_Reg LuaCollimatedBeamPhotometer::methods[] = {
	{ "dump", measurement::nix_collimated_beam_photometer_dump },
	{ "set_collector_sphere",
		measurement::nix_collimated_beam_photometer_set_collector_sphere },
	{ "set_collect_statistics",
		measurement::nix_collimated_beam_photometer_set_collect_statistics },
	{ "__gc", measurement::nix_collimated_beam_photometer_gc },
	{ 0, 0 }
};

void LuaCollimatedBeamPhotometer::setupMetatable(lua_State * L) noexcept
{
	NIX_LUA_DEBUG("Setting up CollimatedBeamPhotometer.");
	luaL_newmetatable(L, LuaCollimatedBeamPhotometer::luaType.c_str());
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_setfuncs(L, LuaCollimatedBeamPhotometer::methods, 0);
}

static auto getLuaContainer(lua_State * L)
{
	return getLuaContainer<LuaCollimatedBeamPhotometer>(
		L, LuaCollimatedBeamPhotometer::luaType);
}

static CollimatedBeamPhotometer & getSelf(lua_State * L)
{
	// Get an underlying object reference, without giving up ownership
	auto pCont = getLuaContainer(L);
	return *(pCont->self.get());
}

namespace measurement {
extern "C" {

int nix_collimated_beam_photometer_dump(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	// Get a reference to self
	// @TODO I'm not sure why auto doesn't work here
	CollimatedBeamPhotometer & self = getSelf(L);

	using namespace std;

	// output debug info
	cout << std::boolalpha
		 << "CollimatedBeamPhotometer:" << endl << std::boolalpha
		 << "    Photons Cast:   " << self.numPhotonsCast() << endl
		 << "    Wavelength:     " << self.wavelength() << endl
		 << "    Incident Angle: " << self.getIncidentAngle() << endl
		 << "    Collect Stats:  " << self.isCollectingStats() << endl;
	return 0;
}

int nix_collimated_beam_photometer_set_collector_sphere(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	auto numArgs = lua_gettop(L);
	if (numArgs != 2) {
		return luaL_argerror(L, numArgs, "Incorrect number of arguments passed"
			" to set_collector_sphere.");
	}

	CollimatedBeamPhotometer & self = getSelf(L);

	// Get the argument, which could be one of three things
	void * p = luaL_testudata(L, 2, LuaSpectrophotometerCollectorSphere::luaType.c_str());
	void * r = luaL_testudata(L, 2, LuaEqualSolidAnglesCollectorSphere::luaType.c_str());
	if (p != nullptr) {
		// Give the collector sphere to the collimated beam photometer
		LuaSpectrophotometerCollectorSphere ** pCont = (LuaSpectrophotometerCollectorSphere **)p;
		self.SetCollectorSphere(std::move((*pCont)->self));
	} else if (r != nullptr) {
		LuaEqualSolidAnglesCollectorSphere ** pCont = (LuaEqualSolidAnglesCollectorSphere **)r;
		self.SetCollectorSphere(std::move((*pCont)->self));
	} else {
		luaL_argerror(L, 2, "Expected a spectrophotometer_collector_sphere, "
			"a equal_polar_angles_collector_sphere or "
			"a equal_solid_angles_collector_sphere as the argument.");
	}

	return 0;
}

int nix_collimated_beam_photometer_set_collect_statistics(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	auto numArgs = lua_gettop(L);
	if (numArgs != 2) {
		return luaL_argerror(L, numArgs, "Incorrect number of arguments passed"
			" to set_collect_statistics.");
	}

	CollimatedBeamPhotometer & self = getSelf(L);

	// Get the argument, which should be a boolean
	bool collect_statistics = lua_toboolean(L, 2);
	self.setCollectStatistics(collect_statistics);

	return 0;
}

// Garbage collector function for Lua
int nix_collimated_beam_photometer_gc(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	auto pContainer = getLuaContainer(L);
	delete pContainer;

	return 0;
}

} // extern "C"
} // namespace measurement
} // namespace lua
} // namespace nix

