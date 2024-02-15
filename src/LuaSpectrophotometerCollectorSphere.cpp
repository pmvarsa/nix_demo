/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the SpectrophotometerCollectorSphere class.          *
 ***************************************************************************/

#include "LuaSpectrophotometerCollectorSphere.h"

#include <iostream>

namespace nix {
namespace lua {

// This array contains a nix_photometer.function_name to C++ implementation
// It must be null-terminated.
const luaL_Reg LuaSpectrophotometerCollectorSphere::methods[] = {
	{ "__gc", measurement::nix_spectrophotometer_collector_sphere_gc_cmd },
	{ "dump", measurement::nix_spectrophotometer_collector_sphere_dump },
	{ 0, 0 }
};

const std::string LuaSpectrophotometerCollectorSphere::luaType
	{"nix.spectrophotometer_collector_sphere"};

static auto getContainer(lua_State * L)
{
	return getLuaContainer<LuaSpectrophotometerCollectorSphere>(
		L, LuaSpectrophotometerCollectorSphere::luaType);
}

static SpectrophotometerCollectorSphere & getSelf(lua_State * L)
{
	auto pCont = getContainer(L);
	return *(pCont->self.get());
}

void LuaSpectrophotometerCollectorSphere::setupMetatable(lua_State * L) noexcept
{
	NIX_LUA_DEBUG("Setting up SpectrophotometerCollectorSphere.");

	luaL_newmetatable(L, LuaSpectrophotometerCollectorSphere::luaType.c_str());
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_setfuncs(L, LuaSpectrophotometerCollectorSphere::methods, 0);
}

namespace measurement {
extern "C" {

// Garbage collector function for Lua
int nix_spectrophotometer_collector_sphere_dump(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	// Get a pointer to self
	auto self = getSelf(L);

	using namespace std;

	// output debug info
	cout << "SpectrophotometerCollectorSphere:" << endl << boolalpha
		 << "    Upper enabled: " << self.upperEnabled() << endl
		 << "    Lower enabled: " << self.lowerEnabled() << endl
		 << "    Up: " << self.up() << endl;
	return 0;
}

int nix_spectrophotometer_collector_sphere_gc_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	auto pContainer = getContainer(L);
	delete pContainer;

	return 0;
}

} // extern "C"
} // namespace measurement
} // namespace lua
} // namespace nix

