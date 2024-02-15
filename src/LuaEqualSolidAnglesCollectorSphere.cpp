/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the EqualSolidAnglesCollectorSphere class.           *
 ***************************************************************************/

#include "LuaEqualSolidAnglesCollectorSphere.h"

#include <iostream>

namespace nix {
namespace lua {

// This array contains a nix_photometer.function_name to C++ implementation
// It must be null-terminated.
const luaL_Reg LuaEqualSolidAnglesCollectorSphere::methods[] = {
	{ "__gc", measurement::nix_equal_solid_angle_collector_sphere_gc_cmd },
	{ "dump", measurement::nix_equal_solid_angle_collector_sphere_dump },
	{ 0, 0 }
};

const std::string LuaEqualSolidAnglesCollectorSphere::luaType
	{"nix.equal_solid_angle_collector_sphere"};

static auto getContainer(lua_State * L)
{
	return getLuaContainer<LuaEqualSolidAnglesCollectorSphere>(
		L, LuaEqualSolidAnglesCollectorSphere::luaType);
}

static EqualSolidAnglesCollectorSphere & getSelf(lua_State * L)
{
	auto pCont = getContainer(L);
	return *(pCont->self.get());
}

void LuaEqualSolidAnglesCollectorSphere::setupMetatable(lua_State * L) noexcept
{
	NIX_LUA_DEBUG("Setting up EqualSolidAnglesCollectorSphere.");

	luaL_newmetatable(L, LuaEqualSolidAnglesCollectorSphere::luaType.c_str());
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_setfuncs(L, LuaEqualSolidAnglesCollectorSphere::methods, 0);
}

namespace measurement {
extern "C" {

// Garbage collector function for Lua
int nix_equal_solid_angle_collector_sphere_dump(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	// Get a pointer to self
	auto self = getSelf(L);

	using namespace std;

	// output debug info
	cout << "EqualSolidAnglesCollectorSphere:" << endl << boolalpha
		 << "    stacks:        " << self.stacks() << endl
		 << "    slices:        " << self.slices() << endl
		 << "    Upper enabled: " << self.upper() << endl
		 << "    Lower enabled: " << self.lower() << endl;
	return 0;
}

int nix_equal_solid_angle_collector_sphere_gc_cmd(lua_State * L)
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

