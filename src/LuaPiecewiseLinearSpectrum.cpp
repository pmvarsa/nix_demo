/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the PiecewiseLinearSpectrum class.                   *
 ***************************************************************************/

#include "LuaPiecewiseLinearSpectrum.h"

#include <iostream>
#include <vector>

namespace nix {
namespace lua {

// This array contains a nix_piecewise_linear_spectrum.function_name to C++
// implementation It must be null-terminated.
const luaL_Reg LuaPiecewiseLinearSpectrum::methods[] = {
	{ "dump", spectrum::nix_piecewise_linear_spectrum_dump },
	{ "__gc", spectrum::nix_piecewise_linear_spectrum_gc },
	{ 0, 0 }
};

const std::string LuaPiecewiseLinearSpectrum::luaType
	{"nix.piecewise_linear_spectrum"};

static auto getLuaContainer(lua_State * L)
{
	return getLuaContainer<LuaPiecewiseLinearSpectrum>(
		L, LuaPiecewiseLinearSpectrum::luaType);
}

static auto getSelf(lua_State * L)
{
	return getSelf<PiecewiseLinearSpectrum, LuaPiecewiseLinearSpectrum>(
		L, LuaPiecewiseLinearSpectrum::luaType);
}

void LuaPiecewiseLinearSpectrum::setupMetatable(lua_State * L) noexcept
{
	NIX_LUA_DEBUG("Setting up PiecewiseLinearSpectrum.");
	luaL_newmetatable(L, LuaPiecewiseLinearSpectrum::luaType.c_str());
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_setfuncs(L, LuaPiecewiseLinearSpectrum::methods, 0);
}

namespace spectrum {
extern "C" {

int nix_piecewise_linear_spectrum_dump(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	auto self = getSelf(L);

	using namespace std;
	cout << "PiecewiseLinearSpectrum:" << endl << boolalpha
		 << "    Name:  " << self->name() << endl
		 << "    Size:  " << self->values().size() << endl;
	if (self->values().size() > 0) {
		cout << "    Range: (" << self->low() << ", " << self->high() << ")" << endl;
	}

	return 0;
}

int nix_piecewise_linear_spectrum_gc(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	auto pData = getLuaContainer(L);
	delete pData;
	return 0;
}

} // extern "C"
} // namespace spectrum
} // namespace lua
} // namespace nix

