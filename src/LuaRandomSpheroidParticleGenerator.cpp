/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the RandomSpheroidParticleGenerator class.           *
 ***************************************************************************/

#include "LuaRandomSpheroidParticleGenerator.h"

#include <iomanip>

namespace nix {
namespace lua {

// This array contains a nix_test1material.function_name to C++ implementation
// It must be null-terminated.
const luaL_Reg LuaRandomSpheroidParticleGenerator::methods[] = {
	{ "dump", material::nix_random_spheroid_particle_generator_dump },
	{ "__gc", material::nix_random_spheroid_particle_generator_gc },
	{ 0, 0 }
};

const std::string LuaRandomSpheroidParticleGenerator::luaType
	{"nix.random_spheroid_particle_generator"};

void LuaRandomSpheroidParticleGenerator::setupMetatable(lua_State * L) noexcept
{
	NIX_LUA_DEBUG("Setting up RandomSpheroidParticleGenerator.");
	luaL_newmetatable(L, LuaRandomSpheroidParticleGenerator::luaType.c_str());
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_setfuncs(L, LuaRandomSpheroidParticleGenerator::methods, 0);
}

static auto getMyContainer(lua_State * L)
{
	return getLuaContainer
		<LuaRandomSpheroidParticleGenerator>
		(L, LuaRandomSpheroidParticleGenerator::luaType);
}

static auto getMyself(lua_State * L)
{
	return getSelf
		<RandomSpheroidParticleGenerator, LuaRandomSpheroidParticleGenerator>
		(L, LuaRandomSpheroidParticleGenerator::luaType);
}

namespace material {
extern "C" {

int nix_random_spheroid_particle_generator_dump(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	auto self = getMyself(L);

	using namespace std;
	cout << "RandomSpheroidParticleGenerator:" << endl
		 << boolalpha << fixed << setprecision(1)
		 << "    Size Warp Fn:         " << self->sizeWarpFunction()->name() << endl
		 << "    Sphericiy Warp Fn:    " << self->sphericityWarpFunction()->name() << endl
	;
	return 0;
}

int nix_random_spheroid_particle_generator_gc(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	auto selfContainer = getMyContainer(L);
	delete selfContainer;
	return 0;
}

} // extern "C"
} // namespace material
} // namespace lua
} // namespace nix

