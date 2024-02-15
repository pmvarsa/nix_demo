/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the PhotometerJob class.                             *
 ***************************************************************************/

#include "LuaPhotometerJob.h"

#include <CollimatedBeamPhotometer.h>
#include <LuaCollimatedBeamPhotometer.h>
#include <LuaDiffuseReflector.h>
#include <LuaTest1Material.h>
#include <SphericalCoordinates.h>

#include <vector>
#include <typeinfo>

namespace nix {
namespace lua {

// This array contains a nix_photometer.function_name to C++ implementation
// It must be null-terminated.
const luaL_Reg LuaPhotometerJob::methods[] = {
	{ "__gc", job::nix_photometer_job_gc_cmd },
	{ "dump", job::nix_photometer_job_dump },
	{ "set_verbose", job::nix_photometer_job_set_verbose_cmd },
	{ "set_n", job::nix_photometer_job_set_n_cmd },
	{ "set_output", job::nix_photometer_job_set_output_cmd },
	{ "set_incident_angles", job::nix_photometer_job_set_incident_angles_cmd },
	{ "set_wavelengths", job::nix_photometer_job_set_wavelengths_cmd },
	{ "set_device", job::nix_photometer_job_set_device_cmd },
	{ "set_material", job::nix_photometer_job_set_test1material_cmd },
	{ "set_diffuse_reflector_material", job::nix_photometer_job_set_diffuse_reflector_material_cmd },
	{ "run", job::nix_photometer_job_run_cmd },
	{ 0, 0 }
};

const std::string LuaPhotometerJob::luaType {"nix.photometer_job"};

static auto getContainer(lua_State * L)
{
	return getLuaContainer<LuaPhotometerJob>(L, LuaPhotometerJob::luaType);
}

static PhotometerJob & getSelf(lua_State * L)
{
	// Get an underlying object reference, without giving up ownership
	auto pCont = getContainer(L);
	return *(pCont->self.get());
}

void LuaPhotometerJob::setupMetatable(lua_State * L) noexcept
{
	NIX_LUA_DEBUG("Setting up PhotometerJob.");

	luaL_newmetatable(L, LuaPhotometerJob::luaType.c_str());
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);

	// Load the functions of nix.photometerjob
	luaL_setfuncs(L, LuaPhotometerJob::methods, 0);
}

namespace job {
extern "C" {

// Garbage collector function for Lua
int nix_photometer_job_gc_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	auto pData = getContainer(L);
	delete pData;

	return 0;
};

// dump data to stdout for debugging
int nix_photometer_job_dump(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	// @TODO (8x) I'm not sure why auto doesn't work here, perhaps it's a g++ bug?
	PhotometerJob & self = getSelf(L);

	using namespace std;
	cout << "PhotometerJob:" << endl << boolalpha
		 << "    Running:    " << self.running() << endl
		 << "    Verbose:    " << self.verbose() << endl
		 << "    N:          " << self.n() << endl
		 << "    File:       " << self.fileName() << endl
		 << "    # Incident: " << self.incidentAngles().size() << endl
		 << "    # Lambda:   " << self.wavelengths().size() << endl
		 << "    Material:   " << self.material().name() << endl
		 << "    Photometer: " << self.photometer().type() << endl
		 << self.photometer() << endl
	;

/*
	cout << endl << "Incident Angles" << endl;
	for(const SphericalCoordinates & coord : self.incidentAngles()) {
		cout << "("  << coord.polar()
			 << ", " << coord.azimuthal()
			 << ", " << coord.radius() << ")" << endl;
	}
	cout << endl << "Wavelengths to measure" << endl;
	for(Scalar lambda : self.wavelengths()) {
		cout << lambda << endl;
	}
*/
	return 0;
}

// set verbosity
int nix_photometer_job_set_verbose_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	PhotometerJob & self = getSelf(L);
	auto numArgs = lua_gettop(L);
	if (numArgs != 2) {
		return luaL_argerror(L, numArgs, "Only one argument should be passed"
			" to set_verbose.");
	}

	// Get the argument
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool is_verbose = lua_toboolean(L, 2);
	self.setVerbose(is_verbose);

	return 0;
}

// set the number of rays to cast per measurement
int nix_photometer_job_set_n_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	PhotometerJob & self = getSelf(L);
	auto numArgs = lua_gettop(L);
	if (numArgs != 2) {
		return luaL_argerror(L, numArgs, "Only one argument should be passed"
			" to set_n.");
	}

	// Get the argument
	if (!lua_isinteger(L, 2)) {
		return luaL_argerror(L, 2, "Expected integer.");
	}
	auto n = lua_tointeger(L, 2);
	self.setN(n);

	return 0;
}

// set the output file name
int nix_photometer_job_set_output_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	PhotometerJob & self = getSelf(L);
	auto numArgs = lua_gettop(L);
	if (numArgs != 2) {
		return luaL_argerror(L, numArgs, "Only one argument should be passed"
			" to set_output.");
	}

	if (!lua_isstring(L, 2)) {
		return luaL_argerror(L, 2, "Expected string.");
	}
	auto fname = lua_tostring(L, 2);
	self.setOutput(fname);

	return 0;
}

