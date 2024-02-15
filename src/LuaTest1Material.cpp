/***************************************************************************
 *   Copyright (C) Natrual Phenomena Simulation Group                      *
 *   University of Waterloo, Waterloo, Canada                              *
 *   Lua bindings for the Test1Material class.                             *
 ***************************************************************************/

#include "LuaTest1Material.h"

#include "LuaPiecewiseLinearSpectrum.h"
#include "LuaRandomSpheroidParticleGenerator.h"
#include "LuaVacuumMedium.h"

#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

// Used locally only
#define ORGANIC 0
#define INORGANIC 1

namespace nix {
namespace lua {

// This array contains a nix.test1material.function_name to C++ implementation
// It must be null-terminated.
const luaL_Reg LuaTest1Material::methods[] = {
	{ "dump", material::nix_test1material_dump },
	{ "set_depth", material::nix_test1material_set_depth },
	{ "set_media", material::nix_test1material_set_media },
	{ "set_mirror", material::nix_test1material_set_mirror },
	{ "set_particles", material::nix_test1material_set_particles },
	{ "__gc", material::nix_test1material_gc },
	{ 0, 0 }
};

const std::string LuaTest1Material::luaType {"nix.test1material"};

void LuaTest1Material::setupMetatable(lua_State * L) noexcept
{
	NIX_LUA_DEBUG("Setting up Test1Material.");
	luaL_newmetatable(L, LuaTest1Material::luaType.c_str());
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_setfuncs(L, LuaTest1Material::methods, 0);
}

static LuaTest1Material * getLuaContainer(lua_State * L)
{
	return getLuaContainer<LuaTest1Material>(L, LuaTest1Material::luaType);
}

// Helper function to get a reference to self
static Test1Material & getSelf(lua_State * L)
{
	auto pCont = getLuaContainer(L);
	return *(pCont->self.get());
}

namespace material {
extern "C" {

int nix_test1material_dump(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	// @TODO I'm not sure why auto doesn't work here.
	Test1Material & self = getSelf(L);

	using namespace std;
	cout << "Test1Material:" << endl << boolalpha
		 << "    Depth:          " << self.getDepth() << endl
		 << "    # Media:        " << self.mediaTypes().size() << endl;
	for (auto medium : self.mediaTypes()) {
		cout << setw(15) << medium.name
			 << fixed << setprecision(1)
			 << ", " << setw(5) << 100. * medium.weight << "%" << endl;
	}
	cout << "    Fresnel Mirror: " << self.isMirrorInterface() << endl;
	cout << "    # Particles: " << self.particles().size() << endl;
	for (auto particle : self.particles()) {
		cout << "       name:              " << particle.name << endl
			 << setprecision(3)
			 << "       Roundness Mean:    " << particle.roundness_mean << endl
			 << "       Roundness Std Dev: " << particle.roundness_var << endl
			 << "       Roundness Range:   " << particle.roundness_range << endl
			 << "       Concentration:     " << particle.concentration << endl
			 << setprecision(11)
			 << "       Mean Distance:     " << particle.meanDistance << endl;
	}
	return 0;
}

int nix_test1material_set_depth(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	Test1Material & self = getSelf(L);
	auto numArgs = lua_gettop(L);
	if (numArgs != 2) {
		return luaL_argerror(L, numArgs,
			"Only on argument should be passed to set_depth.");
	}

	// Get the argument
	luaL_checktype(L, 2, LUA_TNUMBER);
	Scalar depth = lua_tonumber(L, 2);
	self.setDepth(depth);

	return 0;
}

int nix_test1material_set_media(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	Test1Material & self = getSelf(L);
	auto numArgs = lua_gettop(L);
	if (numArgs != 2) {
		return luaL_argerror(L, numArgs,
			"Only one argument should be passed to set_media.");
	}

	// Get the array of media
	std::vector<Test1Material::MediumDef> media_types;
	lua_pushnil(L); // first key
	while (lua_next(L, 2) != 0) {
		if (lua_istable(L, -1)) {

			lua_pushnil(L); // first key
			std::string mediumName;
			Scalar weight;
			std::shared_ptr<const PiecewiseLinearSpectrum> n, k, alpha;
			bool foundName{false}, foundWeight{false}, foundN{false},
				 foundK{false}, foundAlpha{false};

			while (lua_next(L, -2) != 0) {
				// uses 'key' (at index -2) and 'value' (at index -1)
				//
				// Lua seems to be happy to return true for lua_isstring, even
				// if a number is passed into the argument, so the order of the
				// if and elseif appear to be quite important.

				if (lua_isstring(L, -2)) {
					std::string key = lua_tostring(L, -2);

					if (lua_isnumber(L, -1)) {
						if (key == "weight") {
							weight = lua_tonumber(L, -1);
							foundWeight = true;
						} else {
							return luaL_argerror(
								L, 2, "Expected weight = number_value.");
						}
					} else if (lua_isstring(L, -1)) {
						if (key == "name") {
							mediumName = lua_tostring(L, -1);
							foundName = true;
						} else {
							return luaL_argerror(
								L, 2, "Expected medium = 'name'.");
						}
					} else {
						if (key != "n" and key != "k" and key != "alpha") {
							return luaL_argerror(L, 2,
								"Invalid key for piecewise_linear_spectrum.");
						}
						auto pSpectrum =
							getSelf<LuaPiecewiseLinearSpectrum,
									PiecewiseLinearSpectrum>(
								L, -1, LuaPiecewiseLinearSpectrum::luaType);
						if (key == "n") {
							foundN = true;
							n = pSpectrum;
						} else if (key == "k") {
							foundK = true;
							k = pSpectrum;
						} else if (key == "alpha") {
							foundAlpha = true;
							alpha = pSpectrum;
						}
					}
				}
				lua_pop(L, 1);
			}
			if (foundName and foundWeight and foundN and foundK and foundAlpha) {
				media_types.emplace_back(mediumName, weight, n, k, alpha);
			} else if (foundName and foundWeight and foundN and foundK) {
				media_types.emplace_back(mediumName, weight, n, k);
			} else if(mediumName == "vacuum" and foundWeight) {
				// Vacuum is a special case
				media_types.emplace_back(weight);
			} else {
				return luaL_argerror(
					L, 2, "Expected all of name, weight, n, & k keys.");
			}
		} else {
			luaL_argerror(
				L, 2, "Expected a table with weight and material keys.");
		}
		lua_pop(L, 1);
	}
	try {
		self.setMediaTypes(media_types);
	} catch(std::runtime_error & e) {
		std::string error = std::string("Error with media types: ") + e.what();
		luaL_argerror(L, 2, error.c_str());
	}

	return 0;
}

int nix_test1material_set_mirror(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	Test1Material & self = getSelf(L);
	auto numArgs = lua_gettop(L);
	if (numArgs != 2) {
		return luaL_argerror(L, numArgs,
			"Only one argument should be passed to set_mirror.");
	}

	// Get the boolean argument
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool state = lua_toboolean(L, 2);
	self.setMirrorInterface(state);

	return 0;
}

static
std::map<std::string, bool> initializeMap() 
{
	std::map<std::string, bool> m;
	m["name"] = false;
	m["roundness_mean"] = false;
	m["roundness_stdev"] = false;
	m["roundness_range"] = false;
	m["generator"] = false;
	m["cloudiness"] = false;
	m["coating"] = true;		// NB: Specifying a coating is optional
	m["n"] = false;
	m["k"] = false;
	m["concentration"] = false;

	return m;
}

// hard-coded helper function
static
void getLuaNumber(lua_State * L, Scalar & num, const std::string & property,
				  std::map<std::string, bool> & found)
{
	if (lua_isnumber(L, -1)) {
		num = lua_tonumber(L, -1);
		found[property] = true;
	} else {
		using std::string;
		string err = "Particle " + property + " should be a number.";
		throw std::runtime_error(err);
	}
}

int nix_test1material_set_particles(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	Test1Material & self = getSelf(L);
	auto numArgs = lua_gettop(L);
	if (numArgs != 2) {
		return luaL_argerror(L, numArgs,
			"Only one argument should be passed to set_particles.");
	}

	// Iterator over the array of particles
	std::vector<Test1Material::ParticleDef> particles;
	lua_pushnil(L);	// first key
	while (lua_next(L, 2) != 0) {
		if (!lua_istable(L, -1)) {
			luaL_argerror(L, 2, "Expected a table that defines a particle.");
		}

		Test1Material::ParticleDef core;
		auto found = initializeMap();

		lua_pushnil(L);	// dummy first key
		while (lua_next(L, -2) != 0) {
			// uses 'key' (at index -2) and 'value' (at index -1)
			if (!lua_isstring(L, -2)) {
				luaL_argerror(
					L, 2, "Expected a string key in particle definition.");
			}
			std::string key = lua_tostring(L, -2);
			try {
				if (key == "name") {
					found["name"] = true;
					core.name = lua_tostring(L, -1);
				} else if (key == "roundness_mean") {
					getLuaNumber(
						L, core.roundness_mean, "roundness_mean", found);
				} else if (key == "roundness_stdev") {
					getLuaNumber(
						L, core.roundness_var, "roundness_stdev", found);
				} else if (key == "roundness_range") {
					// check for errors
					luaL_checktype(L, -1, LUA_TTABLE);
					luaL_argcheck(L, lua_rawlen(L, -1) == 2, -1,
						"Two numbers expected for range");

					// Get the low value
					lua_rawgeti(L, -1, 1);
					auto low = luaL_checknumber(L, -1);
					lua_pop(L, 1);

					// Get the high value
					lua_rawgeti(L, -1, 2);
					auto high = luaL_checknumber(L, -1);
					lua_pop(L, 1);

					// Set the value
					core.roundness_range.Set(low, high);
					found["roundness_range"] = true;
				} else if (key == "generator") {
					auto generator = getSelf<LuaRandomSpheroidParticleGenerator,
											 RandomSpheroidParticleGenerator>(
						L, -1, "nix.random_spheroid_particle_generator");
					core.generator = generator;
					found["generator"] = true;
				} else if (key == "n") {
					auto n = getSelf<LuaPiecewiseLinearSpectrum,
									 PiecewiseLinearSpectrum>(
						L, -1, "nix.piecewise_linear_spectrum");
					core.n = n;
					found["n"] = true;
				} else if (key == "k") {
					auto k = getSelf<LuaPiecewiseLinearSpectrum,
									 PiecewiseLinearSpectrum>(
						L, -1, "nix.piecewise_linear_spectrum");
					core.k = k;
					found["k"] = true;
				} else if (key == "concentration") {
					getLuaNumber(L, core.concentration, "concentration", found);
				} else {
					std::string err = std::string("Unexpected key ") + key +
						std::string(" found parsing particle.");
					return luaL_argerror(L, 2, err.c_str());
				}
			} catch (std::runtime_error & e) {
				return luaL_argerror(L, 2, e.what());
			}
			lua_pop(L, 1);
		}

		// Verify that all required properties were found
		for (auto pair : found) {
			if (!pair.second) {
				std::string err = "Missing particle property " + pair.first;
				luaL_argerror(L, 2, err.c_str());
			}
		}

		// SPLITS calculation (now done in Lua)
		//core.meanDistance = 1.0 / (extinction * core.concentration);
		core.meanDistance = core.generator->averageParticleDistance();

		particles.push_back(core);
		lua_pop(L, 1);
	}
	self.setParticles(particles);

	return 0;
}

int nix_test1material_set_lower_reflector(lua_State * L)
{
	NIX_LUA_DEBUG_CALL;

	Test1Material & self = getSelf(L);
	auto numArgs = lua_gettop(L);
	if (numArgs != 1) {
		return luaL_argerror(L, numArgs,
			"Exactly zero arguments should be passed to set_lower_reflector.");
	}

	self.setLowerReflector();

	return 0;
}

int nix_test1material_gc(lua_State * L)
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

