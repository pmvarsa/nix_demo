/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the VacuumMedium class.                              *
 ***************************************************************************/

#include "LuaVacuumMedium.h"

namespace nix {
namespace lua {

// This array contains a nix_vacuum_medium.function_name to C++
// implementation It must be null-terminated.
const luaL_Reg LuaVacuumMedium::methods[] = {
	{ "dump", media::nix_vacuum_medium_dump },
	{ "__gc", media::nix_vacuum_medium_gc },
	{ 0, 0 }
};

const std::string LuaVacuumMedium::luaType {"nix.vacuum_medium"};

static auto getLuaContainer(lua_State * L)
{
	return getLuaContainer<LuaVacuumMedium>(L, LuaVacuumMedium::luaType);
}

void LuaVacuumMedium::setupMetatable(lua_State * L) noexcept
{
	NIX_LUA_DEBUG("Setting up VacuumMedium.");
	luaL_newmetatable(L, LuaVacuumMedium::luaType.c_str());
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_setfuncs(L, LuaVacuumMedium::methods, 0);
}

namespace media {
extern "C" {

int nix_vacuum_medium_dump(lua_State *)
{
	NIX_LUA_DEBUG_CALL;
	std::cout << "VacuumMedium" << std::endl;
	return 0;
}

int nix_vacuum_medium_gc(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	auto pData = getLuaContainer(L);
	delete pData;
	return 0;
}

} // extern "C"
} // namespace media
} // namespace lua
} // namespace nix