// A Lua array of tables represent the angles.
int nix_photometer_job_set_incident_angles_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	PhotometerJob & self = getSelf(L);
	auto numArgs = lua_gettop(L);
	if (numArgs != 2) {
		return luaL_argerror(L, numArgs, "Only one argument should be passed"
			" to set_incident_angles.");
	}

	if (!lua_istable(L, 2)) {
		return luaL_argerror(L, 2, "Expected table.");
	}

	// Get the key/value pairs
	// example taken from http://www.lua.org/manual/5.1/manual.html#lua_next
	std::vector<SphericalCoordinates> incident_angles;
	lua_pushnil(L); // first key
	while (lua_next(L, 2) != 0) {
		if (lua_istable(L, -1)) {
			lua_pushnil(L); // first key
			Scalar polar;
			Scalar azimuthal;
			bool foundPolar{false}, foundAzimuth{false};
			while (lua_next(L, -2) != 0) {
				// uses 'key' (at index -2) and 'value' (at index -1)
				if (lua_isstring(L, -2) and lua_isnumber(L, -1)) {
					std::string key{lua_tostring(L, -2)};
					if (key == "polar") {
						polar = lua_tonumber(L, -1);
						foundPolar = true;
					} else if (key == "azimuth") {
						azimuthal = lua_tonumber(L, -1);
						foundAzimuth = true;
					} else {
						return luaL_argerror(L, 2, "Expected polar/azimuth angles.");
					}
				} else {
					return luaL_argerror(L, 2,
						"incident angles should be specified as key/value pairs.");
				}
				lua_pop(L, 1);
			}
			if (foundPolar and foundAzimuth) {
				incident_angles.emplace_back(polar, azimuthal);
			} else {
				return luaL_argerror(L, 2, "Expected both polar/azimuth angles.");
			}
		} else {
			luaL_argerror(L, 2, "Expected a table with keys polar and azimuth.");
		}
		lua_pop(L, 1);
	}
	self.setIncidentAngles(incident_angles);

	return 0;
}

int nix_photometer_job_set_wavelengths_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	PhotometerJob & self = getSelf(L);

	// Check that there is one tble argument
	auto numArgs = lua_gettop(L);
	if (numArgs != 2) {
		return luaL_argerror(L, numArgs, "Only one argument should be passed"
			" to set_wavelengths.");
	}
	if (!lua_istable(L, 2)) {
		return luaL_argerror(L, 2, "Expected table.");
	}

	// Extract the wavelengths
	auto num_wavelengths = lua_rawlen(L, 2);
	std::vector<Scalar> wavelengths(num_wavelengths);
	lua_pushnil(L); // first key
	while (lua_next(L, 2) != 0) {
		if (lua_isnumber(L, -2) and lua_isnumber(L, -1)) {
			auto index  = lua_tointeger(L, -2) - 1; // Lua is 1-indexed
			auto lambda = lua_tonumber(L, -1);
			wavelengths.at(index) = lambda;
		} else {
			return luaL_argerror(L, 2,
				"Wavelengths should be specified in a Lua array.");
		}
		lua_pop(L, 1);
	}

	self.setWavelengths(wavelengths);
	return 0;
}

int nix_photometer_job_set_device_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	// Check that there is one tble argument
	auto numArgs = lua_gettop(L);
	if (numArgs != 2) {
		return luaL_argerror(L, numArgs,
		"Exactly one argument should be passed to set_device.");
	}

	// Get the argument
	auto pDeviceCont = getLuaContainer<LuaCollimatedBeamPhotometer>(
		L, 2, LuaCollimatedBeamPhotometer::luaType);
	PhotometerJob & self = getSelf(L);
	self.setPhotometer(std::move(pDeviceCont->self));

	return 0;
}

int nix_photometer_job_set_test1material_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	PhotometerJob & self = getSelf(L);

	// Check for exactly 1 argument
	if (lua_gettop(L) != 2) {
		return luaL_argerror(L, 2,
			"Only one argument should be passed to set_material.");
	}

	// Get the Test1Material argument
	auto pMatCont = getLuaContainer<LuaTest1Material>(L, 2, LuaTest1Material::luaType);
	self.setMaterial(std::move(pMatCont->self));

	return 0;
}

int nix_photometer_job_set_diffuse_reflector_material_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	PhotometerJob & self = getSelf(L);

	// Check for exactly 1 argument
	if (lua_gettop(L) != 2) {
		return luaL_argerror(L, 2,
			"Only one argument should be passed to set_diffuse_reflector.");
	}

	// Get the DiffuseReflector argument
	auto pMatCont = getLuaContainer<LuaDiffuseReflector>(L, 2, LuaDiffuseReflector::luaType);
	self.setMaterial(std::move(pMatCont->self));

	return 0;
}

int nix_photometer_job_run_cmd(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	PhotometerJob & self = getSelf(L);

	if (lua_gettop(L) != 1) {
		return luaL_argerror(L, 1, "No arguements should be passed to run().");
	}

	self.Run();

	return 0;
}

} // extern "C"
} // namespace job
} // namespace lua
} // namespace nix

