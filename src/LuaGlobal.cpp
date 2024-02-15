/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the SpectrophotometerCollectorSphere class.          *
 ***************************************************************************/

#include "LuaGlobal.h"

#include "LuaCollimatedBeamPhotometer.h"
#include "LuaDiffuseReflector.h"
#include "LuaEqualSolidAnglesCollectorSphere.h"
#include "LuaPhotometerJob.h"
#include "LuaPiecewiseLinearSpectrum.h"
#include "LuaRandomSpheroidParticleGenerator.h"
#include "LuaSpectrophotometerCollectorSphere.h"
#include "LuaTest1Material.h"
#include "LuaVacuumMedium.h"

#include "Array2.h"

#include <thread>

namespace nix {
namespace lua {

unsigned int LuaGlobal::cores = std::thread::hardware_concurrency();

const luaL_Reg LuaGlobal::methods[] = {
	{ "spectrophotometer_collector_sphere",
		global::nix_spectrophotometer_collector_sphere_cmd },
	{ "equal_solid_angles_collector_sphere",
		global::nix_equal_solid_angles_collector_sphere_cmd },
	{ "collimated_beam_photometer", global::nix_collimated_beam_photometer_cmd },
	{ "piecewise_linear_spectrum", global::nix_piecewise_linear_spectrum_cmd },
	{ "photometer_job", global::nix_photometer_job_cmd },
	{ "random_spheroid_particle_generator", global::nix_random_spheroid_particle_generator_cmd },
	{ "test1material", global::nix_test1material_cmd },
	{ "diffuse_reflector", global::nix_diffuse_reflector_cmd },
	{ "vacuum_medium", global::nix_vacuum_medium_cmd },
	{ 0, 0 }
};

/**
 * Read a 2D warping function from Lua.
 * It is assumed that the warping function is 101x101.
 * \param L The Lua stack object.
 * \param index The location on the stack where the 2D array is stored.
 * \param array A 101x101 `std::array<std::array<double>, 101, 101>`
 *         that is ready to be populated with the data from the Lua file.
 * \return Retuns 0, if it ever returns at all. If there's an error, everything
 *         goes sad and this never returns, by Lua C API design.
 */
static
int get2DWarpingArray(lua_State * L, int index, Array2 & array)
{
	luaL_checktype(L, index, LUA_TTABLE);
	auto length = lua_rawlen(L, index);
	if (length != 101) {
		return luaL_argerror(L, index, "Expected 101 rows in fixed-sized array"
			" for 2D spheroid warping function.");
	}

	for (unsigned row=1; row<=101; ++row) {
		for (unsigned col=1; col<=101; ++col) {
			// Get the row table
			lua_rawgeti(L, index, row);

			// Check that the length is correct
			auto colLength = lua_rawlen(L, -1);
			if (colLength != 101) {
				std::cout << colLength << std::endl;
				luaL_argerror(L, index, "Expected 101 elements in column array when"
						" processing 2D spheroid warping function.");
			}

			// Get the value out of the column table
			lua_rawgeti(L, -1, col);

			// Read the actual numerical value
			array[row-1][col-1] = luaL_checknumber(L, -1);
			lua_pop(L, 2);
		}
	}

	return 0;
}

namespace global {
extern "C" {

int nix_photometer_job_cmd (lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	int numArgs = lua_gettop(L);
	if (numArgs != 0) {
		// Incorrect number of arguments passed
		return luaL_argerror(L, numArgs, "Incorrect number of arguments "
			"passed to photometer_job creation.");
	}

	createUniqueUserData<LuaPhotometerJob, PhotometerJob>(L);

	luaL_newmetatable(L, LuaPhotometerJob::luaType.c_str());
	lua_setmetatable(L, -2);

	return 1;
}

int nix_piecewise_linear_spectrum_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	int numArgs = lua_gettop(L);
	if (numArgs == 0) {
		// No arguments passed - default construct
		createSharedUserData<LuaPiecewiseLinearSpectrum, PiecewiseLinearSpectrum>(L);
	} else if (numArgs == 2) {
		// Construct with a name and the values in an array or arrays
		std::string name = luaL_checkstring(L, 1);
		luaL_checktype(L, 2, LUA_TTABLE);
		auto length = lua_rawlen(L, 2);
		if (length <= 1) {
			return luaL_argerror(L, 2, "Expected at least two data points"
				" for piecewise_linear_spectrum");
		}

		// Read in the lamba/value pairs
		std::vector<Scalar> lambdas(length);
		std::vector<Scalar> values(length);

		lua_pushnil(L); // first key
		unsigned curr = 0;
		while (lua_next(L, 2) != 0) {
			if (lua_istable(L, -1)) {
				auto datumLength = lua_rawlen(L, -1);
				if (datumLength != 2) {
					luaL_argerror(L, 2, "Incorrect number of elements in "
						"\"array\" containing lambda/value pair.");
				}

				// get the lambda
				lua_rawgeti(L, -1, 1);
				lambdas[curr] = luaL_checknumber(L, -1);
				lua_pop(L, 1);

				// get the value
				lua_rawgeti(L, -1, 2);
				values[curr++] = luaL_checknumber(L, -1);
				lua_pop(L, 1);

			} else {
				luaL_argerror(L, 2,
					"Expected an \"array\" containing lambda/value pair.");
			}
			lua_pop(L, 1);
		}

		// Construct the object and the user data
		createSharedUserData<LuaPiecewiseLinearSpectrum, PiecewiseLinearSpectrum>(
			L, name, lambdas, values);

	} else if (numArgs == 4) {
		// Construct with the range and data
		std::string name = luaL_checkstring(L, 1);
		Scalar low  = luaL_checknumber(L, 2);
		Scalar high = luaL_checknumber(L, 3);
		luaL_checktype(L, 4, LUA_TTABLE);
		auto length = lua_rawlen(L, 4);
		if (length <= 1) {
			return luaL_argerror(L, 4, "Expected at least two data points"
				" for piecewise_linear_spectrum");
		}
		std::vector<Scalar> values(length);
		for (unsigned i=1; i<=length; ++i) {
			lua_rawgeti(L, 4, i);
			values[i-1] = luaL_checknumber(L, -1);
			lua_pop(L, 1);
		}

		// Construct the object and the user data
		createSharedUserData<LuaPiecewiseLinearSpectrum, PiecewiseLinearSpectrum>(
			L, name, low, high, values);

	} else {
		// Incorrect number of arguments passed
		return luaL_argerror(L, numArgs, "Expected no arguments or 4 arguments"
			"passed to piecewise_linear_spectrum creation.");
	}

	luaL_newmetatable(L, LuaPiecewiseLinearSpectrum::luaType.c_str());
	lua_setmetatable(L, -2);

	return 1;
}

// SpectrophotometerCollectorSphere object construction
int nix_spectrophotometer_collector_sphere_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	// Parse arguments
	int numArgs = lua_gettop(L);
	if (numArgs == 0) {
		createUniqueUserData<LuaSpectrophotometerCollectorSphere,
							 SpectrophotometerCollectorSphere>(L);
	} else if (numArgs == 2) {
		// Two arguments passed
		luaL_checktype(L, 1, LUA_TBOOLEAN);
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool upper = lua_toboolean(L, 1);
		bool lower = lua_toboolean(L, 2);
		createUniqueUserData<LuaSpectrophotometerCollectorSphere,
				 			 SpectrophotometerCollectorSphere>(L, upper, lower);

	} else {
		// Incorrect number of arguments passed
		return luaL_argerror(L, numArgs, "Incorrect number of arguments "
			"passed to spectrophotometer_collector_sphere creation.");
	}

