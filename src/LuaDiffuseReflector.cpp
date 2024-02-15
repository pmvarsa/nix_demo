/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the DiffuseReflector class.                          *
 ***************************************************************************/

#include "LuaDiffuseReflector.h"

#include <iostream>

namespace nix {
namespace lua {

// This array contains a nix.diffuse_reflector.function_name to C++
// implementation. It must be null-terminated.
const luaL_Reg LuaDiffuseReflector::methods[] = {
	{ "dump", material::nix_diffuse_reflector_dump },
	{ "__gc", material::nix_diffuse_reflector_gc },
	{ 0, 0 }
};

const std::string LuaDiffuseReflector::luaType {"nix.diffuse_reflector"};

void LuaDiffuseReflector::setupMetatable(lua_State * L) noexcept
{
	NIX_LUA_DEBUG("Setting up DiffuseReflector.");
	luaL_newmetatable(L, LuaDiffuseReflector::luaType.c_str());
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_setfuncs(L, LuaDiffuseReflector::methods, 0);
}

static LuaDiffuseReflector * getLuaContainer(lua_State * L)
{
	return getLuaContainer<LuaDiffuseReflector>(L, LuaDiffuseReflector::luaType);
}

namespace material {
extern "C" {

int nix_diffuse_reflector_dump(lua_State *)
{
	NIX_LUA_DEBUG_CALL;

	// @TODO I'm not sure why auto doesn't work here, perhaps it's a g++ bug?
	std::cout << "DiffuseReflector" << std::endl;

	return 0;
}

int nix_diffuse_reflector_gc(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	auto pCont = getLuaContainer(L);
	delete pCont;

	return 0;
}

} // extern "C"
} // namespace material
} // namespace lua
} // namespace nix