	luaL_newmetatable(L, LuaSpectrophotometerCollectorSphere::luaType.c_str());
	lua_setmetatable(L, -2);

	return 1;
}

// Extract an integer out of the Lua state at the specified stack index
static int getPositiveInt(lua_State * L, int i)
{
	if (!lua_isinteger(L, i)) {
		// luaL_argerror never really returns, it raises an error.
		// This use is merely idomatic.
		return luaL_argerror(L, i, "Expected integer.");
	}
	auto n = lua_tointeger(L, i);
	if (n<1) {
		return luaL_argerror(L, i, "Expected positive integer.");
	}
	return n;
}

// Extract an integer out of the Lua state at the specified stack index
static bool getBoolean(lua_State * L, int i)
{
	if (!lua_isboolean(L, i)) {
		// luaL_argerror never really returns, it raises an error.
		// This use is merely idomatic.
		return luaL_argerror(L, i, "Expected true or false.");
	}
	return lua_toboolean(L, i);
}

int nix_equal_solid_angles_collector_sphere_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	// Parse arguments
	int numArgs = lua_gettop(L);
	if (numArgs == 4) {
		auto stacks = getPositiveInt(L, 1);
		auto slices = getPositiveInt(L, 2);
		bool upper = getBoolean(L, 3);
		bool lower = getBoolean(L, 4);
		createUniqueUserData<LuaEqualSolidAnglesCollectorSphere,
							 EqualSolidAnglesCollectorSphere>(
			L, stacks, slices, upper, lower);
	} else {
		// Incorrect number of arguments passed
		return luaL_argerror(L, numArgs, "Incorrect number of arguments "
			"passed to equal_solid_angles_collector_sphere creation.");
	}

	luaL_newmetatable(L, LuaEqualSolidAnglesCollectorSphere::luaType.c_str());
	lua_setmetatable(L, -2);

	return 1;
}

int nix_collimated_beam_photometer_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	// Parse arguments
	int numArgs = lua_gettop(L);
	if (numArgs == 0) {
		// No arguments passed - default construct
		createUniqueUserData<LuaCollimatedBeamPhotometer, CollimatedBeamPhotometer>(L);
	} else {
		// Incorrect number of arguments passed
		return luaL_argerror(L, numArgs, "Incorrect number of arguments "
			"passed to collimated_beam_photometer creation.");
	}

	luaL_newmetatable(L, LuaCollimatedBeamPhotometer::luaType.c_str());
	lua_setmetatable(L, -2);

	return 1;
}

int nix_test1material_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	int numArgs = lua_gettop(L);
	if (numArgs == 0) {
		createUniqueUserData<LuaTest1Material, Test1Material>(L);
	} else {
		// Incorrect number of arguments passed
		return luaL_argerror(L, numArgs,
			"Incorrect number of arguments passed to test1material creation.");
	}

	luaL_newmetatable(L, LuaTest1Material::luaType.c_str());
	lua_setmetatable(L, -2);

	return 1;
}

int nix_diffuse_reflector_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	int numArgs = lua_gettop(L);
	if (numArgs == 0) {
		createUniqueUserData<LuaDiffuseReflector, DiffuseReflector>(L);
	} else {
		// Incorrect number of arguments passed
		return luaL_argerror(L, numArgs,
			"Incorrect number of arguments passed to test1material creation.");
	}

	luaL_newmetatable(L, LuaDiffuseReflector::luaType.c_str());
	lua_setmetatable(L, -2);

	return 1;
}

int nix_random_spheroid_particle_generator_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	// Check the number of arguments
	int numArgs = lua_gettop(L);
	if (numArgs != 5) {
		// Incorrect number of arguments passed
		return luaL_argerror(L, numArgs,
			"Incorrect number of arguments passed to "
			"random_spheroid_particle_generator creation.");
	}

	// Get the spheroid warping functions
	Array2 prolateWarp, oblateWarp;
	get2DWarpingArray(L, 1, prolateWarp);
	get2DWarpingArray(L, 2, oblateWarp);

	// Get the size warp function
	auto sizeWarp = getSelf<LuaPiecewiseLinearSpectrum, PiecewiseLinearSpectrum>(
		L, 3, LuaPiecewiseLinearSpectrum::luaType);
	auto sphericityWarp = getSelf<LuaPiecewiseLinearSpectrum, PiecewiseLinearSpectrum>(
		L, 4, LuaPiecewiseLinearSpectrum::luaType);

	// get the average particle distance (calculated in Lua)
	auto avgParticleDist = luaL_checknumber(L, 5);

	// Create the C++ object and the userdata
	createSharedUserData<LuaRandomSpheroidParticleGenerator,
		RandomSpheroidParticleGenerator>(L, prolateWarp, oblateWarp,
				sizeWarp, sphericityWarp, avgParticleDist);

	luaL_newmetatable(L, LuaRandomSpheroidParticleGenerator::luaType.c_str());
	lua_setmetatable(L, -2);

	return 1;
}

int nix_vacuum_medium_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	int numArgs = lua_gettop(L);
	if (numArgs == 0) {
		createSharedUserData<LuaVacuumMedium, VacuumMedium>(L);
	} else {
		return luaL_argerror(L, numArgs,
			"Incorrect number of arguments passed to vacuum_medium creation.");
	}

	luaL_newmetatable(L, LuaVacuumMedium::luaType.c_str());
	lua_setmetatable(L, -2);

	return 1;
}

} // namespace global
} // extern "C"
} // namespace lua
} // namespace nix

